
# include "Core.h"
# include <OpenAL/al.h>
# include <OpenAL/alc.h>
# include "OpenAL+NNT.h"

NNT_BEGIN_CXX

NNT_BEGIN_NS(audio)

extern void SetDefaultAudioSessionCategory();

NNT_END_NS

NNT_BEGIN_NS(codec)

typedef ALvoid AL_APIENTRY (*funcAlcMixerOutputRateProcPtr)(ALdouble const value);
static void alcSetMixerOutputRate(real val)
{
    static funcAlcMixerOutputRateProcPtr func = NULL;
    if (func == NULL)
        func = (funcAlcMixerOutputRateProcPtr)alcGetProcAddress(NULL, (ALCchar const*)"alcMacOSXMixerOutputRate");
    if (func)
        func(val);
}

typedef ALvoid AL_APIENTRY (*funcAlBufferDataStaticProcPtr)(const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq);
static ALvoid alBufferDataStaticProc(const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq)
{
    static funcAlBufferDataStaticProcPtr func = NULL;
    if (func == NULL)
        func = (funcAlBufferDataStaticProcPtr)alcGetProcAddress(NULL, (ALCchar const*)"alBufferDataStatic");
    if (func)
        func(bid, format, data, size, freq);
}

NNTDECL_PRIVATE_BEGIN_CXX(Oal)

void init()
{
    gain_old = 0;
    mute = false;
    device = NULL;
    context = NULL;
    source = 0;
}

void dealloc()
{
    close();
}

void close()
{
    clean();
    
    if (context)
    {
        alcDestroyContext(context);
        context = NULL;
    }
    
    if (device)
    {
        alcCloseDevice(device);
        device = NULL;
    }
}

void clean()
{
    if (source)
    {
        ALint val;
        alGetSourcei(source, AL_SOURCE_STATE, &val);
        if (val == AL_PLAYING)
            alSourceStop(source);
        if (buffers.size())
            alSourceUnqueueBuffers(source, buffers.size(), &buffers[0]);
    }
    
    if (buffers.size())
    {
        alDeleteBuffers(buffers.size(), &buffers[0]);
        buffers.clear();
    }
    
    if (source)
    {
        alDeleteSources(1, &source);
        source = 0;
    }

}

real get_master_gain() const
{
    if (mute)
        return gain_old;
    ALfloat gain;
    alGetListenerf(AL_GAIN, &gain);
    return gain;
}

void set_master_gain(real v)
{
    if (mute)
    {
        gain_old = v;
    }
    else
    {
        alListenerf(AL_GAIN, v);
    }
}

void set_current()
{
    alcMakeContextCurrent(context);
}

ALCdevice* device;
ALCcontext* context;
core::vector<ALuint> buffers;
ALuint source;
uint totalSources;
bool mute;
real gain_old;

NNTDECL_PRIVATE_END_CXX

Oal::Oal()
{
    NNTDECL_PRIVATE_CONSTRUCT(Oal);
    
    length = 0;
}

Oal::~Oal()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Oal::open()
{
    d_ptr->close();
    
    alcSetMixerOutputRate(format.sampler());
    
    d_ptr->device = alcOpenDevice(NULL);
    if (d_ptr->device == NULL)
        return false;
    
    d_ptr->context = alcCreateContext(d_ptr->device, NULL);
    if (d_ptr->context == NULL)
        return false;
    
    d_ptr->set_current();
    
    return true;
}

void Oal::set_mute(bool b)
{
    if (b == d_ptr->mute)
        return;
    
    if (b)
    {
        d_ptr->gain_old = d_ptr->get_master_gain();
        alListenerf(AL_GAIN, 0.f);
    }
    else
    {
        d_ptr->set_master_gain(d_ptr->gain_old);
    }
}

bool Oal::is_mute() const
{
    return d_ptr->mute;
}

bool Oal::read(core::data const& da)
{
    d_ptr->clean();
        
    // create new.
    alGenSources(1, &d_ptr->source);
    ALenum sta = alGetError();
    if (sta != AL_NO_ERROR)
        return false;
    
    length = 0;
    return append(da);
}

