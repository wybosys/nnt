
# include "Foundation+NNT.h"
# include "AppDelegate.h"
# include "MainScene.h"

NNTAPP_BEGIN

static ccApp __gs_ccapp;

void App::load()
{
    set_root(ctlr);
}

ccApp::ccApp()
{
    
}

ccApp::~ccApp()
{
    
}

bool ccApp::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    CCScene *pScene = MainScene::scene();
    
    // run
    pDirector->runWithScene(pScene);
    
    return true;
}

void ccApp::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
}

void ccApp::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
}

NNTAPP_END
