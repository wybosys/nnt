
# ifndef __WSI_PARSER_NULLOBJPARSER_D02485F2497D4987904D29E14A0FDCBE_H_INCLUDED
# define __WSI_PARSER_NULLOBJPARSER_D02485F2497D4987904D29E14A0FDCBE_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@protocol NullObjParser <NSObject>

@property (nonatomic, copy) NSString* contentType;
@property (nonatomic, assign) NSStringEncoding dataEncoding;

@required

- (NSObject*)parse_object:(NSData*)data;

@optional

- (NSData*)parse_todata:(NSObject*)obj;
- (void)prepare:(id)obj;

@end

WSI_EXTERN NSStringEncoding kParserDataEncoding;

@interface NullObjParser : WSIObject <NullObjParser> {
    
    //! the object which own this parser.
    id owner;
    
    //! how many bytes processed.
    ulonglong byteCount;
    
    //! contentType;
    NSString* contentType;
    
    //! encoding.
    NSStringEncoding dataEncoding;
}

@property (nonatomic, assign) id owner;
@property (nonatomic, assign) ulonglong byteCount;

//! from data to object, it will called by parser_object.
- (id)to_object:(id)data;

@end

# ifdef WSI_LIBONLY

WSI_EXTERN void ParserInit();
WSI_EXTERN void ParserFin();

# endif

// signal.
WSI_EXTERN signal_t kSignalParserError;

# ifdef WSI_CXX

@interface _cxxnull_objectparser : NullObjParser

@end

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(parser)

struct IObjParser
{
    virtual ~IObjParser() {}
    virtual ns::Data parse_todata(ns::Object<> const&) = 0;
    virtual ns::String content_type() const = 0;
    virtual ns::Object<> parse_object(ns::Data const&) = 0;
};

template <typename parserT>
class NullObjParser
: public ns::Object<parserT>,
public IObjParser
{
public:
    
    virtual ns::Data parse_todata(ns::Object<> const&)
    {
        return ns::null_data;
    }
    
    virtual ns::String content_type() const
    {
        return this->_self.contentType;
    }
    
    virtual ns::Object<> parse_object(ns::Data const& da)
    {
        this->_self.byteCount = da.length();
        return this->to_object(da);
    }
    
    virtual id objcparser() const
    {
        return (id)this->_self;
    }
    
    virtual ns::Object<> to_object(ns::Data const&) = 0;
    
    void set_encoding(NSStringEncoding encoding)
    {
        this->_self.dataEncoding = encoding;
    }
    
};

class NullObject
: public NullObjParser< _cxxnull_objectparser >
{
public:
    
    virtual ns::Object<> to_object(ns::Data const& da)
    {
        return [this->_self to_object:da];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif // cxx

# endif // objc

# endif
