
# include "Core.h"
# include "MicDevice.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(mic)

NNTDECL_PRIVATE_BEGIN_CXX(Device)

void init()
{
    
}

void dealloc()
{
    
}

NNTDECL_PRIVATE_END_CXX

Device::Device()
{
    NNTDECL_PRIVATE_CONSTRUCT(Device);
}

Device::~Device()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Device::add(audio::Buffer &buf)
{
# ifdef NNT_MACH
    
    int suc = 0;
    for (core::vector<AudioQueueBufferRef>::iterator each = buf.handle().begin();
         each != buf.handle().end();
         ++each)
    {
        OSStatus sta = AudioQueueEnqueueBuffer(buf.queue, *each, 0, NULL);
        if (sta)
        {
            trace_msg("failed to add audio buffer");
        }
        else
        {
            ++suc;
        }
    }
    
    // if success, the buffer will freed when dispose the queue.
    buf.need_release = suc == 0;
    
    return suc != 0;
    
# endif
    return false;
}

NNT_END_NS
NNT_END_CXX
