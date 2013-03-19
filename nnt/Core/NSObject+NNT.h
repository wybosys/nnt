
# ifndef __NNT_NSOBJECT_B11CBCF9F427478DBB592AB9D82FAC1E_H_INCLUDED
# define __NNT_NSOBJECT_B11CBCF9F427478DBB592AB9D82FAC1E_H_INCLUDED

# import "Event+NNT.h"

NNT_BEGIN_HEADER_OBJC

# ifndef _retain
# if __has_feature(objc_arc)
#   define _retain strong
# else
#   define _retain retain
# endif
# endif

# ifndef _assign
# if __has_feature(objc_arc_weak)
#   define _assign weak
# elif __has_feature(objc_arc)
#   define _assign unsafe_unretained
# else
#   define _assign assign
# endif
# endif

# ifdef NNT_DEBUG

NNT_EXTERN BOOL __gs_debug_attachstore_error_enable;

# define __gs_debug_attachstore_error_enable_set(val) __gs_debug_attachstore_error_enable = val;

# else

# define __gs_debug_attachstore_error_enable_set(val) {SPACE}

# endif

NNT_EXTERN dispatch_queue_t kQueueDefault;
NNT_EXTERN dispatch_queue_t kQueueSignalSlot;
NNT_EXTERN char const* DISPATCH_QUEUE_PRIORITY_SIGNALSLOT;

