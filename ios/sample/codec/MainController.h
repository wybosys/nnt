
# ifndef __MAIN_CTLR_63F89ABD4C2B43F6881EDAC3D389634B_H_INCLUDED
# define __MAIN_CTLR_63F89ABD4C2B43F6881EDAC3D389634B_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::BevelButton btn_blow, btn_bottle, btn_glass;
    
protected:
    void act_blow();
    void act_bottle();
    void act_glass();
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
