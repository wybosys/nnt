
# include "Core.h"
# include "AudioBuffer.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

NNTDECL_PRIVATE_BEGIN_CXX(Buffer)

void init()
{
# ifdef NNT_MACH
    
    buffers.resize(3, NULL);
    
# endif
}

void dealloc()
{
# ifdef NNT_MACH
    
    for (core::vector<AudioQueueBufferRef>::iterator each = buffers.begin();
         each != buffers.end();
         ++each)
    {
        AudioQueueFreeBuffer(d_owner->queue, *each);
    }
    
# endif
}

# ifdef NNT_MACH

static void HandlerPropertyListenerProc(
                                        void *						inClientData,
                                        AudioFileStreamID			inAudioFileStream,
                                        AudioFileStreamPropertyID	inPropertyID,
                                        UInt32 *					ioFlags)
{
    
}

static void HandlerPacketsProc(
                               void *							inClientData,
                               UInt32							inNumberBytes,
                               UInt32							inNumberPackets,
                               const void *					inInputData,
                               AudioStreamPacketDescription	*inPacketDescriptions)
{
    
}

usize calc_buffer_size() const
{
    int packets, frames, bytes;
	
	frames = (int)ceil(d_owner->seconds * d_owner->format.mSampleRate);
	
	if (d_owner->format.mBytesPerFrame > 0)
		bytes = frames * d_owner->format.mBytesPerFrame;
	else {
		UInt32 maxPacketSize;
		if (d_owner->format.mBytesPerPacket > 0)
			maxPacketSize = d_owner->format.mBytesPerPacket;	// constant packet size
		else {
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
    
    OSStatus sta = AudioFileStreamOpen(this,
                                       private_type::HandlerPropertyListenerProc,
                                       private_type::HandlerPacketsProc,
                                       type,
                                       &stm);
    
    if (sta != 0)
        return false;
    
    // alloc.
    usize sz = d_ptr->calc_buffer_size();
    if (sz == 0)
        return false;
    
    for (core::vector<AudioQueueBufferRef>::iterator each = d_ptr->buffers.begin();
         each != d_ptr->buffers.end();
         ++each)
    {
        if (AudioQueueAllocateBuffer(queue, sz, &*each))
        {
            trace_msg("failed to allocate audio buffer");
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
        AudioFileStreamClose(stm);
        stm = NULL;
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
