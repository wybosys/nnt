
# ifndef __XMPP_OBJECT_23471F075E784916A79A803749304BA1_H_INCLUDED
# define __XMPP_OBJECT_23471F075E784916A79A803749304BA1_H_INCLUDED

# include "../../Parser/XmlParser.h"

# define XMPP_HEADER_BEGIN \
NNT_BEGIN_HEADER_CXX \
NNT_BEGIN_NS(xmpp)

# define XMPP_HEADER_END \
NNT_END_NS \
NNT_END_HEADER_CXX

# define XMPP_BEGIN \
NNT_BEGIN_CXX \
NNT_BEGIN_NS(xmpp)

# define XMPP_END \
NNT_END_NS \
NNT_END_CXX

XMPP_HEADER_BEGIN

typedef parser::XmlNode xmlnode_t;
typedef parser::XmlAttribute xmlattr_t;

NNTCLASS(Object);

class Object
: public cxx::Object<>
{
    typedef cxx::Object<> super;
    
public:
    
    Object();
    ~Object();
    
public:
        
    //! get data from object.
    virtual bool save(core::data&) const;
    
    //! append self data to target node.
    virtual bool append(xmlnode_t*) const;
    
    //! load data from xml.
    virtual bool load(xmlnode_t const*);
    
};

NNTCLASS(StringObject);

class StringObject
: public Object
{
public:
    
    virtual bool save(core::data&) const;    
    virtual bool load(xmlnode_t const*);
    
    core::string str;
};

class FactoryObject
{
public:
    
    bool (*couldload)(xmlnode_t const*);
    xmpp::Object* (*instance)();
    
    bool operator == (FactoryObject const& r) const
    {
        return
        couldload == r.couldload &&
        instance == r.instance;
    }
    
};

class Client;

template <typename objT>
class ResponseObject
{
public:
    
    typedef struct {} response_object_empty_type;
    
    static xmpp::Object* New()
    {
        return new objT;
    }
    
    static bool couldload(xmlnode_t const*)
    {
        return false;
    }
    
    //! instance.
    virtual xmpp::Object* instance() const;
        
    //! callback while loaded.
    virtual void process(Client&);
    
    //! callback before save.
    virtual void update(Client const&);
    
    //! callback after send.
    virtual void complete(Client const&);
    
    //! static object for register and manager.
    static const FactoryObject FacObj;
	static const FactoryObject& GetFacObj()
	{
		return FacObj;
	}
  
};

template <typename objT>
const FactoryObject ResponseObject<objT>::FacObj = 
{
	objT::couldload,
	New
};

template <typename objT>
template_impl xmpp::Object* ResponseObject<objT>::instance() const
{
    return new objT;
}

template <typename objT>
template_impl void ResponseObject<objT>::process(Client&)
{
    PASS;
}

template <typename objT>
template_impl void ResponseObject<objT>::update(Client const&)
{
    PASS;
}

template <typename objT>
template_impl void ResponseObject<objT>::complete(Client const&)
{
    PASS;
}

template <typename implT, typename objT>
class ExtendObject
: public objT
{
public:
    
    static const FactoryObject FacObj;
    
    static xmpp::Object* New()
    {
        return new implT;
    }
    
    virtual xmpp::Object* instance() const
    {
        return new implT;
    }
    
};

template <typename implT, typename objT>
const FactoryObject ExtendObject<implT, objT>::FacObj = {
    implT::couldload,
    New
};

XMPP_HEADER_END

# endif
