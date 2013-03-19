
# import "Core.h"
# import "NSImageView+NNT.h"

NNT_BEGIN_OBJC

@implementation NSImageView (NNT)

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

@implementation NNTNSImageView

@end

NNT_END_OBJC