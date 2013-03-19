
# ifndef MAIN_CTLR
# define MAIN_CTLR

# include "WSIClipboard.h"

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::TextView input, clip;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    sys::Clipboard clip;
    void act_clip_changed();
    
};

WSIAPP_END

# endif
