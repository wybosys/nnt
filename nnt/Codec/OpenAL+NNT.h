
# ifndef __NNT_OPENAL_928DEF4638E54407876284B0A4CF5FC6_H_INCLUDED
# define __NNT_OPENAL_928DEF4638E54407876284B0A4CF5FC6_H_INCLUDED

# include "AudioFile.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(codec)

// thanks to cocos2dx-denshion

enum
{
    //Tested source limit on 2.2.1 and 3.1.2 with up to 128 sources and appears to work. Older OS versions e.g 2.2 may support only 32
    CD_SOURCE_LIMIT = 32, //Total number of sources we will ever want, may actually get less
    CD_NO_SOURCE = 0xFEEDFAC, //Return value indicating playback failed i.e. no source
    CD_IGNORE_AUDIO_SESSION = 0xBEEFBEE, //Used internally to indicate audio session will not be handled
    CD_MUTE =      0xFEEDBAB, //Return value indicating sound engine is muted or non functioning
    CD_NO_SOUND = -1,
    
    CD_SAMPLE_RATE_HIGH = 44100,
    CD_SAMPLE_RATE_MID =  22050,
    CD_SAMPLE_RATE_LOW =  16000,
    CD_SAMPLE_RATE_BASIC = 8000,
    CD_SAMPLE_RATE_DEFAULT = CD_SAMPLE_RATE_HIGH,
    
    //Number of buffers slots that will be initially created
    CD_BUFFERS_START = 64,
    //Number of buffers that will be added
    CD_BUFFERS_INCREMENT = 16,
    
    CD_BS_NULL = 0,
    CD_BS_EMPTY = 1,
    CD_BS_LOADED = 2,
    CD_BS_FAILED = 3,
    
};

NNTDECL_PRIVATE_HEAD_CXX(Oal);

class Oal
{
    
    NNTDECL_PRIVATE_CXX(Oal);
    
public:
    
    enum
    {
        FORMAT_MONO = 0x10,
        FORMAT_STEREO = 0x20,
        FORMAT_8BITS = 0x1,
        FORMAT_16BITS = 0x2,
        
        FORMAT_MONO8 = FORMAT_8BITS | FORMAT_MONO,
        FORMAT_MONO16 = FORMAT_16BITS | FORMAT_MONO,
        FORMAT_STEREO8 = FORMAT_8BITS | FORMAT_STEREO,
        FORMAT_STEREO16 = FORMAT_16BITS | FORMAT_STEREO,
    };
    
    Oal();
    ~Oal();
    
    bool open();
    void set_mute(bool);
    bool is_mute() const;
    bool read(core::data const&, int format, real freq);
    bool seek(real);
    bool play();
    bool is_playing() const;
    bool stop();
    bool pause();
    bool resume();
    
    audio::FormatType format;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
