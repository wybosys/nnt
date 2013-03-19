
# import "Foundation+NNT.h"
# import "AppDelegate.h"

NNTAPP_BEGIN

void App::load()
{
    set_root(ctlr);
    ctlr.set_orientation(UIOrientationEnableAll);
}

void App::test_local()
{
    NSDate* itemDate = [NSDate dateWithTimeIntervalSinceNow:10];
    UILocalNotification *localNotif = [[UILocalNotification alloc] init];
    if (localNotif == nil)
        return;
    localNotif.fireDate = itemDate;
    localNotif.timeZone = [NSTimeZone defaultTimeZone];
    
    localNotif.alertBody = @"Notification From WSI::Sample::Notification";
    localNotif.alertAction = NSLocalizedString(@"View Details", nil);
    
    localNotif.soundName = UILocalNotificationDefaultSoundName;
    localNotif.applicationIconBadgeNumber = 1;
    
    NSDictionary *infoDict = [NSDictionary dictionaryWithObject:@"TEST" forKey:@"WSI"];
    localNotif.userInfo = infoDict;
    
    [[UIApplication sharedApplication] scheduleLocalNotification:localNotif];
    [localNotif release];
}

NNTAPP_END
