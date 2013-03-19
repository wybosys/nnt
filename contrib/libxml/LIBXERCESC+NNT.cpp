
# include "Core.h"
# include "LIBXERCESC+NNT.h"

# include <xercesc/util/PlatformUtils.hpp>
# include <xercesc/util/XMLString.hpp>

NNT_BEGIN_CXX
NNT_BEGIN_NS(xml)

class Environment
{
public:
	Environment();
	~Environment();
};

Environment::Environment()
{
    ::xercesc::XMLPlatformUtils::Initialize();
}

Environment::~Environment()
{
    ::xercesc::XMLPlatformUtils::Terminate();
}

static Environment __gs_xml_environment;

NNT_END_NS
NNT_END_CXX