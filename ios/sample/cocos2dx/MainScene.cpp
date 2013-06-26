
# include <Foundation+NNT.h>
# include "MainScene.h"
# include <cocos2dx/extension/GUI/CCControlExtension/CCControlButton.h>
# include "UsersLogin.h"

NNTAPP_BEGIN

CCScene* MainScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(MainScene::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    
    // add button.
    CCControlButton* pButton = CCControlButton::create(pLabel, extension::CCScale9Sprite::create("HelloWorld.png"));
    pButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MainScene::act_button_clicked), CCControlEventTouchDown);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pButton->setPosition( ccp(size.width / 2, size.height / 2) );
    
    // add the sprite as a child to this layer
    this->addChild(pButton, 0);
    
    return true;
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}

void MainScene::act_button_clicked(CCObject* pSender)
{
    netobj::UsersLogin* ul = new netobj::UsersLogin;
    ul->setIn_appid(1);
    ul->setIn_channelid(1);
    ul->setIn_equipmentid("iphone");
    ul->setIn_applicationversion("2.0.0");
    ul->setIn_systemversion("ios 5.1");
    ul->setIn_cellbrand("iphone4");
    ul->setIn_cellmodel("5");
    ul->setIn_device_token("fdssdeew123");
    ul->setIn_mac("31232103213213213");
    ul->setIn_name("zzw2@hoodinn.com");
    ul->setIn_password("123456");
    ul->setIn_rndcheck("test");
    ul->delegate = this;
    
    netobj::Model::getInstance().callApi(ul);
    
    ul->release();
}

void MainScene::success(netobj::NetObj *m)
{
    netobj::UsersLogin* ul = dynamic_cast<netobj::UsersLogin*>(m);
    if (ul)
    {
        trace_msg(ul->getData()->getNickname());
    }
}

NNTAPP_END
