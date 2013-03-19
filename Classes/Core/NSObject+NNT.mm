
# import "Core.h"
# import "NSObject+NNT.h"
# import <objc/runtime.h>
# import "coretypes.h"

NNT_BEGIN_OBJC

# define USE_EXCEPTION 0
# if !USE_EXCEPTION
#   undef USE_EXCEPTION
# endif

@implementation NSObject (NNT)

- (void)emit:(NSString *)signal {
    [self emit:signal result:nil data:0];
}

- (void)emit:(id)signal result:(id)result {
    [self emit:signal result:result data:0];
}

- (void)emit:(id)signal data:(void*)data {
    [self emit:signal result:nil data:data];
}

- (void)emit:(NSString *)signal sender:(void*)sender {
    [self emit:signal result:nil data:0 sender:sender];
}

- (void)emit:(id)signal result:(id)result sender:(void*)sender {
    [self emit:signal result:result data:0 sender:sender];
}

- (void)emit:(id)signal data:(void*)data sender:(void*)sender {
    [self emit:signal result:nil data:data sender:sender];
}

# ifdef NNT_DEBUG

BOOL __gs_debug_attachstore_error_enable = YES;

# ifdef USE_EXCEPTION

#   define NNTNS_ERR \
else if (__gs_debug_attachstore_error_enable) { \
NSString *msg = [NSString stringWithFormat:@"this [%@] class isn't inherit from NNTObject or use NNTOBJECT_ macros", [NSString stringWithUTF8String:object_getClassName(self)]]; \
@throw [NSException exceptionWithName:@"::nnt::nsobject" reason:msg userInfo:nil]; \
}

# else

#   define NNTNS_ERR \
else if (__gs_debug_attachstore_error_enable) { \
NSString *msg = [NSString stringWithFormat:@"this [%@] class isn't inherit from NNTObject or use NNTOBJECT_ macros", [NSString stringWithUTF8String:object_getClassName(self)]]; \
trace_msg(msg); \
}

# endif

# else

#   define NNTNS_ERR SPACE

# endif

#   define THROW_MSG(msg)  @throw [NSException exceptionWithName:@"::nnt::ns::object" reason:msg userInfo:nil];

- (BOOL)supportSignalSlot {
    if ([self respondsToSelector:@selector(_event)]) {
        id obj = [self performSelector:@selector(_event) withObject:nil];
        if ([obj isKindOfClass:[NNTEvent class]]) {
            return YES;
        }
    }
    return NO;
}

- (void)emit:(NSString *)signal result:(id)result data:(void*)data {
    if ([self respondsToSelector:@selector(_event)]) {
        id obj = [self performSelector:@selector(_event) withObject:nil];
        if ([obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)obj;
            [event _emit:signal sender:self result:result data:data];
        } NNTNS_ERR;
    }  NNTNS_ERR;
}

- (void)emit:(NSString *)signal result:(id)result data:(void*)data sender:(void*)sender {
    if ([self respondsToSelector:@selector(_event)]) {
        id obj = [self performSelector:@selector(_event) withObject:nil];
        if ([obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)obj;
            [event _emit:signal sender:sender result:result data:data];
        } NNTNS_ERR;
    }  NNTNS_ERR;
}

- (void)register_signal:(NSString *)signal {
    if ([self respondsToSelector:@selector(_event)]) {
        id obj = [self performSelector:@selector(_event) withObject:nil];
        if ([obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)obj;
            [event _register_signal:signal];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)register_signal:(NSString*)signal sel:(SEL)sel obj:(id)obj {
    [self register_signal:signal];
    [self connect:signal sel:sel obj:obj];
}

- (void)register_signal:(NSString*)signal sel:(SEL)sel obj:(id)obj delay:(real)delay {
    [self register_signal:signal];
    [self connect:signal sel:sel obj:obj delay:delay];
}

- (void)register_signal:(NSString*)signal sel:(SEL)sel {
    [self register_signal:signal];
    [self connect:signal sel:sel];
}

- (void)register_signal:(NSString*)signal sel:(SEL)sel delay:(real)delay {
    [self register_signal:signal];
    [self connect:signal sel:sel delay:delay];
}

- (slot_t*)connect:(NSString *)signal sel:(SEL)sel obj:(id)obj delay:(real)delay {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal sel:sel obj:obj delay:delay];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;
}

- (slot_t*)connect:(NSString *)signal sel:(SEL)sel obj:(id)obj {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal sel:sel obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;
}

- (slot_t*)connect:(NSString*)signal sig:(NSString*)sig obj:(id)obj {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal sig:sig obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;
}

- (slot_t*)connect:(NSString*)signal sig:(NSString*)sig obj:(id)obj delay:(real)delay {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal sig:sig obj:obj delay:delay];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;
}

