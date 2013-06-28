
# ifndef __NNT_AUDIO_OBJECT_163FA948254B4FB3B91BCA08C2CA8194_H_INCLUDED
# define __NNT_AUDIO_OBJECT_163FA948254B4FB3B91BCA08C2CA8194_H_INCLUDED

# ifdef NNT_MACH

# include <AudioToolbox/AudioToolbox.h>

# ifdef NNT_OBJC

# include <AVFoundation/AVFoundation.h>

# endif

# ifdef NNT_TARGET_MAC

const UInt32 kAppleSoftwareAudioCodecManufacturer  = 'appl';
const UInt32 kAppleHardwareAudioCodecManufacturer  = 'aphw';

# endif

# endif

# ifdef NNT_C_COMPATIABLE

NNT_BEGIN_HEADER_C

typedef enum
{
# ifdef NNT_MACH
    
    AUDIO_FORMAT_AAC,
    AUDIO_FORMAT_WAVE,
    AUDIO_FORMAT_MP3,
    
# endif
}
NntAudioFormat;

NNT_END_HEADER_C

# endif

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(audio)

class Object
: public cxx::Object<>
{
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
