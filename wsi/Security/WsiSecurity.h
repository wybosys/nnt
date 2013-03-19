
# ifndef __WSI_SECURITY_00B88C23D4944A15B0AB1BFC17110DE6_H_INCLUDED
# define __WSI_SECURITY_00B88C23D4944A15B0AB1BFC17110DE6_H_INCLUDED

# include "./AES+WSI.h"
# include "./DES+WSI.h"
# include "./BaseN+WSI.h"
# include "./MDN+WSI.h"
# include "./RSA+WSI.h"
# include "./UUID+WSI.h"
# include "./SHA+WSI.h"

WSI_BEGIN_HEADER_CXX

WSICLASS(nonce);

class nonce
{
public:
    
    static core::string simple();
    
};

WSI_END_HEADER_CXX

# endif