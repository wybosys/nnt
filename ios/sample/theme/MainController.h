
# ifndef __CTLR_MAIN_18E00539BB9248659CCE9CDF3531B976_H_INCLUDED
# define __CTLR_MAIN_18E00539BB9248659CCE9CDF3531B976_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    void theme(ui::Theme const&);
    ui::ImageView logo;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    void theme(ui::Theme const&);
    void act_black();
    void act_orange();
    void act_appear();
};

WSIAPP_END

# endif