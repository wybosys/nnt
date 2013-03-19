
# include "wae.h"
# include "MainController.h"
# include "LoginController.h"
# include "IndexController.h"
# include "QzEffect.h"

WAE_BEGIN

MainView::MainView()
{
    add_sub(ctlrs);
}

void MainView::layout_subviews()
{
    ctlrs.view().set_frame(bounds());
}

MainController::MainController()
{
    set_orientation(UIOrientationLandscapeEnableAll);
}

void MainController::view_loaded()
{
    ui::Instance<LoginController> login;
    view().ctlrs.add(login);
    
    context::User().connect(kSignalUserLogin, _action(_class::act_logined), this);
    context::User().connect(kSignalUserLogout, _action(_class::act_logout), this);
}

void MainController::act_logined()
{
    ui::Instance<IndexController> index;
    view().ctlrs.add(index);
    
    index->view().add_effect(qz::effect::Popin());
}

void MainController::act_logout()
{
    view().ctlrs.pop();
}

WAE_END
