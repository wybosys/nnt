
# ifndef __MAIN_CTLR_04317E490D5245BBB520C1DC087D8F6D_H_INCLUDED
# define __MAIN_CTLR_04317E490D5245BBB520C1DC087D8F6D_H_INCLUDED

WSIAPP_BEGIN

using namespace wsi;

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    
    void layout_subviews();
    
    ui::BevelButton btn_sms, btn_email;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    
    void view_loaded();
    
protected:
    void act_sms();
    void act_email();
    
};

WSIAPP_END

# endif