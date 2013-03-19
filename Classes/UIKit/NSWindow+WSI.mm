
# import "Core.h"
# import "NSWindow+WSI.h"

WSI_BEGIN_OBJC

@implementation NSWindow (WSI)

- (id)initWithFrame:(NSRect)frame {
    return [self initWithContentRect:frame
                            styleMask:0 
                              backing:NSBackingStoreBuffered 
                                defer:NO];
}

- (id)initWithZero {
    return [self initWithFrame:NSZeroRect];
}

@end

@implementation WSINSWindow

@synthesize keyWindow;

# define INIT \
keyWindow = YES;

WSIOBJECT_IMPL;

- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag {
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
    INIT;
    return self;
}
- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag screen:(NSScreen *)screen {
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag screen:screen];
    INIT;
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (BOOL)canBecomeKeyWindow {
    return keyWindow;
}

@end

WSI_END_OBJC