
# ifndef __MAIN_CTLR_7133ED36799C445D9F27DD16D9189651_H_INCLUDED
# define __MAIN_CTLR_7133ED36799C445D9F27DD16D9189651_H_INCLUDED

WSIAPP_BEGIN

using namespace ::wsi;

class MainView
: public ui::View<MainView>
{
public:
    void layout_subviews();
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    void view_loaded();
};

WSIAPP_END

# endif