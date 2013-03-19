
# include "WSIFoundation.h"
# include "AppDelegate.h"
# include "AppModel.h"

WSIAPP_BEGIN

void App::load()
{
    set_root(ctlr);
    
    connect(kSignalDeviceToken, _action(_class::act_devicetoken));
    connect(kSignalNotification, _action(_class::act_remotenoti));
}

void App::act_devicetoken(EventObj& evt)
{
    MAddDeviceToken mdl;
    mdl.dt = evt.result();
    context::Serv().retrieve(&mdl);
}

void App::act_remotenoti(EventObj& evt)
{
    ns::Dictionary data(evt.result());
    ns::Dictionary aps(data[@"aps"]);
    ns::String str = aps[@"alert"];
    core::Msgbox::info(str);
}

WSIAPP_END
