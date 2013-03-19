
# ifndef __APP_MODEL_F2D96CCF4B7444C18073154837CFD5B8_H_INCLUDED
# define __APP_MODEL_F2D96CCF4B7444C18073154837CFD5B8_H_INCLUDED

# include "Model.h"
# include "Context.h"
# include "Server.h"

NNTAPP_BEGIN

class MAddDeviceToken
: public ns::Model
{
public:
    
    MAddDeviceToken();
    virtual bool process(id) { return true; }
    virtual ns::URL url() const;
    
    ns::Data dt;
};

NNTAPP_END

# endif
