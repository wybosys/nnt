
# ifndef __MAIN_CTLR_CXX_AD294F2E59534CCE814FD9453A3E793D_H_INCLUDED
# define __MAIN_CTLR_CXX_AD294F2E59534CCE814FD9453A3E793D_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
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

WSIAPP_END

# endif