bool Oal::append(core::data const& da)
{
    ALuint buffer;
    alGenBuffers(1, &buffer);
    ALenum sta = alGetError();
    if (sta != AL_NO_ERROR)
        return false;
    
    d_ptr->buffers.push_back(buffer);
    
    ALint fmt = 0;
    switch (format.channel())
    {
        case 1:
        {
            switch (format.bits())
            {
                case 8:
                {
                    fmt = AL_FORMAT_MONO8;
                } break;
                case 16:
                {
                    fmt = AL_FORMAT_MONO16;
                } break;
            }
        } break;
        case 2:
        {
            switch (format.bits())
            {
                case 8:
                {
                    fmt = AL_FORMAT_STEREO8;
                } break;
                case 16:
                {
                    fmt = AL_FORMAT_STEREO16;
                } break;
            }
        } break;
    }
    
    alBufferData(buffer,
                 fmt,
                 da.bytes(),
                 da.length(),
                 format.sampler());
    
    if (alGetError() != AL_NO_ERROR)
        return false;
    
    real curlen = format.channel() * format.bits() / 8;
    curlen = da.length() / format.sampler() / curlen;
    length += curlen;
    
    return true;
}

bool Oal::play()
{
    if (is_playing())
        stop();
    
    if (d_ptr->buffers.size())
        alSourceQueueBuffers(d_ptr->source,
                             d_ptr->buffers.size(),
                             &d_ptr->buffers[0]);
    
    // clear error code.
    alGetError();
    
    // play.
    alSourcePlay(d_ptr->source);
    
    ALenum err = alGetError();
    
    return err == AL_NO_ERROR;
}

bool Oal::is_playing() const
{
    ALint state;
    alGetSourcei(d_ptr->source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

bool Oal::stop()
{
    alSourceStop(d_ptr->source);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::seek(float v)
{
    alSourcef(d_ptr->source, AL_SEC_OFFSET, v);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::position(float& v)
{
    alGetSourcef(d_ptr->source, AL_SEC_OFFSET, &v);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::pause()
{    
    alSourcePause(d_ptr->source);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::resume()
{
    alSourcePlay(d_ptr->source);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::gain(float &v)
{
    alGetSourcef(d_ptr->source, AL_GAIN, &v);
    
    return alGetError() == AL_NO_ERROR;
}

OpenALDevice::OpenALDevice()
{
# ifdef NNT_TARGET_IOS
    // 启动audio
    AudioSessionInitialize(NULL, NULL,
                           HandlerInterruptionListenerCallback, this);
# endif
    
    audio::SetDefaultAudioSessionCategory();
    
    // 建立openal 环境
    dev = alcOpenDevice(NULL);
    ctx = alcCreateContext(dev, NULL);
    alcMakeContextCurrent(ctx);
}

OpenALDevice::~OpenALDevice()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
}

void OpenALDevice::suspend()
{
    alcSuspendContext(ctx);
}

void OpenALDevice::resume()
{
    alcProcessContext(ctx);
}

void OpenALDevice::HandlerInterruptionListenerCallback(void *inUserData, UInt32 interruptionState)
{
# ifdef NNT_TARGET_IOS
    
    OpenALDevice* vp = (OpenALDevice*)inUserData;
    
    if (interruptionState == kAudioSessionBeginInterruption)
    {
        vp->becomingInterrupted();
    }
    else if (interruptionState == kAudioSessionEndInterruption)
    {
        vp->resignInterrupte();
    }
    
# endif
}

void OpenALDevice::becomingInterrupted()
{
# ifdef NNT_TARGET_IOS
    AudioSessionSetActive(false);
# endif
    
    alcSuspendContext(ctx);
    alcMakeContextCurrent(NULL);
}

void OpenALDevice::resignInterrupte()
{
    audio::SetDefaultAudioSessionCategory();
    
# ifdef NNT_TARGET_IOS
    AudioSessionSetActive(true);
# endif
    
    alcMakeContextCurrent(ctx);
    alcProcessContext(ctx);
}

NNT_END_NS
NNT_END_CXX
