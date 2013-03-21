
# ifndef __MAIN_CTLR_7A6991BA55064C309410439970D7229D_H_INCLUDED
# define __MAIN_CTLR_7A6991BA55064C309410439970D7229D_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::uc::View<MainView>
{
public:
    MainView();
};

class MainController
: public ui::uc::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
};

NNTAPP_END

# endif
