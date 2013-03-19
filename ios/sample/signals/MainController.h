
# ifndef __CTLR_MAIN_9366D664E431406583EFA14E6C75B635_H_INCLUDED
# define __CTLR_MAIN_9366D664E431406583EFA14E6C75B635_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    ui::SimpleView block;
    void act_clicked();
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    void act_clicked();
};

WSIAPP_END

# endif