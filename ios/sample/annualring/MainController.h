
# ifndef __MAIN_CTLR_D4C590F16DD24360AFB26BA24E28129C_H_INCLUDED
# define __MAIN_CTLR_D4C590F16DD24360AFB26BA24E28129C_H_INCLUDED

# include "UIAnnualRingView.h"

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    MainView();
    void layout_subviews();
    
    ui::AnnualRing ring;
    ui::BevelButton btn_center;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    MainController();
    void view_loaded();
    void act_click();
};

NNTAPP_END

# endif
