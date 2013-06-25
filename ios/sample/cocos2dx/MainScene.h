
# ifndef MAINSCENE
# define MAINSCENE

# include <Contrib/cocos2dx/cocos2dx+NNT.h>

NNTAPP_BEGIN

class MainScene
: public cocos2d::CCLayer
{
public:

    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
    
    CREATE_FUNC(MainScene);
    
protected:
    
    void act_button_clicked(CCObject*);
    
};

NNTAPP_END

# endif
