
# import "Core.h"
# import "AbstractCache.h"

# define NNT_MACH_PRIVATE
# import "Mach+NNT.h"

# define WATCH_MEMORY 0

# if !defined(NNT_DEBUG) || WATCH_MEMORY == 0
#   undef WATCH_MEMORY
# endif

# ifdef WATCH_MEMORY
#   import "NSTimer+NNT.h"
# endif

NNT_BEGIN_OBJC

@implementation func_object 

@synthesize addr, imp;

- (id)init {
    self = [super init];
    addr = nil;
    imp = nil;
    return self;
}

+ (func_object*)withAddr:(void*)addr {
	func_object* ret = [[func_object new] autorelease];
	ret.addr = addr;
	return ret;
}

+ (func_object*)withHandler:(IMP)imp {
	func_object* ret = [[func_object new] autorelease];
    ret.imp = imp;
	return ret;
}

@end

static NNT *__gs_nnt = nil;
static NSConditionLock *__gs_thread_condition = nil;

NNTDECL_PRIVATE_BEGIN(NNT, NSObject)
{
# ifdef WATCH_MEMORY
    NNTTimer* timer_memory_watcher;
# endif
}

NNTDECL_PRIVATE_IMPL(NNT)

- (id)init {
    self = [super init];
    
# ifdef WATCH_MEMORY
    timer_memory_watcher = [[NNTTimer alloc] initWithTimeInterval:5 repeats:YES];
    [timer_memory_watcher connect:kSignalTimerFired sel:@selector(act_memory_timer) obj:self];
    [timer_memory_watcher start];
# endif
    
    return self;
}

- (void)dealloc {
    
# ifdef WATCH_MEMORY
    [timer_memory_watcher stop];
# endif
    
    [super dealloc];
}

# ifdef WATCH_MEMORY

- (void)act_memory_timer {
    NSString* str = @"memory usage: \n";
    str = [str stringByAppendingFormat:@"\t free: %.2f MB \n", mem_free_size() * B2MB];
    str = [str stringByAppendingFormat:@"\t used: %.2f MB \n", mem_used_size() * B2MB];
    trace_msg(str);
}

# endif

NNTDECL_PRIVATE_END

@implementation NNT

static NSArray *__gs_hooks = nil;
static id<NSObject> __gs_desktop = nil;

+ (NNT*)shared {
    /*
# ifdef NNT_DEBUG
    if (__gs_nnt == nil)
        trace_msg(@"NNT singleton object is nil");
# endif
     */
    
    return __gs_nnt;
}

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNT);
    return self;
}

- (void)dealloc {
	zero_release(__gs_hooks);
    NNTDECL_PRIVATE_DEALLOC();
	[super dealloc];
}

NNT_BEGIN_HEADER_C
NNT_EXTERN void ParserInit(void);
NNT_END_HEADER_C

+ (void)Init {
	trace_msg(@"NNT[OBJC] Toolkit");
    trace_fmt(@"path: %@", [[NSBundle mainBundle] bundlePath]);
    
    __gs_nnt = [[NNT alloc] init];
    __gs_thread_condition = [[NSConditionLock alloc] initWithCondition:8];
    
    // init memory of mach.
    mem_init();
	
	// init
    __gs_hooks = [[NSArray arrayWithObjects:[NSMutableArray array],
                   [NSMutableArray array],
                   [NSMutableArray array],
                   [NSMutableArray array],
                   [NSMutableArray array],
                   nil]
                  retain];
	
    // register
    [NNT Register:NNTHookTypeInit hookFunc:[func_object withAddr:(void*)&CacheInit]];
    [NNT Register:NNTHookTypeInit hookFunc:[func_object withAddr:(void*)&ObjectInit]];
    [NNT Register:NNTHookTypeInit hookFunc:[func_object withAddr:(void*)&ParserInit]];
    	
	// invoke
	[NNT InvokeHook:NNTHookTypeInit]; 
}

+ (void)Fin {
	trace_msg(@"NNT[OBJC] environment ending");
	
	// invoke
	[NNT InvokeHook:NNTHookTypeFin];
    
    // release
    [__gs_desktop release];

    // free nnt
    safe_release(__gs_nnt);
    safe_release(__gs_thread_condition);
}

+ (void)Inactive {
    [NNT InvokeHook:NNTHookTypeInactive];
}

+ (void)Active {
    [NNT InvokeHook:NNTHookTypeActive];
}

+ (void)Boot {
    [NNT InvokeHook:NNTHookTypeBoot];
}

