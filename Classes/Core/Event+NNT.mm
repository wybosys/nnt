
# import "Core.h"
# import "NNTEvent.h"
# import "NSDate+NNT.h"

NNT_BEGIN_OBJC

@implementation NNTSlot

@synthesize 
sel = _sel,
handler = _handler,
sender = _sender,
result = _result,
data = _data,
shotcount = _shotcount,
signal = _signal,
veto = _veto,
redirect = _redirect,

# ifdef NNT_BLOCKS
block = _block,
# endif

# ifdef NNT_CXX
cxx_target = _cxx_target,
cxx_action = _cxx_action,
# endif

function = _function,
delay = _delay,
inMainThread = _inMainThread,
inBackgroundThread = _inBackgroundThread,
fixsender = _fixsender,
frequency = _frequency,
waitFrequency = _waitFrequency,
period = _period
;

- (id)init {
    self = [super init];
    
    _shotcount = -1;
    _veto = NO;
    _delay = 0;
    _data = NULL;
    _fixsender = NO;
    _inMainThread = YES;
    _inBackgroundThread = NO;
    _frequency = 0;
    _waitFrequency = NO;
    
    return self;
}

- (void)dealloc {
    safe_release(_result);
    safe_release(_redirect);
    safe_release(_period);
    
    [super dealloc];
}

- (id)copyWithZone:(NSZone *)zone {
    NNTSlot* slot = [[[self class] allocWithZone:zone] init];
    slot.sel = _sel;
    slot.handler = _handler;
    slot.sender = _sender;
    slot.result = _result;
    slot.shotcount = _shotcount;
    slot.signal = _signal;
    slot.veto = _veto;
# ifdef NNT_BLOCKS
    slot.block = _block;
# endif
    slot.function = _function;
    slot.redirect = _redirect;
    slot.delay = _delay;
    slot.data = _data;
    slot.cxx_target = _cxx_target;
    slot.cxx_action = _cxx_action;
    slot.inMainThread = _inMainThread;
    slot.inBackgroundThread = _inBackgroundThread;
    slot.fixsender = _fixsender;
    slot.frequency = _frequency;
    slot.period = _period;
    return slot;
}

- (void)grab {
    [_result retain];
    
    [self retain];
}

- (void)drop {
    safe_release(_result);
    
    [self release];
}

- (void)oneshot {
    _shotcount = 1;
}

- (id)mainThread {
    _inMainThread = YES;
    _inBackgroundThread = NO;
    return self;
}

- (id)backgroundThread {
    _inMainThread = NO;
    _inBackgroundThread = YES;
    return self;
}

- (id)sameThread {
    _inMainThread = _inBackgroundThread = NO;
    return self;
}

@end

@interface NNTSlot (NNTSignal)

- (void)startFrequencyLimit;

@end

@implementation NNTSlot (NNTSignal)

- (void)startFrequencyLimit {
    _waitFrequency = YES;
    [self performSelector:@selector(_action_frequency_limit_end) withObject:nil afterDelay:_frequency];
}

- (void)_action_frequency_limit_end {
    _waitFrequency = NO;
}

@end

@implementation NNTSignal

@synthesize name = _name;
@synthesize slots = _slots;
@synthesize enable = _enable;

- (id)init {
    self = [super init];
    
    _slots = [[NSMutableArray alloc] init];
    _enable = YES;
    _lock = [[NSLock alloc] init];
    
    return self;
}

- (void)dealloc {
    zero_release(_slots);
    zero_release(_name);
    zero_release(_lock);
    
    [super dealloc];
}

- (NNTSlot*)register_slot:(SEL)sel obj:(NSObject *)obj delay:(real)delay {
    NNTSlot *slot = [[NNTSlot alloc] init];
    slot.sel = sel;
    slot.handler = obj;
    slot.delay = delay;
    [_slots addObject:slot];
    [slot release];
    return slot;
}

- (NNTSlot*)find_slot:(SEL)sel obj:(NSObject*)obj delay:(real)delay {
    for (NNTSlot* each in _slots) {
        if (each.sel == sel && each.handler == obj && each.delay == delay) {
            return each;
        }
    }
    return nil;
}

# ifdef NNT_BLOCKS

