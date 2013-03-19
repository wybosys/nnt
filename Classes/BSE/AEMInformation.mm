
# import "Core.h"
# import "AEMInformation.h"
# import "HttpRequest.h"

WSI_BEGIN_OBJC

@interface AEMHttpRequest : HttpRequest_Get

@end

@implementation AEMHttpRequest

- (id)init {
    self = [super init];
    
    self.verbose = NO;
    
    return self;
}

@end

@implementation AEModel

- (id)init {
    self = [super init];
    
    self.classRpc = [AEMHttpRequest class];
    self.cacheable = NO;
    self.verbose = NO;
    self.verboseWait = NO;
    self.verboseData = NO;
    
    self.odd = tostr(timestamp());
    
    return self;
}

@end

@implementation AEMInfoLaunchCounterIncrease

@synthesize app_name, app_id;

- (id)init {
    self = [super init];
    
    self.method = @"toolkit.counter.launch.increase";
    
    return self;
}

- (void)dealloc {
    safe_release(app_name);
    safe_release(app_id);
    [super dealloc];
}

- (NSMutableArray*)get_params {
    NSMutableArray* arr = [self dup_params];
    
    [arr addObject:pair(@"name", app_name)];
    [arr addObject:pair(@"id", app_id)];
    
    return arr;
}

@end

@implementation AEMInfoLaunchDeviceCounterIncrease

@synthesize app_name, app_id, dev_id;

- (id)init {
    self = [super init];
    
    self.method = @"toolkit.counter.device.launch.increase";
    
    return self;
}

- (void)dealloc {
    safe_release(app_name);
    safe_release(app_id);
    safe_release(dev_id);
    [super dealloc];
}

- (NSMutableArray*)get_params {
    NSMutableArray* arr = [self dup_params];
    
    [arr addObject:pair(@"name", app_name)];
    [arr addObject:pair(@"id", app_id)];
    [arr addObject:pair(@"devid", dev_id)];
    
    return arr;
}

@end

WSI_END_OBJC
