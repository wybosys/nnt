
# import "Core.h"
# import "MicRecorder.h"
# import <AudioToolbox/AudioToolbox.h>

NNT_BEGIN_OBJC

@implementation NNTMicRecorder

- (id)init {
    if ((self = [super init]) is_nil)
        return nil;
    return self;
}

- (void)dealloc {
    [super dealloc];
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(mic)

NNTDECL_PRIVATE_BEGIN_CXX(Recorder)

void init()
{
    
}

void dealloc()
{
    
}

static void InputBufferHandler(void *                          inUserData,
                               AudioQueueRef                   inAQ,
                               AudioQueueBufferRef             inBuffer,
                               const AudioTimeStamp *          inStartTime,
                               UInt32							inNumPackets,
                               const AudioStreamPacketDescription *inPacketDesc)
{
    
}

AudioQueueRef queue;

NNTDECL_PRIVATE_END_CXX

Recorder::Recorder(Device& dev)
: _dev(dev)
{
    NNTDECL_PRIVATE_CONSTRUCT(Recorder);
}

Recorder::~Recorder()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Recorder::start()
{
    format.update(type);
    
    OSStatus suc = AudioQueueNewInput(format,
                                      private_type::InputBufferHandler,
                                      this,
                                      NULL,
                                      NULL,
                                      0,
                                      &d_ptr->queue);
    return suc != 0;
}

bool Recorder::stop()
{
    return true;
}

NNT_END_NS
NNT_END_CXX
