
# include "Core.h"
# include "AudioStream.h"

# ifdef NNT_TARGET_ANDROID

# include <SLES/OpenSLES.h>
# include <SLES/OpenSLES_Android.h>

# endif

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

AbstractPCMAudioStream::AbstractPCMAudioStream()
{
    
}

AbstractPCMAudioStream::~AbstractPCMAudioStream()
{
    
}

NNT_END_NS
NNT_END_CXX
