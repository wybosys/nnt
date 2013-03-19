
# include "Foundation+NNT.h"
# include "MainController.h"
# include "ApnsObject.h"

NNTAPP_BEGIN

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

NNTAPP_END
