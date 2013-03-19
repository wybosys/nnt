
# ifndef __A_CTLR_76E20B548C814919B908332E68F4F05A_H_INCLUDED
# define __A_CTLR_76E20B548C814919B908332E68F4F05A_H_INCLUDED

# include "EController.h"

NNTAPP_BEGIN

class AView
: public wsi::ui::View<AView>
{
public:
    AView();
    void layout_subviews();
    EController ctlr;
};

class AController
: public wsi::ui::Controller<AController, AView>
{
public:
    AController();
    void view_loaded();
    
protected:
    void act_appear();
    void act_disappear();
};

NNTAPP_END

# endif