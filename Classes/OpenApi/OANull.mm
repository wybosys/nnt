
# import "Core.h"
# import "OANull.h"

NNT_BEGIN_OBJC

@implementation OANull

@synthesize version;
@synthesize error_code, error_msg;
@synthesize result;

- (id)init {
    self = [super init];
    
    self.cacheUpdate = YES;
    self.version = (version_t){0, 0, 0, 0};
    
    return self;
}

- (void)dealloc {
    [error_code release];
    [error_msg release];
    [result release];
    [super dealloc];
}

+ (NSString*)Name {
    return @"OANULL";
}

@end

NNT_END_OBJC