+ (void)InvokeHook:(NNTHookType)__type {
	NSMutableArray* arr = [__gs_hooks objectAtIndex:__type];
	for (NSInteger i = 0; i < [arr count]; ++i) {
		func_object* obj = [arr objectAtIndex:i];
		(*(void (*)())obj.addr)();
	}
}

+ (void)Register:(NNTHookType)__type hookFunc:(func_object*)__func {
	NSMutableArray* arr = [__gs_hooks objectAtIndex:__type];
	[arr addObject:__func];
}

+ (void)ThreadUse {
    [__gs_thread_condition lock];
}

+ (void)ThreadFree {
    [__gs_thread_condition unlock];
}

@end

void _trace_msg(NSString* __str) {
    NNTConsole* console = [NNTConsole shared];
    NSString* str = [__str unescape];
    str = [NSString stringWithFormat:@"%@.", str];
    [console println:str];
}

void _trace_obj(NSString* __objname, id __obj) {
    NNTConsole* console = [NNTConsole shared];
        
    if (__obj == nil) {
        [console println:[NSString stringWithFormat:@"%@ is nil", __objname]];
        return;
    }
    
    if ([__obj isKindOfClass:[NSNull class]]) {
        [console println:[NSString stringWithFormat:@"%@ is null type", __objname]];
        return;
    }
    
    if ([__obj isKindOfClass:[NSArray class]]) {
        [console println:[NSString stringWithFormat:@"Array %@ ->", __objname]];
        if ([(NSArray*)__obj count]) {
            for (NSObject *each in (NSArray*)__obj) {
# ifdef NNT_GCC
#   pragma GCC diagnostic ignored "-Wformat"
# endif
                _trace_obj([NSString stringWithFormat:@"child 0x%x", &each], each);
            }
        } else {
            _trace_msg(@"count: 0");
        }
        return;
    }

    if ([__obj isKindOfClass:[NSDictionary class]]) {
        [console println:[NSString stringWithFormat:@"%@ : Dictionary ->", __objname]];
        for (NSString *key in [(NSDictionary*)__obj allKeys]) {
            _trace_obj(key, [(NSDictionary*)__obj valueForKey:key]);
        }
        return;
    }
    
    if ([__obj isKindOfClass:[NSString class]]) {        
        [console println:[NSString stringWithFormat:@"NSString %@ = %@", __objname, (NSString*)__obj]];
        return;
    }
    
    if ([__obj isKindOfClass:[NSNumber class]]) {        
        [console println:[NSString stringWithFormat:@"NSNumber %@ = %@", __objname, [(NSNumber*)__obj stringValue]]];
        return;
    }
    
    if ([__obj isKindOfClass:[NSData class]]) {
        NSString* str = [[NSString alloc] initWithData:(NSData*)__obj encoding:NSUTF8StringEncoding];
        if (str == nil) {
            str = [[NSString alloc] initWithData:(NSData*)__obj encoding:NSASCIIStringEncoding];
        }
        [console println:str];
        safe_release(str);
        return;
    }
    
    [console println:[NSString stringWithFormat:@"%@: %@", __objname, __obj]];
}

void _trace_int(NSString *__objname, int __val) {
    NNTConsole* console = [NNTConsole shared];
    [console println:[NSString stringWithFormat:@"%@ dec= %d , hex= 0x%x, oct= 0%o , bin= b%@", __objname, __val, __val, __val, [NSNumber StringValueBinary:__val]]];
}

void _trace_float(NSString *__objname, float __val) {
    NNTConsole* console = [NNTConsole shared];
    [console println:[NSString stringWithFormat:@"%@ = %f", __objname, __val]];
}

NNT_END_OBJC

NNT_BEGIN_C

int VersionCmp(version_t const* l, version_t const* r) {
    if (l->major > r->major)
        return 1;
    else if (l->major < r->major)
        return -1;
    else {
        if (l->minor > r->minor)
            return 1;
        else if (l->minor < r->minor)
            return -1;
        else {
            if (l->patch > r->patch)
                return 1;
            else if (l->patch < r->patch)
                return -1;
        }
    }
    return 0;
}

NSString* NNTGetMajorAuthor()
{
    return NNTMACRO_TOSTR_OBJC(NNT_MAJOR_AUTHOR);
}

NSString* NNTGetBaseURL()
{
    return NNTMACRO_TOSTR_OBJC(NNT_BASE_URL);
}

NSString* NNTGetProjectURL()
{
    return NNTMACRO_TOSTR_OBJC(NNT_PROJECT_URL);
}

NSString* NNTGetFeedbackEmail()
{
    return NNTMACRO_TOSTR_OBJC(NNT_FEEDBACK_EMAIL);
}

NNT_END_C