
# import "Core.h"
# import "DBMS.h"

WSI_BEGIN_OBJC

@implementation DBMSAbstract

- (NSString*)errmsg {
    return @"";
}

- (void)close {
    PASS;
}

@end

WSI_END_OBJC