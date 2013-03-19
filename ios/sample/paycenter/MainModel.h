
# ifndef __MAIN_MODEL_83409FF2B7624D8EA240ABF9258398CE_H_INCLUDED
# define __MAIN_MODEL_83409FF2B7624D8EA240ABF9258398CE_H_INCLUDED

# include "Model.h"
# include "Server.h"
# include "Context.h"

NNTAPP_BEGIN

class ByPayModel
: public ns::Model
{
public:
    
    ByPayModel();
    
    virtual bool process(id result);
    
    ns::String IN oid, time, amt, desc, timeout, backendurl;
    ns::String result;
};

NNTAPP_END

# endif
