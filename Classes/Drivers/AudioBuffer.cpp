
# include "Core.h"
# include "AudioBuffer.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

NNTDECL_PRIVATE_BEGIN_CXX(Buffer)

void init()
{
# ifdef NNT_MACH
    
    d_owner->need_release = true;
    buffers.resize(3, NULL);
    
# endif
}

void dealloc()
{
# ifdef NNT_MACH
    
    if (d_owner->need_release)
    {
        for (core::vector<AudioQueueBufferRef>::iterator each = buffers.begin();
             each != buffers.end();
             ++each)
        {
            AudioQueueFreeBuffer(d_owner->queue, *each);
        }
    }
    
# endif
}

# ifdef NNT_MACH

static OSStatus HandlerRead(void *		inClientData,
                            SInt64		inPosition,
                            UInt32	requestCount,
                            void *		buffer,
                            UInt32 *	actualCount)
{
    use<Buffer> buf = inClientData;
    if (requestCount > (buf->data.length() - inPosition))
        *actualCount = (buf->data.length() - inPosition);
    else
        *actualCount = requestCount;
    memcpy(buffer, buf->data.bytes() + inPosition, *actualCount);
    return 0;
}

static OSStatus HandlerWrite(void * 		inClientData,
                             SInt64		inPosition,
                             UInt32		requestCount,
                             const void *buffer,
                             UInt32    * actualCount)
{
    use<Buffer> buf = inClientData;
    
    // write.
    if (inPosition == buf->data.length())
    {
        buf->data.append((void*)buffer, requestCount);
    }
    else
    {
        buf->data.copy((void*)buffer, requestCount, inPosition);
    }
    
    *actualCount = requestCount;
    
    return 0;
}

static SInt64 HandlerGetSize(void * 		inClientData)
{
    use<Buffer> buf = inClientData;
    return buf->data.length();
}

static OSStatus HandlerSetSize(void *		inClientData,
                               SInt64		inSize)
{
    use<Buffer> buf = inClientData;
    core::data da = buf->data;
    buf->data.resize(inSize);
    buf->data.fill(0);
    buf->data.copy(da);
    return 0;
}

static void HandlerPropertyListener(
                                    void *						inClientData,
                                    AudioFileStreamID			inAudioFileStream,
                                    AudioFileStreamPropertyID	inPropertyID,
                                    UInt32 *					ioFlags)
{
    trace_msg("audio buffer property callback");
}

static void HandlerPackets(
                           void *							inClientData,
                           UInt32							inNumberBytes,
                           UInt32							inNumberPackets,
                           const void *					inInputData,
                           AudioStreamPacketDescription	*inPacketDescriptions)
{
    trace_msg("audio buffer packets callback");
}

usize calc_buffer_size() const
{
    int packets, frames, bytes;
	
	frames = (int)ceil(d_owner->seconds * d_owner->format.mSampleRate);
	
	if (d_owner->format.mBytesPerFrame > 0)
    {
		bytes = frames * d_owner->format.mBytesPerFrame;
	}
    else
    {
		UInt32 maxPacketSize;
		if (d_owner->format.mBytesPerPacket > 0)
        {
			maxPacketSize = d_owner->format.mBytesPerPacket;	// constant packet size
		}
        else
        {
			UInt32 propertySize = sizeof(maxPacketSize);
            if (AudioQueueGetProperty(d_owner->queue,
                                      kAudioConverterPropertyMaximumOutputPacketSize,
                                      &maxPacketSize,
                                      &propertySize))
                return 0;
		}
		if (d_owner->format.mFramesPerPacket > 0)
			packets = frames / d_owner->format.mFramesPerPacket;
		else
			packets = frames;	// worst-case scenario: 1 frame in a packet
		if (packets == 0)		// sanity check
			packets = 1;
		bytes = packets * maxPacketSize;
	}
    
	return bytes;
}

void set_stream()
{
    OSStatus err;
	UInt32 propertySize;
	
	// get the magic cookie, if any, from the converter
	err = AudioQueueGetPropertySize(d_owner->queue,
                                    kAudioConverterCompressionMagicCookie,
                                    &propertySize);
	
	if (err == noErr && propertySize > 0) {
		// there is valid cookie data to be fetched;  get it
		Byte *magicCookie = (Byte *)malloc(propertySize);
        err = AudioQueueGetProperty(d_owner->queue,
                                    kAudioConverterCompressionMagicCookie,
                                    magicCookie,
                                    &propertySize);
        if (err == 0)
        {
            // now set the magic cookie on the output file
            // even though some formats have cookies, some files don't take them, so we ignore the error
            /*err =*/
            AudioFileSetProperty(d_owner->stm, kAudioFilePropertyMagicCookieData, propertySize, magicCookie);
        }
		free(magicCookie);
	}
    
    /*
    if (err != 0)
        trace_fmt("failed to set stream, %.4s", &err);
     */
}

core::vector<AudioQueueBufferRef> buffers;

# endif

NNTDECL_PRIVATE_END_CXX

Buffer::Buffer()
{
    NNTDECL_PRIVATE_CONSTRUCT(Buffer);
    
# ifdef NNT_MACH
    
    queue = NULL;
    stm = NULL;
    type = 0;
    used = false;
    packets = 0;
    
# endif
    
    seconds = 0.5f;
}

Buffer::~Buffer()
{
    close();
    
    NNTDECL_PRIVATE_DESTROY();
}

NNTDECL_SIGNALS_BEGIN(Buffer, Object)
NNT_SIGNAL(kSignalBytesAvailable)
NNTDECL_SIGNALS_END

bool Buffer::open()
{
    close();
    
# ifdef NNT_MACH

    OSStatus sta = AudioFileInitializeWithCallbacks(this,
                                                    private_type::HandlerRead,
                                                    private_type::HandlerWrite,
                                                    private_type::HandlerGetSize,
                                                    private_type::HandlerSetSize,
                                                    type,
                                                    &format,
                                                    0,
                                                    &stm);
        
    if (sta != 0)
    {
        trace_fmt("failed to open buffer, %.4s", (char*)&sta);
        return false;
    }
    
    d_ptr->set_stream();    
    
    // alloc.
    usize sz = d_ptr->calc_buffer_size();
    if (sz == 0)
    {
        trace_fmt("failed to calc buffer size, %.4s", (char*)&sta);
        return false;
    }
    
    for (core::vector<AudioQueueBufferRef>::iterator each = d_ptr->buffers.begin();
         each != d_ptr->buffers.end();
         ++each)
    {
        if ((sta = AudioQueueAllocateBuffer(queue, sz, &*each)))
        {
            trace_fmt("failed to allocate audio buffer, %.4s", (char*)&sta);
            return false;
        }
    }
    
    return true;
    
# endif
    
    return false;
}

void Buffer::close()
{
# ifdef NNT_MACH
    
    if (stm)
    {
        AudioFileClose(stm);
        stm = NULL;
    }
    
    if (need_release && queue)
    {
        for (core::vector<AudioQueueBufferRef>::iterator each = d_ptr->buffers.begin();
             each != d_ptr->buffers.end();
             ++each)
        {
            if (*each != NULL)
            {
                AudioQueueFreeBuffer(queue, *each);
                *each = NULL;
            }
        }
    }
    
# endif
}

# ifdef NNT_MACH

core::vector<AudioQueueBufferRef>& Buffer::handle()
{
    return d_ptr->buffers;
}

# endif

NNT_END_NS
NNT_END_CXX
