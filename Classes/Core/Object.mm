
# import "Core.h"

# ifdef NNT_USE_SBJSON
#   import <SBJson/SBJsonWriter.h>
#   import <SBJson/SBJsonParser.h>
# endif

# ifdef NNT_USE_BASE64
#   import <Google/GTMBase64.h>
# endif

# import "Task+NNT.h"

NNT_BEGIN_OBJC

@implementation NNTWeakReference

@synthesize obj;

- (id)initWith:(NSObject *)__obj {
    self = [super init];
    self.obj = __obj;
    return self;
}

+ (NNTWeakReference*)weakWith:(NSObject *)obj {
    return [[[NNTWeakReference alloc] initWith:obj] autorelease];
}

@end

@implementation NNTObjectAttachNull

@synthesize storePushPop;

- (id)init {
    self = [super init];
    storePushPop = [[NSMutableDictionary alloc] init];        
    return self;
}

- (void)dealloc {
    zero_release(storePushPop);
    
    [super dealloc];
}

- (void)push:(id)key obj:(id)obj {
    NSMutableArray *arr = [storePushPop objectForKey:key];
    if (arr == nil) {
        arr = [NSMutableArray new];
        [storePushPop setObject:arr forKey:key];
        [arr release];
    }
    
    [arr addObject:[self pack:obj]];
}

- (id)pop:(id)key {
    NSMutableArray *arr = [storePushPop objectForKey:key];
    if (arr == nil)
        return NULL;
    if (![arr count])
        return NULL;
    id obj = [arr objectAtIndex:[arr count] - 1];
    id ret = [self unpack:obj];
    [arr removeObjectAtIndex:[arr count] - 1];
    return ret;
}

- (id)pop:(id)key null:(id)null {
    id ret = [self pop:key];
    if (ret == nil)
        return null;
    return ret;
}

- (id)find:(id)key {
    NSMutableArray *arr = [storePushPop objectForKey:key];
    if (arr == nil)
        return NULL;
    if ([arr count] == 0)
        return NULL;
    id obj = [arr objectAtIndex:[arr count] - 1];
    return [self get:obj];
}

- (id)find:(id)key null:(id)null {
    id ret = [self find:key];
    if (ret == nil)
        return null;
    return ret;
}

- (usize)count {
    return [storePushPop count];
}

- (usize)count:(id)key {
    NSMutableArray const* arr = [storePushPop objectForKey:key];
    return [arr count];
}

- (void)set:(id)key obj:(id)obj {
    NSMutableArray *arr = [storePushPop objectForKey:key];
    if (arr == nil) {
        [self push:key obj:obj];
        return;
    }
    if ([arr count])
        [arr replaceObjectAtIndex:[arr count] - 1 withObject:[self pack:obj]];
    else
        [arr addObject:[self pack:obj]];
}

- (id)swap:(id)key obj:(id)obj {
    NSMutableArray *arr = [storePushPop objectForKey:key];
    if (arr == nil) {
        [self push:key obj:obj];
        return Nil;
    }
    id ret = [arr objectAtIndex:[arr count] - 1];
    ret = [self unpack:ret];
    [arr replaceObjectAtIndex:[arr count] - 1 withObject:[self pack:obj]];
    return ret;
}

- (id)pack:(id)obj {
    return obj;
}

- (id)unpack:(id)obj {
    return obj;
}

- (id)get:(id)obj {
    return obj;
}

@end

@implementation NNTObjectAttachWeak

- (id)pack:(id)__obj {
    return [NNTWeakReference weakWith:__obj];
}

- (id)unpack:(id)__obj {
    NNTWeakReference *obj = (NNTWeakReference*)__obj;
    return obj.obj;
}

- (id)get:(id)__obj {
    NNTWeakReference *obj = (NNTWeakReference*)__obj;
    return obj.obj;
}

@end

@implementation NNTObjectAttachStrong

- (id)unpack:(id)obj {
    return [[obj retain] autorelease];
}

@end

@implementation NNTObject

NNTOBJECT_IMPL;

- (id)init {
    self = [super init];
    if (self == nil)
        return nil;

    _lock = NULL;
    _block = NULL;
    
    return self;
}

- (void)dealloc {
    [self fini];
    
    safe_release(_lock);
    safe_release(_block);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)fini {
    PASS;
}

- (void)lock {
    NNT_SYNCHRONIZED(self)
    if (_lock == nil) {
        _lock = [[NNTNSLock alloc] init];
        //_lock= [[NNTNSConditionLock alloc] initWithCondition:1];
    }
    NNT_SYNCHRONIZED_END
    
    [_lock lock];
}

- (void)unlock {
    NNT_SYNCHRONIZED(self)
    if (_lock == nil)
        @throw [NSException exceptionWithName:@"lock-unlock" reason:@"lost lock object" userInfo:NULL];
    NNT_SYNCHRONIZED_END
    
    [_lock unlock];
}

