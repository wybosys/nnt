
# ifndef __NNT_NSSTRING_8B02981BC619423FADBA6410572E7EF1_H_INCLUDED
# define __NNT_NSSTRING_8B02981BC619423FADBA6410572E7EF1_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSString (NNT)

//! to binary string.
- (NSString*)encodeBinaryString:(NSStringEncoding)encoding;

//! from binary string.
- (NSString*)decodeBinaryString:(NSStringEncoding)encoding;

//! unicode string.
- (NSString*)toUnicodeString;

//! from unicode string.
- (NSString*)fromUnicodeString;

//! uuid string
+ (NSString*)uuidString;

//! md5
- (NSString*)md5;

//! hmac(sha1-base64).
- (NSString*)hmac_sha1:(NSString*)secret;

//! uniqueIdentify;
- (NSString*)uniqueIdentify;

//! real value.
- (real)realValue;

//! json.
- (id)json_decode;

//! string to array.
- (NSArray*)getCharactersArray;
- (NSArray*)getCharactersArray:(BOOL)reverse;

//! unescape.
- (NSString*)unescape;

//! is empty.
//- (BOOL)isEmpty;

//! is not empty. because [nil isEmpty] will return NO, so call this function safely.
//! will return NO while "", "   ".
- (BOOL)notEmpty;

//! value type.
- (NNTValueType)valueType;

//! url.
- (NSString*)urlencode;
- (NSString*)urldecode;
 
@end

NNTDECL_CATEGORY(NSString, NNT);

typedef enum {
    StringRegexOptionsNoOptions             = 0,
    StringRegexOptionsCaseless              = 2,
    StringRegexOptionsComments              = 4,
    StringRegexOptionsDotAll                = 32,
    StringRegexOptionsMultiline             = 8,
    StringRegexOptionsUnicodeWordBoundaries = 256
} StringRegexOptions;

@interface NSString (Regex)

//! is matched by regex.
- (BOOL)matchedByRegex:(NSString *)regex;
- (BOOL)matchedByRegex:(NSString *)regex full:(BOOL)full;
- (BOOL)matchedByRegex:(NSString *)regex inRange:(NSRange)range;
- (BOOL)matchedByRegex:(NSString *)regex options:(StringRegexOptions)options inRange:(NSRange)range error:(NSError **)error;

//! replace by regex.
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regex withString:(NSString *)replacement;
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regex withString:(NSString *)replacement range:(NSRange)searchRange;
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regex withString:(NSString *)replacement options:(StringRegexOptions)options range:(NSRange)searchRange error:(NSError **)error;

//! grep.
- (NSArray *)componentsMatchedByRegex:(NSString *)regex;
- (NSArray *)componentsMatchedByRegex:(NSString *)regex capture:(NSInteger)capture;
- (NSArray *)componentsMatchedByRegex:(NSString *)regex range:(NSRange)range;
- (NSArray *)componentsMatchedByRegex:(NSString *)regex options:(StringRegexOptions)options range:(NSRange)range capture:(NSInteger)capture error:(NSError **)error;


- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regex;
- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regex range:(NSRange)range;
- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regex options:(StringRegexOptions)options range:(NSRange)range error:(NSError **)error;

- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regex;
- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regex range:(NSRange)range;
- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regex options:(StringRegexOptions)options range:(NSRange)range error:(NSError **)error;

@end

NNTDECL_CATEGORY(NSString, Regex);

NNT_EXTERN NSString *kNSStringYES, *kNSStringNO;

NNT_EXTERN id kNSStringUUID();
NNT_EXTERN id kNSStringTimestamp();
NNT_EXTERN id kNSStringNonce();
NNT_EXTERN id kNSStringNonceSimple();

NNT_EXTERN NSStringEncoding NSGB18030Encoding;
NNT_EXTERN NSStringEncoding NSGB2312Encoding;
NNT_EXTERN NSStringEncoding NSGBKEncoding;
NNT_EXTERN NSStringEncoding NSGig5Encoding;

