
# ifndef __MAIN_CTLR_F195F326ACDC4A8EBA56A9F9B8932BDD_H_INCLUDED
# define __MAIN_CTLR_F195F326ACDC4A8EBA56A9F9B8932BDD_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::SimpleView view;
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
