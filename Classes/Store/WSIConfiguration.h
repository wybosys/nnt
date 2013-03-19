
# ifndef __NNT_STORE_CONFCENTER_0BB0C7F159894961B61B55C69084913C_H_INCLUDED
# define __NNT_STORE_CONFCENTER_0BB0C7F159894961B61B55C69084913C_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(NNTConfiguration);

@interface NNTConfiguration : NNTObject {
    
    //! default is NO.
    bool _readonly;
    
    NNTDECL_PRIVATE(NNTConfiguration);
}

@property (nonatomic, assign) bool readonly;

- (id)init;
- (id)initWithFile:(NSString*)file;

+ (NNTConfiguration*)shared;

//! set key-value.
- (void)set:(NSString*)key val:(NSString*)val;
- (void)set:(NSString*)key data:(NSData*)data;
- (void)set:(NSString*)key data:(void*)data dlen:(usize)dlen;
- (void)set:(NSString*)key obj:(id)obj;

//! remove key.
- (BOOL)del:(NSString*)key;

//! get value by key.
- (NSString*)get:(NSString*)key;
- (NSString*)get:(NSString*)key null:(NSString*)val;
- (NSString*)ava:(NSString*)key null:(NSString*)val;
- (NSData*)getAsData:(NSString*)key;
- (byte*)getAsBytes:(NSString*)key;
- (byte*)getAsBytes:(NSString*)key dlen:(usize*)dlen;
- (id)getAsObject:(NSString*)key;
- (id)getAsObject:(NSString*)key null:(id)obj;
- (id)avaAsObject:(NSString*)key null:(id)obj;

//! other types.
- (void)set:(NSString*)key boolValue:(bool)val;
- (void)set:(NSString*)key intValue:(int)val;
- (void)set:(NSString*)key floatValue:(float)val;
- (void)set:(NSString*)key doubleValue:(double)val;
- (void)set:(NSString*)key realValue:(real)val;

- (bool)getBool:(NSString*)key null:(bool)val;
- (int)getInt:(NSString*)key null:(int)val;
- (float)getFloat:(NSString*)key null:(float)val;
- (double)getDouble:(NSString*)key null:(double)val;
- (real)getReal:(NSString*)key null:(real)val;

- (bool)avaBool:(NSString*)key null:(bool)val;
- (int)avaInt:(NSString*)key null:(int)val;
- (float)avaFloat:(NSString*)key null:(float)val;
- (double)avaDouble:(NSString*)key null:(double)val;
- (real)avaReal:(NSString*)key null:(real)val;

//! open file.
- (BOOL)open:(NSString*)file;

//! clear.
- (void)clear;

//! static.
+ (NNTConfiguration*)configuration:(NSString*)file;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(store)
NNT_BEGIN_NS(ns)

using namespace ::wsi::ns;

