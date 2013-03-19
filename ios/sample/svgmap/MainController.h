
# ifndef MAIN_CTLR
# define MAIN_CTLR

# include "UIChinaMapController.h"

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::ChinaMapController map;
    
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