NNTAPI(NSString*) GetStringEncodingName(NSStringEncoding encoding);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNT_EXTERN NSString* tostr(int val);
NNT_EXTERN NSString* tostr(uint val);
NNT_EXTERN NSString* tostr(float val);
NNT_EXTERN NSString* tostr(double val);
NNT_EXTERN NSString* tostr(long val);
NNT_EXTERN NSString* tostr(ulong val);
NNT_EXTERN NSString* tostr(longlong val);
NNT_EXTERN NSString* tostr(ulonglong val);
NNT_EXTERN NSString* tostr(NSString* val);
NNT_EXTERN NSString* tostr(NSData* val);
NNT_EXTERN NSString* tostr(char const* val);
NNT_EXTERN NSString* tostr(core::string const& val);
NNT_EXTERN NSString* tostr(bool val);
NNT_EXTERN NSString* tostr(NSURL* url);

template <typename valT>
inline_impl NSString* tostr(valT val, NSString* fmt)
{
    return [NSString stringWithFormat:fmt, val, nil];
}

NNT_BEGIN_NS(ns)

class Data;

NNT_BEGIN_NS(tpl)

template <typename strT>
class String
: public Object<strT>
{
    typedef String<strT> self_type;
    typedef Object<strT> super;
    
public:
    
    typedef typename super::objc_type objc_type;
    typedef strT string_type;
    
    enum
    {
        DEFAULT_ENCODING = NSUTF8StringEncoding,
    };
    
    String()
    {
        PASS;
    }
    
    String(string_type* str)
    : super(nil)
    {
        this->_self = [str retain];
    }
    
    explicit String(id str)
    : super(nil)
    {
        this->_self = [str retain];
    }
    
    String(self_type const& r)
    : super(nil)
    {
        this->_self = [r._self retain];
    }
    
    template <typename valT>
    explicit String(valT val,
                          typename ntl::is_wrapper<valT>::nonwrapper const* = NULL)
    : super(nil)
    {
        this->_self = [::nnt::tostr(val) retain];
    }
    
    template <typename valT>
    String(valT const& obj,
           typename ntl::is_wrapper<valT>::wrapper* = NULL)
    {
        this->_self = [obj retain];
    }
    
    String(Data const& data, NSStringEncoding encoding = DEFAULT_ENCODING);
    
    String(core::string const& str, NSStringEncoding encoding = DEFAULT_ENCODING)
    : super(nil)
    {
        this->_self = [[NSString stringWithCString:str.c_str() encoding:encoding] retain];
    }
    
    String(char const* str, NSStringEncoding encoding = DEFAULT_ENCODING)
    : super(nil)
    {
        this->_self = [[NSString stringWithCString:str encoding:encoding] retain];
    }
        
    ~String()
    {
        PASS;
    }
    
    static self_type As(id obj)
    {
        return (NSString*)obj;
    }
    
    template <typename valT>
    static self_type Value(valT const& val)
    {
        return tostr(val);
    }
    
    static self_type Format(NSString* fmt, ...)
    {
        va_list arg;
        va_start(arg, fmt);
        objc_type* str = [[objc_type alloc] initWithFormat:fmt arguments:arg];
        va_end(arg);
        self_type ret(str);
        safe_release(str);
        return ret;
    }
    
    self_type operator + (self_type const& r) const
    {
        return *this + r._self;
    }
        
    self_type operator + (string_type* r) const
    {
# ifdef NNT_DEBUG
        if (r == nil)
            trace_msg(@"exception: append a nil string.");
# endif
        objc_type* str = [this->_self stringByAppendingString:r];
        return self_type(str);
    }
    
    self_type& operator += (string_type* r)
    {
# ifdef NNT_DEBUG
        if (r == nil)
            trace_msg(@"exception: append a nil string.");
# endif
        objc_type* str = [this->_self stringByAppendingString:r];
        safe_release(this->_self);
        this->_self = [str retain];
        return *this;
    }
    
    self_type& operator << (self_type const& r)
    {
        return *this += r._self;
    }
    
    self_type& operator = (self_type const& r)
    {
        objc_type* str = [r._self copy];
        safe_release(this->_self);
        this->_self = str;
        return *this;
    }
        
    bool operator == (string_type* r) const
    {
        return [this->_self isEqualToString:r];
    }
    
    bool operator != (string_type* r) const
    {
        return ![this->_self isEqualToString:r];
    }
    
    bool is_equal(string_type* r) const
    {
        return [this->_self isEqualToString:r];
    }
    
    usize length() const
    {
        return [this->_self length];
    }
    
    char const* utf8() const
    {
        return [this->_self UTF8String];
    }
    
    bool not_empty() const
    {
        return [this->_self notEmpty];
    }
    
    bool is_empty() const
    {
        return !not_empty();
    }
    
    static self_type const& Null()
    {
        static self_type const null_str;
        return null_str;
    }
    
    bool contain(NSString* tgt) const
    {
        NSRange rg = [this->_self rangeOfString:tgt];
        return rg.length != 0;
    }
    
    self_type replace(String const& src, String const& des) const
    {
        return [this->_self stringByReplacingOccurrencesOfString:src withString:des];
    }
    
};
    
