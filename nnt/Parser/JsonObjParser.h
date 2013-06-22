
# ifndef __NNT_PARSER_JSONOBJ_9A363773982D4C4AA3A4FC0CB7C59349_H_INCLUDED
# define __NNT_PARSER_JSONOBJ_9A363773982D4C4AA3A4FC0CB7C59349_H_INCLUDED

# include "NullObjParser.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface JsonObjParser : NullObjParser

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

class JsonObject
: public NullObjParser<JsonObjParser>
{
public:
    
    virtual ns::Data parse_todata(ns::Object<> const&);
    virtual ns::String content_type() const;
    virtual ns::Object<> to_object(ns::Data const&);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif // cxx

# endif // objc

# endif