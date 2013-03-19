
# ifndef __MAIN_CTLR_BF1C598C36574AA69BB85D3C893B7A64_H_INCLUDED
# define __MAIN_CTLR_BF1C598C36574AA69BB85D3C893B7A64_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
};

NNTAPP_END

# endif