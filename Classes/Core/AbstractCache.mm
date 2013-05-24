
# import "Core.h"
# import "AbstractCache.h"

NNT_BEGIN_OBJC

# define CACHE_LIMIT_COUNT 10
# define CACHE_LIMIT_SIZE 5120
# define CACHE_BUFFER 10
# define CACHE_BUFFER_OVERFLOW 15

@interface AbstractCachePrivate : NNTObject {

    //! if enable limit control.
    BOOL _skip_limit_control;
        
    //! store all cache items.
    NSMutableDictionary *_storage;
    NSMutableArray *_storage_time;
    NSMutableArray *_storage_freq;
    
    AbstractCache *d_owner;
}

@property (nonatomic, assign) AbstractCache *d_owner;
@property (nonatomic, assign) BOOL skip_limit_control;
@property (nonatomic, retain) NSMutableDictionary *storage;
@property (nonatomic, retain) NSMutableArray *storage_time, *storage_freq;

- (BOOL)limit_control;

@end

@implementation AbstractCachePrivate

@synthesize skip_limit_control = _skip_limit_control;
@synthesize d_owner;
@synthesize storage = _storage, storage_freq = _storage_freq, storage_time = _storage_time;

- (id)init {
    self = [super init];
    
    _storage = [[NSMutableDictionary alloc] init];
    _storage_time = [[NSMutableArray alloc] init];
    _storage_freq = [[NSMutableArray alloc] init];
    
    _skip_limit_control = NO;
    
    return self;
}

- (void)dealloc {
    zero_release(_storage);
    zero_release(_storage_time);
    zero_release(_storage_freq);
    
    [super dealloc];
}

- (BOOL)limit_control {
    if (_skip_limit_control)
        return NO;
    
    NNTMACRO_LOCKOBJ(self);
        
    // adjust buffer.
    if ([_storage_time count] > d_owner.cfgBufferOverflow) {
        trace_msg(@"Cache:: filtering items in FIFO buffer.");
        NSMutableArray *sto = [[NSMutableArray alloc] init];
        int i = (int)[_storage_time count];
        for (CacheItem *each in _storage_time) {
            if (YES == (each->_in_fifo_storage = (i-- < d_owner.cfgBuffer))) {
                
                // collect it.
                [sto addObject:each];
                
            }
        }
        self.storage_time = sto;
        safe_release(sto);
    }
    
    if ([_storage_freq count] > d_owner.cfgBufferOverflow) {
        trace_msg(@"Cache:: filtering items in FREQ buffer.");
        NSSortDescriptor *sortDescriptor = [[NSSortDescriptor alloc] initWithKey:@"counter" ascending:NO];
        NSArray *sortDescriptors = [NSArray arrayWithObject:sortDescriptor];
        NSArray *result = [_storage_freq sortedArrayUsingDescriptors:sortDescriptors];
        NSMutableArray *sto = [[NSMutableArray alloc] init];
        int i = 0;
        for (CacheItem *each in result) {
            if (YES == (each->_in_freq_storage = (i++ < d_owner.cfgBuffer)))
            {
                
                // collect it.
                [sto addObject:each];

            }
        }
        self.storage_freq = sto;
        safe_release(sto);
        safe_release(sortDescriptor);
    }
    
    // get need array.
    BOOL skip = NO;
    NSMutableArray *arr = [[NSMutableArray alloc] initWithCapacity:[_storage count]];
    // get all need items.
    {
        NSArray *vals = [_storage allValues];
        for (CacheItem *each in vals) {
            if (!each->_in_fifo_storage &&
                !each->_in_freq_storage &&
                [each need_save]
                )
            {
                
                // collect it.
                [arr addObject:each];
                
            }            
        }
    }
    
    // process count control.
    if (!skip && d_owner.policyLimit) {
        if ([arr count] >= d_owner.cfgCount) {
            
# ifdef NNT_DEBUG
            trace_fmt(@"cache limit control: processing %d; there is %d; in memory is %d.", (int)arr.count, (int)d_owner.count, (int)(_storage_freq.count + _storage_time.count));
# endif
            
            for (CacheItem *each in arr) {
                BOOL suc = [d_owner freeItem:each];
                if (suc == NO) {
                    trace_msg(@"failed to free cache-item");
                }
            }
            
            skip = YES;
        }        
    }
    
    // process memory usage control.
    if (!skip && d_owner.policySize) {
        skip = YES;
    }
    
    safe_release(arr);
        
    return skip;
}

