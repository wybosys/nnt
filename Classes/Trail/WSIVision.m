
# import "Core.h"
# import "NNTVision.h"

NNT_BEGIN_OBJC

@interface NNTVisionPrivate : NNTObject {
    
}

@property (nonatomic, assign) NNTVision *d_owner;

@end

@implementation NNTVisionPrivate

@synthesize d_owner;

@end

@implementation NNTVision

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNTVision);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

@end

NNT_END_OBJC