
# ifndef __NNT_OBJECT_77794445A92C40C1ACCA7F19B1EF88E9_H_INCLUDED
# define __NNT_OBJECT_77794445A92C40C1ACCA7F19B1EF88E9_H_INCLUDED

# ifdef NNT_CXX

# include <stack>
# include <map>
# include "../TL/Exception+NNT.h"

NNT_BEGIN_HEADER_CXX

# define NNTDECL_INSTANCE_STACK(cls) \
protected: \
cls() {}

NNTCLASS(Object);
NNTCLASS(RefObject);

class Object
{
public:
    
    Object();
	~Object();
    
    //! must override in subclass.
    void Destroy();
    
    //! func types.
    typedef void (Object::*func_destroy)();
    typedef void (Object::*func_simple)();
    typedef void (Object::*func_callback)(void*);
    
# ifdef NNT_DEBUG
	static long __global_object_counter;
# endif

};

class VirObject
//: public Object
{
public:
    
    VirObject()
    {
        PASS;
    }
    
    virtual ~VirObject()
    {
        PASS;
    }
    
};

class RefObject
: public Object
{
public:
    
    RefObject()
    : _reference_count(1)
    {
        PASS;
    }
    
    virtual ~RefObject()
    {
        PASS;
    }
    
    virtual bool drop() const
    {
        if (--_reference_count == 0)
        {
            delete this;
            return true;
        }
        return false;
    }
    
    virtual void grab() const
    {
        ++_reference_count;
    }
    
protected:
    
    void _check_destroy()
    {
# ifdef NNT_DEBUG
        if (_reference_count)
            throw exception::earlydrop();
# endif
    }
    
    mutable int _reference_count;
    
};

typedef RefObject IObject;

template <typename T>
inline_impl void destroy(T* obj)
{
    delete obj;
}

template <>
inline_impl void destroy<RefObject>(RefObject* obj)
{
    safe_drop(obj);
}

class AnyObject
{
protected:
    
    AnyObject()
    {
        PASS;
    }
    
public:
    
    bool operator == (void const* ptr) const
    {
        return this == ptr;
    }
    
    template <typename T>
    bool operator == (T const& r) const
    {
        return this == &r;
    }
    
    operator void* () const
    {
        return (void*)this;
    }
    
    template <typename T>
    operator T* () const
    {
        return (T*)(void*)this;
    }
    
    template <typename T>
    operator T& () const
    {
        return *(T*)(void*)this;
    }
    
};

template <typename objT>
class auto_ref
{
    typedef auto_ref<objT> self_type;
    
public:
    
    typedef objT value_type;
    
    auto_ref()
    : _obj(NULL)
    {
        PASS;
    }
    
    auto_ref(self_type& r)
    : _obj(NULL)
    {
        reset(r._obj);
    }
    
    auto_ref(value_type* r)
    : _obj(NULL)
    {
        reset(r);
    }
    
    ~auto_ref()
    {
        safe_drop(_obj);
    }
    
    operator value_type* () const
    {
        return (value_type*)_obj;
    }

    operator value_type& () const
    {
        return *(value_type*)_obj;
    }
    
    value_type* operator -> () const
    {
        return (value_type*)_obj;
    }
    
    self_type& operator = (self_type& r)
    {
        reset(r._obj);
        return *this;
    }
    
    value_type& operator * () const
    {
        return *(value_type*)_obj;
    }
    
    value_type& operator () () const
    {
        return *(value_type*)_obj;
    }
    
    void reset(value_type* r)
    {
        safe_drop(_obj);
        _obj = r;
        safe_grab(_obj);
    }
    
    static self_type Instance()
    {
        return self_type();
    }
    
protected:
    
    value_type* _obj;
    
};

template <typename objT>
class use
{
public:

    typedef objT value_type;

    use(value_type* obj = NULL)
        : _obj(obj)
    {
        PASS;
    }

    use(void const* obj)
        : _obj((value_type*)obj)
    {
        PASS;
    }

    use(value_type const* obj)
        : _obj((value_type*)obj)
    {
        PASS;
    }

    use(value_type& obj)
        : _obj(&obj)
    {
        PASS;
    }

    use(value_type const& obj)
        : _obj((value_type*)&obj)
    {
        PASS;
    }

    operator value_type& ()
    {
        return *_obj;
    }

    operator value_type const& () const
    {
        return *_obj;
    }

    operator value_type* ()
    {
        return _obj;
    }

