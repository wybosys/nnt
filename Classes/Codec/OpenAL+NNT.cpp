
# include "Core.h"
# include "OpenAL+NNT.h"
# include <OpenAL/al.h>
# include <OpenAL/alc.h>

NNT_BEGIN_CXX
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
    buffer = 0;    
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
        alSourcei(source, AL_BUFFER, 0);
    }
    
    if (buffer)
    {
        alDeleteBuffers(1, &buffer);
        buffer = 0;
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
ALuint buffer;
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

bool Oal::read(core::data const& da, int format, real freq)
{
    d_ptr->set_current();
    d_ptr->clean();
        
    // create new.
    alGenSources(1, &d_ptr->source);
    ALenum sta = alGetError();
    if (sta != AL_NO_ERROR)
        return false;
    
    alGenBuffers(1, &d_ptr->buffer);
    sta = alGetError();
    if (sta != AL_NO_ERROR)
        return false;
    
    ALint fmt = 0;
    switch (format)
    {
        case FORMAT_MONO8: fmt = AL_FORMAT_MONO8; break;
        case FORMAT_MONO16: fmt = AL_FORMAT_MONO16; break;
        case FORMAT_STEREO8: fmt = AL_FORMAT_STEREO8; break;
        case FORMAT_STEREO16: fmt = AL_FORMAT_STEREO16; break;
    }
    
    alBufferData(d_ptr->buffer,
                 fmt,
                 da.bytes(),
                 da.length(),
                 freq);
    
    if (alGetError() != AL_NO_ERROR)
        return false;
    
    length = da.length() / freq / TRIEXP(MASK_CHECK(FORMAT_MONO, format), 1, 2) / TRIEXP(MASK_CHECK(FORMAT_8BITS, format), 1, 2);
    
    return true;
}

bool Oal::play()
{
    d_ptr->set_current();
    
    if (is_playing())
        stop();
    
    alSourcei(d_ptr->source, AL_BUFFER, d_ptr->buffer);
    
    // clear error code.
    alGetError();
    
    // play.
    alSourcePlay(d_ptr->source);
    
    ALenum err = alGetError();
    
    return err == AL_NO_ERROR;
}

bool Oal::is_playing() const
{
    d_ptr->set_current();
    
    ALint state;
    alGetSourcei(d_ptr->source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

bool Oal::stop()
{
    d_ptr->set_current();
    
    alSourceStop(d_ptr->source);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::seek(real v)
{
    d_ptr->set_current();
    
    alSourcef(d_ptr->source, AL_SEC_OFFSET, v);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::position(real& v)
{
    d_ptr->set_current();
    
    alGetSourcef(d_ptr->source, AL_SEC_OFFSET, &v);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::pause()
{
    d_ptr->set_current();
    
    alSourcePause(d_ptr->source);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::resume()
{
    d_ptr->set_current();
    
    alSourcePlay(d_ptr->source);
    
    return alGetError() == AL_NO_ERROR;
}

bool Oal::gain(real &v)
{
    d_ptr->set_current();
    
    alGetSourcef(d_ptr->source, AL_GAIN, &v);
    
    return alGetError() == AL_NO_ERROR;
}

NNT_END_NS
NNT_END_CXX
