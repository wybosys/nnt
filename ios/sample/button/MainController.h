
# ifndef __MAIN_CTLR_DA58A2A16A7B44739855C1ED4351983F_H_INCLUDED
# define __MAIN_CTLR_DA58A2A16A7B44739855C1ED4351983F_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::BadgeIndicator badge;
    ui::StateButton btn_0, btn_1;
    ui::ButtonGroup grp;
    
    ui::BevelButton btn_parent, btn_child0, btn_child1, btn_child2;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    void act_parent_clicked();
    void act_child_clicked();
    void hide_child();
    
};

WSIAPP_END

# endif