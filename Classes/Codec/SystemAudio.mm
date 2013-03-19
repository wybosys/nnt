
# import "Core.h"
# import "SystemAudio.h"
# import <AudioToolbox/AudioToolbox.h>

WSI_BEGIN_OBJC

@interface SAudioID : NSObject {
    SystemSoundID aid;
}

@property (nonatomic, assign) SystemSoundID aid;

@end

@implementation SAudioID

@synthesize aid;

@end

@implementation SystemAudioManager

+ (id)defaultManager {
    static SystemAudioManager* __default_manager = nil;
    WSI_SYNCHRONIZED(self)
    if (__default_manager == nil)
        __default_manager = [[SystemAudioManager alloc] init];
    WSI_SYNCHRONIZED_END
    return __default_manager;
}

- (id)init {
    self = [super init];
    
    _dict = [[NSMutableDictionary alloc] init];
    
    return self;
}

- (void)dealloc {
    zero_release(_dict);
    
    [super dealloc];
}

- (BOOL)registerURL:(NSURL*)url withId:(NSString*)idr {
    id obj = [_dict objectForKey:idr];
    if (obj != nil)
        return NO;
    
    SystemSoundID ssid;
    if (0 != AudioServicesCreateSystemSoundID((CFURLRef)url, &ssid))
        return NO;
    
    SAudioID* aid = [[SAudioID alloc] init];
    aid.aid = ssid;
    [_dict setObject:aid forKey:idr];
    safe_release(aid);
    
    return YES;
}

- (BOOL)play:(NSString*)idr {
    SAudioID* sid = [_dict objectForKey:idr];
    if (sid == nil)
        return NO;
    
    AudioServicesPlaySystemSound(sid.aid);    
    return YES;
}

@end

WSI_END_OBJC
