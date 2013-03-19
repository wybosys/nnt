
# ifndef __MAIN_CTLR_BA3C3F6AEEF9489CA1237744468CEF11_H_INCLUDED
# define __MAIN_CTLR_BA3C3F6AEEF9489CA1237744468CEF11_H_INCLUDED

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