    operator value_type const* () const
    {
        return _obj;
    }

    value_type* operator -> ()
    {
        return _obj;
    }

    value_type const* operator -> () const
    {
        return _obj;
    }

protected:

    objT* _obj;

};

template <typename objT>
class instance_fly
{
public:

    typedef objT value_type;

    instance_fly()
    {
        _obj = new value_type;
    }

    operator value_type& ()
    {
        return *_obj;
    }

    operator value_type const& () const
    {
        return *_obj;
    }

    operator value_type* ()
    {
        return _obj;
    }

    operator value_type const* () const
    {
        return _obj;
    }

    value_type* operator -> ()
    {
        return _obj;
    }

    value_type const* operator -> () const
    {
        return _obj;
    }

protected:

    value_type* _obj;
};

template <typename objT>
class instance_ref
: public auto_ref<objT>
{
    
    typedef auto_ref<objT> super;

    instance_ref(instance_ref const&);
    
public:
    
    typedef objT value_type;
    
    instance_ref()
		: super(NULL)
    {
        this->_obj = new value_type;
    }

    instance_ref(objT* ptr)
      : super(NULL)
    {
	this->_obj = ptr;
    }
    
};

template <class ObjectT>
class StrongObjectStore
{
public:
    typedef ::std::stack<ObjectT*> values_type;
	typedef ::std::map< ::std::string, values_type> store_type;
    
	StrongObjectStore()
	{
        PASS;
	}
    
	~StrongObjectStore()
	{
		clear();
	}
    
	void clear()
	{
		for (typename_ store_type::iterator iter = store.begin(); iter != store.end(); ++iter)
		{
			values_type& values = iter->second;
			while (values.size())
			{
				ObjectT* obj = values.top();
				obj->drop();
				values.pop();
			}
		}
		store.clear();
	}
    
	void set(char const* name, void* __obj)
	{
		ObjectT* obj = (ObjectT*)__obj;
		typename_ store_type::iterator found = store.find(name);
		if (found == store.end())
		{
			values_type vals;
			vals.push(obj);
			store.insert(std::make_pair(name, vals));			
			obj->grab();
		}
		else
		{
			values_type& vals = found->second;
			ObjectT* top = vals.top();
			vals.pop();
			vals.push(obj);
			obj->grab();
			top->drop();
		}
	}
    
    void push(char const* name, void* __obj) 
    {
        ObjectT* obj = (ObjectT*)__obj;
		typename_ store_type::iterator found = store.find(name);
		if (found == store.end())
		{
			values_type vals;
			vals.push(obj);
			store.insert(std::make_pair(name, vals));			
			obj->grab();
		}
		else
		{
			values_type& vals = found->second;
			vals.push(obj);
			obj->grab();
		}
    }
    
	void* find(char const* name) const
	{
		typename_ store_type::const_iterator found = store.find(name);
		if (found == store.end())
			return NULL;
		return (void*)found->second.top();
	}
    
    values_type const* all(char const* name) const
    {
        typename_ store_type::const_iterator found = store.find(name);
		if (found == store.end())
			return NULL;
        return found->second;
    }
    
    bool exist(char const* name, void* obj) const
    {
        typename_ store_type::const_iterator found = store.find(name);
        if (found == store.end())
            return false;
        values_type tmp = found->second;
        while (tmp.size())
            if (tmp.top() == obj)
                return true;
            else
                tmp.pop();
        return false;
    }
    
	void pop(char const* name)
	{
		typename_ store_type::iterator iter = store.find(name);
		if (iter == store.end())
			return;
		ObjectT *top = iter->second.top();
		iter->second.pop();
		top->drop();
	}
    
protected:	    
	store_type store;
};

template <class ObjectT>
class WeakObjectStore
{
public:
    typedef std::stack<ObjectT*> values_type;
	typedef std::map<std::string, values_type> store_type;
    
	WeakObjectStore()
	{
        PASS;
	}
    
	~WeakObjectStore()
	{
		clear();
	}
    
	void clear()
	{
		store.clear();
	}
    
	void set(char const* name, void* __obj)
	{
		ObjectT* obj = (ObjectT*)__obj;
		typename_ store_type::iterator found = store.find(name);
		if (found == store.end())
		{
			values_type vals;
			vals.push(obj);
			store.insert(std::make_pair(name, vals));			
		}
		else
		{
			values_type& vals = found->second;
			//ObjectT* top = vals.top();
			vals.pop();
			vals.push(obj);
		}
	}
    
