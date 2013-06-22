
# ifndef __NNT_PARSER_XMLUTIL_0030448F30B94CE9831B7645BC89CD95_H_INCLUDED
# define __NNT_PARSER_XMLUTIL_0030448F30B94CE9831B7645BC89CD95_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

NNTCLASS(XmlAttributeUtil);

class XmlAttributeUtil
{
public:
    
    //! find attribute's value in str, using xml attribute pattern.
    static core::string AttributeFind(core::string const& tgt, core::string const& str);
    
    //! make attribute string.
    static core::string AttributeMake(core::string const& name, core::string const& value, bool str = false);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
