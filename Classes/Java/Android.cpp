
# include "Core.h"
# include "Android.h"

# ifdef NNT_TARGET_ANDROID

NNT_BEGIN_CXX

Android::Android()
{
	_m.open("android");
}

Android::~Android()
{

}

NNT_END_CXX

# endif
