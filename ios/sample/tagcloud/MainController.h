
# ifndef __MAIN_CTLR_CA0A3436ECFB427A8E6B18D372309AC4_H_INCLUDED
# define __MAIN_CTLR_CA0A3436ECFB427A8E6B18D372309AC4_H_INCLUDED

# include "UITagCloudController.h"

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    ui::TagCloudController tag;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    void act_click(EventObj&);
    void act_play();
    void act_touchin();
    void act_touchout();
    bool play;
};

WSIAPP_END

# endif
