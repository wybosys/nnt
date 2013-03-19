
# ifndef __WSI_CORE_NSDICTIONARY_92F95E99F8914B5F9073D5807516B939_H_INCLUDED
# define __WSI_CORE_NSDICTIONARY_92F95E99F8914B5F9073D5807516B939_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface NSDictionary (WSI)

//! object for key with null object.
- (id)objectForKey:(id)key null:(id)null;
- (id)valueForKey:(NSString*)key null:(id)null;

//! get object at path.
- (id)valueForPath:(NSArray*)path null:(id)null;
- (id)valueForPath:(NSArray*)path;

//! dictionary with key - obj.
+ (id)dictionaryWithKey:(id)key forObj:(id)obj;

//! restrict.
+ (NSDictionary*)restrictDictionary:(id)obj;

//! pairArray.
- (NSArray*)pairArray;

//! combine with kv-sep and seg-sep.
- (NSString*)combineWithKVSep:(NSString*)kvsep andSegSep:(NSString*)segsep keysur:(NSString*)keysur valsur:(NSString*)valsur;
- (NSString*)combineWithKVSep:(NSString*)kvsep andSegSep:(NSString*)segsep;
- (NSString*)combineWithKVSep:(NSString*)kvsep andSegSep:(NSString*)segsep keysur:(NSString*)keysur valsur:(NSString*)valsur sort:(SEL)sort;
- (NSString*)combineWithKVSep:(NSString*)kvsep andSegSep:(NSString*)segsep sort:(SEL)sort;

//! coretype.
- (uint)coreType;

@end

@interface NSMutableDictionary (WSI)

//! set key - obj.
- (void)setKey:(id)key forObj:(id)obj;

//! restrict.
+ (NSMutableDictionary*)restrictDictionary:(id)obj;

@end

WSIDECL_CATEGORY(NSDictionary, WSI);
WSIDECL_CATEGORY(NSMutableDictionary, WSI);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

WSI_BEGIN_NS(tpl)

template <typename TDict>
class Dictionary
: public ns::Object<TDict>
{
    typedef Dictionary<TDict> self_type;
    typedef ns::Object<TDict> super;
    
public:
    
    Dictionary()
    {
        PASS;
    }
    
    Dictionary(id obj)
    : super(obj)
    {
        PASS;
    }
    
    ~Dictionary()
    {
        PASS;
    }
    
    id operator [] (id key) const
    {
        return [this->_self objectForKey:key null:nil];
    }
    
    NSArray* allkeys() const
    {
        return [this->_self allKeys];
    }
    
    NSArray* allvalues() const
    {
        return [this->_self allValues];
    }
    
    id find(id key, id null = nil) const
    {
        return [this->_self objectForKey:key null:null];
    }
    
};

WSI_END_NS

template <typename TDict>
class dictionary
: public tpl::Dictionary<TDict>
{
    
};

template <>
class dictionary <NSDictionary>
: public tpl::Dictionary<NSDictionary>
{
    typedef tpl::Dictionary<NSDictionary> super;
    
public:
    
    dictionary()
    {
        PASS;
    }
    
    dictionary(id obj)
    : super(obj)
    {
        PASS;
    }
    
    dictionary(NSDictionary *dict)
    : super(dict)
    {
        PASS;
    }
    
};

template <>
class dictionary <NSMutableDictionary>
: public tpl::Dictionary<NSMutableDictionary>
{
    typedef dictionary <NSMutableDictionary> self_type;
    typedef tpl::Dictionary<NSMutableDictionary> super;
    
public:
    
    dictionary()
    {
        PASS;
    }
    
    dictionary(id obj)
    : super(obj)
    {
        PASS;
    }
    
    dictionary(NSMutableDictionary* dict)
    : super(dict)
    {
        PASS;
    }
    
protected:
    
    class pair
    {
    public:
        
        typedef dictionary <NSMutableDictionary> dict_type;
        
        operator id ()
        {
            return obj;
        }
        
        dict_type& operator = (id val)
        {
# ifdef WSI_DEBUG
            if (val == nil)
                dthrow_msg(@"NULL", @"the object for insert is NULL.");
# endif
            
            obj = val;
            [_dict->_self setObject:obj forKey:key];
            return *_dict;
        }
        
        dict_type& operator = (ignore_null val)
        {
            if (val == nil)
                return *_dict;
            obj = (id)val;
            [_dict->_self setObject:obj forKey:key];
            return *_dict;
        }
        
    public:
        
        id key;
        id obj;
        dict_type* _dict;
        
    };
    
    class const_pair
    {
    public:
        
        typedef dictionary <NSMutableDictionary> dict_type;
        
        operator id ()
        {
            return obj;
        }
                
    public:
        
        id key;
        id obj;
        dict_type const* _dict;
        
    };
    
    friend class pair;
    friend class const_pair;
    
public:
    
    self_type& insert(id key, id obj)
    {
        [this->_self setObject:obj forKey:key];
        return *this;
    }
    
    pair operator [] (id key)
    {
        pair ret;
        ret.key = key;
        ret.obj = [this->_self objectForKey:key null:nil];
        ret._dict = this;
        return ret;
    }
    
    const_pair operator [] (id key) const
    {
        const_pair ret;
        ret.key = key;
        ret.obj = [this->_self objectForKey:key null:nil];
        ret._dict = this;
        return ret;
    }

    self_type& remove(id key)
    {
        [this->_self removeObjectForKey:key];
        return *this;
    }
    
    self_type& clear()
    {
        [this->_self removeAllObjects];
        return *this;
    }
    
    operator dictionary<NSDictionary> ()
    {
        return dictionary<NSDictionary>(this->_self);
    }
        
};

typedef dictionary<NSMutableDictionary> MutableDictionary;
typedef dictionary<NSDictionary> Dictionary;

WSI_EXTERN Dictionary null_dictionary;

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
