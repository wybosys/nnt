
# ifndef __MAIN_CTLR_1CC93110C0DD448487FAC93C4FD10762_H_INCLUDED
# define __MAIN_CTLR_1CC93110C0DD448487FAC93C4FD10762_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    void layout_subviews();
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    void act_appear();
    void act_disappear();
    
};

NNTAPP_END

# endif
