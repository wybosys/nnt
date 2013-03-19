
# include "Core.h"
# include "XmlParserUtil.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(parser)

core::string XmlAttributeUtil::AttributeFind(core::string const& tgt, core::string const& str)
{
    core::regex_captured_t result;
    core::regex_capture(tgt + "=\"([a-zA-Z0-9\\.-_\\+=]+)\"", str, result);
    if (result.size() == 0)
        return core::null_string;
    return result[0][1];
}

core::string XmlAttributeUtil::AttributeMake(core::string const& name, core::string const& value, bool str)
{
    if (str == false)
        return name + "=" + value;
    return name + "=" + "\"" + value + "\"";
}

WSI_END_NS
WSI_END_CXX
