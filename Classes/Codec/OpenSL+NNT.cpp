
# include "Core.h"
# include "OpenSL+NNT.h"
# include <dlfcn.h>

# ifdef NNT_TARGET_ANDROID

#  include <SLES/OpenSLES.h>
#  include <SLES/OpenSLES_Android.h>

# endif

NNT_BEGIN_CXX

# ifdef NNT_TARGET_ANDROID

OpenSLES::OpenSLES()
{
	_m.open("OpenSLES");
}

OpenSLES::~OpenSLES()
{

}

# endif

NNT_END_CXX
