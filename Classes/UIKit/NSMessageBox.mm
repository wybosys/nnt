
# import "Core.h"
# import "NSMessageBox.h"
# import "NSView+NNT.h"

NNT_BEGIN_OBJC

@interface NSMessageBoxView : NNTNSView

@end

@implementation NSMessageBoxView

@end

@implementation NSMessageBox

- (id)initWithTitle:(NSString *)title {
    self = [super initWithFrame:NSMakeRect(0, 0, 300, 300)];
    NSMessageBoxView* view = [[NSMessageBoxView alloc] initWithFrame:NSZeroRect];
    self.contentView = view;
    [view release];
    return self;
}

- (void)show {
    [[NSApplication sharedApplication] runModalForWindow:self];
}

@end

NNT_END_OBJC