@end

@implementation AbstractCache

@synthesize policySize = _policySize, policyLimit = _policyLimit;
@synthesize cfgSize = _cfgSize, cfgCount = _cfgCount, cfgBuffer = _cfgBuffer, cfgBufferOverflow = _cfgBufferOverflow;
@synthesize timestamp = _timestamp;
@dynamic store;
@synthesize isloaded = _isloaded;
@synthesize version = _version;

static AbstractCache *__gs_defaultCache = nil;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT_EX(AbstractCache, d_ptr_cache);
    
    _timestamp = time(NULL);
    _policyLimit = _policySize = NO;
    
    _cfgCount = CACHE_LIMIT_COUNT;
    _cfgSize = CACHE_LIMIT_SIZE;
    _cfgBuffer = CACHE_BUFFER;
    _cfgBufferOverflow = CACHE_BUFFER_OVERFLOW;
    
    _isloaded = NO;
    
    _version = 3;
    
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC_EX(d_ptr_cache);
    [super dealloc];
}

- (NSUInteger)count {
    return [d_ptr_cache.storage count];
}

- (Class)classCacheItem:(NSObject*)obj {
    Class ret = nil;
    switch ([(NSObject*)obj coreType]) {
        default: {
# ifdef NNT_DEBUG
            NSString *msg = [NSString stringWithFormat:@"cache warning: skip a [%s] class object", object_getClassName(obj)];
            trace_msg(msg);
# endif
        } break;
        case NNTCoreTypeArray: ret = [CacheItemArray class]; break;
        case NNTCoreTypePair: ret = [CacheItemPair class]; break;
        case NNTCoreTypeDictionary: ret = [CacheItemDictionary class]; break;
        case NNTCoreTypeString: ret = [CacheItemString class]; break;
        case NNTCoreTypeData: ret = [CacheItemData class]; break;
    }
    return ret;
}
                
- (BOOL)isCachableItem:(NSObject*)obj {
    BOOL ret = YES;
    switch ([obj coreType]) {
        default: break;
        case NNTCoreTypePointer: ret = NO; break;
    }
    return ret;
}

- (CacheItem*)setObject:(id)obj key:(NSString<NSHash> *)key {
    if (obj == nil) {
        trace_msg(@"skipping a null object!");
        return nil;
    }
    
    if ([self isCachableItem:obj] == NO)
        return nil;
        
    Class classItem = [self classCacheItem:obj];
    if (classItem == nil)
        return nil;
    
    CacheItem *item = [[classItem alloc] init];
    item.data = obj;
    
    // success.
    if ([self addItem:item key:key]) {
        
        // time, fifo.
        [d_ptr_cache.storage_time insertObject:item atIndex:0];
        
        // freq, sort.
        [d_ptr_cache.storage_freq addObject:item];
        
        item->_in_fifo_storage = YES;
        item->_in_freq_storage = YES;
        
    }
    
    safe_release(item);
    return item;
}

- (CacheItem*)addItem:(CacheItem*)item key:(NSString<NSHash> *)key {
    item.name = key;
    item.code = [key uniqueIdentify];
    [self addItem:item];
    return item;
}

- (CacheItem*)addItem:(CacheItem*)item {
    // if overdate, skip add.
    if ([item is_overdate]) {
        [self removeItem:item];
        return nil;
    }
    
    // test limit.
    [d_ptr_cache limit_control];
    
    // add item.
    item.cache = self;
    
    // store.
    [d_ptr_cache.storage setObject:item forKey:item.code];
    
# ifdef NNT_DEBUG
    
    trace_fmt(@"added a cache item, there is [%d] items.",
              (int)[self count]);
    
# endif
    
    // set origin counter.
    item.counter = 1;
    
    return item;
}

