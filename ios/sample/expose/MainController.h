
# ifndef __MAIN_CTLR_732D27BCFA0841B5937FA9E23C3772FF_H_INCLUDED
# define __MAIN_CTLR_732D27BCFA0841B5937FA9E23C3772FF_H_INCLUDED

# include "UIExposeControl.h"

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::HorExpose hor;
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
