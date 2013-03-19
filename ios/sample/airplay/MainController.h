
# ifndef MAIN_CTLR
# define MAIN_CTLR

# include "UIAirplayButton.h"

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::AirplayButton airplay;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    void act_remotecontrol(EventObj&);

};

WSIAPP_END

# endif
