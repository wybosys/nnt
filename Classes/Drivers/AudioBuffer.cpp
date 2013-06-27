
# include "Core.h"
# include "AudioBuffer.h"
# include "../Core/File+NNT.h"

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

usize calc_buffer_size() const
{
    int packets, frames, bytes;
	
	frames = (int)ceil(d_owner->seconds * d_owner->format->mSampleRate);
	
	if (d_owner->format->mBytesPerFrame > 0)
    {
		bytes = frames * d_owner->format->mBytesPerFrame;
	}
    else
    {
		UInt32 maxPacketSize;
		if (d_owner->format->mBytesPerPacket > 0)
        {
			maxPacketSize = d_owner->format->mBytesPerPacket;	// constant packet size
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
		if (d_owner->format->mFramesPerPacket > 0)
			packets = frames / d_owner->format->mFramesPerPacket;
		else
			packets = frames;	// worst-case scenario: 1 frame in a packet
		if (packets == 0)		// sanity check
			packets = 1;
		bytes = packets * maxPacketSize;
	}
    
	return bytes;
}

core::vector<AudioQueueBufferRef> buffers;

void clear_buffers()
{
    if (d_owner->need_release && d_owner->queue)
    {
        for (core::vector<AudioQueueBufferRef>::iterator each = buffers.begin();
             each != buffers.end();
             ++each)
        {
            if (*each != NULL)
            {
                AudioQueueFreeBuffer(d_owner->queue, *each);
                *each = NULL;
            }
        }
    }   
}

void create_buffers()
{
    clear_buffers();
    
    usize sz = calc_buffer_size();
    
    OSStatus sta;
    for (core::vector<AudioQueueBufferRef>::iterator each = buffers.begin();
         each != buffers.end();
         ++each)
    {
        if ((sta = AudioQueueAllocateBuffer(d_owner->queue, sz, &*each)))
        {
            trace_fmt("failed to allocate audio buffer, %.4s", (char*)&sta);
        }
    }
}

# endif

NNTDECL_PRIVATE_END_CXX

Buffer::Buffer()
{
    NNTDECL_PRIVATE_CONSTRUCT(Buffer);
    
# ifdef NNT_MACH
    
    queue = NULL;
    stm = NULL;
    used = false;
    
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

void Buffer::close()
{
# ifdef NNT_MACH
    
    if (stm)
    {
        AudioFileClose(stm);
        stm = NULL;
    }
    
    d_ptr->clear_buffers();
    
    packets = 0;
    
# endif
}

# ifdef NNT_MACH

core::vector<AudioQueueBufferRef>& Buffer::handle()
{
    return d_ptr->buffers;
}

# endif

/////// RECORD BUFFER

NNTDECL_PRIVATE_BEGIN_CXX(RecordBuffer)

void init()
{
    
}

void dealloc()
{
    
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
    *actualCount = requestCount;
    
    // write.
    if (inPosition == buf->data.length())
    {
        buf->data.append((void*)buffer, requestCount);
    }
    else if (inPosition > buf->data.length())
    {
        core::data da = buf->data;
        buf->data.resize(inPosition);
        buf->data.fill(0);
        buf->data.copy(da);
        buf->data.append((void*)buffer, requestCount);
    }
    else
    {
        buf->data.copy((void*)buffer, requestCount, inPosition);
    }
    
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

# endif

NNTDECL_PRIVATE_END_CXX

RecordBuffer::RecordBuffer()
{
    NNTDECL_PRIVATE_CONSTRUCT(RecordBuffer);
}

RecordBuffer::~RecordBuffer()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool RecordBuffer::open()
{
    close();
    
# ifdef NNT_MACH
    
    OSStatus sta = AudioFileInitializeWithCallbacks(this,
                                                    private_type::HandlerRead,
                                                    private_type::HandlerWrite,
                                                    private_type::HandlerGetSize,
                                                    private_type::HandlerSetSize,
                                                    type,
                                                    format,
                                                    0,
                                                    &stm);
    
    if (sta != 0)
    {
        trace_fmt("failed to open buffer, %.4s", (char*)&sta);
        return false;
    }
    
    d_ptr->set_stream();
    
    // alloc.
    usize sz = Buffer::_d()->calc_buffer_size();
    if (sz == 0)
    {
        trace_fmt("failed to calc buffer size, %.4s", (char*)&sta);
        return false;
    }
    
    Buffer::_d()->create_buffers();
    
    return true;
    
# endif
    
    return false;
}

///////// PLAY BUFFER

NNTDECL_PRIVATE_BEGIN_CXX(PlayBuffer)

void init()
{
# ifdef NNT_MACH
    
    length = 0;
    
# endif
}

void dealloc()
{
    
}

# ifdef NNT_MACH

static OSStatus HandlerRead(void *		inClientData,
                            SInt64		inPosition,
                            UInt32	requestCount,
                            void *		buffer,
                            UInt32 *	actualCount)
{
    use<PlayBuffer> buf = inClientData;
    core::IoStream* stream = buf->stream;
    
    core::data da(requestCount);
    stream->seek(inPosition, Io::seek_set);
    *actualCount = stream->read(da);
    memcpy(buffer, da.bytes(), *actualCount);
    
    return 0;
}

static OSStatus HandlerWrite(void * 		inClientData,
                             SInt64		inPosition,
                             UInt32		requestCount,
                             const void *buffer,
                             UInt32    * actualCount)
{
    trace_msg("play buffer request write");
    return 0;
}

static SInt64 HandlerGetSize(void * 		inClientData)
{
    use<PlayBuffer> buf = inClientData;
    core::IoStream* stream = buf->stream;
    return stream->length();
}

static OSStatus HandlerSetSize(void *		inClientData,
                               SInt64		inSize)
{
    trace_msg("play buffer set size");
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

bool update_info()
{
    AudioStreamBasicDescription& fmt = d_owner->format;
    
    UInt32 size = sizeof(fmt);
    
    OSStatus sta;
    sta = AudioFileGetProperty(d_owner->stm,
                               kAudioFilePropertyDataFormat,
                               &size,
                               &fmt);
    
    if (sta != 0)
        return false;
    
    UInt64 count;
    size = sizeof(count);
    sta = AudioFileGetProperty(d_owner->stm,
                               kAudioFilePropertyAudioDataByteCount,
                               &size,
                               &count);
    length = count;
    
    return true;
}

usize length;

# endif

NNTDECL_PRIVATE_END_CXX

PlayBuffer::PlayBuffer()
: stream(NULL)
{
    NNTDECL_PRIVATE_CONSTRUCT(PlayBuffer);
}

PlayBuffer::~PlayBuffer()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool PlayBuffer::open()
{
    close();
    
# ifdef NNT_MACH
    
    OSStatus sta = AudioFileOpenWithCallbacks(this,
                                              private_type::HandlerRead,
                                              private_type::HandlerWrite,
                                              private_type::HandlerGetSize,
                                              private_type::HandlerSetSize,
                                              type,
                                              &stm);
    
    if (sta != 0)
    {
        trace_fmt("failed to open buffer, %.4s", (char*)&sta);
        return false;
    }
    
    return d_ptr->update_info();
    
# endif
    
    return false;
}

bool PlayBuffer::read(core::data &da, uint offset)
{
# ifdef NNT_MACH
    
    UInt32 readed = da.length();
    OSStatus sta = AudioFileReadBytes(stm,
                                      YES,
                                      offset,
                                      &readed,
                                      da.bytes());
    
    if (sta == 0)
    {
        da.set_length(readed);
        return true;
    }
    
# endif
    
    return false;
}

usize PlayBuffer::length() const
{
    return d_ptr->length;
}

NNT_END_NS
NNT_END_CXX
