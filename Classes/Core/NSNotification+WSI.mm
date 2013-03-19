
# import "Core.h"
# import "NSNotification+NNT.h"

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

@implementation NNTLocalNotification

- (id)init {
    self = [super init];
    
    self.timeZone = ns::TimeZone::ShangHai();
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

@end

NNT_END_OBJC
