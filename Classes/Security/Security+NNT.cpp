
# include "Core.h"
# include "Security+NNT.h"

NNT_BEGIN_CXX

core::string nonce::simple()
{
    core::stringstream oss;

# ifdef NNT_MACH

    oss << arc4random() % (9999999 - 123400) + 123400;

# else

	oss << (int)(rand01() * (9999999 - 123400)) + 123400;

# endif

    return oss.str();
}

NNT_END_CXX
