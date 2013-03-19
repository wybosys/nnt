
# ifndef __WSI_PARSER_CSS_8E42B79793F04C70A69EF5C887666BCA_H_INCLUDED
# define __WSI_PARSER_CSS_8E42B79793F04C70A69EF5C887666BCA_H_INCLUDED

WSI_BEGIN_HEADER_CXX

WSI_BEGIN_NS(css)

class Attr;
class Tag;
class Class;
class Object;

typedef core::multimap<core::string, Attr*> attributes_type;
typedef core::map<core::string, Class*> classes_type;
typedef core::map<core::string, Object*> objects_type;

class Attr
: public RefObject
{
public:
    
    Attr()
    : empty(false)
    {
        PASS;
    }
    
    //! name of attr.
    core::string name;
    
    //! value of attr.
    core::string value;
    
    //! is empty. default is false.
    bool empty;
    
};

class Base
: public RefObject
{
public:
    
    //! attributes.
    attributes_type attributes;
    
    //! name of element.
    core::string name;
    
    Base()
    {
        PASS;
    }

	virtual ~Base()
	{
		clear();
	}

	void clear()
	{
		core::clear_drop(attributes);
	}
};

class Class
: public Base
{
public:
    
    Class()
    {
        
    }
    
    virtual ~Class()
    {
        clear();
    }
    
    void clear()
    {
        Base::clear();
        core::clear_drop(classes);
    }
    
    //! subclasses.
    classes_type classes;
    
};

WSI_END_NS

WSICLASS(CSSParser);
WSIDECL_PRIVATE_HEAD_CXX(CSSParser);

class CSSParser
{
    WSIDECL_NOCOPY(CSSParser);
    WSIDECL_PRIVATE_CXX(CSSParser);
    
public:
    CSSParser();
    ~CSSParser();
    
public:

	//! parse string.
    bool parse(core::string const&);
  
	//! get classes.
	css::classes_type const& classes() const;

	//! get attributes.
	css::attributes_type const& attributes() const;

};

WSI_END_HEADER_CXX

# endif