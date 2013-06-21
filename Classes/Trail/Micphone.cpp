
# include "Core.h"
# include "Micphone.h"

# ifdef NNT_MACH

# include <AudioToolbox/AudioToolbox.h>

# endif

NNT_BEGIN_CXX
NNT_BEGIN_NS(mic)

Channel::Channel()
{

}

Channel::~Channel()
{
    
}

real Channel::average_power() const
{
# ifdef NNT_MACH
    
    return use<AudioQueueLevelMeterState>(_buffer)->mAveragePower;
    
# endif
    
    return 0;
}

real Channel::peak_power() const
{
# ifdef NNT_MACH
    
    return use<AudioQueueLevelMeterState>(_buffer)->mPeakPower;
    
# endif
    
    return 0;
}

NNTDECL_PRIVATE_BEGIN_CXX(Trail)

static void InputBufferHandler(void *                          inUserData,
                               AudioQueueRef                   inAQ,
                               AudioQueueBufferRef             inBuffer,
                               const AudioTimeStamp *          inStartTime,
                               UInt32							inNumPackets,
                               const AudioStreamPacketDescription *inPacketDesc)
{
    PASS;
}

void init()
{
    queue = NULL;
    
# ifdef NNT_MACH
    
    d_owner->left._buffer = state;
    d_owner->right._buffer = state + 1;

    AudioStreamBasicDescription fmt = {0};
    fmt.mSampleRate = 44100;
    fmt.mFormatID = kAudioFormatLinearPCM;
    fmt.mChannelsPerFrame = 2;
    fmt.mBitsPerChannel = 16;
    fmt.mFormatFlags = 12;
    fmt.mBytesPerPacket = 4;
    fmt.mFramesPerPacket = 1;
    fmt.mBytesPerFrame = 4;
    fmt.mReserved = 0;
    AudioQueueNewInput(&fmt,
                       InputBufferHandler,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       &queue);
    
# endif
}

void dealloc()
{

}

# ifdef NNT_MACH

AudioQueueRef queue;
AudioQueueLevelMeterState state[2];

# endif

NNTDECL_PRIVATE_END_CXX

Trail::Trail(bool autostart)
{
    NNTDECL_PRIVATE_CONSTRUCT(Trail);
    
    interval = 0.1; // second.

    if (autostart)
        start();
}

Trail::~Trail()
{
    NNTDECL_PRIVATE_DESTROY();
}

void Trail::start()
{
# ifdef NNT_MACH
    
    //AudioQueueBufferRef buf;
    //AudioQueueAllocateBuffer(d_ptr->queue, 88200, &buf);
    //AudioQueueEnqueueBuffer(d_ptr->queue, buf, 0, NULL);
    
    UInt32 val = 1;
    AudioQueueSetProperty(d_ptr->queue,
                          kAudioQueueProperty_EnableLevelMetering,
                          &val, sizeof(UInt32));
    
    AudioQueueStart(d_ptr->queue, NULL);
    
# endif
}

void Trail::stop()
{    
# ifdef NNT_MACH
    
    AudioQueueStop(d_ptr->queue, YES);
    
# endif
}

bool Trail::update()
{
# ifdef NNT_MACH
    
    UInt32 sz = sizeof(d_ptr->state);
    OSErr sta = AudioQueueGetProperty(d_ptr->queue,
                                      kAudioQueueProperty_CurrentLevelMeterDB,
                                      d_ptr->state,
                                      &sz);
    if (sta != 0)
        return false;
    
# endif
    
    return true;
}

real Trail::average_power() const
{
    return (left.average_power() + right.average_power()) * .5f;
}

real Trail::peak_power() const
{
    return ::std::max(left.peak_power(), right.peak_power());
}

NNT_END_NS
NNT_END_CXX
