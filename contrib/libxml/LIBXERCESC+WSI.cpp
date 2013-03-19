
# include "Core.h"
# include "LIBXERCESC+WSI.h"

# include <xercesc/util/PlatformUtils.hpp>
# include <xercesc/util/XMLString.hpp>

WSI_BEGIN_CXX
WSI_BEGIN_NS(xml)

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

WSI_END_NS
WSI_END_CXX