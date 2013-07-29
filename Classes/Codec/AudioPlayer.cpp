
# include "Core.h"
# include "AudioPlayer.h"
# include "../Drivers/AudioBuffer.h"
# include "AudioFile.h"
# include "AudioStream.h"

# ifdef NNT_TARGET_IOS

# include <OpenAL/al.h>
# include <OpenAL/alc.h>
# include <AudioToolbox/AudioToolbox.h>
# include "OpenAL+NNT.h"

# endif

# ifdef NNT_TARGET_ANDROID

# include <SLES/OpenSLES.h>
# include <SLES/OpenSLES_Android.h>
# include "OpenSL+NNT.h"

# endif

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

signal_t kSignalPlayerStopped = "::nnt::audio::player::stop";
signal_t kSignalPlayerPlaying = "::nnt::audio::player::playing";
signal_t kSignalPlayerSuspended = "::nnt::audio::player::suspended";

AbstractAudioPlayer::AbstractAudioPlayer()
{
    register_signal(kSignalPlayerStopped);
    register_signal(kSignalPlayerPlaying);
    register_signal(kSignalPlayerSuspended);
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

static codec::OpenALDevice __gs_openal_device;

OpenALAudioPlayer::OpenALAudioPlayer()
: _state(kPlayerStateStopped)
{
    alGenSources(1, &_src);
    alGenBuffers(1, &_buf);
    
    _tskwh.infinite();
    _tskwh.func = OpenALAudioPlayerStateWatcher;
    _tskwh.data = this;
    _tskwh.delay = core::TimeInterval::MilliSecond(10);
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

int OpenALAudioPlayer::OpenALAudioPlayerStateWatcher(core::Task*, void* data)
{
    OpenALAudioPlayer* ply = (OpenALAudioPlayer*)data;
    PlayerState sta = ply->state();
    if (sta == ply->_state)
        return 0;
    
    ply->_state = sta;
    
    signal_t sig;

    switch (sta)
    {
        default: break;
        case kPlayerStatePlaying: sig = kSignalPlayerPlaying; break;
        case kPlayerStateStopped: sig = kSignalPlayerStopped; break;
        case kPlayerStateSuspended: sig = kSignalPlayerSuspended; break;
    }
    
    ply->emit(sig);
    
    return 0;
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
