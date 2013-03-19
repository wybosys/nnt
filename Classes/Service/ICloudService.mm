
# import "Core.h"
# import "ICloudService.h"

WSI_BEGIN_OBJC

@implementation ICloudService

@synthesize store = _kvstore;

- (id)init {
    self = [super init];
    
    _kvstore = [[NSUbiquitousKeyValueStore defaultStore] retain];
    
    return self;
}

- (void)dealloc {
    safe_release(_kvstore);
    [super dealloc];
}

+ (id)shared {
    static ICloudService* ret = nil;
    WSI_SYNCHRONIZED(self)
    if (ret == nil)
        ret = [[[self class] alloc] init];
    WSI_SYNCHRONIZED_END
    return ret;
}

- (BOOL)synchronize {
    BOOL suc = [_kvstore synchronize];
    if (!suc)
        trace_msg(@"failed synchronize data to iCloud.");
    return suc;
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(cloud)

iCloud::iCloud()
{
    
}

iCloud::iCloud(id obj)
: super(obj)
{
    
}

iCloud& iCloud::getInstance()
{
    static iCloud obj([objc_type shared]);
    return obj;
}

WSI_END_NS
WSI_END_CXX
