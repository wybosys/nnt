
# import "Core.h"
# import "UIImagePickerController+NNT.h"

NNT_BEGIN_OBJC

@implementation NNTUIImagePickerController

NNTOBJECT_IMPL;

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

+ (id)controller {
    return [[[NNTUIImagePickerController alloc] init] autorelease];
}

@end

NNT_END_OBJC