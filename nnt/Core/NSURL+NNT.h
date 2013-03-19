
# ifndef __NNT_CORE_NSURL_87B52856AD554A799F9FD6622EE8975E_H_INCLUDED
# define __NNT_CORE_NSURL_87B52856AD554A799F9FD6622EE8975E_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSURL (NNT)

//! from utf8 string.
+ (NSURL*)URLWithUTF8String:(NSString*)str;

# ifndef NNT_iOS_4

//! path extension.
- (NSString *)pathExtension;

//! append path.
- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent;

# endif

//! combine arguments, arr is a key-value array.
+ (NSString*)combineArguments:(NSArray*)arr;

//! combine arguments, arr is a key-value array.
+ (NSString*)combineArgumentsDictionary:(NSDictionary*)dict;

@end

NNTDECL_CATEGORY(NSURL, NNT);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class URL
: public ::nnt::ns::Object<NSURL>
{
    typedef ::nnt::ns::Object<NSURL> super;
    
public:
    
    URL(String const& str)
    : super(nil)
    {
        if (str.is_null())
        {
            this->_self = nil;
        }
        else
        {
            this->_self = [[NSURL alloc] initWithString:str];
        }
    }
    
    URL(NSURL* url)
    : super(url)
    {
        PASS;
    }
    
    URL(URL const& r)
    : super(r)
    {
        PASS;
    }
    
    URL()
    : super(nil)
    {
        PASS;
    }
    
    static URL String(ns::String const& str)
    {
        return [NSURL URLWithString:str];
    }
    
    static URL UTF8(ns::String const& str)
    {
        return [NSURL URLWithUTF8String:str];
    }
    
    static URL File(ns::String const& str)
    {
        return [NSURL fileURLWithPath:str];
    }
    
    ns::String absolute_string() const
    {
        return [this->_self absoluteString];
    }
    
    ns::String relative_path() const
    {
        return [this->_self relativePath];
    }
    
    ns::String relative_string() const
    {
        return [this->_self relativeString];
    }
    
    ns::String std() const
    {
        return relative_path();
    }
    
    operator ns::String () const
    {
        return std();
    }
    
    static URL Bundle(ns::String const&);
    
    URL& operator = (ns::String const& str)
    {
        _release();
        this->_self = [[NSURL alloc] initWithString:str];
        return *this;
    }
    
    URL& operator = (URL const& r)
    {
        _release();
        this->_self = [r._self retain];
        return *this;
    }
    
    URL& operator += (ns::String const& comp)
    {
        NSURL* url = [this->_self URLByAppendingPathComponent:comp];
        _set(url);
        return *this;
    }
    
    ns::Array components() const
    {
        return [this->_self pathComponents];
    }
    
    ns::String component_last() const
    {
        return [this->_self lastPathComponent];
    }
    
    ns::String extension() const
    {
        return [this->_self pathExtension];
    }

    ns::URL append_comp(ns::String comp) const
    {
        return [this->_self URLByAppendingPathComponent:comp];
    }
    
    ns::URL append_ext(ns::String ext) const
    {
        return [this->_self URLByAppendingPathExtension:ext];
    }
    
    ns::URL delete_last() const
    {
        return [this->_self URLByDeletingLastPathComponent];
    }
    
    ns::URL delete_ext() const
    {
        return [this->_self URLByDeletingPathExtension];
    }
    
    bool is_file() const
    {
        return [this->_self isFileURL];
    }
    
};

NNT_EXTERN URL const null_url;

class URLRequest
: public ns::Object<NSMutableURLRequest>
{
    typedef ns::Object<NSMutableURLRequest> super;
    typedef URLRequest self_type;
    
public:
    
    URLRequest()
    {
        PASS;
    }
    
    URLRequest(ns::URL const& url)
    : super(nil)
    {
        this->_self = [[objc_type alloc] initWithURL:url];
    }
    
    URLRequest(ns::String const& str)
    : super(nil)
    {
        NSURL* url = [NSURL URLWithString:str];
        this->_self = [[objc_type alloc] initWithURL:url];
    }

    void set_cache(NSURLRequestCachePolicy cache)
    {
        this->_self.cachePolicy = cache;
    }
    
    NSURLRequestCachePolicy cache_policy() const
    {
        return this->_self.cachePolicy;
    }
    
    static self_type NoCache(ns::String const& url)
    {
        self_type obj;
        obj.set_cache(NSURLRequestReloadIgnoringLocalCacheData);
        return obj;
    }
    
};

NNT_END_NS
    
NNT_BEGIN_NS(ntl)
    
template <>
inline_impl ns::String type_cast<ns::String, ns::URL>(ns::URL const& url)
{
    return url.relative_string();
}
    
template <>
inline_impl string type_cast<string, ns::URL>(ns::URL const& url)
{
    return type_cast<string>(url.std());
}
    
NNT_END_NS
    
NNT_END_HEADER_CXX

# endif

# endif