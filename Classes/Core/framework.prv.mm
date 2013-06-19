
# include "Core.h"
# include "framework.prv.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(prv)

core::string resource_directory()
{
    ns::String str = ns::URL::Bundle(@"nnt.framework/Resources");
    return core::type_cast<core::string>(str) + "/";
}

NNT_END_NS
NNT_END_CXX
