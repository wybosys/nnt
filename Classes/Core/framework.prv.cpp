
# include "Core.h"
# include "framework.prv.h"
# include "App.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(prv)

# ifndef NNT_MACH

core::string resource_directory()
{
    return core::Environment::workingDirectory();
}

# endif

NNT_END_NS
NNT_END_CXX
