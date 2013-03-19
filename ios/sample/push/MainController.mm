
# include "WSIFoundation.h"
# include "MainController.h"
# include "ApnsObject.h"

WSIAPP_BEGIN

MainView::MainView()
{
    
}

void MainView::layout_subviews()
{
    
}

MainController::MainController()
{

}

void MainController::view_loaded()
{
    push::Apns apns;
    if (!apns.is_registered())
    {
        apns.set(UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound);
        apns.register_to();
    }
}

WSIAPP_END