- (BOOL)tryLock {
    BOOL ret;
    NNT_SYNCHRONIZED(self)
    if (_lock == nil) {
        _lock = [[NNTNSLock alloc] init];
        //_lock= [[NNTNSConditionLock alloc] initWithCondition:1];
    }
    NNT_SYNCHRONIZED_END
    
    ret = [_lock tryLock];
    return ret;
}

- (void)block {
    NNT_SYNCHRONIZED(self)
    if (_block == nil)
        _block = [[NNTCondition alloc] init];
    NNT_SYNCHRONIZED_END
    
    [_block wait];
}

- (void)unblock {
    NNT_SYNCHRONIZED(self)
    if (_block == nil)
        @throw [NSException exceptionWithName:@"block-unblock" reason:@"lost block object" userInfo:NULL];
    NNT_SYNCHRONIZED_END
    
    [(NSCondition*)_block signal];
}

# ifdef NNT_USE_SBJSON

+ (NSString*)json_encode:(NSObject*)__obj {
	SBJsonWriter *jsonWriter = [SBJsonWriter new];    
    NSString *json = [jsonWriter stringWithObject:__obj];
    //if (!json)
    //    NSLog(@"JSONRepresentation failed. Error trace is: %@", [jsonWriter errorTrace]);
    [jsonWriter release];
    return json;
}

+ (NSDictionary*)json_decode:(NSString*)__str {
	SBJsonParser *jsonParser = [SBJsonParser new];
    id repr = [jsonParser objectWithString:__str];
    //if (!repr)
    //    NSLog(@"JSONValue failed. Error trace is: %@", [jsonParser errorTrace]);
    [jsonParser release];
    return repr;
}

# endif

# ifdef NNT_USE_BASE64

+ (NSData*)base64_encode:(NSData *)data {
    return [GTMBase64 encodeData:data];
}

+ (NSData*)base64_decode:(NSData *)data {
    return [GTMBase64 decodeData:data];
}

# endif

static int __gs_looponce_count = 0;

- (BOOL)loopOnce {
    BOOL ret = NO;
    NNT_SYNCHRONIZED(self)
    ++__gs_looponce_count;
    if (__gs_looponce_count == 1) {
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
        ret = YES;
    }
    --__gs_looponce_count;
    NNT_SYNCHRONIZED_END
    return ret;
}

@end

NSString* json_encode_object(NSObject* obj) {
    SBJsonWriter *jsonWriter = [[SBJsonWriter alloc] init];    
    NSString *json = [jsonWriter stringWithObject:obj];
    [jsonWriter release];
    return json;
}

NSDictionary* json_decode_string(NSString* str) {
    SBJsonParser *jsonParser = [[SBJsonParser alloc] init];
    id repr = [jsonParser objectWithString:str];
    [jsonParser release];
    return repr;
}

NSData* base64_encode_data(NSData* data) {
    return [GTMBase64 encodeData:data];
}

NSData* base64_decode_data(NSData* data) {
    return [GTMBase64 decodeData:data];
}

@implementation NSObjectSel

@synthesize selector;

+ (NSObjectSel*)objectWithSel:(SEL)sel {
    NSObjectSel *obj = [[NSObjectSel new] autorelease];
    obj.selector = sel;
    return obj;
}

@end

@implementation NSPointer

@synthesize addr;

- (id)initWithAddr:(void *)__addr {
    self = [super init];
    addr = __addr;
    return self;
}

+ (id)pointerWithAddr:(void *)__addr {
    return [[[NSPointer alloc] initWithAddr:__addr] autorelease];
}

- (uint)coreType {
    return NNTCoreTypePointer;
}

- (void*)object {
    return addr;
}

@end

NSNumber *NSNumberN1 = NULL;
NSNumber *NSNumber0 = NULL;
NSNumber *NSNumber1 = NULL;
NSNumber *NSNumber2 = NULL;
NSNumber *NSNumber3 = NULL;
NSNumber *NSNumber4 = NULL;
NSNumber *NSNumber5 = NULL;
NSNumber *NSNumber6 = NULL;
NSNumber *NSNumber7 = NULL;
NSNumber *NSNumber8 = NULL;
NSNumber *NSNumber9 = NULL;
NSNumber *NSNumberYes = NULL;
NSNumber *NSNumberNo = NULL;

void ObjectInit () {
    NSNumberN1  = [NSNumber numberWithInt:-1];
    NSNumber0   = [NSNumber numberWithInt:0];
    NSNumber1   = [NSNumber numberWithInt:1];
    NSNumber2   = [NSNumber numberWithInt:2];
    NSNumber3   = [NSNumber numberWithInt:3];
    NSNumber4   = [NSNumber numberWithInt:4];
    NSNumber5   = [NSNumber numberWithInt:5];
    NSNumber6   = [NSNumber numberWithInt:6];
    NSNumber7   = [NSNumber numberWithInt:7];
    NSNumber8   = [NSNumber numberWithInt:8];
    NSNumber9   = [NSNumber numberWithInt:9];
    NSNumberYes =  NSNumber1;
    NSNumberNo  =  NSNumber0;
}

NNT_END_OBJC