- (NNTSlot*)register_block:(slot_block_callback)block delay:(real)delay {
    NNTSlot *slot = [[NNTSlot alloc] init];    
    slot.block = block;    
    slot.delay = delay;
    [_slots addObject:slot];
    [slot release];
    return slot;
}

# endif

- (NNTSlot*)register_function:(slot_function_callback)function delay:(real)delay {
    NNTSlot *slot = [[NNTSlot alloc] init];    
    slot.function = function;    
    slot.delay = delay;
    [_slots addObject:slot];
    [slot release];
    return slot;
}

- (NNTSlot*)register_redirect:(signal_t)sig obj:(NSObject*)obj delay:(real)delay {
    NNTSlot *slot = [[NNTSlot alloc] init];    
    slot.redirect = sig;
    slot.handler = obj;
    slot.delay = delay;
    [_slots addObject:slot];
    [slot release];
    return slot;
}

# ifdef NNT_CXX

- (NNTSlot*)register_action:(::nnt::objevent_func)action target:(::nnt::Object*)target delay:(real)delay {
    NNTSlot *slot = [[NNTSlot alloc] init];    
    slot.cxx_target = target;
    slot.cxx_action = action;
    slot.delay = delay;
    [_slots addObject:slot];
    [slot release];
    return slot;
}

# endif

- (NSUInteger)indexOfSlot:(NNTSlot*)slot {
    return [_slots indexOfObject:slot];
}

- (void)remove_slot:(NSObject *)obj {
    [_lock lock];
    
    NSMutableArray *arr = [[NSMutableArray alloc] init];
    for (NNTSlot *slot in _slots) {
        if (slot.handler == obj) {
            [arr addObject:slot];
        }
    }
    [_slots removeObjectsInArray:arr];
    [arr release];
    
    [_lock unlock];
}

- (void)remove_slot:(SEL)sel obj:(NSObject *)obj {
    [_lock lock];
    
    NSMutableArray *arr = [[NSMutableArray alloc] init];
    for (NNTSlot *slot in _slots) {
        if ((slot.handler == obj) && (slot.sel == sel)) {
            [arr addObject:slot];
        }
    }
    [_slots removeObjectsInArray:arr];
    [arr release];
    
    [_lock unlock];
}

- (void)remove_slots {
    [_lock lock];
    
    [_slots removeAllObjects];
    
    [_lock unlock];
}

# ifdef NNT_CXX

- (void)remove_action:(::nnt::objevent_func)action target:(::nnt::Object*)target {
    [_lock lock];
    
    NSMutableArray *arr = [[NSMutableArray alloc] init];
    for (NNTSlot *slot in _slots) {
        if ((slot.cxx_target == target) && (slot.cxx_action == action)) {
            [arr addObject:slot];
        }
    }
    [_slots removeObjectsInArray:arr];
    [arr release];
    
    [_lock unlock];
}

- (void)remove_target:(::nnt::Object*)target {
    [_lock lock];
    
    NSMutableArray *arr = [[NSMutableArray alloc] init];
    for (NNTSlot *slot in _slots) {
        if (slot.cxx_target == target) {
            [arr addObject:slot];
        }
    }
    [_slots removeObjectsInArray:arr];
    [arr release];
    
    [_lock unlock];
}

# endif

- (void)emit:(void*)obj result:(id)result {
    [self emit:obj result:result data:0];
}

- (void)emit:(void*)obj data:(void*)data {
    [self emit:obj result:nil data:data];
}

- (void)emit:(void*)obj result:(id)result data:(void*)data {
    autocollect;
    
    [self do_emit:obj result:result data:data];
}