    void push(char const* name, void* __obj)
    {
        ObjectT* obj = (ObjectT*)__obj;
		typename_ store_type::iterator found = store.find(name);
		if (found == store.end())
		{
			values_type vals;
			vals.push(obj);
			store.insert(std::make_pair(name, vals));			
		}
		else
		{
			values_type& vals = found->second;
			vals.push(obj);
		} 
    }
    
	void* find(char const* name) const
	{
		typename_ store_type::const_iterator found = store.find(name);
		if (found == store.end())
			return NULL;
		return (void*)found->second.top();
	}
    
    values_type const* all(char const* name) const
    {
        typename_ store_type::const_iterator found = store.find(name);
		if (found == store.end())
			return NULL;
        return &found->second;
    }
    
    bool exist(char const* name, void* obj) const
    {
        typename_ store_type::const_iterator found = store.find(name);
        if (found == store.end())
            return false;
        values_type tmp = found->second;
        while (tmp.size())
            if (tmp.top() == obj)
                return true;
            else
                tmp.pop();
        return false;
    }
    
	void pop(char const* name)
	{
		typename_ store_type::iterator iter = store.find(name);
		if (iter == store.end())
			return;
		iter->second.pop();
	}
    
protected:	
	store_type store;
};

NNT_END_HEADER_CXX

# endif

# include "Event+NNT.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

# define NNTOBJECT_DECL \
NNTObjectAttachStrong *_store; \
NNTObjectAttach *_attach; \
NNTEvent *_event;

# define NNTOBJECT_PROP \
@property (nonatomic, retain) NNTObjectAttachStrong *_store; \
@property (nonatomic, retain) NNTObjectAttach *_attach; \
@property (nonatomic, retain) NNTEvent *_event; \
- (void)initSignals;

# define NNTOBJECT_DEALLOC \
zero_release(_attach); \
zero_release(_store); \
zero_release(_event);

# define NNTOBJECT_IMPL_NOSIGNALS \
NNTOBJECT_SYN; \
- (NNTObjectAttachStrong*)_store { \
@synchronized(self) { if (_store == nil) { \
_store = [[NNTObjectAttachStrong alloc] init]; \
}} \
return _store; \
} \
- (NNTObjectAttach*)_attach { \
@synchronized(self) { if (_attach == nil) { \
_attach = [[NNTObjectAttach alloc] init]; \
}} \
return _attach; \
} \
- (NNTEvent*)_event { \
@synchronized(self) { if (_event == nil) { \
_event = [[NNTEvent alloc] init]; \
[self initSignals]; \
}} \
return _event; \
}

# define NNTOBJECT_IMPL \
NNTOBJECT_SYN; \
- (NNTObjectAttachStrong*)_store { \
@synchronized(self) { if (_store == nil) { \
_store = [[NNTObjectAttachStrong alloc] init]; \
}} \
return _store; \
} \
- (NNTObjectAttach*)_attach { \
@synchronized(self) { if (_attach == nil) { \
_attach = [[NNTObjectAttach alloc] init]; \
}} \
return _attach; \
} \
- (NNTEvent*)_event { \
@synchronized(self) { if (_event == nil) { \
_event = [[NNTEvent alloc] init]; \
[self initSignals]; \
}} \
return _event; \
} \
- (void)initSignals {}
# define NNTOBJECT_SYN \
@synthesize _store, _attach, _event;

# define NNTEVENT_BEGIN \
- (void)initSignals { \
[super initSignals];

# define NNTEVENT_END \
}

# define NNTEVENT_SIGNAL(signal) [self._event _register_signal:signal];
# define NNTEVENT_SIGNAL_SLOT(signal, slot) [self._event _register_signal:signal sel:@selector(slot) obj:self];

@protocol NSHash

//! get uid.
- (NSString*)uniqueIdentify;

@end

@interface NNTWeakReference : NSObject {
    id obj;
}

@property (nonatomic, assign) id obj;

- (id)initWith:(NSObject*)obj;

//! create a weak reference object.
+ (NNTWeakReference*)weakWith:(NSObject*)obj;

@end

@interface NNTObjectAttachNull : NSObject {
    NSMutableDictionary* storePushPop;
}

@property (nonatomic, retain) NSMutableDictionary *storePushPop;

