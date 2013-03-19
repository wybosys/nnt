
# include "Core.h"
# include "PropertyTree.h"

# include "../Core/Boost+WSI.h"
# include <boost/property_tree/ptree.hpp>
# include <boost/property_tree/xml_parser.hpp>
# include <boost/property_tree/json_parser.hpp>
# include <boost/property_tree/ini_parser.hpp>
# include <boost/property_tree/info_parser.hpp>

WSI_BEGIN_CXX 
WSI_BEGIN_NS(parser)

using ::boost::property_tree::ptree;

WSIDECL_PRIVATE_BEGIN_CXX(PropertyTree)

void init()
{
    PASS;
}

void dealloc()
{
    PASS;
}

void clear()
{
    this->properties.clear();
}

bool load_xml(core::string const& str)
{
    using namespace ::boost::property_tree::xml_parser;    
    read_xml(str, properties, no_comments | trim_whitespace);
    return true;
}

bool load_info(core::string const& str)
{
    using namespace ::boost::property_tree::info_parser;
    read_info(str, properties);
    return true;
}

bool load_json(core::string const& str)
{
    using namespace ::boost::property_tree::json_parser;
    read_json(str, properties);
    return true;
}

bool load_ini(core::string const& str)
{
    using namespace ::boost::property_tree::ini_parser;
    read_ini(str, properties);
    return true;
}

ptree properties;

WSIDECL_PRIVATE_END_CXX

PropertyTree::PropertyTree()
{
    WSIDECL_PRIVATE_CONSTRUCT(PropertyTree);
}

PropertyTree::~PropertyTree()
{
    WSIDECL_PRIVATE_DESTROY();
}

void PropertyTree::clear()
{
    d_ptr->clear();
}

bool PropertyTree::load(core::string const& str, FormatType fmt)
{
    bool ret = false;
    switch (fmt)
    {
        case FORMAT_XML: ret = d_ptr->load_xml(str); break;
        case FORMAT_JSON: ret = d_ptr->load_json(str); break;
        case FORMAT_INI: ret = d_ptr->load_ini(str); break;
        case FORMAT_INFO: ret = d_ptr->load_info(str); break;
    }
    return ret;
}

WSI_END_NS 
WSI_END_CXX
