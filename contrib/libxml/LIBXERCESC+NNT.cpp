
# include "Core.h"
# include "LIBXERCESC+NNT.h"

# include <xercesc/util/PlatformUtils.hpp>
# include <xercesc/util/XMLString.hpp>

NNT_BEGIN_CXX
NNT_BEGIN_NS(xml)

Environment::Environment()
{
    ::xercesc::XMLPlatformUtils::Initialize();
}

Environment::~Environment()
{
    ::xercesc::XMLPlatformUtils::Terminate();
}

NNT_END_NS
NNT_END_CXX