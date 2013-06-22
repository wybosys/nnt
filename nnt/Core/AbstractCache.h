
# ifndef __NNT_CORE_ABSTRACTCACHE_C8D4723BFDFE403183F9FC61D7A1C785_H_INCLUDED
# define __NNT_CORE_ABSTRACTCACHE_C8D4723BFDFE403183F9FC61D7A1C785_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@class CacheItem;

//! @brief interface for Cache Pattern.
@protocol ICache <NSObject>

- (CacheItem*)setObject:(id)obj key:(NSString*)key;
- (CacheItem*)addItem:(CacheItem*)item key:(NSString*)key;
- (CacheItem*)addItem:(CacheItem*)item;
- (void)removeItem:(CacheItem*)item;
- (void)removeAtKey:(NSString*)key;
- (id)objectForKey:(NSString*)key;
- (id)itemForKey:(NSString*)key;
- (void)clear;
- (void)reset;
- (void)walk:(id)obj sel:(SEL)sel; // sel = BOOL function (key, item)
- (BOOL)loadItem:(CacheItem*)item;

@end

//! @brief interface for CacheItem Pattern.
@protocol ICacheItem <NSObject>

//! is overdate.
- (BOOL)is_overdate;

@end

NNTDECL_PRIVATE_HEAD(AbstractCache);

//! @brief general cache implementation base for the special cache implementation.
@interface AbstractCache : NNTObject <ICache> {
    
    //! timestamp for cache.
    time_t _timestamp;
    
    //! use limit policy, default is NO.
    BOOL   _policyLimit;
    
    //! use size policy, default is NO.
    BOOL   _policySize;
    
    //! use for limit policy.
    uint   _cfgCount;
    
    //! use for size policy, KB unit.
    uint   _cfgSize;
    
    //! length of fifo/freq buffer.
    uint   _cfgBuffer;
    
    //! overflow for buffer.
    uint   _cfgBufferOverflow;
    
    //! version.
    int _version;
    
    //! if cache loaded.
    BOOL _isloaded;
     
    NNTDECL_PRIVATE_EX(AbstractCache, d_ptr_cache);       
}

@property (nonatomic, assign) time_t timestamp;
@property (nonatomic, readonly) NSMutableDictionary *store;
@property (nonatomic, assign) BOOL policyLimit, policySize;
@property (nonatomic, assign) uint cfgCount, cfgSize, cfgBuffer, cfgBufferOverflow;
@property (nonatomic, assign) BOOL isloaded;
@property (nonatomic, readonly) int version;

//! set to default
- (id)setDefault;
+ (id)setDefault:(id)cache;
+ (id)defaultCache;

//! get cacheItemClass from object.
- (Class)classCacheItem:(NSObject*)obj;
- (BOOL)isCachableItem:(NSObject*)obj;

//! save & load
- (BOOL)save;
- (BOOL)saveItem:(CacheItem*)item;
- (BOOL)saveItem:(NSString*)key item:(CacheItem*)item;

//! load functions.
- (void)begin_load;
- (BOOL)load;
- (void)end_load;

//! freeitem, take the steps: save item -> free data.
- (BOOL)freeItem:(CacheItem*)item;

//! other
- (NSUInteger)count;

//! default.
+ (CacheItem*)SetObject:(id)obj key:(NSString*)key;
+ (CacheItem*)ItemForKey:(NSString*)key;
+ (void)RemoveItem:(CacheItem*)item;
+ (void)RemoveAtKey:(NSString*)key;
+ (id)ObjectForKey:(NSString*)key;
+ (id)ObjectForKey:(NSString*)key def:(id)obj;
+ (id)ObjectForKey:(NSString*)key def:(id)obj od:(NSUInteger)od;
+ (id)ObjectForKey:(NSString*)key defun:(id (*)(void))defun;
+ (id)ObjectForKey:(NSString*)key defun:(id (*)(void))defun od:(NSUInteger)od;
+ (id)ObjectForKey:(NSString*)key sel:(SEL)sel obj:(id)obj;
+ (id)ObjectForKey:(NSString*)key sel:(SEL)sel obj:(id)obj od:(NSUInteger)od;

+ (NSUInteger)Count;
+ (void)Clear;
+ (void)Reset;
+ (void)Save;
+ (void)Load;

//! get storage.
- (NSDictionary*)get_storage;

@end

static const NSUInteger kCacheOverDateInfinate = -1;

