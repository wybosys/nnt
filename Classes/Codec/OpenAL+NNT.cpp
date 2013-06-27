
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

class sourceGroup
{
public:
    
    sourceGroup()
    {
        memset(this, 0, sizeof(*this));
    }
    
    int startIndex;
    int currentIndex;
    int totalSources;
    bool enabled;
    bool nonInterruptible;
    int *sourceStatuses;//pointer into array of source status information
};

class bufferInfo
{
public:
    
    bufferInfo()
    {
        memset(this, 0, sizeof(*this));
    }
    
    ALuint bufferId;
    int bufferState;
    void* bufferData;
    ALenum format;
    ALsizei sizeInBytes;
    ALsizei frequencyInHertz;
};

class sourceInfo
{
public:
    
    sourceInfo()
    {
        memset(this, 0, sizeof(*this));
    }
    
    bool usable;
    ALuint sourceId;
    ALuint attachedBufferId;
};

NNTDECL_PRIVATE_BEGIN_CXX(Oal)

void init()
{
    gain_old = 0;
    mute = false;
    device = NULL;
    context = NULL;
    buffers.resize(CD_BUFFERS_START);
    sources.resize(CD_SOURCE_LIMIT);
}

void dealloc()
{
    close();
}

void close()
{
    clear_buffers();
    clear_sources();
    
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

void create_buffers()
{
    for (uint i = 0; i < buffers.size(); ++i)
    {
        bufferInfo& bi = buffers.at(i);
        if (bi.bufferState == CD_BS_NULL)
        {
            alGenBuffers(1, &bi.bufferId);
            if (alGetError() == AL_NO_ERROR)
            {
                bi.bufferState = CD_BS_EMPTY;
                bi.bufferData = NULL;
            }
            else
            {
                bi.bufferState = CD_BS_FAILED;
            }
        }
    }
}

void clear_buffers()
{
# define CD_BS_NEED_FREE(bs) ((bs == CD_BS_EMPTY) || (bs == CD_BS_LOADED))
    
    for (uint i = 0; i < buffers.size(); ++i)
    {
        bufferInfo& bi = buffers.at(i);
        if (CD_BS_NEED_FREE(bi.bufferState))
        {
            alDeleteBuffers(1, &bi.bufferId);
            bi.bufferId = 0;
            bi.bufferState = CD_BS_NULL;
            safe_free(bi.bufferData);
        }
    }
}

void create_sources()
{
    totalSources = 0;
    bool failed = false;
    for (uint i = 0; i < sources.size(); ++i)
    {
        sourceInfo& si = sources.at(i);
        si.usable = false;
        if (!failed)
        {
            alGenSources(1, &si.sourceId);
            if (alGetError() == AL_NO_ERROR)
            {
                alSourcei(si.sourceId, AL_BUFFER, 0);
                if (alGetError() == AL_NO_ERROR)
                {
                    si.usable = true;
                    ++totalSources;
                }
                else
                {
                    failed = true;
                }
            }
            else
            {
                failed = true;
            }
        }
    }
}

void clear_sources()
{
    for (uint i = 0; i < sources.size(); ++i)
    {
        sourceInfo& si = sources.at(i);
        if (si.usable)
        {
            alDeleteSources(1, &si.sourceId);
            si.usable = false;
        }
    }
}

void create_groups(uint defines[], uint count)
{    
    clear_groups();
    
    groups.resize(count);
    
    uint sourceCount = 0;
    for (uint i = 0; i < count; ++i)
    {
        sourceGroup& sg = groups.at(i);
        sg.startIndex = 0;
        sg.currentIndex = sg.startIndex;
        sg.enabled = false;
        sg.nonInterruptible = false;
        sg.totalSources = defines[i];
        sg.sourceStatuses = (int*)malloc(sizeof(sg.sourceStatuses[0]) * sg.totalSources);
        if (sg.sourceStatuses)
        {
            for (uint j = 0; j < sg.totalSources; ++j)
            {
                sg.sourceStatuses[j] = (sourceCount + j) << 1;
            }
        }
        sourceCount += defines[i];
    }
}

void clear_groups()
{
    for (uint i = 0; i < groups.size(); ++i)
    {
        sourceGroup& sg = groups.at(i);
        safe_free(sg.sourceStatuses);
    }
    groups.clear();
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
        gain_old = v;
    else
    {
        alListenerf(AL_GAIN, v);
    }
}

bool test_get_gain()
{
    ALfloat testValue = .7f;
    ALuint testSourceId = sources[0].sourceId;
    alSourcef(testSourceId, AL_GAIN, 0.f);
    alSourcef(testSourceId, AL_GAIN, testValue);
    ALfloat gainVal;
    alGetSourcef(testSourceId, AL_GAIN, &gainVal);
    return testValue == gainVal;
}

ALCdevice* device;
ALCcontext* context;
uint totalSources;
core::vector<bufferInfo> buffers;
core::vector<sourceInfo> sources;
core::vector<sourceGroup> groups;
bool mute;
real gain_old;

NNTDECL_PRIVATE_END_CXX

OalConfig::OalConfig()
{
    sample_rate = CD_SAMPLE_RATE_DEFAULT;
}

Oal::Oal()
{
    NNTDECL_PRIVATE_CONSTRUCT(Oal);
}

Oal::~Oal()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Oal::open()
{
    d_ptr->close();
    
    alcSetMixerOutputRate(config.sample_rate);
    
    d_ptr->device = alcOpenDevice(NULL);
    if (d_ptr->device == NULL)
        return false;
    
    d_ptr->context = alcCreateContext(d_ptr->device, NULL);
    if (d_ptr->context == NULL)
        return false;
    
    alcMakeContextCurrent(d_ptr->context);
    
    d_ptr->create_buffers();
    d_ptr->create_sources();
    
    // create source group.
    {
        uint sourceDefs[1];
        sourceDefs[0] = d_ptr->totalSources;
        d_ptr->create_groups(sourceDefs, 1);
    }
    
    // test gain.
    d_ptr->test_get_gain();
    
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

NNT_END_NS
NNT_END_CXX
