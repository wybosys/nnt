
# ifndef MODEL_H_INCLUDED
# define MODEL_H_INCLUDED

# include "NetObject.h"

NETOBJ_BEGIN

class Model
: public cocos2d::CCObject
{
public:
    
    void callApi(NetObj*);
    
    static Model& getInstance()
    {
        static Model __m;
        return __m;
    }
    
protected:
    
    void cbHttpResponse(NetObj::cli_type*, NetObj::respn_type*);
    
};

NETOBJ_END

# endif
