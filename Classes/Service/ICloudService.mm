
# import "Core.h"
# import "ICloudService.h"

NNT_BEGIN_OBJC

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
    NNT_SYNCHRONIZED(self)
    if (ret == nil)
        ret = [[[self class] alloc] init];
    NNT_SYNCHRONIZED_END
    return ret;
}

- (BOOL)synchronize {
    BOOL suc = [_kvstore synchronize];
    if (!suc)
        trace_msg(@"failed synchronize data to iCloud.");
    return suc;
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(cloud)

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

NNT_END_NS
NNT_END_CXX
