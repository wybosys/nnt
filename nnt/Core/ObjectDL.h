
# ifndef __NNT_CORE_OBJECT_DESCRIBE_LAYER_6F1619FB1BA5482D842D3ED4E1362E55_H_INCLUDED
# define __NNT_CORE_OBJECT_DESCRIBE_LAYER_6F1619FB1BA5482D842D3ED4E1362E55_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(lang)

NNTCLASS(Object);
NNTCLASS(Method);
NNTCLASS(Field);
NNTCLASS(Class);
NNTCLASS(Namespace);

class Object
{
public:
    Object()
    : _refcnt(1)
    {
        PASS;
    }
    
    virtual ~Object()
    {
        PASS;
    }
    
public:
    void grab()
    {
        ++_refcnt;
    }
    
    void drop()
    {
        if (--_refcnt == 0)
            delete this;
    }
    
protected:
    int _refcnt;
};

class Field
: public Object
{
    NNTDECL_NOCOPY(Field);
    
public:
    Field()
    : cls(NULL)
    {
        PASS;
    }
    
    Field(core::string const& nm)
    : cls(NULL), name(nm)
    {
        PASS;
    }
    
    ~Field()
    {
        PASS;
    }
    
public:
    
    bool is_equal(Field const* fld) const
    {
        if (this == fld)
            return true;
        if (name != fld->name)
            return false;
        if (cls != fld->cls)
            return false;
        return true;
    }
    
    Field* clone() const
    {
        Field* ret = new Field;
        ret->cls = cls;
        ret->name = name;
        ret->value = value;
        return ret;
    }
    
    operator variant_t const& () const
    {
        return value;
    }
    
    operator variant_t& ()
    {
        return value;
    }
    
public:
    //! type.
    Class* cls;
    
    //! name of field.
    core::string name;
    
    //! value of field.
    variant_t value;
};

class Parameter
: public Field
{
public:
    
    Parameter(bool _opt = false)
    : Field(),
    optional(_opt)
    {
        PASS;
    }
    
    Parameter(core::string const& nm, bool _opt = false)
    : Field(nm),
    optional(_opt)
    {
        PASS;
    }
    
    bool is_equal(Parameter const* fld) const
    {
        if (this == fld || optional || fld->optional)
            return true;
        if (name != fld->name)
            return false;
        if (cls != fld->cls)
            return false;
        return true;
    }
    
    Parameter* clone() const
    {
        Parameter* ret = new Parameter;
        ret->cls = cls;
        ret->name = name;
        ret->value = value;
        ret->optional = optional;
        return ret;
    }
    
    bool optional;
};

class Method
: public Object
{
    NNTDECL_NOCOPY(Method);
    
public:
    Method()    
    : method(0)
    {
        PASS;
    }
    
    typedef core::map<core::string, Parameter*> params_type;    
    typedef core::map<core::string, Field*> returns_type;
    
    //! type for callback.
    //! @param 1st, parameters.
    //! @param 2nd, returns.
    //! @param 3rd, custom data pointer.
    typedef int (Object::*method_type)(params_type const&, returns_type&, void*);
    
    Method(core::string const& nm, method_type hdl)
    : method(hdl), name(nm)
    {
        PASS;
    }
    
    ~Method()
    {
        for (params_type::const_iterator each = params.begin();
             each != params.end();
             ++each)
        {
            each->second->drop();
        }
        
        for (returns_type::const_iterator each = returns.begin();
             each != returns.end();
             ++each)
        {
            each->second->drop();
        }
    }
    
    void clear_returns()
    {
        for (returns_type::const_iterator each = returns.begin();
             each != returns.end();
             ++each)
        {
            each->second->drop();
        }
        returns.clear();
    }
    
public:    
    
    bool is_equal(Method const* mtd) const
    {
        if (this == mtd)
            return true;
        if (name != mtd->name)
            return false;
        if (params.size() != mtd->params.size())
            return false;
        
        if (returns.size() && mtd->returns.size() && returns.size() == mtd->returns.size())
        {
             for (returns_type::const_iterator icur = returns.begin(), ides = mtd->returns.begin();
             icur != returns.end();
             ++icur, ++ides)
             {
                 if (icur->second->is_equal(ides->second) == false)
                     return false;
             }
        }
        else if (returns.size() && mtd->returns.size() && returns.size() != mtd->returns.size())
            return false;
        
        if (method && mtd->method && method != mtd->method)
            return false;
        
        for (params_type::const_iterator icur = params.begin(), ides = mtd->params.begin();
             icur != params.end();
             ++icur, ++ides)
        {
            if (icur->second->is_equal(ides->second) == false)
                return false;
        }
        
        return true;
    }
    
public:
    core::string name;    
    
    //typedef core::map<core::string, Field*> params_type;
    params_type params;
    
    //typedef params_type returns_type;
    returns_type returns;
    
    //typedef void (Object::*method_type)(params_type const&, returns_type&);
    method_type method;
};