- (void)do_emit:(void*)obj result:(id)result data:(void*)data {
    if (_enable == NO)
        return;
    
    // prevent self release.
    [self retain];
        
    NSMutableArray* need_removes = nil;
    
    [_lock lock];
    NSArray* slots = [NSArray arrayWithArray:_slots];
    [_lock unlock];
    
    for (NNTSlot *each in slots) {
        BOOL could_call = YES;
        
        if (each.shotcount != -1) {
            if (each.shotcount == 0)
                could_call = NO;
            else if (--each.shotcount == 0) {
                if (need_removes == nil)
                    need_removes = [[NSMutableArray alloc] init];
                
                [need_removes addObject:each];
            }
        }
                
        // period check.
        if (could_call && each.period && !each.period.isDuring)
            could_call = NO;
        
        // for next.
        if (could_call && each.veto)
            could_call = NO;
        
        // frenquency limit.
        if (could_call && each.waitFrequency == YES)
            could_call = NO;
        
        // if callable?
        if (could_call == NO)
            continue;
        
        NNTEventObj* evtobj = [[NNTEventObj alloc] initWithSlot:each];
        
        evtobj.slot.result = result;
        evtobj.slot.data = data;
        evtobj.slot.signal = self;
        if (!evtobj.slot.fixsender)
            evtobj.slot.sender = obj;
        
        if (each.delay == 0) {
            
            if (0) {}
            
            // block slot.
# ifdef NNT_BLOCKS
            else if (each.block) {
                (each.block)(evtobj);
            }
# endif
            
            // function slot.
            else if (each.function) {
                if (each.inMainThread) {
                    [self performSelectorOnMainThread:@selector(func_invoke_function:) withObject:evtobj waitUntilDone:YES];
                } else {
                    (*each.function)(evtobj);
                }
            }
            
            // redirect signal to other object.
            else if (each.redirect) {
                [each.handler emit:each.redirect result:result data:data];
            }
            
            // c++ object target.
# ifdef NNT_CXX
            
            else if (each.cxx_target) {
                if (each.inMainThread) {
                    [self performSelectorOnMainThread:@selector(func_invoke_objevent:) withObject:evtobj waitUntilDone:YES];
                } else if (each.inBackgroundThread) {
                    [self performSelectorInBackground:@selector(func_invoke_objevent:) withObject:evtobj];
                } else {
                    ::nnt::objevent_func func = each.cxx_action;
                    ::nnt::EventObj evt(evtobj);
                    (each.cxx_target->*func)(evt);
                }
            }
            
# endif
            
            // print debug message.
            else {
# ifdef NNT_DEBUG
                
                if ([each.handler respondsToSelector:each.sel]) {
                    if (each.inMainThread) {
                        [each.handler performSelectorOnMainThread:each.sel withObject:evtobj waitUntilDone:YES];
                    } else if (each.inBackgroundThread) {
                        [each.handler performSelectorInBackground:each.sel withObject:evtobj];
                    } else {
                        [each.handler performSelector:each.sel withObject:evtobj];
                    }
                } else {
                    NSString* str = [NSString stringWithFormat:@"selector is not found, the handler is [%@], the selector is [%@].",
                                     NSStringFromClass([each.handler class]),
                                     NSStringFromSelector(each.sel)];
                    dthrow([NSException exceptionWithName:@"signals/slots" reason:str userInfo:nil]);
                }
                
# else
                if (each.inMainThread) {
                    [each.handler performSelectorOnMainThread:each.sel withObject:evtobj waitUntilDone:YES];
                } else if (each.inBackgroundThread) {
                    [each.handler performSelectorInBackground:each.sel withObject:evtobj];
                } else {
                    [each.handler performSelector:each.sel withObject:evtobj];
                }
# endif
            }
            
        } else {
            
            if (0) {}
            
            // block.
# ifdef NNT_BLOCKS
            
            else if (each.block) {
                [self performSelector:@selector(func_invoke_block:) withObject:evtobj afterDelay:each.delay];
            }
            
# endif
            
            // function.
            else if (each.function) {
                [self performSelector:@selector(func_invoke_function:) withObject:evtobj afterDelay:each.delay];
            }
            
            // c++
# ifdef NNT_CXX
            
            else if (each.cxx_target) {
                [self performSelector:@selector(func_invoke_objevent:) withObject:evtobj afterDelay:each.delay];
            }
            
# endif
            
            // redirect signal to other object.
            else if (each.redirect) {
                [self performSelector:@selector(func_invoke_redirect:) withObject:evtobj afterDelay:each.delay];
            }
            
            // goto main thread.
            else {
                if (each.inMainThread) {
                    [each.handler performSelectorOnMainThread:each.sel withObject:evtobj waitUntilDone:YES];
                } else if (each.inBackgroundThread) {
                    [each.handler performSelectorInBackground:each.sel withObject:evtobj];
                } else {
                    [each.handler performSelector:each.sel withObject:evtobj afterDelay:each.delay];
                }
            }
        }
        // end slot call.
        
        // frequency limit.
        if (each.frequency != 0) {
            [each startFrequencyLimit];
        }
        
        safe_release(evtobj);
    }

    // remove the non-used slots.
    if (need_removes) {
        [_slots removeObjectsInArray:need_removes];
        safe_release(need_removes);
    }
    
    // free.
    [self release];
}

