
# import "Core.h"
# import "MicRecorder.h"
# import "AudioBuffer.h"

NNT_BEGIN_OBJC

signal_t kSignalStart = @"::nnt::start";
signal_t kSignalStop = @"::nnt::stop";
signal_t kSignalPause = @"::nnt::pause";
signal_t kSignalResume = @"::nnt::resume";

@implementation NNTMicRecorder

- (id)init {
    if ((self = [super init]) is_nil)
        return nil;
    return self;
}

- (void)dealloc {
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalStart);
NNTEVENT_SIGNAL(kSignalStop);
NNTEVENT_END

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(mic)

NNTDECL_PRIVATE_BEGIN_CXX(Recorder)

void init()
{
    queue = NULL;
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
    use<owner_type> rdr = inUserData;
    rdr->d_ptr->buffer.receive(inAQ, inBuffer, inStartTime, inNumPackets, inPacketDesc);
}

AudioQueueRef queue;
audio::Buffer buffer;

NNTDECL_PRIVATE_END_CXX

Recorder::Recorder(Device* dev)
: _dev(dev)
{
    NNTDECL_PRIVATE_CONSTRUCT(Recorder);
}

Recorder::~Recorder()
{
    stop();
    
    NNTDECL_PRIVATE_DESTROY();
}

void Recorder::set(Device& dev)
{
    _dev = &dev;
}

void Recorder::set(Device* dev)
{
    _dev = dev;
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
    
    if (suc != 0)
    {
        trace_fmt(@"failed to create audio queue, %.4s", (char*)&suc);
        return false;
    }
    
    format.update(d_ptr->queue);
    
    // open stream.
    d_ptr->buffer.type = type;
    d_ptr->buffer.queue = d_ptr->queue;
    d_ptr->buffer.format = format;
    
    if (!d_ptr->buffer.open())
    {
        trace_fmt(@"failed to open audio buffer, %.4s", (char*)&suc);
        return false;
    }
    
    if (!_dev->add(d_ptr->buffer))
    {
        trace_fmt(@"failed to add audio buffer to device, %.4s", (char*)&suc);
        return false;
    }
    
    d_ptr->buffer.used = true;
    suc = AudioQueueStart(d_ptr->queue, NULL);
    
    if (suc != 0)
    {
        d_ptr->buffer.used = false;
        trace_fmt(@"failed to start audio queue, %.4s", (char*)&suc);
        return false;
    }
    
    return true;
}

bool Recorder::stop()
{
    d_ptr->buffer.used = false;
    
    if (d_ptr->queue)
    {
        AudioQueueStop(d_ptr->queue, YES);
        AudioQueueDispose(d_ptr->queue, YES);
        d_ptr->queue = NULL;
    }
    
    d_ptr->buffer.close();
    
    return true;
}

audio::Buffer const& Recorder::buffer() const
{
    return d_ptr->buffer;
}

NNT_END_NS
NNT_END_CXX