- (id)objectForKey:(NSString<NSHash> *)key {
    NNTMACRO_LOCKOBJ(self);
    
    id ret = nil;
    NSString *code = [key uniqueIdentify];
    CacheItem* item = [d_ptr_cache.storage objectForKey:code];
    if ([item is_overdate]) {
        [self removeItem:item];
        item = nil;
    }
    
    // if has item.
    if (item) {
        if (item.name == nil)
            item.name = key;
        
        // load data.
        if (item.pending) {
            // load data from cache system.
            [self loadItem:item];
        }
        
        // if is overdate.
        if ([item is_overdate]) {
            
# ifdef NNT_DEBUG
            trace_msg(@"a cache item is timeout.");
# endif
            
            [self removeItem:item];
            item = nil;
        }
        
        // increase count.
        if (item) {
            ++item.counter;
            ret = item.data;
        }
    }
    return ret;
}

- (id)itemForKey:(NSString<NSHash> *)key {
    NNTMACRO_LOCKOBJ(self);
    
    NSString *code = [key uniqueIdentify];
    
    CacheItem* ret = [d_ptr_cache.storage objectForKey:code];
    
    if ([ret is_overdate]) {
        [self removeItem:ret];
        ret = nil;
    }
    if (ret) {
        if (ret.name == nil)
            ret.name = key;
    }
    return ret;
}

- (void)removeItem:(CacheItem *)item { 
    // remove from buffer.
    if (item->_in_fifo_storage)
        [d_ptr_cache.storage_time removeObject:item];
    if (item->_in_freq_storage)
        [d_ptr_cache.storage_freq removeObject:item];
    
    // remove from storage.
    [d_ptr_cache.storage removeObjectForKey:item.code];
    
# ifdef NNT_DEBUG
    trace_fmt(@"a cache item was removed, there is [%d] items.", (int)[self count]);
# endif
}

- (void)removeAtKey:(NSString<NSHash> *)key {
    CacheItem *item = [self itemForKey:key];
    if (item) {
        [self removeItem:item];
    }
}

- (NSDictionary*)store {
    return d_ptr_cache.storage;
}

- (void)clear {
    [d_ptr_cache.storage removeAllObjects];
    [d_ptr_cache.storage_time removeAllObjects];
    [d_ptr_cache.storage_freq removeAllObjects];
    _isloaded = NO;
}

- (void)reset {
    [d_ptr_cache.storage removeAllObjects];
    [d_ptr_cache.storage_time removeAllObjects];
    [d_ptr_cache.storage_freq removeAllObjects];
    _isloaded = NO;
}

- (id)setDefault {
    return [AbstractCache setDefault:self];
}

+ (id)defaultCache {
    return __gs_defaultCache;
}

+ (id)setDefault:(id)cache {
    NNT_SYNCHRONIZED(self)

    [__gs_defaultCache save];
    [__gs_defaultCache release];
    
    __gs_defaultCache = [cache retain];
    if (__gs_defaultCache.isloaded == NO) {
        [__gs_defaultCache load];
    }
    
    NNT_SYNCHRONIZED_END
    return cache;
}

- (NSDictionary*)get_storage {
    return d_ptr_cache.storage;
}

- (BOOL)save {
    NNTMACRO_LOCKOBJ(self);
    
    for (id key in d_ptr_cache.storage) {
        id item = [d_ptr_cache.storage objectForKey:key];        
                
        // save.
        if ([item need_save]) {
            [self saveItem:key item:item];
        }
    }
    return YES;
}

- (BOOL)saveItem:(CacheItem *)item {
    return [self saveItem:item.code item:item];
}

- (BOOL)saveItem:(NSString*)key item:(CacheItem *)item {
    return YES;
}

- (BOOL)freeItem:(CacheItem *)item {    
    if ([self saveItem:item] == NO)
        return NO;
    
    item.data = nil;
    item.pending = YES;
    return YES;
}

- (BOOL)load {
    return YES;
}

- (BOOL)loadItem:(CacheItem *)item {
    item.pending = NO;
    trace_msg(@"loading a cache item.");
    return YES;
}

- (void)begin_load {
    d_ptr_cache.skip_limit_control = YES;
}