# ifdef NNT_BLOCKS

- (void)func_invoke_block:(NNTEventObj*)obj {
    (obj.slot.block)(obj);
}

# endif

- (void)func_invoke_function:(NNTEventObj*)obj {
    (*obj.slot.function)(obj);
}

- (void)func_invoke_redirect:(NNTEventObj*)obj {
    [obj.handler emit:obj.redirect
               result:obj.result
                 data:obj.data];
}

# ifdef NNT_CXX

- (void)func_invoke_objevent:(NNTEventObj*)obj {
    ::nnt::objevent_func func = obj.slot.cxx_action;
    ::nnt::EventObj evt(obj);
    (obj.slot.cxx_target->*func)(evt);
}

# endif

- (NSUInteger)count {
    return _slots.count;
}

@end

@implementation NNTEvent

@synthesize signals = _signals;
@synthesize enable = _enable, forceEnable = _forceEnable;
@synthesize redirects = _redirects;

- (id)init {
    self = [super init];  
    
    _signals = [[NSMutableDictionary alloc] init];
    _enable = YES;
    _forceEnable = NO;
    
    return self;
}

- (void)dealloc {
    zero_release(_signals);
    zero_release(_redirects);
    
    [super dealloc];
}

- (NNTSignal*)_register_signal:(signal_t)name {
    NNTSignal *signal = [_signals objectForKey:name];
    if (signal)
        return signal;
    signal = [[NNTSignal alloc] init];
    signal.name = name;
    [_signals setObject:signal forKey:name];
    [signal release];
    return signal;
}

- (NNTSignal*)_find_signal:(signal_t)name {
    return [_signals objectForKey:name];
}

- (void)_remove_signal:(signal_t)name {
    [_signals removeObjectForKey:name];
}

static int __gs_signal_enable = 1;

+ (void)EnableEverywhere {
    NNT_SYNCHRONIZED(self)
    
    ++__gs_signal_enable;
    
    NNT_SYNCHRONIZED_END
}

+ (void)DisableEverywhere {
    NNT_SYNCHRONIZED(self)
    
    --__gs_signal_enable;
    
    NNT_SYNCHRONIZED_END
}

- (void)_emit:(signal_t)name sender:(void *)sender result:(id)result data:(void*)data {
    //NNT_SYNCHRONIZED(self)
    
    if (!_forceEnable) {
        if ((_enable == NO) &&
            (__gs_signal_enable < 1)) {
            return;
        }
    }
    
    NNTSignal *signal = [_signals valueForKey:name];
    if (signal == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"signal [%@] is not found, current signals list:", name];
        for (NSString *name in _signals) {
            msg = [msg stringByAppendingFormat:@" %@ ", name];
        }
        dthrow([NSException exceptionWithName:@"signals/slots" reason:msg userInfo:nil]);
# endif
        return;
    }
    
    // emit signal.
    [signal emit:sender result:result data:data];
    
    // emit redirect.
    for (NNTEvent *each in _redirects) {
        [each _emit:name sender:each result:result data:data];
    }
    
    //NNT_SYNCHRONIZED_END
}

- (void)_emit:(signal_t)sig sender:(void*)sender result:(id)result {
    [self _emit:sig sender:sender result:result data:0];
}

- (void)_emit:(signal_t)sig sender:(void*)sender data:(void*)data {
    [self _emit:sig sender:sender result:nil data:data];
}

- (void)_emit:(signal_t)sig sender:(void*)sender {
    [self _emit:sig sender:sender result:nil data:0];
}

- (void)_enable:(signal_t)sig tog:(BOOL)tog {
    NNTSignal *signal = [_signals valueForKey:sig];
    if (signal == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"signal [%@] is not found, current signals list:", sig];
        for (NSString *name in _signals) {
            msg = [msg stringByAppendingFormat:@" %@ ", sig];
        }
        dthrow([NSException exceptionWithName:@"signals/slots" reason:msg userInfo:nil]);
# endif
        return;
    }
    
    signal.enable = tog;
}

