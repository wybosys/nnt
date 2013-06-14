
# include "Core.h"
# include "AppStatistics.h"
# include "umeng/MobClick.h"

NNT_BEGIN_OBJC

@implementation AppStatistics

@synthesize appid = _appid;

- (id)init {
    if ((self = [super init]) == nil)
        return nil;
    
    self.appid = @"51bb01ec56240b683f004886";
    
    return self;
}

- (void)dealloc {
    safe_release(_appid);
    [super dealloc];
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX


NNT_END_CXX