//! @brief base cache item.
@interface CacheItem : NNTObject <ICacheItem> {
    
    //! timestamp when object create.
    time_t _timestamp;
    
    //! overt date.
    time_t _overdate;
    
    //! name of item.
    NSString* _name;
    
    //! unidentify id.
    NSString *_code;
    
    //! is date updated, if YES will permanent. and will be set to YES while data changed.
    BOOL _updated;
    
    //! data is pending for read.
    BOOL _pending;
    
    //! pending data.
    id _pdata;
    
    //! reference to cache.
    id<ICache> _cache;
    
    //! data.
    id _data;
    
    //! use counter.
    uint _counter;
    
@public
    
    BOOL _in_fifo_storage, _in_freq_storage;
    
}

@property (nonatomic, copy)   NSString *name;
@property (nonatomic, copy)   NSString *code;
@property (nonatomic, assign) time_t timestamp;
@property (nonatomic, assign) time_t overdate;
@property (nonatomic, assign) id<ICache> cache;
@property (retain) id data;
@property (assign) BOOL updated;
@property (assign) BOOL pending;
@property (nonatomic, retain) id pdata;
@property (nonatomic, assign) uint counter;

//! serialization
- (NSData*)toData;
- (BOOL)fromData:(NSData*)data;

//! offset.
- (void)offsetOverdate:(uint)sec;

//! set overdate from now.
- (void)setOverdateFromNow:(time_t)overdate;

//! infinate.
- (void)infinate;

//! is used
- (BOOL)is_used;

//! is need for save.
- (BOOL)need_save;

@end

# pragma mark -
# pragma mark item for types

/*
@interface CacheItemNull : CacheItem
@end
 */

@interface CacheItemArray : CacheItem
@end

@interface CacheItemPair : CacheItem
@end

@interface CacheItemString : CacheItem 
@end

@interface CacheItemDictionary : CacheItem 
@end

@interface CacheItemData : CacheItem 
@end

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_C

void CacheInit(void);

NNT_END_HEADER_C

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(core)

class CacheItem
: public ns::Object< ::CacheItem>
{
    
    typedef ns::Object< ::CacheItem> super;
    
public:
    
    CacheItem(::CacheItem* item = nil)
    : super(item)
    {
        PASS;
    }
    
    ~CacheItem()
    {
        PASS;
    }
    
    void infinate()
    {
        [this->_self infinate];
    }
    
    void set_overdate(time_t tm, bool fromnow = true)
    {
        if (fromnow)
            [this->_self setOverdateFromNow:tm];
        else
            this->_self.overdate = tm;
    }
    
    void set_update(bool val)
    {
        this->_self.updated = val;
    }
    
    uint count() const
    {
        return this->_self.counter;
    }
    
};

class Cache
: public ns::Object<AbstractCache>
{
    typedef ns::Object<AbstractCache> super;
    
public:
    
    Cache(AbstractCache* cache = nil)
    : super(cache)
    {
        PASS;
    }
    
    ~Cache()
    {
        PASS;
    }
    
    static Cache& Default()
    {
        static Cache __gs_cache([AbstractCache defaultCache]);
        return __gs_cache;
    }
    
    CacheItem set(id obj, id key)
    {
        return [this->_self setObject:obj key:key];
    }
    
    id find(id key)
    {
        return [this->_self objectForKey:key];
    }
    
    id find(id key, id def)
    {
        id ret = [this->_self objectForKey:key];
        if (ret == nil)
            return def;
        return ret;
    }
                
    id find(id key, id def, uint od)
    {
        id ret = [this->_self objectForKey:key];
        if (ret == nil)
        {
            ret = def;
            ::CacheItem* item = [this->_self setObject:ret key:key];
            if (od != kCacheOverDateInfinate)
            {
                item.overdate = item.timestamp + od;
            }            
        }
        return ret;
    }
    
    id find(id key, id (*defun)())
    {
        id ret = [this->_self objectForKey:key];
        if (ret == nil)
            return (*defun)();
        return ret;
    }
    
    id find(id key, id (*defun)(), uint od)
    {
        id ret = [this->_self objectForKey:key];
        if (ret == nil)
        {
            ret = (*defun)();
            ::CacheItem* item = [this->_self setObject:ret key:key];
            if (od != kCacheOverDateInfinate)
            {
                item.overdate = item.timestamp + od;
            }            
        }
        return ret;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
// end cxx

# endif
// end objc

# endif