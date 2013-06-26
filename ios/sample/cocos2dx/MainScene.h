
# ifndef MAINSCENE
# define MAINSCENE

# include <Contrib/cocos2dx/cocos2dx+NNT.h>
# include "NetObject.h"

NNTAPP_BEGIN

class MainScene
: public cocos2d::CCLayer,
public netobj::NetObj::IDelegate
{
public:

    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
    
    CREATE_FUNC(MainScene);
    
protected:
    
    void act_button_clicked(CCObject*);
    virtual void success(netobj::NetObj*);
    
};

NNTAPP_END

# endif
