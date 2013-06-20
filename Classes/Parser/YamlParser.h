
# ifndef __NNT_PARSER_YAML_5B8A76ACAE084C01807281E46939A8B8_H_INCLUDED
# define __NNT_PARSER_YAML_5B8A76ACAE084C01807281E46939A8B8_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

NNTDECL_PRIVATE_HEAD_CXX(YamlDocument);

class YamlDocument
{
    
    NNTDECL_PRIVATE_CXX(YamlDocument);
    
public:
    
    YamlDocument();
    ~YamlDocument();
    
    bool parse(core::data const&);

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
