
# ifndef __WSI_NSDATA_859AA390F3184E689D5A01C24E7B0783_H_INCLUDED
# define __WSI_NSDATA_859AA390F3184E689D5A01C24E7B0783_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface NSData (WSI)

//! encode binary.
- (NSData*)encodeBinaryString;

//! need release.
- (void)encodeBinaryStringEx:(NSMutableData*)data;

//! decode binary.
- (NSData*)decodeBinaryString;

//! need release.
- (void)decodeBinaryStringEx:(NSMutableData*)data;

//! md5
- (NSData*)md5;
- (void)md5ex:(NSMutableData*)data;

//! coretype.
- (uint)coreType;

@end

WSIDECL_CATEGORY(NSData, WSI);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "NSString+WSI.h"
# include "NSURL+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

WSI_BEGIN_NS(tpl)

template <typename implT, typename objcT>
class Data
: public Object<objcT>
{
    typedef Object<objcT> super;
    
public:
    
    Data()
    {
        PASS;
    }
    
    Data(objcT* obj)
    : super(obj)
    {
        PASS;
    }
    
    static implT Obj(id obj)
    {
        return implT((objcT*)obj);
    }
    
    static implT Obj(void* obj)
    {
        return implT((objcT*)obj);
    }
        
    usize size() const
    {
        return [this->_self length];
    }
    
    usize length() const
    {
        return [this->_self length];
    }
    
    byte const* bytes() const
    {
        return (byte const*)[this->_self bytes];
    }
    
    template <typename valT>
    void map(valT& obj) const
    {
        uint len = [this->_self length];
        if (len == 0)
            memset(&obj, 0, sizeof(valT));
        else
            memcpy(&obj, [this->_self bytes], len);
    }
    
};

WSI_END_NS

class Data
: public tpl::Data<Data, NSData>
{
    typedef tpl::Data<Data, NSData> super;
    
public:
    
    Data()
    {
        PASS;
    }
    
    Data(NSData* da)
    : super(da)
    {
        PASS;
    }
    
    Data(Data const& da)
    : super(da._self)
    {
        PASS;
    }
    
    explicit Data(ns::String const& r, NSStringEncoding encoding = NSUTF8StringEncoding)
    : super(nil)
    {
        this->_self = [[r dataUsingEncoding:encoding] retain];
    }
    
    explicit Data(ns::URL const& url)
    : super(nil)
    {
        this->_self = [[NSData alloc] initWithContentsOfURL:url];
    }
    
    explicit Data(void* data, usize len, core::_bool_copy copy, bool release)
    : super(nil)
    {
        if (copy == core::copy)
        {
            this->_self = [[NSData alloc] initWithBytes:data length:len];
        }
        else
        {
            this->_self = [[NSData alloc] initWithBytesNoCopy:data length:len freeWhenDone:release];
        }
    }
    
    template <typename valT>
    explicit Data(valT const& obj,
                  typename wtl::is_equal<valT, id>::unequal* = NULL)
    {
        this->_self = [[NSData alloc] initWithBytes:(void*)&obj length:sizeof(valT)];
    }
    
};

class MutableData
: public tpl::Data<MutableData, NSMutableData>
{
    typedef tpl::Data<MutableData, NSMutableData> super;
    
public:
    
    MutableData()
    {
        PASS;
    }
    
    MutableData(NSMutableData* da)
    : super(da)
    {
        PASS;
    }
    
    MutableData(MutableData& r)
    : super(r._self)
    {
        PASS;
    }
        
    MutableData& append(ns::MutableData const& r)
    {
        [this->_self appendData:r];
        return *this;
    }
    
    MutableData& append(ns::Data const& r)
    {
        [this->_self appendData:r];
        return *this;
    }
    
    MutableData& append(core::data const& da)
    {
        [this->_self appendBytes:(void const*)da.bytes() length:da.length()];
        return *this;
    }
    
};

WSI_BEGIN_NS(tpl)

template <typename strT>
inline_impl String<strT>::String(ns::Data const& data, NSStringEncoding encoding)
: super(nil)
{
    this->_self = [[NSString alloc] initWithData:data encoding:encoding];
}

WSI_END_NS

WSI_EXTERN Data null_data;

WSI_END_NS

WSI_BEGIN_NS(wtl)

template <>
inline_impl data type_cast<data, ns::Data>(ns::Data const& da)
{
    return data(da.bytes(), da.length(), wtl::assign);
}

template <>
inline_impl ns::Data type_cast<ns::Data, data>(data const& da)
{
    return ns::Data((void*)da.bytes(), da.size(), wtl::assign, false);
}

template <>
inline_impl data dup_cast<data, ns::Data>(ns::Data const& da)
{
    return data(da.bytes(), da.size(), wtl::copy);
}

template <>
inline_impl ns::Data dup_cast<ns::Data, data>(data const& da)
{
    return ns::Data((void*)da.bytes(), da.size(), wtl::copy, true);
}

template <>
inline_impl ns::Data type_cast<ns::Data, ns::String>(ns::String const& str)
{
    return ns::Data(str);
}

template <>
inline_impl ns::Data type_cast<ns::Data, NSString>(NSString* str)
{
    return ns::Data(ns::String(str));
}

template <>
inline_impl ns::String type_cast<ns::String, ns::Data>(ns::Data const& da)
{
    return ns::String(da, ns::String::DEFAULT_ENCODING);
}

template <>
inline_impl ns::String type_cast<ns::String, NSData>(NSData* da)
{
    return ns::String(da, ns::String::DEFAULT_ENCODING);
}

template <>
inline_impl ns::String type_cast<ns::String, data>(data const& da)
{
    return ns::String(core::type_cast<ns::Data>(da));
}

WSI_END_NS

WSI_END_HEADER_CXX

# endif

# endif