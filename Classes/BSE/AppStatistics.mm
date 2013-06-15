
# include "Core.h"
# include "AppStatistics.h"
# include "umeng/MobClick.h"

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(AppStatistics, NSObject)
{
    //MobClick* mc;
}

NNTDECL_PRIVATE_IMPL(AppStatistics)

- (id)init {
    self = [super init];
    
    //mc = [[MobClick alloc] init];
    [MobClick startWithAppkey:d_owner.appid];
    
    return self;
}

- (void)dealloc {
    //safe_release(mc);
    [super dealloc];
}

NNTDECL_PRIVATE_END

@implementation AppStatistics

@synthesize appid = _appid;

- (id)init {
    if ((self = [super init]) == nil)
        return nil;
    
    NNTDECL_PRIVATE_INIT(AppStatistics);
    
    self.appid = @"51bb01ec56240b683f004886";
    
    return self;
}

- (void)dealloc {
    safe_release(_appid);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX


NNT_END_CXX
