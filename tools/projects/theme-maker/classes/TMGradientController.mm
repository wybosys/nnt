
# import <wsi/WSIFoundation.h>
# import "TMGradientController.h"

WSIAPP_BEGIN_OBJC

@implementation TMGradientController

- (id)init {
    self = [super init];
    self.identity = self.title = @"GRADIENT";
    return self;
}

@end

WSIAPP_END_OBJC