
# ifndef __NNT_CROSS_SMTPCLIENT_7F9F12B067BA4C32B543CF65DFDDEF1B_H_INCLUDED
# define __NNT_CROSS_SMTPCLIENT_7F9F12B067BA4C32B543CF65DFDDEF1B_H_INCLUDED

# include "EmailContent.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cross)

NNTDECL_PRIVATE_HEAD_CXX(SmtpClient);

class SmtpClient
{
    NNTDECL_PRIVATE_CXX(SmtpClient);
    NNTDECL_NOCOPY(SmtpClient);
    
public:
    
    SmtpClient();
    ~SmtpClient();    
    
    bool post();
    
    virtual core::data get_user() const;
    virtual core::data get_password() const;
    
    EmailContent content;
    
    core::string server;
    core::string user;
    core::string password;
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif