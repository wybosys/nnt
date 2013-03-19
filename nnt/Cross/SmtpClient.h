
# ifndef __WSI_CROSS_SMTPCLIENT_7F9F12B067BA4C32B543CF65DFDDEF1B_H_INCLUDED
# define __WSI_CROSS_SMTPCLIENT_7F9F12B067BA4C32B543CF65DFDDEF1B_H_INCLUDED

# include "EmailContent.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)

WSIDECL_PRIVATE_HEAD_CXX(SmtpClient);

class SmtpClient
{
    WSIDECL_PRIVATE_CXX(SmtpClient);
    WSIDECL_NOCOPY(SmtpClient);
    
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif