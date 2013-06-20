
# ifndef __NNT_AUDIO_OBJECT_163FA948254B4FB3B91BCA08C2CA8194_H_INCLUDED
# define __NNT_AUDIO_OBJECT_163FA948254B4FB3B91BCA08C2CA8194_H_INCLUDED

# ifdef NNT_MACH

# include <AudioToolbox/AudioToolbox.h>

# ifdef NNT_OBJC

# include <AVFoundation/AVFoundation.h>

# endif

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