//! push & pop object
- (void)push:(id)key obj:(id)obj;
- (id)pop:(id)key;
- (id)pop:(id)key null:(id)null;
- (id)find:(id)key;
- (id)find:(id)key null:(id)null;
- (void)set:(id)key obj:(id)obj;
- (id)swap:(id)key obj:(id)obj;
- (usize)count:(id)key;
- (usize)count;

//! use by inherit class.
- (id)pack:(id)obj;
- (id)unpack:(id)obj;
- (id)get:(id)obj;

@end

@interface NNTObjectAttachWeak : NNTObjectAttachNull {
}
@end

@interface NNTObjectAttachStrong : NNTObjectAttachNull {
}
@end

typedef NNTObjectAttachWeak NNTObjectAttach;

# pragma mark NNTObject

@protocol NNTObject <NSObject>

- (void)lock;
- (void)unlock;
- (BOOL)tryLock;

@end

@interface NNTObject : NSObject <NNTObject> {
    NNTOBJECT_DECL;
    
    @private
    id _lock;
    id _block;
    
}

NNTOBJECT_PROP;

//! for arc mode, will call while dealloc.
- (void)fini;

//! lock
- (void)lock;
- (void)unlock;
- (BOOL)tryLock;

//! block.
- (void)block;
- (void)unblock;

//! cluster for json process.
+ (NSString*)json_encode:(NSObject*)obj;
+ (NSDictionary*)json_decode:(NSString*)str;

//! cluster for base64.
+ (NSData*)base64_encode:(NSData*)data;
+ (NSData*)base64_decode:(NSData*)data;

//! run loop.
- (BOOL)loopOnce;

@end

//! cluster for json process.
NNT_EXTERN NSString* json_encode_object(NSObject*);
NNT_EXTERN NSDictionary* json_decode_string(NSString*);

//! cluster for base64.
NNT_EXTERN NSData* base64_encode_data(NSData*);
NNT_EXTERN NSData* base64_decode_data(NSData*);

# define selectorAsObj(arg) [NSObjectSel objectWithSel:@selector(arg)]

@interface NSObjectSel : NSObject {
    SEL selector;
}

@property (nonatomic, assign) SEL selector;

+ (NSObjectSel*)objectWithSel:(SEL)sel;

@end

@interface NSPointer : NSObject {
    void* addr;
}

//! address of pointer.
@property (nonatomic, assign) void* addr;

//! init with pointer.
- (id)initWithAddr:(void*)addr;

//! instance with pointer.
+ (id)pointerWithAddr:(void*)addr;

//! core type.
- (uint)coreType;

//! object.
- (void*)object;

@end

# define pointerAsObj(obj) [NSPointer pointerWithAddr:obj]

extern void ObjectInit();

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX_OBJC

# define NNTIMPL_SINGLETON(cls) ::nnt::AutoReleaseObj<cls> __gs_singleton_##cls; \
+ (cls*)getInstance { return __gs_singleton_##cls.getInstance(); }

# define NNTSINGLETON_INIT() - (void) instanceInit

# endif

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

# define NNTDECL_SINGLETON(cls) + (cls*)getInstance;

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

# include "../TL/String+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cxx)

template <bool val>
class bool_object
{
public:
    
    operator bool() const
    {
        return val;
    }
    
};

# define NNTDECL_BOOLOBJECT(t, f) \
const ::nnt::cxx::bool_object<true> t = ::nnt::cxx::bool_object<true>(); \
const ::nnt::cxx::bool_object<false> f = ::nnt::cxx::bool_object<false>();

# define extend_(cls) ::nnt::cxx::Class< cls >

template <typename SelfT>
class Class
: public SelfT
{
protected:
	typedef SelfT super;
    typedef Class class_type;
};

# define NNTDECL_SIGNALS_SLOTS virtual void init_signals();
# define NNTDECL_SIGNALS_BEGIN(cls, sup) void cls::init_signals() { sup::init_signals();
# define NNTDECL_SIGNALS_END }
# define NNT_SIGNAL(sig) this->register_signal(sig);

# define NNTMPL_SIGNALS_BEGIN(supercls) void init_signals() { supercls::init_signals();
# define NNTMPL_SIGNALS_END }

typedef Event< ::nnt::RefObject > event_type;
typedef event_type::event_func event_func;
typedef event_type::event_pure event_pure;
typedef event_type::eventobj_t eventobj_t;

NNT_EXTERN eventobj_t null_eventobj;

# define _cxxaction(func) (::nnt::cxx::event_func)&func
# define _cbaction(func) (::nnt::event_pure)func

# ifdef NNT_PURE_CXX

#   define _action _cxxaction

# else

# ifdef NNT_OBJC

#   define _cxxobjc_action(func) (::nnt::cxx::event_func)&func##_cxxobjc_mainthread
#   define cxxobjc_action(func) \
void func(::nnt::cxx::eventobj_t&); \
void func##_cxxobjc_mainthread(::nnt::cxx::eventobj_t& evt) { \
NNT_MAINTHREAD( \
autocollect; \
::nnt::core::down_const(this)->func(::nnt::core::down_const(evt)); \
); \
}

