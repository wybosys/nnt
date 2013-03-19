
# ifndef __MAIN_CTLR_73AF36CAB1C441C795126BED303D6291_H_INCLUDED
# define __MAIN_CTLR_73AF36CAB1C441C795126BED303D6291_H_INCLUDED

WSIAPP_BEGIN

using namespace ::wsi;

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();
    
protected:
    
    ui::PushButton btn_msg;
    void act_msg();
    
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