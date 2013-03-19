
# import "Core.h"
# import "ApnsObject.h"
# import "WSIConfiguration.h"
# import "App.h"

WSI_BEGIN_OBJC

@implementation APNSObject

@synthesize notificationType = _notiType;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)registerToSystem {
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:_notiType];
}

- (void)unregisterFromSystem {    
    [[UIApplication sharedApplication] unregisterForRemoteNotifications];
    [[WSIConfiguration shared] del:kConfigDeviceToken];
}

+ (BOOL)isRegistered {
    NSData* da = [APNSObject deviceToken];
    return da != nil;
}

+ (NSData*)deviceToken {
    return [[WSIConfiguration shared] getAsData:kConfigDeviceToken];
}

@end

WSI_END_OBJC
