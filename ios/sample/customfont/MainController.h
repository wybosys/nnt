
# ifndef __MAIN_CTLR_E868F5D619A74DE8B4FC5F33B61D6EDB_H_INCLUDED
# define __MAIN_CTLR_E868F5D619A74DE8B4FC5F33B61D6EDB_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::MarqueeLabel lbl, lbl2;
    ui::TextView txt;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    void act_next();
};

WSIAPP_END

# endif