# endif // objc

# endif // pure cxx

# define OBJECT_TPL_DECL template <class BaseT>
# define OBJECT_TPL_IMPL BaseT

template <class BaseT = ::nnt::RefObject >
class Object
: public Class<BaseT>
{
    NNTDECL_NOCOPY(Object);
    
protected:

	typedef Object<BaseT> self_type;
    
public:
    
	Object();
	virtual ~Object();
    
    //! type for member slot.
	typedef void (self_type::*member_func)(void*);
    
    //! type for attach & store.
	typedef StrongObjectStore< RefObject > store_type;
	typedef WeakObjectStore< RefObject > attach_type;
    
public:
        
    //! register signal.
	virtual void register_signal(signal_t const&);
    
    //! connect signal to slot.
    virtual event_type::slot_t* connect(signal_t const& sig, event_func func, void* tag);
	virtual event_type::slot_t* connect(signal_t const& sig, event_pure func);
    
    //! redirect signal.
    virtual event_type::slot_t* redirect(signal_t const& sig, signal_t const& sigto, RefObject*);
    
    //! disconnect.
    virtual void disconnect(void*);
    virtual void disconnect(signal_t const&, event_func, void*);
    virtual void disconnect(signal_t const&, void*);
    
    //! block a signal.
    virtual void block(signal_t const&);
    
    //! unblock a signal.
    virtual void unblock(signal_t const&);
    
    //! exist.
    virtual bool exist_signal(signal_t const&) const;
    
    //! emit signal.
	virtual void emit(signal_t const&);
    virtual void emit(signal_t const&, eventobj_t& evtobj, void* sender);
	virtual void emit(signal_t const&, eventobj_t& evtobj);
    virtual void emit(signal_t const&, eventobj_t const& evtobj);

    //! signals init.
	virtual void init_signals();
    
    //! get event object.
	virtual event_type* getEvent();
    
    //! store a object, will grab its reference count.
	void store_set(char const* name, void* obj);
    void store_push(char const* name, void* obj);
    
    //! find a object in store.
	void* store_find(char const* name);
    
    //! pop a object from store.
	void store_pop(char const* name);
    
    //! store a object, will remain its reference count.
	void attach_set(char const* name, void* obj);
    void attach_push(char const* name, void* obj);
    
    //! find a object in attach.
	void* attach_find(char const* name);
    
    //! pop a object from attach store.
	void attach_pop(char const* name);
    
    //! get attach & store.
    attach_type const& attachs() const;
    store_type const& stores() const;
    
    //! to string.
    virtual core::string to_string() const;
    
protected:

    //! event.
	event_type *_event;
    
    //! store.
	store_type *_store;
    
    //! attach.
	attach_type *_attach;
    
};

# ifdef NNT_GCC

template <typename objT>
class Autolock
{
public:

	Autolock(objT* obj)
		: _obj(obj)
	{
		_obj->lock();
	}

	~Autolock()
	{
		_obj->unlock();
	}

protected:

	objT* _obj;

};

# define NNTMACRO_AUTOLOCK(obj) ::nnt::cxx::Autolock<__typeof(obj)> __autolock_##__LINE__##_obj(&obj);

# else

class Autolock
{
public:

    class Object
    {
    public:
        typedef void (Object::*func_type)();
    };

    template <typename T>
    Autolock(T& obj)
        : _obj(&obj)
    {
        obj.lock();
        _unlock = (Object::func_type)&T::unlock;
    }

    ~Autolock()
    {
        (((Object*)_obj)->*_unlock)();
    }

protected:

    void* _obj;
    Object::func_type _unlock;

};

# define NNTMACRO_AUTOLOCK(obj) Autolock __autolock_##__LINE__##_obj(obj);

# endif

template <typename mtxT>
class Lockable
{
public:
    
    typedef mtxT mutex_type;
    
    Lockable()
    : _locked(0)
    {
        PASS;
    }
    