# define NNT_MAINTHREAD_BEGIN \
dispatch_sync(dispatch_get_main_queue(), ^{
# define NNT_MAINTHREAD_END });

# define NNT_MAINTHREAD_RUNNING \
(CFRunLoopGetMain() == CFRunLoopGetCurrent())

# define NNT_MAINTHREAD(exp) \
if (NNT_MAINTHREAD_RUNNING) \
{ exp; } \
else \
{ \
NNT_MAINTHREAD_BEGIN \
exp; \
NNT_MAINTHREAD_END \
}

@interface NSObject (NNT)

//! emit signal.
- (void)emit:(id)signal result:(id)result data:(void*)data;
- (void)emit:(id)signal result:(id)result;
- (void)emit:(id)signal data:(void*)data;
- (void)emit:(id)signal;

- (void)emit:(id)signal result:(id)result data:(void*)data sender:(void*)sender;
- (void)emit:(id)signal result:(id)result sender:(void*)sender;
- (void)emit:(id)signal data:(void*)data sender:(void*)sender;
- (void)emit:(id)signal sender:(void*)sender;

//! register signal.
- (void)register_signal:(id)signal;
- (void)register_signal:(id)signal sel:(SEL)sel obj:(id)obj;
- (void)register_signal:(id)signal sel:(SEL)sel obj:(id)obj delay:(real)delay;
- (void)register_signal:(id)signal sel:(SEL)sel;
- (void)register_signal:(id)signal sel:(SEL)sel delay:(real)delay;

//! connect signal with slot.
- (slot_t*)connect:(id)signal sel:(SEL)sel obj:(id)obj;
- (slot_t*)connect:(id)signal sel:(SEL)sel obj:(id)obj delay:(real)delay;
- (slot_t*)connect:(id)signal sel:(SEL)sel;
- (slot_t*)connect:(id)signal sel:(SEL)sel delay:(real)delay;
- (slot_t*)connect:(id)signal sig:(NSString*)sig obj:(id)obj;
- (slot_t*)connect:(id)signal sig:(NSString*)sig obj:(id)obj delay:(real)delay;

//! find slot.
- (BOOL)is_connected:(id)signal sel:(SEL)sel obj:(id)obj;

//! enable signals.
- (void)enable_signals:(BOOL)val;

//! enable signal.
- (void)enable_signal:(id)signal val:(BOOL)val;

//! has signal.
- (BOOL)hasSignal:(id)sig;
- (NNTSignal*)find_signal:(id)signal;

//! set block signals/slots.
# ifdef NNT_BLOCKS

- (void)register_signal:(id)signal block:(void (^)(NNTEventObj*))block;
- (void)register_signal:(id)signal block:(void (^)(NNTEventObj*))block delay:(real)delay;

- (slot_t*)connect:(id)signal block:(void (^)(NNTEventObj*))block;
- (slot_t*)connect:(id)signal block:(void (^)(NNTEventObj*))block delay:(real)delay;

# endif

//! set cxx signals/slots.
# ifdef NNT_CXX

- (void)register_signal:(id)signal action:(::nnt::objevent_func)action target:(::nnt::Object*)target;
- (void)register_signal:(id)signal action:(::nnt::objevent_func)action target:(::nnt::Object*)target delay:(real)delay;

- (slot_t*)connect:(id)signal action:(::nnt::objevent_func)action target:(::nnt::Object*)target;
- (slot_t*)connect:(id)signal action:(::nnt::objevent_func)action target:(::nnt::Object*)target delay:(real)delay;

- (void)disconnect_target:(::nnt::Object*)target;
- (void)disconnect_target:(::nnt::Object *)target signal:(id)signal;

# endif

- (slot_t*)connect:(id)signal func:(void (*)(NNTEventObj*))func;
- (slot_t*)connect:(id)signal func:(void (*)(NNTEventObj*))func delay:(real)delay;

//! disconnect signal from slot.
- (void)disconnect:(id)signal sel:(SEL)sel obj:(id)obj;
- (void)disconnect:(id)signal obj:(id)obj;
- (void)disconnect:(id)obj;
- (void)disconnect_signal:(id)signal;
- (void)disconnect_all;

//! if support signal slot pattern.
- (BOOL)supportSignalSlot;

//! redirect signal to other.
- (void)redirect:(NSObject*)obj;
- (void)disredirect:(NSObject*)obj;

//! store a object with key. will increase object reference count.
- (void) storePush:  (id)key obj:(id)obj;
- (void) storeSet:   (id)key obj:(id)obj;
- (id)   storeSwap:  (id)key obj:(id)obj;
- (id)   storePop:   (id)key;
- (id)   storePop:   (id)key null:(id)null;
- (id)   storeFind:  (id)key;
- (id)   storeFind:  (id)key null:(id)null;

//! if support store pattern.
- (BOOL)supportStore;

//! attach a object with key. no change to object reference count.
- (void) attachPush:  (id)key obj:(id)obj;
- (void) attachSet:   (id)key obj:(id)obj;
- (id)   attachSwap:  (id)key obj:(id)obj;
- (id)   attachPop:   (id)key;
- (id)   attachPop:   (id)key null:(id)null;
- (id)   attachFind:  (id)key;
- (id)   attachFind:  (id)key null:(id)null;

//! if support attach pattern.
- (BOOL)supportAttach;

//! refobj set.
+ (void)refobjSet:(id*)left obj:(id*)right;
+ (void)refobjSet:(id*)left ref:(id)right;
+ (void)refobjCopy:(id*)left obj:(id*)right;
+ (void)refobjCopy:(id*)left ref:(id)right;

//! consign, like [[obj retain] autorelease].
- (id)consign;

//! get core type, @see CoreTypes in coretypes.h
- (uint)coreType;

//! get value type.
- (NNTValueType)valueType;

//! get safe object.
- (void*)object;

# ifdef NNT_CXX

//! some cxx function.
- (void)performCxxObjectFunctionWrapper:(id)obj;

# endif

@end

NNT_EXTERN id class_callMethod(Class cls, SEL sel, ...);
NNT_EXTERN BOOL class_existMethod(Class cls, SEL sel);
NNT_EXTERN void class_swizzleMethod(Class c, SEL origs, SEL news);
NNT_EXTERN IMP class_getImplementation(Class cls, SEL sel);
NNT_EXTERN id objc_getPropertyValue(id obj, char const* name);
NNT_EXTERN bool objc_setPropertyValue(id value, id obj, char const* name);

typedef struct _objc_swizzle_t
{
    Class cls;
    IMP default_impl;
    IMP next_impl;
} objc_swizzle_t;

NNTDECL_CATEGORY(NSObject, NNT);

# ifdef NNT_CXX

# define reference_retain assign

@interface NSRefObject : NSObject {
    ::nnt::RefObject const* _cxxobj;
}

@property (nonatomic, reference_retain) ::nnt::RefObject const* object;

- (id)initWith:(::nnt::RefObject const*)object;
+ (id)objectWith:(::nnt::RefObject const*)object;
- (void)setObject:(::nnt::RefObject const*)obj grab:(BOOL)grab;

@end

# endif

# if __clang_major__ < 3
//! do not insert 'return' between NNT_AUTORELEASEPOOL_BEGIN and NNT_AUTORELEASEPOOL_END, if will cause memory leak and unknown error.
#   define NNT_AUTORELEASEPOOL_BEGIN { NSAutoreleasePool *__tmp_autoreleasepool = [[NSAutoreleasePool alloc] init];
#   define NNT_AUTORELEASEPOOL_END   [__tmp_autoreleasepool drain]; }
#   define safe_alloc(cls) (cls*)[cls alloc]
# else
#   define NNT_AUTORELEASEPOOL_BEGIN @autoreleasepool {
#   define NNT_AUTORELEASEPOOL_END   }
#   define safe_alloc(cls) [cls alloc]
# endif

# define NNT_AUTORELEASE(exp) \
NNT_AUTORELEASEPOOL_BEGIN \
exp; \
NNT_AUTORELEASEPOOL_END

# define NNT_SYNCHRONIZED(obj) @synchronized(obj) {
# define NNT_SYNCHRONIZED_END  }

# ifdef NNT_CXX

@interface _cxxobject_perform_wrapper : NSObject {
    ::nnt::Object* _object;
    void* _params;
    ::nnt::Object::func_callback _function;
}

@property (nonatomic, assign) ::nnt::Object* object;
@property (nonatomic, assign) void * params;
@property (nonatomic, assign) ::nnt::Object::func_callback function;

@end

# define NNT_OBJCXX_WRAPPER(cls) \
_nnt_objcxx_wrapper_##cls

@protocol NNT_OBJCXX_WRAPPER(object)
<NSObject>
@property (nonatomic, assign) ::nnt::IObject* _cxxobj;
@end

# else

# define NNTDECL_OBJCXX_WRAPPER(cls) \
NNTDECL_OBJCXX_WRAPPER_BEGIN(cls) \
NNTDECL_OBJCXX_WRAPPER_END

# define NNTDECL_OBJCXX_WRAPPER_BEGIN(cls)
# define NNTDECL_OBJCXX_WRAPPER_END

# define NNTIMPL_OBJCXX_WRAPPER(cls) \
NNTIMPL_OBJCXX_WRAPPER_BEGIN(cls) \
NNTIMPL_OBJCXX_WRAPPER_END

# define NNTIMPL_OBJCXX_WRAPPER_BEGIN(cls)
# define NNTIMPL_OBJCXX_WRAPPER_END

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# define objc_cbbegin \
autocollect; \
NNT_MAINTHREAD_BEGIN

# define objc_cbend \
NNT_MAINTHREAD_END

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class auto_id
{
    auto_id(auto_id const&);
    auto_id& operator = (id);
    auto_id& operator = (auto_id const&);
    
public:
    
    explicit auto_id(id o)
    : obj(o)
    {
        PASS;
    }
    
    ~auto_id()
    {
        [obj release];
    }
    
    operator id () const
    {
        return (id)obj;
    }
    
    id obj;
};

class share_id
{
public:
    
    explicit share_id(id o)
    : obj(o)
    {
        [obj retain];
    }
    
    share_id(share_id const& r)
    : obj((id)r.obj)
    {
        [obj retain];
    }
    
    ~share_id()
    {
        [obj release];
    }
    
    share_id& operator = (share_id const& r)
    {
        obj = [(id)r.obj retain];
        return *this;
    }
    
    operator id () const
    {
        return obj;
    }
    
    id obj;
};

enum
{
    THREAD_CURRENT = 0,
    THREAD_MAIN = 1,
    THREAD_BACKGROUND = 2,
};

typedef struct { enum { THREAD_MODE = THREAD_MAIN }; } thread_main_t;
typedef struct { enum { THREAD_MODE = THREAD_BACKGROUND }; } thread_background_t;
typedef struct { enum { THREAD_MODE = THREAD_CURRENT }; } thread_same_t;

const thread_main_t thread_main = thread_main_t();
const thread_background_t thread_background = thread_background_t();
const thread_same_t thread_same = thread_same_t();

template <typename ObjT>
class AutoLockObject
{
public:
    
    AutoLockObject(ObjT* obj)
    : _obj(obj)
    {
        [_obj lock];
    }
    
    ~AutoLockObject()
    {
        [_obj unlock];
    }
    
protected:
    
    ObjT* _obj;
    
};

# define NNTMACRO_LOCKOBJ(obj) ::nnt::ns::AutoLockObject<__typeof__(*obj)> NNTAUTO_NAME(obj);

class AutoreleasePool
{
public:
    
    AutoreleasePool()
    {
        pool = [[NSAutoreleasePool alloc] init];
    }
    
    ~AutoreleasePool()
    {
        [pool drain];
    }
    
    NSAutoreleasePool* pool;
    
};

# define autocollect ::nnt::ns::AutoreleasePool NNTAUTO_NAME;

class Null
{
public:
    
    bool operator == (id obj) const
    {
        if (obj == nil)
            return true;
        if ([obj isKindOfClass:[NSNull class]])
            return true;
        return false;
    }
    
    bool operator == (void* ptr) const
    {
        return ptr == NULL;
    }
    
    bool operator == (void const* ptr) const
    {
        return ptr == NULL;
    }
    
};

static const Null null = Null();

template <typename T>
class WeakStore
{
public:
    
    WeakStore(T* r)
    : objc(r)
    {
        PASS;
    }
    
    void push(id key, id obj)
    {
        [objc attachPush:key obj:obj];
    }
    
    void set(id key, id obj)
    {
        [objc attachSet:key obj:obj];
    }
    
    id swap(id key, id obj)
    {
        return [objc attachSwap:key obj:obj];
    }
    
    id pop(id key, id null = nil)
    {
        return [objc attachPop:key null:null];
    }
    
    id find(id key, id null = nil) const
    {
        return [objc attachFind:key null:null];
    }
    
    T* objc;
};

template <typename T>
class StrongStore
{
public:
    
    StrongStore(T* r)
    : objc(r)
    {
        PASS;
    }
    
    void push(id key, id obj)
    {
        [objc storePush:key obj:obj];
    }
    
    void set(id key, id obj)
    {
        [objc storeSet:key obj:obj];
    }
    
    id swap(id key, id obj)
    {
        return [objc storeSwap:key obj:obj];
    }
    
    id pop(id key, id null = nil)
    {
        return [objc storePop:key null:null];
    }
    
    id find(id key, id null = nil) const
    {
        return [objc storeFind:key null:null];
    }
    
    T* objc;
};

# define _perform_action(clsfunc) (owner_function_type)&clsfunc

template <typename T = ::NNTObject,
typename baseT = ::nnt::Object >
class Object
: public baseT
{
    typedef Object<T, baseT> self_type;
    
public:
    
    typedef T objc_type;
    typedef void (self_type::*owner_function_type)(void*);
    typedef ns::WeakStore<objc_type> weakstore_type;
    typedef ns::StrongStore<objc_type> strongstore_type;
    typedef WeakObjectStore<void> cxxweakstore_type;
    typedef StrongObjectStore<RefObject> cxxstrongstore_type;
    
    Object()
    : _needrelease(true)
    {
        _self = [[objc_type alloc] init];
    }
    
    Object(objc_type* r)
    : _self(r),
    _needrelease(true)
    {
        [_self retain];
    }
    
    Object(self_type const& r)
    : _self(r._self),
    _needrelease(true)
    {
        [_self retain];
    }
    
    ~Object()
    {
        if (_needrelease)
            zero_release(_self);
    }
    
    self_type& operator = (self_type const& r)
    {
        _release();
        _self = r._self;
        [_self retain];
        return *this;
    }
    
    self_type& operator = (objc_type* obj)
    {
        _release();
        _self = obj;
        [_self retain];
        return *this;
    }
    
    objc_type* operator * () const
    {
        return (objc_type*)_self;
    }
    
    objc_type* operator () () const
    {
        return (objc_type*)_self;
    }
    
    operator objc_type* () const
    {
        return (objc_type*)_self;
    }
    
    objc_type* nsobject() const
    {
        return (objc_type*)_self;
    }
    
    baseT* cxxobject() const
    {
        return (baseT*)this;
    }
    
    /*
    operator self_type* () const
    {
        return (self_type*)this;
    }
    
    operator baseT* () const
    {
        return (baseT*)this;
    }
     */
    
    static Class getClass()
    {
        return [objc_type class];
    }
    
    bool is_null() const
    {
        return _self == nil;
    }
    
    void set_null()
    {
        zero_release(_self);
    }
    
    bool is_equal(id r) const
    {
        return [this->_self isEqual:r] == YES;
    }
    
    NSString* tr(NSString* str) const
    {
        return NSLocalizedString(str, SPACE);
    }
    
    void renew()
    {
        this->_release();
        this->_self = [[NSString alloc] init];
    }
    
    void renew(objc_type* r)
    {
        this->_release();
        this->_self = [r retain];
    }
    
    template <typename impT>
    impT clone() const
    {
        objc_type* obj = [this->_self copy];
        impT ret;
        ret.renew((typename impT::objc_type*)obj);
        [obj release];
        return ret;
    }
    
    void perform(owner_function_type func, NSTimeInterval ti = 0, void* params = NULL)
    {
        _cxxobject_perform_wrapper* wrapper = [[_cxxobject_perform_wrapper alloc] init];
        wrapper.object = (::nnt::Object*)this;
        wrapper.function = (::nnt::Object::func_callback)func;
        wrapper.params = params;
        
        if (ti) {
            NNT_MAINTHREAD(
                           [this->_self performSelector:@selector(performCxxObjectFunctionWrapper:) withObject:wrapper afterDelay:ti]
                           );
        } else {
            [this->_self performSelector:@selector(performCxxObjectFunctionWrapper:) withObject:wrapper];
        }
        
        [wrapper release];
    }
        
    void perform(owner_function_type func, thread_main_t const& thdobj, void* params = NULL, bool wait = true)
    {
        _cxxobject_perform_wrapper* wrapper = [[_cxxobject_perform_wrapper alloc] init];
        wrapper.object = (::nnt::Object*)this;
        wrapper.function = (::nnt::Object::func_callback)(func);
        wrapper.params = params;        
        [this->_self performSelectorOnMainThread:@selector(performCxxObjectFunctionWrapper:) withObject:wrapper waitUntilDone:wait];
        [wrapper release];
    }
    
    void perform(owner_function_type func, thread_background_t const& thdobj, void* params = NULL, bool wait = true)
    {
        _cxxobject_perform_wrapper* wrapper = [[_cxxobject_perform_wrapper alloc] init];
        wrapper.object = (::nnt::Object*)this;
        wrapper.function = (::nnt::Object::func_callback)(func);
        wrapper.params = params;
        [this->_self performSelectorInBackground:@selector(performCxxObjectFunctionWrapper:) withObject:wrapper];
        [wrapper release];
    }
    
    void perform(owner_function_type func, thread_same_t const& thdobj, void* params = NULL, bool wait = true)
    {
        _cxxobject_perform_wrapper* wrapper = [[_cxxobject_perform_wrapper alloc] init];
        wrapper.object = (::nnt::Object*)this;
        wrapper.function = (::nnt::Object::func_callback)(func);
        wrapper.params = params;
        [this->_self performSelector:@selector(performCxxObjectFunctionWrapper:) withObject:wrapper];
        [wrapper release];
    }
    
public:
    
    void emit(id signal, id result = 0, void* data = 0)
    {
        [_self emit:signal result:result data:data sender:this];
    }
    
    void register_signal(id signal)
    {
        [_self register_signal:signal];
    }
    
    self_type& signal(id signal)
    {
        if (false == has_signal(signal))
            register_signal(signal);
        return *this;
    }
    
    ns::Slot connect(id signal, SEL sel, id obj = nil, real delay = 0)
    {
        if (obj == nil)
            obj = _self;
        slot_t* slot = [_self connect:signal sel:sel obj:obj delay:delay];
        slot.fixsender = YES;
        slot.sender = this;
        return slot;
    }
    
    ns::Slot connect(id signal, id signal2, id obj = nil, real delay = 0)
    {
        if (obj == nil)
            obj = _self;
        slot_t* slot = [_self connect:signal sig:signal2 obj:obj delay:delay];
        slot.fixsender = YES;
        slot.sender = this;
        return slot;
    }
    
    bool is_connected(id signal, SEL sel, id obj = nil)
    {
        if (obj == nil)
            obj = _self;
        return [_self is_connected:signal sel:sel obj:obj];
    }
    
    void enable_signals(bool val = true)
    {
        [_self enable_signals:val];
    }
    
    void enable_signal(id sig, bool val = true)
    {
        [_self enable_signal:sig val:val];
    }
    
    bool has_signal(id sig) const
    {
        return [_self hasSignal:sig];
    }
    
    //! set block signals/slots.
# ifdef NNT_BLOCKS
    
    void register_signal(id sig, void (^block)(NNTEventObj*), real delay = 0)
    {
        [_self register_signal:sig block:block delay:delay];
    }
    
    ns::Slot connect(id sig, void (^block)(NNTEventObj*), real delay = 0)
    {
        slot_t* slot = [_self connect:sig block:block delay:delay];
        slot.sender = this;
        slot.fixsender = YES;
        return slot;
    }
    
# endif
        
    void register_signal(id sig, objevent_func act, ::nnt::Object* tgt, real delay = 0)
    {
        slot_t* slot = [_self register_signal:sig action:act target:tgt delay:delay];
        slot.sender = this;
        slot.fixsender = YES;
    }
    
    ns::Slot connect(id sig, objevent_func act, ::nnt::Object* tgt = NULL, real delay = 0)
    {
        if (tgt == NULL)
            tgt = this;
        slot_t* slot = [_self connect:sig action:act target:tgt delay:delay];
        slot.sender = this;
        slot.fixsender = YES;
        return slot;
    }
        
    template <typename objT>
    ns::Slot connect(id sig, objevent_func act, objT& tgt, real delay = 0)
    {
        return connect(sig, act, (::nnt::Object*)tgt.cxxobject(), delay);
    }
    
    void disconnect(::nnt::Object* tgt)
    {
        [_self disconnect_target:tgt];
    }
    
    void disconnect(id sig, ::nnt::Object* tgt)
    {
        [_self disconnect_target:tgt signal:sig];
    }
    
    ns::Slot connect(id sig, void (*act)(NNTEventObj*), real delay = 0)
    {
        slot_t* slot = [_self connect:sig func:act delay:delay];
        slot.sender = this;
        slot.fixsender = YES;
        return slot;
    }
    
    void disconnect(id sig, SEL sel, id obj)
    {
        [_self disconnect:sig sel:sel obj:obj];
    }
    
    void disconnect(id sig, id obj)
    {
        [_self disconnect:sig obj:obj];
    }
    
    void disconnect(id obj)
    {
        [_self disconnect:obj];
    }
    
    void disconnect_signal(id sig)
    {
        [_self disconnect_signal:sig];
    }
    
    bool support_signalslot() const
    {
        return [_self supportSignalSlot];
    }
    
    void redirect(id obj)
    {
        [_self redirect:obj];
    }
    
    void disredirect(id obj)
    {
        [_self disredirect:obj];
    }
    
    self_type& consign()
    {
        [_self consign];
        return *this;
    }
    
    weakstore_type& nsattach()
    {
        if (_attach.get() == NULL)
            _attach.reset(new weakstore_type(_self));
        return *_attach;
    }
    
    weakstore_type const& nsattach() const
    {
        return *_attach;
    }
    
    strongstore_type& nsstore()
    {
        if (_strong.get() == NULL)
            _strong.reset(new strongstore_type(_self));
        return *_strong;
    }
    
    strongstore_type const& nsstore() const
    {
        return *_strong;;
    }
    
    cxxweakstore_type& attach()
    {
        if (_cxxattach.get() == NULL)
            _cxxattach.reset(new cxxweakstore_type);
        return *_cxxattach;
    }
    
    cxxweakstore_type const& attach() const
    {
        return *_cxxattach;
    }
    
    cxxstrongstore_type& store()
    {
        if (_cxxstrong.get() == NULL)
            _cxxstrong.reset(new cxxstrongstore_type);
        return *_cxxstrong;
    }
    
    cxxstrongstore_type const& store() const
    {
        return *_cxxstrong;
    }
    
    void replace(objc_type* obj)
    {
        _set(obj);
    }
    
protected:
    
    objc_type* _self;
    ::std::auto_ptr<weakstore_type> _attach;
    ::std::auto_ptr<strongstore_type> _strong;
    ::std::auto_ptr<cxxweakstore_type> _cxxattach;
    ::std::auto_ptr<cxxstrongstore_type> _cxxstrong;
    bool _needrelease;
    
    void _set(objc_type* obj)
    {
        _release();
        _self = obj;
        [_self retain];
    }
    
    void _release()
    {
        safe_release(_self);
    }
    
    void _retain()
    {
        [_self retain];
    }
    
    uint _reference_count()
    {
        return [_self retainCount];
    }
    
};

typedef Object < ::NNTObject, ::nnt::Object > SimpleObject;
typedef Object < ::NNTObject, ::nnt::RefObject > RefObject;

typedef struct {} property_writable;
typedef struct {} property_readonly;
typedef struct {} property_retain;
typedef struct {} property_copy;
typedef struct {} property_assign;

template <typename schemeT>
struct _scheme_traits
{
    enum { CANSET = YES };
};

template <>
struct _scheme_traits<property_readonly>
{
    enum { CANSET = NO };
};

typedef struct {} wrapper_type;

template <typename propT,
typename schemeT = property_writable,
BOOL SETABLE = _scheme_traits<schemeT>::CANSET
>
class class_property
{
public:
    
    typedef wrapper_type is_wrapper_type;
    
    class_property(id obj, char const* nm)
    : target(obj), name(nm)
    {
        PASS;
    }
    
    operator propT () const
    {
        return (propT)objc_getPropertyValue((id)target, name);
    }
    
    propT operator * () const
    {
        return (propT)objc_getPropertyValue((id)target, name);
    }
    
    propT operator () () const
    {
        return (propT)objc_getPropertyValue((id)target, name);
    }
    
    propT obj() const
    {
        return (propT)objc_getPropertyValue((id)target, name);
    }
    
    char const* name;
    id target;
    
};

template <typename propT, typename schemeT>
struct class_property_wrapper
{
    
    static propT instance(propT obj)
    {
        return obj;
    }
    
    static void release(propT obj)
    {
        PASS;
    }
    
};

template <typename propT>
struct class_property_wrapper <propT, property_assign>
{
 
    static propT instance(propT obj)
    {
        return obj;
    }
    
    static void release(propT obj)
    {
        PASS;
    }
    
};

template <typename propT>
struct class_property_wrapper <propT, property_copy>
{
    
    static propT instance(propT obj)
    {
        return [obj copy];
    }
    
    static void release(propT obj)
    {
        [obj release];
    }
    
};

template <typename propT>
struct class_property_wrapper <propT, property_retain>
{
    
    static propT instance(propT obj)
    {
        return [obj retain];
    }
    
    static void release(propT obj)
    {
        [obj release];
    }
    
};

template <typename propT, typename schemeT>
class class_property<propT, schemeT, YES>
: public class_property<propT, schemeT, NO>
{
    typedef class_property<propT, schemeT, YES> self_type;
    typedef class_property<propT, schemeT, NO> super;
    typedef class_property_wrapper<propT, schemeT> wrapper_type;
    
public:
    
    class_property(id obj, char const* nm)
    : super(obj, nm)
    {
        PASS;
    }
    
    self_type& set(propT r)
    {
        propT obj = objc_getPropertyValue(this->target, this->name);
        wrapper_type::release(obj);
        obj = wrapper_type::instance(r);
        if (!objc_setPropertyValue(obj, this->target, this->name))
            dthrow_msg(@"obj-c", @"failed to set property value.");
        return *this;
    }
    
    self_type& operator = (propT r)
    {
        return set(r);
    }
    
    self_type& operator = (self_type const& r)
    {
        *this = *r;
        return *this;
    }
    
};
    
# define NNTDECL_SELECTOR(selr, type) \
type selr() { return [this->_self selr]; }
    
# define NNTDECL_PROPERTY(prop, type, scheme) \
::nnt::ns::class_property<type, scheme> prop () const \
{ \
return ::nnt::ns::class_property<type, scheme>((id)this->_self, #prop); \
}
    
# define NNTDECL_PROPERTY_RETAIN(prop, type) \
NNTDECL_PROPERTY(prop, type, ::nnt::ns::property_retain)
    
# define NNTDECL_PROPERTY_ASSIGN(prop, type) \
NNTDECL_PROPERTY(prop, type, ::nnt::ns::property_assign)
    
# define NNTDECL_PROPERTY_READONLY(prop, type) \
NNTDECL_PROPERTY(prop, type, ::nnt::ns::property_readonly)
    
# define NNTDECL_PROPERTY_COPY(prop, type) \
NNTDECL_PROPERTY(prop, type, ::nnt::ns::property_copy)
    
# define NNTDECL_PROPERTY_ACCESS(prop, type) \
void set_##prop(type val) { this->_self.prop = val; } \
type prop() const { return this->_self.prop; }
    
# define NNTDECL_OBJCXX_WRAPPER(cls) \
NNTDECL_OBJCXX_WRAPPER_BEGIN(cls) \
NNTDECL_OBJCXX_WRAPPER_END
    
# define NNTDECL_OBJCXX_WRAPPER_BEGIN(cls) \
@interface NNT_OBJCXX_WRAPPER(cls) : cls <NNT_OBJCXX_WRAPPER(object)>
    
# define NNTDECL_OBJCXX_WRAPPER_END \
@end
    
# define NNTIMPL_OBJCXX_WRAPPER(cls) \
NNTIMPL_OBJCXX_WRAPPER_BEGIN(cls) \
NNTIMPL_OBJCXX_WRAPPER_END
    
# define NNTIMPL_OBJCXX_WRAPPER_BEGIN(cls) \
@implementation NNT_OBJCXX_WRAPPER(cls) \
@synthesize _cxxobj; \
- (void)dealloc { \
::nnt::destroy(self._cxxobj); \
[super dealloc]; }
    
# define NNTIMPL_OBJCXX_WRAPPER_END \
@end
    
NNT_BEGIN_NS(cxx)
    
class IObject
: public ::nnt::IObject
{
    
public:
    
};
    
template <typename objcT, typename interT = IObject >
class Object
    : public ns::Object<objcT, interT>
{
    typedef ns::Object<objcT, interT> super;
    
public:
    
    Object()
    {
        this->_self._cxxobj = this;
    }
    
    Object(id obj)
    : super(obj)
    {
        this->_self._cxxobj = this;
    }
    
    virtual ~Object()
    {
        this->_self._cxxobj = NULL;
    }
    
    void grab()
    {
        [this->_self retain];
    }
    
    bool drop() const
    {
        bool ret = this->_self.retainCount == 1;
        [this->_self release];
        return ret;
    }
    
    void Release()
    {
        safe_release(this->_self);
    }
    
protected:
    
    void _set(id obj)
    {
        this->_self = obj;
        this->_self._cxxobj = this;
    }
  
};
    
NNT_END_NS
    
NNT_END_NS

using ns::thread_main;
using ns::thread_background;
using ns::thread_same;

NNT_END_HEADER_CXX

# endif

# endif
