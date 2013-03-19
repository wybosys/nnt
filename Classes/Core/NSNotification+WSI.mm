
# import "Core.h"
# import "NSNotification+WSI.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

@implementation WSILocalNotification

- (id)init {
    self = [super init];
    
    self.timeZone = ns::TimeZone::ShangHai();
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

@end

WSI_END_OBJC
