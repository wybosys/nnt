
# include "Core.h"
# include "AudioPlayer.h"
# include "OpenAL+NNT.h"
# include "../Drivers/AudioBuffer.h"
# include "AudioFile.h"
# include "AudioStream.h"

# ifdef NNT_TARGET_IOS

# include <OpenAL/al.h>
# include <OpenAL/alc.h>
# include <AudioToolbox/AudioToolbox.h>

# endif

# ifdef NNT_TARGET_ANDROID

# include <SLES/OpenSLES.h>

# endif

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

AbstractAudioPlayer::AbstractAudioPlayer()
{
    //signals.add(kSignalAudioPlayerPlaying).add(kSignalAudioPlayerStopped).add(kSignalAudioPlayerSuspended);
}

AbstractAudioPlayer::~AbstractAudioPlayer()
{
    
}

PlayerState AbstractAudioPlayer::state() const
{
    if (is_playing())
        return kPlayerStatePlaying;
    if (is_suspended())
        return kPlayerStateSuspended;
    return kPlayerStateStopped;
}

# ifdef NNT_TARGET_IOS

extern void SetDefaultAudioSessionCategory();

class CCOpenALDevice
{
public:
    
    CCOpenALDevice()
    {
        // 启动audio
        AudioSessionInitialize(NULL, NULL,
                               HandlerInterruptionListenerCallback, this);
        
        SetDefaultAudioSessionCategory();
        
        // 建立openal 环境
        dev = alcOpenDevice(NULL);
        ctx = alcCreateContext(dev, NULL);
        alcMakeContextCurrent(ctx);
    }
    
    ~CCOpenALDevice()
    {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(ctx);
        alcCloseDevice(dev);
    }
    
    void suspend()
    {
        alcSuspendContext(ctx);
    }
    
    void resume()
    {
        alcProcessContext(ctx);
    }
    
    ALCdevice* dev;
    ALCcontext* ctx;
    
protected:
    
    friend void HandlerInterruptionListenerCallback(void *inUserData, UInt32 interruptionState);
    static void HandlerInterruptionListenerCallback(void *inUserData, UInt32 interruptionState) {
        CCOpenALDevice* vp = (CCOpenALDevice*)inUserData;
        
        if (interruptionState == kAudioSessionBeginInterruption)
        {
            vp->becomingInterrupted();
        }
        else if (interruptionState == kAudioSessionEndInterruption)
        {
            vp->resignInterrupte();
        }
    }
    
    void becomingInterrupted()
    {
        AudioSessionSetActive(false);
        alcSuspendContext(ctx);
        alcMakeContextCurrent(NULL);
    }
    
    void resignInterrupte()
    {
        SetDefaultAudioSessionCategory();
        
        AudioSessionSetActive(true);
        alcMakeContextCurrent(ctx);
        alcProcessContext(ctx);
    }
    
};

static bool alSuccessFail()
{
    ALenum sta = alGetError();
    
# ifdef CC_DEBUG
    
    if (sta != AL_NO_ERROR)
    {
        printf("OpenAL Error: %d.\n", sta);
        fflush(stdout);
    }
    
# endif
    
    return sta == AL_NO_ERROR;
}

static CCOpenALDevice __gs_openal_device;

OpenALAudioPlayer::OpenALAudioPlayer()
: _state(kPlayerStateStopped)
{
    alGenSources(1, &_src);
    alGenBuffers(1, &_buf);
    
    _tskwh.infinite();
    //_tskwh.func = (CCTask::TaskFunc)CCOpenALAudioPlayerStateWatcher;
    //_tskwh.data = this;
    //_tskwh.delay = CCInterval::MilliSecond(10);
    _tskwh.start();
}

OpenALAudioPlayer::~OpenALAudioPlayer()
{
    alSourcei(_src, AL_BUFFER, 0);
    
    alDeleteBuffers(1, &_buf);
    alDeleteSources(1, &_src);
}

bool OpenALAudioPlayer::load(PCMAudioStream const& stm)
{
    ALenum alfmt = AL_FORMAT_STEREO16;
    
    switch (stm._ofmt->mChannelsPerFrame)
    {
        case 1:
        {
            switch (stm._ofmt->mBitsPerChannel)
            {
                case 8:
                {
                    alfmt = AL_FORMAT_MONO8;
                } break;
                case 16:
                {
                    alfmt = AL_FORMAT_MONO16;
                } break;
            }
        } break;
        case 2:
        {
            switch (stm._ofmt->mBitsPerChannel)
            {
                case 8:
                {
                    alfmt = AL_FORMAT_STEREO8;
                } break;
                case 16:
                {
                    alfmt = AL_FORMAT_STEREO16;
                } break;
            }
        } break;
    }
    
    // clean last play.
    clean();
    
    // bind data.
    alBufferData(_buf, alfmt,
                 stm._buf.buf(), stm._buf.length(),
                 stm._ofmt->mSampleRate);
    
    return alSuccessFail();
}

void OpenALAudioPlayer::clean()
{
    alSourceStop(_src);
    alSourcei(_src, AL_BUFFER, 0);
}

bool OpenALAudioPlayer::play()
{
    alSourcei(_src, AL_BUFFER, _buf);
    alSourcePlay(_src);
    
    return alSuccessFail();
}

bool OpenALAudioPlayer::stop()
{
    alSourceStop(_src);
    return alSuccessFail();
}

bool OpenALAudioPlayer::resume()
{
    if (is_suspended() == false)
        return false;
    
    alSourcePlay(_src);
    return alSuccessFail();
}

bool OpenALAudioPlayer::suspend()
{
    alSourcePause(_src);
    return alSuccessFail();
}

bool OpenALAudioPlayer::is_playing() const
{
    ALint state;
    alGetSourcei(_src, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

bool OpenALAudioPlayer::is_suspended() const
{
    ALint state;
    alGetSourcei(_src, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

void OpenALAudioPlayer::CCOpenALAudioPlayerStateWatcher(CCTask*, void* data)
{
    CCOpenALAudioPlayer* ply = (CCOpenALAudioPlayer*)data;
    CCAudioPlayerState sta = ply->state();
    if (sta == ply->_state)
        return;
    
    ply->_state = sta;
    
    CCSignal sig;
    switch (sta)
    {
        default: break;
        case kCCAudioPlayerStatePlaying: sig = kSignalAudioPlayerPlaying; break;
        case kCCAudioPlayerStateStopped: sig = kSignalAudioPlayerStopped; break;
        case kCCAudioPlayerStateSuspended: sig = kSignalAudioPlayerSuspended; break;
    }
    
    ply->signals.emit(sig);
}

# endif

# ifdef CC_BUILD_ANDROID

CCOpenSLAudioPlayer::CCOpenSLAudioPlayer()
{
    
}

CCOpenSLAudioPlayer::~CCOpenSLAudioPlayer()
{
    
}

bool CCOpenSLAudioPlayer::load(CCPCMAudioStream const& stm)
{
    return false;
}

bool CCOpenSLAudioPlayer::play()
{
    return false;
}

bool CCOpenSLAudioPlayer::stop()
{
    return false;
}

bool CCOpenSLAudioPlayer::resume()
{
    return false;
}

bool CCOpenSLAudioPlayer::suspend()
{
    return false;
}

bool CCOpenSLAudioPlayer::is_playing() const
{
    return false;
}

bool CCOpenSLAudioPlayer::is_suspended() const
{
    return false;
}

# endif

NNT_END_NS
NNT_END_CXX
