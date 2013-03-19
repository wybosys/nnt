
# ifndef __WSI_PARSER_XMLUTIL_0030448F30B94CE9831B7645BC89CD95_H_INCLUDED
# define __WSI_PARSER_XMLUTIL_0030448F30B94CE9831B7645BC89CD95_H_INCLUDED

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(parser)

WSICLASS(XmlAttributeUtil);

class XmlAttributeUtil
{
public:
    
    //! find attribute's value in str, using xml attribute pattern.
    static core::string AttributeFind(core::string const& tgt, core::string const& str);
    
    //! make attribute string.
    static core::string AttributeMake(core::string const& name, core::string const& value, bool str = false);
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif
