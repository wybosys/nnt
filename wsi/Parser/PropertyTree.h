
# ifndef __WSI_PARSER_PROPERTYTREE_DED17F38D1AF479F83520764572A4CC7_H_INCLUDED
# define __WSI_PARSER_PROPERTYTREE_DED17F38D1AF479F83520764572A4CC7_H_INCLUDED

WSI_BEGIN_HEADER_CXX WSI_BEGIN_NS(parser)

WSIDECL_PRIVATE_HEAD_CXX(PropertyTree);

WSICLASS(PropertyTree);

class PropertyTree
: public cxx::Object<>
{
    WSIDECL_PRIVATE_CXX(PropertyTree);
    WSIDECL_NOCOPY(PropertyTree);
    
public:

    typedef enum 
	{ 
		FORMAT_XML, 
		FORMAT_JSON, 
		FORMAT_INI, 
		FORMAT_INFO,
	} FormatType;
    
public:
    PropertyTree();
    ~PropertyTree();
    
public:
    
    //! clear tree.
    void clear();
    
    //! load from string.
    bool load(core::string const&, FormatType);
    
};

WSI_END_NS WSI_END_HEADER_CXX

# endif