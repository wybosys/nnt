
# ifndef __WSI_PARSER_HTMLOBJ_949CE4314C8343DE806030E119900D14_H_INCLUDED
# define __WSI_PARSER_HTMLOBJ_949CE4314C8343DE806030E119900D14_H_INCLUDED

# import "NullObjParser.h"
# import "HtmlParser.h"

WSI_BEGIN_HEADER_OBJC

@interface HtmlObjParser : NullObjParser {
    NSMutableArray* _queries;
}

@property (nonatomic, retain) NSMutableArray* queries;

//! add query.
- (void)add_query:(NSString*)str;
- (void)set_query:(NSString*)str;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "HtmlParser.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(parser)

class HtmlObject
: public NullObjParser<HtmlObjParser>
{
public:
    
    HtmlObject()
    {
        PASS;
    }
    
    virtual ns::Data parse_todata(ns::Object<> const&);
    virtual ns::String content_type() const;
    virtual ns::Object<> to_object(ns::Data const&);
    
    void add_query(ns::String const& str)
    {
        [this->_self add_query:str];
    }
    
    void set_query(ns::String const& str)
    {
        [this->_self set_query:str];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif