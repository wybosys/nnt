
# ifndef __NNT_SECURITY_00B88C23D4944A15B0AB1BFC17110DE6_H_INCLUDED
# define __NNT_SECURITY_00B88C23D4944A15B0AB1BFC17110DE6_H_INCLUDED

# include "./AES+NNT.h"
# include "./DES+NNT.h"
# include "./BaseN+NNT.h"
# include "./MDN+NNT.h"
# include "./RSA+NNT.h"
# include "./UUID+NNT.h"
# include "./SHA+NNT.h"

NNT_BEGIN_HEADER_CXX

NNTCLASS(nonce);

class nonce
{
public:
    
    static core::string simple();
    
};

NNT_END_HEADER_CXX

# endif