class Class
: public Object
{
    NNTDECL_NOCOPY(Class);
    
public:
    Class()
    : instance(0)
    {
        PASS;
    }
    
    typedef core::map<core::string, Field*> fields_type;    
    typedef core::vector<Method*> methods_type;    
    typedef core::map<core::string, Class*> classes_type;    
    typedef Object* (*instance_type)();
    
    Class(core::string const& nm, instance_type hdl)
    : instance(hdl), name(nm)
    {
        PASS;
    }
    
    ~Class()
    {
        for (fields_type::iterator each = fields.begin();
             each != fields.end();
             ++each)
        {
            each->second->drop();
        }
        
        for (methods_type::iterator each = methods.begin();
             each != methods.end();
             ++each)
        {
            (*each)->drop();
        }
        
        for (classes_type::iterator each = classes.begin();
             each != classes.end();
             ++each)
        {
            each->second->drop();
        }

    }
    
public:
    
    bool could_instance(Class const* cls) const
    {
        if (name != cls->name)
            return false;
        if (fields.size() != cls->fields.size())
            return false;
        
        for (fields_type::const_iterator icur = fields.begin(), ides = cls->fields.begin();
             icur != fields.end();
             ++icur, ++ides)
        {
            if (icur->second->is_equal(ides->second) == false)
                return false;
        }
        
        return true;
    }
    
    bool is_equal(Class const* cls) const
    {        
        if (this == cls)
            return true;
        if (name != cls->name)
            return false;
        if (fields.size() != cls->fields.size())
            return false;
        if (methods.size() != cls->methods.size())
            return false;
        if (classes.size() != cls->classes.size())
            return false;
        
        for (fields_type::const_iterator icur = fields.begin(), ides = cls->fields.begin();
             icur != fields.end();
             ++icur, ++ides)
        {
            if (icur->second->is_equal(ides->second) == false)
                return false;
        }
        
        for (methods_type::const_iterator icur = methods.begin(), ides = cls->methods.begin();
             icur != methods.end();
             ++icur, ++ides)
        {
            if ((*icur)->is_equal(*ides) == false)
                return false;
        }
        
        for (classes_type::const_iterator icur = classes.begin(), ides = cls->classes.begin();
             icur != classes.end();
             ++icur, ++ides)
        {
            if (icur->second->is_equal(ides->second) == false)
                return false;
        }
        
        return true;
    }
    
public:
    //! name of method.
    core::string name;
    
    //typedef core::map<core::string, Field*> fields_type;
    fields_type fields;
    
    //typedef core::vector<Method*> methods_type;
    methods_type methods;
    
    //typedef core::map<core::string, Class*> classes_type;
    classes_type classes;
    
    //typedef Object* (*instance_type)();
    instance_type instance;
};

enum {
    INVOKE_SUCCESS        = 0,
    INVOKE_ERROR          = -1,
    CLASS_NOTFOUND        = -10000001,
    METHOD_NOTFOUND       = -10000002,
    INSTANCE_FAILED       = -10000003,
};

typedef uint INVOKE_STA;

//! get namespace.
NNTAPI(Namespace*) getNamespace(core::string const& = "");

//! add namespace.
NNTAPI(Namespace*) addNamespace(core::string const&);

//! instance a class's object in namespace.
NNTAPI(Object*) instanceObject(Namespace const*, Class const*);

//! find decl class.
NNTAPI(Class const*) findDeclClass(Namespace const*, Class const*);

//! invoke a class on object.
NNTAPI(INVOKE_STA) invokeClass(Object* obj, Class const* objcls, void*);
NNTAPI(INVOKE_STA) invokeClass(Object* obj, Class const* objcls, Class const* declclass, void*);

class Namespace
{
    friend class DLObject;
    friend Namespace* addNamespace(core::string const&);

    Namespace()
    {        
        PASS;
    }
    
public:
    
    ~Namespace()
    {
        for (fields_type::iterator each = fields.begin();
             each != fields.end();
             ++each)
        {
            each->second->drop();
        }
        
        for (methods_type::iterator each = methods.begin();
             each != methods.end();
             ++each)
        {
            (*each)->drop();
        }
        
        for (classes_type::iterator each = classes.begin();
             each != classes.end();
             ++each)
        {
            each->second->drop();
        }
    }
    
    core::string name;
    
    typedef core::map<core::string, Field*> fields_type;
    fields_type fields;
    
    typedef core::vector<Method*> methods_type;
    methods_type methods;
    
    typedef core::map<core::string, Class*> classes_type;
    classes_type classes;
};

NNT_BEGIN_NS(fp)

NNT_END_NS

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif