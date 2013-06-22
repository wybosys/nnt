
# ifndef __NNT_PARSER_XMLOBJ_49D56ABF63134B9C884065F6F289FE00_H_INCLUDED
# define __NNT_PARSER_XMLOBJ_49D56ABF63134B9C884065F6F289FE00_H_INCLUDED

# import "NullObjParser.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(XmlObjParser);

@interface XmlObjParser : NullObjParser {
    
    NSString *_encoding;
    NSString *_version;
    NSString *_root;
    
    //! hide root. default is YES.
    BOOL _hideRoot;
    
    NNTDECL_PRIVATE(XmlObjParser);
}

@property (nonatomic, copy) NSString *encoding;
@property (nonatomic, copy) NSString *version;
@property (nonatomic, copy) NSString *root;
@property (nonatomic, assign) BOOL hideRoot;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

class XmlObject
: public NullObjParser<XmlObjParser>
{
public:
        
    virtual ns::Data parse_todata(ns::Object<> const&);
    virtual ns::Object<> to_object(ns::Data const&);
    
    void hideroot(bool val)
    {
        this->_self.hideRoot = val;
    }
    
    bool is_hideroot() const
    {
        return this->_self.hideRoot;
    }
    
    ns::Dictionary parse(ns::Data const& da)
    {
        return (ns::Dictionary::objc_type*)to_object(da).nsobject();
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