class Configuration
: public Object<NNTConfiguration>
{
    typedef Object<NNTConfiguration> super;
    
public:
    
    explicit Configuration(String const& file)
    : super(nil)
    {
        this->_self = [[objc_type configuration:file] retain];
    }
    
    Configuration(Configuration& obj)
    : super(obj._self)
    {
        PASS;
    }
    
    Configuration(objc_type* obj)
    : super(obj)
    {
        PASS;
    }
    
    void set(ns::String const& val, ns::String const& key)
    {
        [this->_self set:key val:val];
    }
    
    void set(ns::Data const& da, ns::String const& key)
    {
        [this->_self set:key data:da];
    }
    
    void set(void* data, usize dlen, ns::String const& key)
    {
        [this->_self set:key data:data dlen:dlen];
    }
    
    void set(core::data const& da, ns::String const& key)
    {
        [this->_self set:key data:(void*)da.bytes() dlen:da.length()];
    }
    
    void set(id obj, ns::String const& key)
    {
        [this->_self set:key obj:obj];
    }
    
    void del(ns::String const& key)
    {
        [this->_self del:key];
    }
    
    ns::String string(ns::String const& key, ns::String const& null = @"")
    {
        return [this->_self get:key null:null];
    }
    
    ns::String string_ava(ns::String const& key, ns::String const& null = @"")
    {
        return [this->_self ava:key null:null];
    }

    ns::Data data(ns::String const& key)
    {
        return [this->_self getAsData:key];
    }
    
    byte* bytes(ns::String const& key)
    {
        return [this->_self getAsBytes:key];
    }
    
    void bytes(ns::String const& key, core::data& da)
    {
        usize dlen = 0;
        byte* bytes = [this->_self getAsBytes:key dlen:&dlen];
        da = core::data(bytes, dlen, core::assign);
        da.set_release(true);
    }

    id object(ns::String const& key, id null = nil)
    {
        return [this->_self getAsObject:key null:null];
    }
    
    id object_ava(ns::String const& key, id null = nil)
    {
        return [this->_self avaAsObject:key null:null];
    }

    void set(bool val, ns::String const& key)
    {
        [this->_self set:key boolValue:val];
    }
    
    void set(int val, ns::String const& key)
    {
        [this->_self set:key intValue:val];
    }
    
    void set(float val, ns::String const& key)
    {
        [this->_self set:key floatValue:val];
    }
    
    void set(double val, ns::String const& key)
    {
        [this->_self set:key doubleValue:val];
    }

    bool get_bool(ns::String const& key, bool null = false)
    {
        return [this->_self getBool:key null:null];
    }
    
    int get_int(ns::String const& key, int null = 0)
    {
        return [this->_self getInt:key null:null];
    }

    float get_float(ns::String const& key, float null = 0)
    {
        return [this->_self getFloat:key null:null];
    }
    
    double get_double(ns::String const& key, double null = 0)
    {
        return [this->_self getDouble:key null:null];
    }
    
    real get_real(ns::String const& key, real null = 0)
    {
        return [this->_self getReal:key null:null];
    }

    bool ava_bool(ns::String const& key, bool null = false)
    {
        return [this->_self avaBool:key null:null];
    }
    
    int ava_int(ns::String const& key, int null = 0)
    {
        return [this->_self avaBool:key null:null];
    }
    
    float ava_float(ns::String const& key, float null = 0)
    {
        return [this->_self avaFloat:key null:null];
    }
    
    double ava_double(ns::String const& key, double null = 0)
    {
        return [this->_self avaDouble:key null:null];
    }
    
    real ava_real(ns::String const& key, real null = 0)
    {
        return [this->_self avaReal:key null:null];
    }
    
    void set_readonly(bool val)
    {
        this->_self.readonly = val;
    }
    
    bool is_readonly() const
    {
        return this->_self.readonly;
    }
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

NNTCLASS(Configuration);

class connection_info;

NNTDECL_PRIVATE_HEAD_CXX(Configuration);

class Configuration
{
    NNTDECL_PRIVATE_CXX(Configuration);
    NNTDECL_NOCOPY(Configuration);
    
public:
    
    Configuration();
    explicit Configuration(core::string const&);
    ~Configuration();    
    
# ifdef NNT_PURE_CXX
    
    static Configuration& getInstance();
    
# endif
    
# ifdef NNT_OBJC
    
    explicit Configuration(ns::String const&);
    
    static Configuration& shared();
    
    bool open(ns::String const&);
    
# endif
    
public:
    
    //! open file.
    bool open(core::string const&);
    
    //! add record.
    bool add(void* key, usize klen, void* data, usize dlen);
    
    bool add(core::data const& key, core::data const& data)
    {
        return add((void*)key.bytes(), key.length(), (void*)data.bytes(), data.length());
    }
    
    //! set record.
    bool set(void* key, usize klen, void* data, usize dlen);
    
    bool set(core::data const& key, core::data const& data)
    {
        return set((void*)key.bytes(), key.length(), (void*)data.bytes(), data.length());
    }    
    
# ifdef NNT_OBJC

    //! in objc.
    bool set_obj(ns::String const& key, id obj);
    id get_obj(ns::String const& key, id null = nil) const;
    bool remove(ns::String const& key);
    
# endif
    
    template <typename keyT, typename valT>
    bool set(keyT const& key, valT const& val)
    {
        core::data dak = core::type_cast<core::data>(key);
        core::data dav = core::type_cast<core::data>(val);
        return this->set(dak, dav);
    }
    
    //! remove key.
    bool remove(void* key, usize klen);
    
    bool remove(core::data const& key)
    {
        return this->remove((void*)key.bytes(), key.length());
    }
    
    //! find.
    bool find(void* key, usize klen, core::data&) const;
    bool find(void* key, usize klen, core::list<core::data>& datas) const;
    
    bool find(core::data const& key, core::data& data) const
    {
        return find((void*)key.bytes(), key.length(), data);
    }
    
    bool find(core::data const& key, core::list<core::data>& datas) const
    {
        return find((void*)key.bytes(), key.length(), datas);
    }
    
    template <typename keyT, typename valT>
    typename ::wsi::wtl::cxx_type<valT>::type
    get(keyT const& key, valT const& null) const
    {
        core::data da;
        if (find(core::type_cast<core::data>(key), da) == false)
            return null;
        return core::type_cast< typename ::wsi::wtl::cxx_type<valT>::type >(da);
    }
    
    template <typename valT>
    typename ::wsi::wtl::cxx_type<valT>::type
    get(core::data const& key, valT const& null) const
    {
        core::data da;
        if (find(key, da) == false)
            return null;
        return core::type_cast< typename ::wsi::wtl::cxx_type<valT>::type >(da);
    }
    
    void clear();
    
protected:
    
    void _init();
    
    bool _connect(connection_info const&);
    
};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif