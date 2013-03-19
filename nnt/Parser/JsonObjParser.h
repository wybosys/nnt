
# ifndef __WSI_PARSER_JSONOBJ_9A363773982D4C4AA3A4FC0CB7C59349_H_INCLUDED
# define __WSI_PARSER_JSONOBJ_9A363773982D4C4AA3A4FC0CB7C59349_H_INCLUDED

# include "NullObjParser.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface JsonObjParser : NullObjParser

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(parser)

class JsonObject
: public NullObjParser<JsonObjParser>
{
public:
    
    virtual ns::Data parse_todata(ns::Object<> const&);
    virtual ns::String content_type() const;
    virtual ns::Object<> to_object(ns::Data const&);
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif // cxx

# endif // objc

# endif