- (slot_t*)connect:(NSString *)signal sel:(SEL)sel {
    return [self connect:signal sel:sel obj:self];
}

- (slot_t*)connect:(NSString *)signal sel:(SEL)sel delay:(real)delay {
    return [self connect:signal sel:sel obj:self delay:delay];
}

- (BOOL)is_connected:(id)signal sel:(SEL)sel obj:(id)obj {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            return [event _find_connect:signal sel:sel obj:obj] != nil;
        }
    }
    return NO;
}

- (void)enable_signals:(BOOL)val {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            event.enable = val;
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)enable_signal:(id)signal val:(BOOL)val {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            [event _enable:signal tog:val];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

# ifdef NNT_BLOCKS

- (void)register_signal:(NSString*)signal block:(void (^)(NNTEventObj*))block {
    [self register_signal:signal];
    [self connect:signal block:block];
}

- (void)register_signal:(NSString*)signal block:(void (^)(NNTEventObj*))block delay:(real)delay {
    [self register_signal:signal];
    [self connect:signal block:block delay:delay];
}

- (slot_t*)connect:(NSString*)signal block:(void (^)(NNTEventObj*))block {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal block:block];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;
}

- (slot_t*)connect:(NSString*)signal block:(void (^)(NNTEventObj*))block delay:(real)delay {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal block:block delay:delay];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;
}

# endif

# ifdef NNT_CXX

- (void)register_signal:(id)signal action:(::nnt::objevent_func)action target:(::nnt::Object*)target {
    [self register_signal:signal];
    [self connect:signal action:action target:target];
}

- (void)register_signal:(id)signal action:(::nnt::objevent_func)action target:(::nnt::Object*)target delay:(real)delay {
    [self register_signal:signal];
    [self connect:signal action:action target:target delay:delay];
}

- (slot_t*)connect:(id)signal action:(::nnt::objevent_func)action target:(::nnt::Object*)target {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal action:action target:target];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;
}

- (slot_t*)connect:(id)signal action:(::nnt::objevent_func)action target:(::nnt::Object*)target delay:(real)delay {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal action:action target:target delay:delay];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;   
}

# endif

- (BOOL)hasSignal:(id)sig {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            return [event _hasSignal:sig];
        }
    }
    return NO;
}

- (NNTSignal*)find_signal:(id)sig {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            return [event _find_signal:sig];
        }
    }
    return nil;
}

- (slot_t*)connect:(NSString*)signal func:(void (*)(NNTEventObj*))func {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal func:func];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;
}

- (slot_t*)connect:(NSString*)signal func:(void (*)(NNTEventObj*))func delay:(real)delay {
    slot_t* ret = nil;
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            ret = [event _connect:signal func:func delay:delay];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return ret;
}

