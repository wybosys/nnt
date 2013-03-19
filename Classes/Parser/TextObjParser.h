
# ifndef __WSI_PARSER_TEXTOBJ_9FB00DC021F9487889C5D63496AB2B6F_H_INCLUDED
# define __WSI_PARSER_TEXTOBJ_9FB00DC021F9487889C5D63496AB2B6F_H_INCLUDED

# include "NullObjParser.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface TextObjParser : NullObjParser

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(parser)

class TextObject
: public NullObjParser<TextObjParser>
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
