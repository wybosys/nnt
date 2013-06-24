
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

# ifdef NNT_CXX

# include "../Core/ObjectDL.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

NNTDECL_PRIVATE_HEAD_CXX(JsonDocument);

class JsonObj;

class JsonDocument
{
    NNTDECL_PRIVATE_CXX(JsonDocument);
    
public:
    
    JsonDocument();
    ~JsonDocument();
    
    void clear();
    bool parse(core::data const&);
    bool save(core::data&) const;
    
    NNTDECL_PRIVATE_FRIEND(JsonObj);
};

class JsonObj
{
public:
    
    JsonObj(JsonDocument&);
    ~JsonObj();
    
    lang::Object* to_object() const;
    bool to_data(lang::Object const*);
    
protected:
    
    JsonDocument& _doc;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
