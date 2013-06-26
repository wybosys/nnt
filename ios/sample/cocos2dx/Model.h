
# ifndef MODEL_H_INCLUDED
# define MODEL_H_INCLUDED

# include "NetObject.h"

NETOBJ_BEGIN

class Model
: public cocos2d::CCObject
{
public:
    
    Model();
    ~Model();
    
    void callApi(NetObj*);
    
    static Model& getInstance()
    {
        static Model __m;
        return __m;
    }
    
    typedef cocos2d::extension::CCHttpResponse respn_type;
    typedef cocos2d::extension::CCHttpClient cli_type;
    
protected:
    
    void cbHttpResponse(cli_type*, respn_type*);
    
private:
    
    class ModelTask* task;
    
};

NETOBJ_END

# endif