NNT_END_NS
    
class StringEncode
{
public:
    
    static NSString* unique_id(NSString* str)
    {
        return [str uniqueIdentify];
    }
    
    static NSString* md5(NSString* str)
    {
        return [str md5];
    }
    
    static NSString* URLEncode(NSString* str)
    {
        return [str urlencode];
    }
    
    static NSString* URLDecode(NSString* str)
    {
        return [str urldecode];
    }
    
};

typedef tpl::String<NSString> String;

NNT_EXTERN String null_string;

inline_impl String uuid_string()
{
    return [NSString uuidString];
}

static String operator + (NSString* l, String const& r)
{
    String str_l(l);
    return str_l + r.nsobject();
}

class Regex
{
public:
    
    Regex()
    {
        PASS;
    }
    
    Regex(String const& str)
    : _regex(str)
    {
        PASS;
    }
    
    void set(String const& str)
    {
        _regex = str;
    }
    
    String const& get() const
    {
        return _regex;
    }
    
    bool match(String const& str, bool full = true)
    {
        return [str matchedByRegex:_regex full:full] == YES;
    }
    
    NSArray* grep(String const& str)
    {
        return [str componentsMatchedByRegex:_regex];
    }
    
    NSArray* capture(String const& str)
    {
        return [str captureComponentsMatchedByRegex:_regex];
    }
    
    NSArray* captures(String const& str)
    {
        return [str arrayOfCaptureComponentsMatchedByRegex:_regex];
    }
    
protected:
    String _regex;
};

NNT_END_NS

NNT_BEGIN_NS(ntl)

template <>
struct value_type< ::NSString* >
{ 
    typedef ::nnt::ns::String type; 
};


template <>
struct cxx_type<NSString*>
{
    typedef ns::String type;
};

template <>
inline_impl data type_cast<data, ns::String>(ns::String const& str)
{
    //return data((byte const*)str.utf8(), str.length());
    // str.utf8() is not equal to encoding.
    NSData* da = [str dataUsingEncoding:NSUTF8StringEncoding];
    return data((byte const*)[da bytes], [da length]);
}

template <>
inline_impl data type_cast<data, NSString>(NSString* str)
{
    NSData* da = [str dataUsingEncoding:NSUTF8StringEncoding];
    return data((byte const*)[da bytes], [da length]);
}

template <>
inline_impl data type_cast<data, NSString>(NSString const* str)
{
    NSData* da = [str dataUsingEncoding:NSUTF8StringEncoding];
    return data((byte const*)[da bytes], [da length]);
}

template <>
inline_impl data type_cast<data, NSString*>(NSString* const& str)
{
    NSData* da = [str dataUsingEncoding:NSUTF8StringEncoding];
    return data((byte const*)[da bytes], [da length]);
}

template <>
inline_impl core::string type_cast<core::string, ns::String>(ns::String const& str)
{
    return core::tostr(str);
}

template <>
inline_impl ns::String type_cast<ns::String, core::string>(core::string const& str)
{
    return ::nnt::tostr(str);
}

template <>
inline_impl string type_cast<string, NSString>(NSString* str)
{
    NSData* data = [str dataUsingEncoding:NSUTF8StringEncoding];
    return string((char const*)[data bytes], [data length]);
}
    
NNT_END_NS

template <>
inline_impl id to_object<core::string>(core::string const& str)
{
    return ntl::type_cast<ns::String>(str);
}
    
NNT_END_HEADER_CXX

NNT_BEGIN_HEADER_C

using ::nnt::tostr;

NNT_END_HEADER_C

# endif

# endif