- (NNTSlot*)_connect:(signal_t)sig sel:(SEL)sel obj:(NSObject *)obj {
    return [self _connect:sig sel:sel obj:obj delay:0];
}

- (NNTSlot*)_connect:(signal_t)sig sel:(SEL)sel obj:(NSObject *)obj delay:(real)delay {
    NNTSignal *signal = [_signals valueForKey:sig];
    if (signal == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"signal [%@] is not found, current signals list:", sig];
        for (NSString *name in _signals) {
            msg = [msg stringByAppendingFormat:@" %@ ", name];
        }
        dthrow([NSException exceptionWithName:@"signals/slots" reason:msg userInfo:nil]);
# endif
        return nil;
    }
    return [signal register_slot:sel obj:obj delay:delay];
}

- (NNTSlot*)_connect:(signal_t)sig sig:(signal_t)sig2 obj:(NSObject*)obj {
    return [self _connect:sig sig:sig2 obj:obj delay:0];
}

- (NNTSlot*)_connect:(signal_t)sig sig:(signal_t)sig2 obj:(NSObject*)obj delay:(real)delay {
    NNTSignal *signal = [_signals valueForKey:sig];
    if (signal == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"signal [%@] is not found, current signals list:", sig];
        for (NSString *name in _signals) {
            msg = [msg stringByAppendingFormat:@" %@ ", name];
        }
        dthrow([NSException exceptionWithName:@"signals/slots" reason:msg userInfo:nil]);
# endif
        return nil;
    }
    return [signal register_redirect:sig2 obj:obj delay:delay];
}

# ifdef NNT_BLOCKS

- (NNTSlot*)_connect:(signal_t)sig block:(slot_block_callback)block {
    return [self _connect:sig block:block delay:0];
}

- (NNTSlot*)_connect:(signal_t)sig block:(slot_block_callback)block delay:(real)delay {
    NNTSignal *signal = [_signals valueForKey:sig];
    if (signal == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"signal [%@] is not found, current signals list:", sig];
        for (NSString *name in _signals) {
            msg = [msg stringByAppendingFormat:@" %@ ", name];
        }
        dthrow([NSException exceptionWithName:@"signals/slots" reason:msg userInfo:nil]);
# endif
        return nil;
    }
    return [signal register_block:block delay:delay];
}

# endif

# ifdef NNT_CXX

- (NNTSlot*)_connect:(signal_t)sig action:(::nnt::objevent_func)action target:(::nnt::Object*)target {
    return [self _connect:sig action:action target:target delay:0];
}

- (NNTSlot*)_connect:(signal_t)sig action:(::nnt::objevent_func)action target:(::nnt::Object*)target delay:(real)delay {
    NNTSignal *signal = [_signals valueForKey:sig];
    if (signal == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"signal [%@] is not found, current signals list:", sig];
        for (NSString *name in _signals) {
            msg = [msg stringByAppendingFormat:@" %@ ", name];
        }
        dthrow([NSException exceptionWithName:@"signals/slots" reason:msg userInfo:nil]);
# endif
        return nil;
    }
    return [signal register_action:action target:target delay:delay];
}

# endif

- (NNTSlot*)_connect:(signal_t)sig func:(slot_function_callback)func {
    return [self _connect:sig func:func delay:0];
}

- (NNTSlot*)_connect:(signal_t)sig func:(slot_function_callback)func delay:(real)delay {
    NNTSignal *signal = [_signals valueForKey:sig];
    if (signal == nil) {
# ifdef NNT_DEBUG
        NSString *msg = [NSString stringWithFormat:@"signal [%@] is not found, current signals list:", sig];
        for (NSString *name in _signals) {
            msg = [msg stringByAppendingFormat:@" %@ ", name];
        }
        dthrow([NSException exceptionWithName:@"signals/slots" reason:msg userInfo:nil]);
# endif
        return nil;
    }
    return [signal register_function:func delay:delay];
}

- (NNTSlot*)_find_connect:(signal_t)sig sel:(SEL)sel obj:(NSObject*)obj {
    return [self _find_connect:sig sel:sel obj:obj delay:0];
}

- (NNTSlot*)_find_connect:(signal_t)sig sel:(SEL)sel obj:(NSObject*)obj delay:(real)delay {
    NNTSignal *signal = [_signals valueForKey:sig];
    if (signal == nil) {
        return nil;
    }
    return [signal find_slot:sel obj:obj delay:delay];
}

