
# import "Core.h"
# import "WSIVision.h"

WSI_BEGIN_OBJC

@interface WSIVisionPrivate : WSIObject {
    
}

@property (nonatomic, assign) WSIVision *d_owner;

@end

@implementation WSIVisionPrivate

@synthesize d_owner;

@end

@implementation WSIVision

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSIVision);
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

@end

WSI_END_OBJC