- (void)disconnect:(NSString *)signal sel:(SEL)sel obj:(id)obj {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            [event _disconnect:signal sel:sel obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)disconnect:(NSString *)signal obj:(id)obj {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            [event _disconnect:signal obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)disconnect:(id)obj {
    // disconnect signal & slot.
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            [event _disconnect:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
    
    // dis redirect.
    [self disredirect:obj];
}

- (void)disconnect_signal:(id)signal {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            [event _disconnect_signal:signal];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)disconnect_target:(::nnt::Object*)target {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            [event _disconnect_target:target];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)disconnect_all {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            [event _disconnect_all];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)disconnect_target:(::nnt::Object *)target signal:(id)signal {
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            NNTEvent *event = (NNTEvent*)evt_obj;
            [event _disconnect_target:target signal:signal];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)redirect:(NSObject*)obj {
    NNTEvent *evt_self = nil, *evt_target = nil;
    
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            evt_self = evt_obj;
        } NNTNS_ERR;
    } NNTNS_ERR;
    
    if ([obj respondsToSelector:@selector(_event)]) {
        id evt_obj = [obj performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            evt_target = evt_obj;
        } NNTNS_ERR;
    } NNTNS_ERR;
    
    if (evt_self && evt_target) {
        [evt_self _redirect:evt_target];
    }
}

- (void)disredirect:(NSObject*)obj {
    NNTEvent *evt_self = nil, *evt_target = nil;
    
    if ([self respondsToSelector:@selector(_event)]) {
        id evt_obj = [self performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            evt_self = evt_obj;
        } NNTNS_ERR;
    } NNTNS_ERR;
    
    if ([obj respondsToSelector:@selector(_event)]) {
        id evt_obj = [obj performSelector:@selector(_event) withObject:nil];
        if ([evt_obj isKindOfClass:[NNTEvent class]]) {
            evt_target = evt_obj;
        } NNTNS_ERR;
    } NNTNS_ERR;
    
    if (evt_self && evt_target) {
        [evt_self _disredirect:evt_target];
    }  
}

- (BOOL)supportStore {
    if ([self respondsToSelector:@selector(_store)]) {
        id anyobj = [self performSelector:@selector(_store) withObject:nil];
        if ([anyobj isKindOfClass:[NNTObjectAttachStrong class]]) {
            return YES;
        }
    }
    return NO;
}

- (void)storePush:(id)key obj:(id)obj {
    if (obj == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"store: push a NULL object !"];
        THROW_MSG(msg);
# endif
        return;
    }
    
    if ([self respondsToSelector:@selector(_store)]) {
        id anyobj = [self performSelector:@selector(_store) withObject:nil];
        if ([anyobj isKindOfClass:[NNTObjectAttachStrong class]]) {
            NNTObjectAttachStrong *store = (NNTObjectAttachStrong*)anyobj;
            [store push:key obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)storeSet:(id)key obj:(id)obj {
    if (obj == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"store: set a NULL object !"];
        THROW_MSG(msg);
# endif
        return;
    }

    if ([self respondsToSelector:@selector(_store)]) {
        id anyobj = [self performSelector:@selector(_store) withObject:nil];
        if ([anyobj isKindOfClass:[NNTObjectAttachStrong class]]) {
            NNTObjectAttachStrong *store = (NNTObjectAttachStrong*)anyobj;
            [store set:key obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (id)storeSwap:(id)key obj:(id)obj {
    if (obj == 0) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"store: swap with a NULL object !"];
        THROW_MSG(msg);
# endif
        return nil;
    }

    if ([self respondsToSelector:@selector(_store)]) {
        id anyobj = [self performSelector:@selector(_store) withObject:nil];
        if ([anyobj isKindOfClass:[NNTObjectAttachStrong class]]) {
            NNTObjectAttachStrong *store = (NNTObjectAttachStrong*)anyobj;
            return [store swap:key obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return nil;
}

- (id)storePop:(id)key {
    if ([self respondsToSelector:@selector(_store)]) {
        id obj = [self performSelector:@selector(_store) withObject:nil];
        if ([obj isKindOfClass:[NNTObjectAttachStrong class]]) {
            NNTObjectAttachStrong *store = (NNTObjectAttachStrong*)obj;
            return [store pop:key];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return nil;
}

- (id)storePop:(id)key null:(id)null {
    id ret = [self storePop:key];
    if (ret == nil)
        return null;
    return ret;
}

- (id)storeFind:(id)key {
    if ([self respondsToSelector:@selector(_store)]) {
        id obj = [self performSelector:@selector(_store) withObject:nil];
        if ([obj isKindOfClass:[NNTObjectAttachStrong class]]) {
            NNTObjectAttachStrong *store = (NNTObjectAttachStrong*)obj;
            return [store find:key];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return nil;
}

- (id)storeFind:(id)key null:(id)null {
    id ret = [self storeFind:key];
    if (ret == nil)
        return null;
    return ret;
}

- (BOOL)supportAttach {
    if ([self respondsToSelector:@selector(_attach)]) {
        id anyobj = [self performSelector:@selector(_attach) withObject:nil];
        if ([anyobj isKindOfClass:[NNTObjectAttach class]]) {
            return YES;
        }
    }
    return NO;
}

- (void)attachPush:(id)key obj:(id)obj {
    if (obj == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"attach: push a NULL object !"];
        THROW_MSG(msg);
# endif
        return;
    }

    if ([self respondsToSelector:@selector(_attach)]) {
        id anyobj = [self performSelector:@selector(_attach) withObject:nil];
        if ([anyobj isKindOfClass:[NNTObjectAttach class]]) {
            NNTObjectAttach *store = (NNTObjectAttach*)anyobj;
            [store push:key obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (void)attachSet:(id)key obj:(id)obj {
    if (obj == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"attach: set a NULL object !"];
        THROW_MSG(msg);
# endif
        return;
    }

    if ([self respondsToSelector:@selector(_attach)]) {
        id anyobj = [self performSelector:@selector(_attach) withObject:nil];
        if ([anyobj isKindOfClass:[NNTObjectAttach class]]) {
            NNTObjectAttach *store = (NNTObjectAttach*)anyobj;
            [store set:key obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
}

- (id)attachSwap:(id)key obj:(id)obj {
    if (obj == 0) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"attach: swap with a NULL object !"];
        THROW_MSG(msg);
# endif
        return nil;
    }

    if ([self respondsToSelector:@selector(_attach)]) {
        id anyobj = [self performSelector:@selector(_attach) withObject:nil];
        if ([anyobj isKindOfClass:[NNTObjectAttach class]]) {
            NNTObjectAttach *store = (NNTObjectAttach*)anyobj;
            return [store swap:key obj:obj];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return Nil;
}

- (id)attachPop:(id)key {
    if ([self respondsToSelector:@selector(_attach)]) {
        id obj = [self performSelector:@selector(_attach) withObject:nil];
        if ([obj isKindOfClass:[NNTObjectAttach class]]) {
            NNTObjectAttach *store = (NNTObjectAttach*)obj;
            return [store pop:key];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return nil;    
}

- (id)attachPop:(id)key null:(id)null {
    id ret = [self attachPop:key];
    if (ret == nil)
        return null;
    return ret;
}

- (id)attachFind:(id)key {
    if ([self respondsToSelector:@selector(_attach)]) {
        id obj = [self performSelector:@selector(_attach) withObject:nil];
        if ([obj isKindOfClass:[NNTObjectAttach class]]) {
            NNTObjectAttach *store = (NNTObjectAttach*)obj;
            return [store find:key];
        } NNTNS_ERR;
    } NNTNS_ERR;
    return nil;
}

- (id)attachFind:(id)key null:(id)null {
    id ret = [self attachFind:key];
    if (ret == nil)
        return null;
    return ret;
}

+ (void)refobjSet:(id*)left obj:(id*)right {
    [*right retain];
# ifdef NNT_DEBUG
    safe_release(*left);
# else
    [*left release];
# endif
    *left = [*right retain];
    [*right release];
}

+ (void)refobjSet:(id*)left ref:(id)right {
    [right retain];
# ifdef NNT_DEBUG
    safe_release(*left);
# else
    [*left release];
# endif
    *left = [right retain];
    [right release];        
}

+ (void)refobjCopy:(id*)left obj:(id*)right {
    [*right retain];
# ifdef NNT_DEBUG
    safe_release(*left);
# else
    [*left release];
# endif
    *left = [*right copy];
    [*right release];   
}

+ (void)refobjCopy:(id*)left ref:(id)right {
    [right retain];
# ifdef NNT_DEBUG
    safe_release(*left);
# else
    [*left release];
# endif
    *left = [right copy];
    [right release];
}

- (id)consign {
    return [[self retain] autorelease];
}

- (uint)coreType {
    return CoreTypeObject;
}

- (NNTValueType)valueType {
    return NNTValueTypeUnknown;
}

- (void*)object {
    return self;
}

// for cxx.

- (void)performCxxObjectFunctionWrapper:(_cxxobject_perform_wrapper*)obj {
    (obj.object->*obj.function)(obj.params);    
}

@end

@implementation NSRefObject

@synthesize object = _cxxobj;

- (id)init {
    self = [super init];
    return self;
}

- (id)initWith:(::nnt::RefObject const*)object {
    self = [super init];
    self.object = object;
    return self;
}

+ (id)objectWith:(::nnt::RefObject const*)object {
    return [[[NSRefObject alloc] initWith:object] autorelease];
}

- (void)dealloc {
    safe_drop(_cxxobj);
    [super dealloc];
}

- (void)setObject:(::nnt::RefObject const*)object {
    if (object == _cxxobj)
        return;
    
    safe_drop(_cxxobj);
    _cxxobj = object;
    safe_grab(_cxxobj);
}

- (void)setObject:(::nnt::RefObject const*)object grab:(BOOL)grab {
    if (object == _cxxobj)
        return;
    
    safe_drop(_cxxobj);
    _cxxobj = object;
    
    if (grab)
        safe_grab(_cxxobj);
}

@end

id class_callMethod(Class cls, SEL sel, ...) {
    Method mtd = class_getClassMethod(cls, sel);
    IMP imp = method_getImplementation(mtd);
    char ctype;
    method_getReturnType(mtd, &ctype, sizeof(char));
    id ret = nil;
    if (ctype == _C_ID) {
        ret = (imp)(nil, sel);
    } else {
        (imp)(nil, sel);
    }
    return ret;
}

BOOL class_existMethod(Class cls, SEL sel) {
    Method mtd = class_getClassMethod(cls, sel);
    return mtd != NULL;
}

void class_swizzleMethod(Class c, SEL origs, SEL news) {
    Method origMethod = class_getInstanceMethod(c, origs);
    Method newMethod = class_getInstanceMethod(c, news);
    if(class_addMethod(c, origs, method_getImplementation(newMethod), method_getTypeEncoding(newMethod))) {
        class_replaceMethod(c, news, method_getImplementation(origMethod), method_getTypeEncoding(origMethod));
    } else {
        method_exchangeImplementations(origMethod, newMethod);
    }
}

IMP class_getImplementation(Class c, SEL sel) {
    return method_getImplementation(class_getInstanceMethod(c, sel));
}

id objc_getPropertyValue(id obj, char const* name) {
    Class cls = object_getClass(obj);
    //Ivar var = class_getClassVariable(cls, name);
    Ivar var = class_getInstanceVariable(cls, name);
    id ret = object_getIvar(obj, var);
    return ret;
}

bool objc_setPropertyValue(id value, id obj, char const* name) {
    Class cls = object_getClass(obj);
    Ivar var = class_getInstanceVariable(cls, name);
    if (var == nil)
        return false;
    object_setIvar(obj, var, value);
    return true;
}

NNTIMPL_CATEGORY(NSObject, NNT);

@implementation _cxxobject_perform_wrapper

@synthesize object = _object, function = _function, params = _params;

- (id)init {
    self = [super init];
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

@end

dispatch_queue_t kQueueDefault;
dispatch_queue_t kQueueSignalSlot;
char const* DISPATCH_QUEUE_PRIORITY_SIGNALSLOT = "::nnt::gcd::queue::signalslot";

NNT_END_OBJC

NNT_BEGIN_HEADER_CXX

class QueueSignalSlot
{
public:
    
    QueueSignalSlot()
    {
        kQueueDefault = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        kQueueSignalSlot = dispatch_queue_create(DISPATCH_QUEUE_PRIORITY_SIGNALSLOT, 0);
    }
    
};

static QueueSignalSlot __gs_queue_signalslot;

NNT_END_HEADER_CXX
