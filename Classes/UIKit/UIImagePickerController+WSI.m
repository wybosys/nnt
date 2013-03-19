
# import "Core.h"
# import "UIImagePickerController+WSI.h"

WSI_BEGIN_OBJC

@implementation WSIUIImagePickerController

WSIOBJECT_IMPL;

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

+ (id)controller {
    return [[[WSIUIImagePickerController alloc] init] autorelease];
}

@end

WSI_END_OBJC