
# ifndef __WSI_CROSS_EMAILCONTENT_2EA945E4418D44D2A8142FACB776C9A7_H_INCLUDED
# define __WSI_CROSS_EMAILCONTENT_2EA945E4418D44D2A8142FACB776C9A7_H_INCLUDED

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)

class EmailContent
{
public:
    
    EmailContent();
    ~EmailContent();
    
public:
    
    core::string header;
    core::string message;
    core::string from;
    
    core::string to;
    core::string cc;
    core::string bcc;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif