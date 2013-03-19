
# ifndef __MAIN_CTLR_21C1339A2B3749689A6AC4FC677E3F98_H_INCLUDED
# define __MAIN_CTLR_21C1339A2B3749689A6AC4FC677E3F98_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::BevelButton show;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    
protected:
    void act_show();
};

NNTAPP_END

# endif