    ~Lockable()
    {
        if (is_locked())
            _mtx.unlock();
    }
    
    void lock()
    {
        _mtx.lock();
        ++_locked;
    }
    
    void unlock()
    {
        _mtx.unlock();
        --_locked;
    }
    
    bool is_locked() const
    {
        return _locked > 0;
    }
    
protected:
    
    mutex_type _mtx;
    int _locked;
    
};

# ifdef NNT_PURE_CXX
typedef Object<> NNTObject;
# endif

# ifndef release_ref
#   define release_ref(obj) { if (obj) { if (obj->drop()) obj = 0; } }
# endif

template <class lT, class rT>
inline_impl void refobj_set(lT*& l, rT*& r)
{
	if (r) r->grab();
	if (l) l->drop();
	l = r;
}

OBJECT_TPL_DECL
template_impl Object<OBJECT_TPL_IMPL>::Object()
: _event(NULL), _store(NULL), _attach(NULL)
{
	PASS;
}

OBJECT_TPL_DECL
template_impl Object<OBJECT_TPL_IMPL>::~Object()
{
    safe_delete(_event);
    safe_delete(_store);
    safe_delete(_attach);
}

OBJECT_TPL_DECL
template_impl event_type* Object<OBJECT_TPL_IMPL>::getEvent()
{
	if (_event == NULL) 
    { 
        _event = new event_type(); 
        this->init_signals(); 
    }
	return _event;
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::register_signal(signal_t const& sig)
{	
	this->getEvent()->register_signal(sig);
}

OBJECT_TPL_DECL
template_impl event_type::slot_t*
Object<OBJECT_TPL_IMPL>::connect(signal_t const& sig, event_func act, void* tgt)
{
	return this->getEvent()->connect(sig, (Object<> *)tgt, act);
}

OBJECT_TPL_DECL
template_impl event_type::slot_t* 
Object<OBJECT_TPL_IMPL>::connect(signal_t const& sig, event_pure func)
{
	return this->getEvent()->connect(sig, func);
}

OBJECT_TPL_DECL
template_impl event_type::slot_t*
Object<OBJECT_TPL_IMPL>::redirect(signal_t const& sig, signal_t const& sigto, RefObject *tgt)
{
    return this->getEvent()->redirect(sig, sigto, tgt);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::disconnect(void* tgt)
{
    this->getEvent()->disconnect((Object<> *)tgt);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::disconnect(signal_t const& sig, event_func func, void* tgt)
{
    this->getEvent()->disconnect(sig, (Object<> *)tgt, func);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::disconnect(signal_t const& sig, void* tgt)
{
    this->getEvent()->disconnect(sig, (Object<> *)tgt);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::block(signal_t const& sig)
{
    this->getEvent()->block(sig);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::unblock(signal_t const& sig)
{
    this->getEvent()->unblock(sig);
}

OBJECT_TPL_DECL
template_impl bool Object<OBJECT_TPL_IMPL>::exist_signal(signal_t const& sig) const
{
    return (const_cast<self_type*>(this))->getEvent()->exist(sig);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::emit(signal_t const& sig)
{
    eventobj_t evt;
	this->getEvent()->emit(sig, evt, this);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::emit(signal_t const& sig, eventobj_t& obj)
{
	this->getEvent()->emit(sig, obj, this);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::emit(signal_t const& sig, eventobj_t const& obj)
{
	this->getEvent()->emit(sig, (eventobj_t&)obj, this);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::emit(signal_t const& sig, eventobj_t& obj, void* sender)
{
	this->getEvent()->emit(sig, obj, sender);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::init_signals()
{
	PASS;
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::store_set(char const* name, void* obj)
{
	if (_store == NULL) 
        _store = new store_type();
	_store->set(name, obj);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::store_push(char const* name, void* obj)
{
	if (_store == NULL) 
        _store = new store_type();
	_store->push(name, obj);
}

OBJECT_TPL_DECL
template_impl void* Object<OBJECT_TPL_IMPL>::store_find(char const* name)
{
	if (_store == NULL) 
        return NULL;
	return _store->find(name);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::store_pop(char const* name)
{
	if (_store == NULL) 
        return;
	_store->pop(name);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::attach_set(char const* name, void* obj)
{
	if (_attach == NULL) 
        _attach = new attach_type();
	_attach->set(name, obj);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::attach_push(char const* name, void* obj)
{
	if (_attach == NULL) 
        _attach = new attach_type();
	_attach->push(name, obj);
}

OBJECT_TPL_DECL
template_impl void* Object<OBJECT_TPL_IMPL>::attach_find(char const* name)
{
	if (_attach == NULL) 
        return NULL;
	return _attach->find(name);
}

OBJECT_TPL_DECL
template_impl void Object<OBJECT_TPL_IMPL>::attach_pop(char const* name)
{
	if (_attach == NULL) 
        return;
    _attach->pop(name);
}

OBJECT_TPL_DECL
template_impl typename Object<OBJECT_TPL_IMPL>::attach_type const& Object<OBJECT_TPL_IMPL>::attachs() const
{
    if (_attach == NULL) {
        static attach_type null_attachs;
        return null_attachs;
    }    
    return *_attach;
}

OBJECT_TPL_DECL
template_impl typename Object<OBJECT_TPL_IMPL>::store_type const& Object<OBJECT_TPL_IMPL>::stores() const
{
    if (_store == NULL) {
        static store_type null_stores;
        return null_stores;
    }
    return *_store;
}

OBJECT_TPL_DECL
template_impl core::string Object<OBJECT_TPL_IMPL>::to_string() const
{
    return core::null_string;
}

template <class BaseT = ::nnt::RefObject >
class AutoFreeObject
: public Object<BaseT>
{
public:
	AutoFreeObject()
    : data(NULL)
	{
        PASS;
	}
    
	AutoFreeObject(size_t sz)
	{
		data = ::malloc(sz);
	}
    
	virtual ~AutoFreeObject()
	{
		this->free();
	}
    
	void* malloc(size_t sz)
	{
		if (data) 
			::free(data);
		data = ::malloc(sz);
		return data;
	}
    
	void free()
	{
		if (data) 
			::free(data);
		data = NULL;
	}
    
	void* data;
};

template <class StrT>
class String
: public Object<>
{
public:
    
	String(StrT const& s)
    : str(s)
	{
        PASS;
	}
    
	StrT& operator* ()
	{
		return str;
	}
    
	StrT const& operator * () const
	{
		return str;
	}
    
public:
    
	StrT str;
    
};

template <typename ValT>
class Number
: public Object <>
{
public:
    
	Number(ValT v)
    : num(v)
	{
	}
    
	ValT& operator* ()
	{
		return num;
	}
    
	ValT operator * () const
	{
		return num;
	}
    
	operator ValT () const
	{
		return num;
	}
    
	operator ValT& ()
	{
		return num;
	}
    
public:
    
	ValT num;
    
};

typedef Number<int> NumberInt;
typedef Number<uint> NumberUInt;
typedef Number<float> NumberFloat;
typedef Number<double> NumberDouble;
typedef Number<char> NumberChar;
typedef Number<long> NumberLong;
typedef Number<ulong> NumberULong;
typedef Number<longlong> NumberLongLong;
typedef Number<ulonglong> NumberULongLong;
typedef Number<short> NumberShort;
typedef Number<ushort> NumberUShort;

template <typename T>
class ObjectSingleton
: public Object<>
{
public:
    
    static T& getInstance()
    {
        if(!m_pInstance) {
            m_pInstance = new T;
            m_pInstance->__instance__();
        }
        return *m_pInstance;
    }
    
    T* operator -> () const
    {
        return (T*)m_pInstance;
    }
    
protected:
    
    ObjectSingleton() {}    
    ~ObjectSingleton() {}
    
    void __instance__() {}
    
private:
    
    ObjectSingleton(ObjectSingleton const&);
    ObjectSingleton& operator=(ObjectSingleton const&);
    static T* m_pInstance;

};

template <class T> T* ObjectSingleton<T>::m_pInstance = NULL;

# if __clang_major__ < 3
# define _assign_ = (id)
# else
# define _assign_ =
# endif

// implement for other.

NNT_BEGIN_NS(impl)

NNTCLASS(TaskBackground);

class TaskBackground
	: public RefObject
{
public:

	TaskBackground();
	virtual ~TaskBackground();

	virtual void start();
	virtual void run() = 0;

};

template <typename objT, typename evtfuncT, typename eventT>
class BackgroundEmit
	: public TaskBackground
{
public:

	BackgroundEmit(objT* target, event_func func, eventT const& evt)
		: _target(target), _func(func), _event(evt)
	{
		PASS;
	}

	virtual void run()
	{
		(_target->*_func)(_event);
	}

protected:

	objT* _target;
	event_func _func;
	eventT _event;

};

NNT_END_NS

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::_do_emit(signal_t const& sig, eventobj_t& evt, void* sender) const
{
    // find signal.
	typename_ store_type::const_iterator found = _store.find(sig);
	if (found == _store.end())
		return;
    
    // if is block.
    typename_ block_type::const_iterator found_block = std::find(_block.begin(), _block.end(), sig);
    if (found_block != _block.end())
        return;
    
	slots_type const& slots = found->second;
	for (typename_ slots_type::const_iterator iter = slots.begin(); 
         iter != slots.end();
         ++iter)
	{        
        eventobj_t *slot = *iter;
        
        if (slot->shotcount != -1)
        {
            if (slot->shotcount == 0)
                continue;
            --slot->shotcount;
        }
        
		evt.sender = sender;
		evt.signal = sig;
        
        // begin invoke slot.
		if (slot->action)
		{
			object_t* obj = slot->target;
			event_func func = slot->action;
			if (slot->background) 
			{
				typedef impl::BackgroundEmit<object_t, event_func, eventobj_t> background_emit;
				instance_ref<background_emit> task(new background_emit(obj, func, evt));
				task->start();
			}
			else
			{
				(obj->*func)(evt);
			}
		}
		else if (slot->pure_action)
		{
			(*slot->pure_action)(evt);
		}        
        else if (slot->redirect_signal.size())
        {
            typedef ::nnt::cxx::Object<object_t> origin_object;
            origin_object* obj = dynamic_cast<origin_object*>(slot->target);
            obj->emit(slot->redirect_signal, evt, sender);
        }
        // end invoke.
        
        // if veto.
        if (evt.veto)
            break;
	}
}

NNT_END_NS

NNT_BEGIN_NS(ntl)

/*
template <typename objT>
cxx::Autolock<objT> autolock(objT* obj)
{
	return cxx::Autolock<objT>(obj);
}
*/

NNTDECL_BOOLOBJECT(enable, disable);
NNTDECL_BOOLOBJECT(on, off);
NNTDECL_BOOLOBJECT(active, inactive);
NNTDECL_BOOLOBJECT(use, unuse);

NNT_END_NS

typedef void* (*func_new)();

template <typename T>
class Instanceable
{
public:
    
    typedef void* (*func_new)();
    typedef T* (*func_typenew)();
    
    static T* New()
    {
        return new T;
    }
    
};

template <typename enumT>
enumT enum_or(enumT l, enumT r)
{
    return enumT((uint)l | (uint)r);
}

template <typename enumT>
enumT enum_and(enumT l, enumT r)
{
    return enumT((uint)l & (uint)r);
}

template <typename enumT>
enumT enum_xor(enumT l, enumT r)
{
    return enumT((uint)l ^ (uint)r);
}

template <typename enumT = uint>
class Enum
{
    typedef Enum<enumT> self_type;
    
public:
    
    Enum()
    : _val((enumT)0)
    {
        PASS;
    }
    
    Enum(enumT val)
    : _val(val)
    {
        PASS;
    }
    
    operator enumT () const
    {
        return _val;
    }
    
    self_type operator | (enumT const& r) const
    {
        return enum_or(_val, r);
    }
    
    self_type& operator |= (enumT const& r)
    {
        _val = enum_or(_val, r);
        return *this;
    }
    
    self_type operator & (enumT const& r) const
    {
        return enum_and(_val, r);
    }
    
    self_type& operator &= (enumT const& r)
    {
        _val = enum_and(_val, r);
        return *this;
    }
    
    self_type operator ^ (enumT const& r) const
    {
        return enum_xor(_val, r);
    }
    
    self_type& operator ^= (enumT const& r)
    {
        _val = enum_xor(_val, r);
        return *this;
    }
    
    bool operator == (enumT const& r) const
    {
        return _val == r;
    }
    
    bool operator != (enumT const& r) const
    {
        return _val != r;
    }
    
    bool mark(enumT r) const
    {
        return MASK_CHECK(r, _val);
    }
    
    void mask(enumT r)
    {
        MASK_SET(r, _val);
    }
    
    void unmask(enumT r)
    {
        MASK_UNSET(r, _val);
    }
    
protected:
    
    enumT _val;
    
};

NNT_END_HEADER_CXX

NNT_BEGIN_HEADER_C

NNTAPI(bool) Drop(::nnt::RefObject* obj);
NNTAPI(void) Grab(::nnt::RefObject* obj);

NNT_END_HEADER_C

# endif

# endif
