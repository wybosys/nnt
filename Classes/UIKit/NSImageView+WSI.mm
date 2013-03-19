
# import "Core.h"
# import "NSImageView+WSI.h"

WSI_BEGIN_OBJC

@implementation NSImageView (WSI)

- (id)initWithURL:(NSURL*)url {
    self = [super initWithZero];
    [self loadURL:url];
    return self;
}

- (void)loadURL:(NSURL *)url {
    NSImage* img = [[NSImage alloc] initWithContentsOfURL:url];
    if (img)
        self.image = img;
}

@end

@implementation WSINSImageView

@end

WSI_END_OBJC