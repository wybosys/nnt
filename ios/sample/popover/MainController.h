
# ifndef __MAIN_CTLR_E59BEDA7383547399C1EE51C0E894A02_H_INCLUDED
# define __MAIN_CTLR_E59BEDA7383547399C1EE51C0E894A02_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::BevelButton pop;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
    void act_pop();
    void act_dismiss();
    
};

NNTAPP_END

# endif
