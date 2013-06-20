
# include "Core.h"
# include "YamlParser.h"

NNT_BEGIN_HEADER_C

# include "../../contrib/yaml/yaml.h"

NNT_END_HEADER_C

NNT_BEGIN_CXX
NNT_BEGIN_NS(parser)

NNTDECL_PRIVATE_BEGIN_CXX(YamlDocument)

void init()
{
    
}

void dealloc()
{

}

yaml_parser_t psr;

NNTDECL_PRIVATE_END_CXX

YamlDocument::YamlDocument()
{
    NNTDECL_PRIVATE_CONSTRUCT(YamlDocument);
}

YamlDocument::~YamlDocument()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool YamlDocument::parse(core::data const& da)
{
    return false;
}

NNT_END_NS
NNT_END_CXX
