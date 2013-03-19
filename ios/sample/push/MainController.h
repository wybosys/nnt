
# ifndef __MAIN_CTLR_79F3BE637748482EBBF19ABAD7AF38FA_H_INCLUDED
# define __MAIN_CTLR_79F3BE637748482EBBF19ABAD7AF38FA_H_INCLUDED

WSIAPP_BEGIN

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

WSIAPP_END

# endif