- (void)end_load {
    _isloaded = YES;
    d_ptr_cache.skip_limit_control = NO;
}

- (void)walk:(id)obj sel:(SEL)sel {
    for (id key in d_ptr_cache.storage) {
        id item = [d_ptr_cache.storage objectForKey:key];
        if ([item need_save]) {
            [obj performSelector:sel withObject:key withObject:item];
        }
    }
}

+ (CacheItem*)SetObject:(id)obj key:(NSString*)key {
    if (__gs_defaultCache == nil)
        return nil;
    return [__gs_defaultCache setObject:obj key:key];
}

+ (CacheItem*)ItemForKey:(NSString*)key {
    if (__gs_defaultCache == nil)
        return nil;
    return [__gs_defaultCache itemForKey:key];
}

+ (void)RemoveItem:(CacheItem *)item {
    if (__gs_defaultCache == nil)
        return;
    return [__gs_defaultCache removeItem:item];
}

+ (void)RemoveAtKey:(NSString*)key {
    if (__gs_defaultCache == nil)
        return;
    return [__gs_defaultCache removeAtKey:key];
}

+ (id)ObjectForKey:(NSString*)key {
    if (__gs_defaultCache == nil)
        return nil;
    return [__gs_defaultCache objectForKey:key];
}

+ (id)ObjectForKey:(NSString*)key def:(id)obj {
    if (__gs_defaultCache == nil)
        return nil;
    id ret = [__gs_defaultCache objectForKey:key];
    if (ret == nil) {
        [__gs_defaultCache setObject:obj key:key];
        ret = obj;
    }
    return ret;
}

+ (id)ObjectForKey:(NSString*)key def:(id)obj od:(NSUInteger)od {
    if (__gs_defaultCache == nil)
        return nil;
    id ret = [__gs_defaultCache objectForKey:key];
    if (ret == nil) {
        CacheItem *item = [__gs_defaultCache setObject:obj key:key];
        if (od != kCacheOverDateInfinate) {
            item.overdate = item.timestamp + od;
        }
        ret = obj;
    }
    return ret;
}

+ (id)ObjectForKey:(NSString*)key defun:(id (*)())defun {
    if (__gs_defaultCache == nil)
        return nil;
    id ret = [__gs_defaultCache objectForKey:key];
    if (ret == nil) {
        ret = (*defun)();
        [__gs_defaultCache setObject:ret key:key];
    }
    return ret;
}

+ (id)ObjectForKey:(NSString*)key defun:(id (*)(void))defun od:(NSUInteger)od {
    if (__gs_defaultCache == nil)
        return nil;
    id ret = [__gs_defaultCache objectForKey:key];
    if (ret == nil) {
        ret = (*defun)();
        CacheItem *item = [__gs_defaultCache setObject:ret key:key];
        if (od != kCacheOverDateInfinate) {
            item.overdate = item.timestamp + od;
        }        
    }
    return ret;
}

+ (id)ObjectForKey:(NSString*)key sel:(SEL)sel obj:(id)obj {
    if (__gs_defaultCache == nil)
        return nil;
    id ret = [__gs_defaultCache objectForKey:key];
    if (ret == nil) {
        ret = [obj performSelector:sel];
        [__gs_defaultCache setObject:ret key:key];
    }
    return ret;
}

+ (id)ObjectForKey:(NSString*)key sel:(SEL)sel obj:(id)obj od:(NSUInteger)od {
    if (__gs_defaultCache == nil)
        return nil;
    id ret = [__gs_defaultCache objectForKey:key];
    if (ret == nil) {
        ret = [obj performSelector:sel];
        CacheItem *item = [__gs_defaultCache setObject:ret key:key];
        if (od != kCacheOverDateInfinate) {
            item.overdate = item.timestamp + od;
        }        
    }
    return ret;
}

+ (NSUInteger)Count {
    if (__gs_defaultCache)
        return [__gs_defaultCache count];
    return 0;
}

+ (void)Clear {
    if (__gs_defaultCache)
        [__gs_defaultCache clear];
}

+ (void)Reset {
    if (__gs_defaultCache)
        [__gs_defaultCache reset];
}

