
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

void MainView::layout_subviews()
{
    
}

void MainController::view_loaded()
{    
    //trace_obj(ns::TimeZone::SupportNames());
    core::Time tm = core::Time::Local();
    ns::Date date(tm);
    date += 10;
    
    ns::LocalNotification noti;    
    noti.set_date(date);
    noti.set_body(@"Notification From WSI::Sample::Notification");
    noti.set_action(tr(@"act::details"));
    noti.set_sound(UILocalNotificationDefaultSoundName);
    noti.set_badge(1);
    noti.execute();
}

NNTAPP_END