- (void)_disconnect:(signal_t)name obj:(NSObject *)obj {
    NNT_SYNCHRONIZED(self)
    
    NNTSignal *signal = [_signals valueForKey:name];
    if (signal == nil)
        return;
    [signal remove_slot:obj];
    
    NNT_SYNCHRONIZED_END
}

- (void)_disconnect:(signal_t)name sel:(SEL)sel obj:(NSObject *)obj {
    NNT_SYNCHRONIZED(self)

    NNTSignal *signal = [_signals valueForKey:name];
    if (signal == nil)
        return;
    [signal remove_slot:sel obj:obj];
    
    NNT_SYNCHRONIZED_END
}

- (void)_disconnect:(NSObject *)obj {
    NNT_SYNCHRONIZED(self)

    for (NNTSignal *signal in [_signals allValues]) {
        [signal remove_slot:obj];
    }
    
    NNT_SYNCHRONIZED_END
}

- (void)_disconnect_signal:(id)name {
    NNT_SYNCHRONIZED(self)
    
    NNTSignal *signal = [_signals valueForKey:name];
    if (signal == nil)
        return;

    [signal remove_slots];
    
    NNT_SYNCHRONIZED_END
}

- (void)_disconnect_all {
    NNT_SYNCHRONIZED(self)
    
    for (NNTSignal* sig in [_signals allValues])
        [sig remove_slots];
    
    NNT_SYNCHRONIZED_END
}

# ifdef NNT_CXX

- (void)_disconnect:(id)name target:(::nnt::Object*)target action:(::nnt::objevent_func)action {
    NNT_SYNCHRONIZED(self)
    
    NNTSignal* signal = [_signals valueForKey:name];
    if (signal == nil)
        return;
    [signal remove_action:action target:target];
    
    NNT_SYNCHRONIZED_END
}

- (void)_disconnect_target:(::nnt::Object*)target {
    NNT_SYNCHRONIZED(self)
    
    for (NNTSignal *signal in [_signals allValues]) {
        [signal remove_target:target];
    }
    
    NNT_SYNCHRONIZED_END
}

- (void)_disconnect_target:(::nnt::Object*)target signal:(id)name {
    NNT_SYNCHRONIZED(self)
    
    NNTSignal* signal = [_signals valueForKey:name];
    if (signal == nil)
        return;
    [signal remove_target:target];
    
    NNT_SYNCHRONIZED_END
}

# endif

- (void)_redirect:(NNTEvent*)evt {
    if (_redirects == nil) {
        _redirects = [[NSMutableArray alloc] init];
    }
    [_redirects addObject:evt];
}

- (void)_disredirect:(NNTEvent*)evt {
    if ([_redirects containsObject:evt])
        return;
    [_redirects addObject:evt];
}

- (BOOL)_hasSignal:(signal_t)sig {
    NNTSignal *signal = [_signals valueForKey:sig null:nil];
    return signal != nil;
}

@end

@implementation NNTEventObj

@synthesize slot = _slot;

@dynamic
sel,
handler,
sender,
result,
data,
shotcount,
signal,
redirect,
frequency,
waitFrequency,
period
;

- (id)initWithSlot:(NNTSlot *)slot {
    self = [super init];
    
    _origin = [slot retain];
    _slot = [slot copy];
    
    return self;
}

- (void)dealloc {
    safe_release(_origin);
    safe_release(_slot);
    [super dealloc];
}

- (SEL)sel {
    return _slot.sel;
}

- (NSObject*)handler {
    return _slot.handler;
}

- (void*)sender {
    return _slot.sender;
}

- (id)result {
    return _slot.result;
}

- (void*)data {
    return _slot.data;
}

- (int)shotcount {
    return _slot.shotcount;
}

- (NNTSignal*)signal {
    return _slot.signal;
}

- (signal_t)redirect {
    return _slot.redirect;
}

- (real)frequency {
    return _slot.frequency;
}

- (BOOL)waitFrequency {
    return _slot.waitFrequency;
}

- (NSDatePeriod*)period {
    return _slot.period;
}

- (void)veto {
    _origin.veto = _slot.veto = YES;
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX

EventObj null_eventobj(nil);

NNT_END_CXX
