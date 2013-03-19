
# ifndef __MAIN_CTLR_2943070062A14C00B0EFE2EE058AF669_H_INCLUDED
# define __MAIN_CTLR_2943070062A14C00B0EFE2EE058AF669_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::BevelButton samba, bundle;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    
protected:
    void act_samba();
    void act_bundle();
};

NNTAPP_END

# endif
