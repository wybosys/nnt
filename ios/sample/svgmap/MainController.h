
# ifndef MAIN_CTLR
# define MAIN_CTLR

# include "UIChinaMapController.h"

NNTAPP_BEGIN

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

NNTAPP_END

# endif
