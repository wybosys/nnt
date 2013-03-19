
# ifndef __MAIN_CTLR_B52C39E5470E417A9EFE07074375E0F8_H_INCLUDED
# define __MAIN_CTLR_B52C39E5470E417A9EFE07074375E0F8_H_INCLUDED

NNTAPP_BEGIN

using namespace ::wsi;

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