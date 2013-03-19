
# ifndef __JUICE_OBJECT_3B2CBA84CE0543FCB09F01525DC319D8_H_INCLUDED
# define __JUICE_OBJECT_3B2CBA84CE0543FCB09F01525DC319D8_H_INCLUDED

# include "JuiceCore.hpp"

JUICE_BEGIN

JUICE_EXCEPTION(overflow_refcount);

typedef struct {} refable;

class Object
{   
    
public:
    
    typedef refable refable;
    
    static Object* New();    
    static void Destroy(Object*&);
    static Object* Reference(Object*&);
    static Object* Dereference(Object*&);
    
protected:
    
    Object() {}
    ~Object() {}
    
};

typedef Object* (*func_new)();
typedef void (*func_destroy)(Object*&);
typedef Object* (*func_ref)(Object*&);
typedef Object* (*func_deref)(Object*&);

struct object_wrapper
{
    Object* object;
    func_new fnew;
    func_destroy fdestroy;
    func_ref fref;
    func_deref fderef;
    
    operator Object* () const
    {
        return (Object*)object;
    }
    
    Object* operator * () const
    {
        return (Object*)object;
    }
    
};

template <typename implT>
class RefObject
: public Object
{
public:
    
    typedef implT class_type;
    
protected:
    
    RefObject()
    : _refcount(1)
    {
        PASS;
    }
    
    ~RefObject()
    {
# ifdef JUICE_DEBUG
        if (_refcount != 0)
            debug_throw(exception::overflow_refcount);
# endif
    }
        
public:
    
    class_type* drop()
    {
        if (--_refcount == 0)
        {
            delete (class_type*) this;
            return NULL;
        }
        return (class_type*) this;
    }
    
    class_type* grab()
    {
        ++_refcount;
        return (class_type*) this;
    }
    
    static class_type* New()
    {
        class_type* obj = new class_type();
        return obj;
    }
    
    static void Destroy(class_type*& obj)
    {
        obj->drop(); obj = NULL;
    }
    
    static class_type* Reference(class_type*& obj)
    {
        obj->grab();
        return obj;
    }
    
    static class_type* Dereference(class_type*& obj)
    {
        return obj->drop();
    }
    
protected:
    
    implT* _impl() const
    {
        return (implT*)this;
    }
    
    uint _refcount;
    
};

template <typename classT, typename setT = null_op>
class NNT_NOVTABLE Property
{
    typedef Property<classT> self_type;
    
public:
    
    Property()
    :_ptr(NULL)
    {
        PASS;
    }
    
    Property(classT* ptr)
    :_ptr(ptr)
    {
        if (_ptr)
            _ptr->grab();
    }
    
    ~Property()
    {
        if (_ptr)
        {
            _ptr->drop();
            _ptr = NULL;
        }
    }
    
    classT* operator -> ()
    {
        return _ptr;
    }
    
    classT const* operator -> () const
    {
        return _ptr;
    }
    
    self_type& operator = (classT* ptr)
    {
        if (_ptr)
        {
            _ptr->drop();
            _ptr = NULL;
        }
        if (ptr)
            _ptr = ptr->grab();
        
        setT()(this);
        
        return *this;
    }
    
    operator self_type* ()
    {
        return _ptr;
    }
    
    operator self_type const* ()
    {
        return _ptr;
    }
    
    bool operator == (classT const* ptr) const
    {
        return _ptr == ptr;
    }
    
protected:
    
    classT* _ptr;
    
};

template <typename classT>
class Assign
{
    typedef Assign<classT> self_type;
    
public:
    
    Assign()
    :_ptr(NULL)
    {
        PASS;
    }
    
    Assign(classT* ptr)
    :_ptr(ptr)
    {
        PASS;
    }
    
    classT* operator -> ()
    {
        return _ptr;
    }
    
    classT const* operator -> () const
    {
        return _ptr;
    }
    
    self_type& operator = (classT* ptr)
    {
        _ptr = ptr;
        return *this;
    }
    
    operator self_type* ()
    {
        return _ptr;
    }
    
    operator self_type const* ()
    {
        return _ptr;
    }
    
    bool operator == (classT const* ptr) const
    {
        return _ptr == ptr;
    }
    
protected:
    
    classT* _ptr;
    
};

typedef struct {} empty_type;

JUICE_END

# endif
