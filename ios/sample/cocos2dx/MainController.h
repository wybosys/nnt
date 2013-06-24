
# ifndef MAINCTLR
# define MAINCTLR

# include <Contrib/cocos2dx/cocos2dx+NNT.h>

NNTAPP_BEGIN

class MainView
: public cocos::View
{
public:
    
    MainView();
    void layout_subviews();
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
};

NNTAPP_END

# endif
