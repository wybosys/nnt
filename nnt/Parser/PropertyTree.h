
# ifndef __NNT_PARSER_PROPERTYTREE_DED17F38D1AF479F83520764572A4CC7_H_INCLUDED
# define __NNT_PARSER_PROPERTYTREE_DED17F38D1AF479F83520764572A4CC7_H_INCLUDED

NNT_BEGIN_HEADER_CXX NNT_BEGIN_NS(parser)

NNTDECL_PRIVATE_HEAD_CXX(PropertyTree);

NNTCLASS(PropertyTree);

class PropertyTree
: public cxx::Object<>
{
    NNTDECL_PRIVATE_CXX(PropertyTree);
    NNTDECL_NOCOPY(PropertyTree);
    
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

NNT_END_NS NNT_END_HEADER_CXX

# endif