+ (void)Save {
    if (__gs_defaultCache)
        [__gs_defaultCache save];
}

+ (void)Load {
    if (__gs_defaultCache)
        [__gs_defaultCache load];
}

@end

@implementation CacheItem

@synthesize name = _name, code = _code;
@synthesize timestamp = _timestamp, cache = _cache, overdate = _overdate;
@synthesize data = _data;
@synthesize updated = _updated;
@synthesize pending = _pending, pdata = _pdata;
@synthesize counter = _counter;

- (id)init {
    self = [super init];

    _timestamp = time(NULL);
    _overdate = 0;
    _counter = 0;
    
    return self;
}

- (void)dealloc {
    zero_release(_name);
    zero_release(_code);
    zero_release(_data);
    zero_release(_pdata);
    
    [super dealloc];
}

- (BOOL)is_overdate {
    time_t now = time(NULL);
    if (_overdate <= 0UL)
        return NO;
    return now > _overdate;
}

- (void)setData:(id)data {
    if (_data == data)
        return;
    
    safe_release(_data);
    
# ifdef NNT_DEBUG
    if (_data != nil) {
        trace_fmt(@"the cache data remain in memory but should be free. retain count: %d .", (int)[_data retainCount]);
    }
# endif
    
    _data = [data retain];
    _updated = YES;
}

- (id)data {
    return _data;
}

- (NSData*)toData {
    return NULL;
}

- (BOOL)fromData:(NSData *)data {
    return YES;
}

- (void)offsetOverdate:(uint)sec {
    _overdate = _timestamp + sec;
}

- (void)infinate {
    _overdate = 0;
}

- (BOOL)is_used {
    return (!_pending) && (_data != nil);
}

- (BOOL)need_save {
    if (_pending)
        return NO;
    return _updated;
}

- (void)setOverdateFromNow:(time_t)overdate {
    _overdate = time(NULL) + overdate;
}

@end

/*
@implementation CacheItemNull

- (NSData*)toData {
    return [NSData data];
}

- (BOOL)fromData:(NSData *)data {
    return YES;
}

@end
 */

@implementation CacheItemArray

- (NSData*)toData {
    if (_data == nil)
        return nil;
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setValue:[NNTObject json_encode:self.data] forKey:@"value"];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.timestamp] forKey:@"timestamp"];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.overdate] forKey:@"overdate"];
    NSString *str = [NNTObject json_encode:dict];
    [dict release];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)fromData:(NSData *)__data {
    NSString *str = [[NSString alloc] initWithData:__data encoding:NSUTF8StringEncoding];
    NSDictionary *dict = [NNTObject json_decode:str];
    [str release];
    self.timestamp = [[dict valueForKey:@"timestamp"] unsignedLongValue];
    self.overdate = [[dict valueForKey:@"overdate"] unsignedLongValue];
    NSString *value = [dict valueForKey:@"value"];
    self.data = [NNTObject json_decode:value];
    return YES;
}

@end

@implementation CacheItemPair

- (NSData*)toData {
    if (_data == nil)
        return nil;
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setValue:[NNTObject json_encode:self.data] forKey:@"value"];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.timestamp] forKey:@"timestamp"];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.overdate] forKey:@"overdate"];
    NSString *str = [NNTObject json_encode:dict];
    [dict release];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)fromData:(NSData *)__data {
    NSString *str = [[NSString alloc] initWithData:__data encoding:NSUTF8StringEncoding];
    NSDictionary *dict = [NNTObject json_decode:str];
    [str release];
    self.timestamp = [[dict valueForKey:@"timestamp"] unsignedLongValue];
    self.overdate = [[dict valueForKey:@"overdate"] unsignedLongValue];
    NSString *value = [dict valueForKey:@"value"];
    self.data = [NNTObject json_decode:value];
    return YES;
}

@end

@implementation CacheItemDictionary

