
# ifndef __MAIN_CTLR_0AAAECDBC5954E289A0EDE7273647490_H_INCLUDED
# define __MAIN_CTLR_0AAAECDBC5954E289A0EDE7273647490_H_INCLUDED

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::TextField txt0, txt1;
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
