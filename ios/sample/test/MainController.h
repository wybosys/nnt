
# ifndef __MAIN_CTLR_2C79654664C147E3BB6CBFD18D78A4A2_H_INCLUDED
# define __MAIN_CTLR_2C79654664C147E3BB6CBFD18D78A4A2_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    ui::BevelButton btn;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    void act_btn();
};

NNTAPP_END

# endif