- (NSData*)toData {
    if (_data == nil)
        return nil;
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setValue:[NNTObject json_encode:self.data] forKey:@"value"];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.timestamp] forKey:@"timestamp"];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.overdate] forKey:@"overdate"];
    NSString *str = [NNTObject json_encode:dict];
    [dict release];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)fromData:(NSData *)__data {
    NSString *str = [[NSString alloc] initWithData:__data encoding:NSUTF8StringEncoding];
    NSDictionary *dict = [NNTObject json_decode:str];
    [str release];
    self.timestamp = [[dict valueForKey:@"timestamp"] unsignedLongValue];
    self.overdate = [[dict valueForKey:@"overdate"] unsignedLongValue];
    NSString *value = [dict valueForKey:@"value"];
    self.data = [NNTObject json_decode:value];
    return YES;
}

@end

@implementation CacheItemString

- (NSData*)toData {
    if (_data == nil)
        return nil;
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setValue:(NSString*)self.data forKey:@"value"];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.timestamp] forKey:@"timestamp"];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.overdate] forKey:@"overdate"];
    NSString *str = [NNTObject json_encode:dict];
    [dict release];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)fromData:(NSData *)__data {
    NSString *str = [[NSString alloc] initWithData:__data encoding:NSUTF8StringEncoding];
    NSDictionary *dict = [NNTObject json_decode:str];
    [str release];
    self.timestamp = [[dict valueForKey:@"timestamp"] unsignedLongValue];
    self.overdate = [[dict valueForKey:@"overdate"] unsignedLongValue];
    self.data = [dict valueForKey:@"value"];
    return YES;
}

@end

@implementation CacheItemData

- (NSData*)toData {
    if (_data == nil)
        return nil;
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    NSData *base64 = [NNTObject base64_encode:(NSData*)self.data];
    NSString *value = [[NSString alloc] initWithData:base64 encoding:NSUTF8StringEncoding];
    [dict setValue:value forKey:@"value"];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.timestamp] forKey:@"timestamp"];
    [value release];
    [dict setValue:[NSNumber numberWithUnsignedLong:self.overdate] forKey:@"overdate"];
    NSString *str = [NNTObject json_encode:dict];
    [dict release];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)fromData:(NSData *)__data {
    NSString *str = [[NSString alloc] initWithData:__data encoding:NSUTF8StringEncoding];
    NSDictionary *dict = [NNTObject json_decode:str];
    [str release];
    self.timestamp = [[dict valueForKey:@"timestamp"] unsignedLongValue];
    self.overdate = [[dict valueForKey:@"overdate"] unsignedLongValue];
    id value = [dict valueForKey:@"value"];
    self.data = [NNTObject base64_decode:[(NSString*)value dataUsingEncoding:NSUTF8StringEncoding]];
    return YES;
}

@end

NNT_END_OBJC

NNT_BEGIN_C

void CacheBoot();
void CacheFin();
void CacheActive();
void CacheInactive();

void CacheInit() {
    [NNT Register:NNTHookTypeFin hookFunc:[func_object withAddr:(void*)&CacheFin]];
    [NNT Register:NNTHookTypeActive hookFunc:[func_object withAddr:(void*)&CacheActive]];
    [NNT Register:NNTHookTypeInactive hookFunc:[func_object withAddr:(void*)&CacheInactive]];
    //[NNT Register:NNTHookTypeBoot hookFunc:[func_object withAddr:(void*)&CacheBoot]];
}

void CacheBoot() {
    AbstractCache *cache = [AbstractCache defaultCache];
    if (cache == nil)
        return;
    
    // load cache.
    [cache load];
}

void CacheFin() {
    [AbstractCache setDefault:nil];
}

void CacheActive() {    
    AbstractCache *cache = [AbstractCache defaultCache];
    if (cache == nil)
        return;

    if (cache.isloaded == NO) {
        // clear cache but don't delete cacheitem storage.
        [cache reset];    
    
        // load cache items from storage.
        [cache load];
    }
    
    trace_msg(@"cache is loaded.");
}

void CacheInactive() {
    AbstractCache *cache = [AbstractCache defaultCache];
    if (cache == nil)
        return;
    
    // save cache items to storage.
    [cache save];
    
    // clear cache but don't delete cacheitem storate.
    [cache reset];
    
    trace_msg(@"cache is saved.");
}

NNT_END_C
