
# import "Core.h"
# import "DBMS.h"

NNT_BEGIN_OBJC

@implementation DBMSAbstract

- (NSString*)errmsg {
    return @"";
}

- (void)close {
    PASS;
}

@end

NNT_END_OBJC