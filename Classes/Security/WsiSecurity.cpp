
# include "Core.h"
# include "WsiSecurity.h"

WSI_BEGIN_CXX

core::string nonce::simple()
{
    core::stringstream oss;

# ifdef WSI_MACH

    oss << arc4random() % (9999999 - 123400) + 123400;

# else

	oss << (int)(rand01() * (9999999 - 123400)) + 123400;

# endif

    return oss.str();
}

WSI_END_CXX
