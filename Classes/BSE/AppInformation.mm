
# import "Core.h"
# import "AppInformation.h"
# import "AEMInformation.h"
# import "Server.h"
# import "WSIConfiguration.h"

WSI_BEGIN_OBJC

@implementation BSEAppInformation

@synthesize app = _app;

- (id)init {
    self = [super init];
    
    _serv = [[Server alloc] init];
    
    return self;
}

- (void)dealloc {
    safe_release(_serv);
    
    [super dealloc];
}

- (void)setApp:(WSIApplication *)app {
    if (app == _app)
        return;
    _app = app;
    
    if (_app == nil)
        return;
    
    [self performSelectorInBackground:@selector(_do_init) withObject:nil];
}

- (void)_do_init {
    NSString* appname = [WSIApplication Name];
    NSString* appid = [WSIApplication Identity];
    NSString* devid = [WSIApplication DeviceIdentity];

    // increase any counter.
    {
        AEMInfoLaunchCounterIncrease* mdl = [[AEMInfoLaunchCounterIncrease alloc] init];
        mdl.app_name = appname;
        mdl.app_id = appid;
        [_serv retrieve_model_async:mdl callbackType:ServerCallbackTypeBackgroundThread];
        safe_release(mdl);
    }
    
    // increase dev.
    {
        AEMInfoLaunchDeviceCounterIncrease* mdl = [[AEMInfoLaunchDeviceCounterIncrease alloc] init];
        mdl.app_name = appname;
        mdl.app_id = appid;
        mdl.dev_id = devid;
        [_serv retrieve_model_async:mdl callbackType:ServerCallbackTypeBackgroundThread];
        safe_release(mdl);
    }
    
    // other.
    [_app connect:kSignalAppFinishLaunching sel:@selector(act_finish_loading) obj:self];
}

- (void)act_finish_loading {
    // increase app launch counter.
    {
        uint val = [[WSIConfiguration shared] getInt:@"::wsi::app::counter::launch" null:0];
        val += 1;
        [[WSIConfiguration shared] set:@"::wsi::app::counter::launch" intValue:val];
    }
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(bse)

uint Application::Counter::Launch()
{
    uint val = [[WSIConfiguration shared] getInt:@"::wsi::app::counter::launch" null:1];
    return val;
}

WSI_END_NS
WSI_END_CXX
