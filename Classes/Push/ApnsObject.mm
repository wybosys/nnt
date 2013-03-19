
# import "Core.h"
# import "ApnsObject.h"
# import "NNTConfiguration.h"
# import "App.h"

NNT_BEGIN_OBJC

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
    [[NNTConfiguration shared] del:kConfigDeviceToken];
}

+ (BOOL)isRegistered {
    NSData* da = [APNSObject deviceToken];
    return da != nil;
}

+ (NSData*)deviceToken {
    return [[NNTConfiguration shared] getAsData:kConfigDeviceToken];
}

@end

NNT_END_OBJC
