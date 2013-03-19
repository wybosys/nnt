
# ifndef __MAIN_CTLR_CE7CD2778B7249A4AA4E56C8BC3B48F9_H_INCLUDED
# define __MAIN_CTLR_CE7CD2778B7249A4AA4E56C8BC3B48F9_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public wsi::ui::View<MainView>
{
public:
    MainView();
    
    void layout_subviews();
    
    wsi::ui::Button<UIBackButton> btn;
};

class MainController
: public wsi::ui::Controller<MainController, MainView>
{
public:
    void view_loaded();
};

WSIAPP_END

# endif