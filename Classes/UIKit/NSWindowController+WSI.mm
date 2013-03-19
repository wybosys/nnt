
# import "Core.h"
# import "NSWindowController+WSI.h"
# import "NSWindow+WSI.h"
# import "NSViewController+WSI.h"
# import "NSView+WSI.h"

WSI_BEGIN_OBJC

@implementation WSINSWindowControllerBase

WSIOBJECT_IMPL;

@synthesize contentViewController;

- (void)dealloc {
    [contentViewController release];
    
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)setContentViewController:(WSINSViewController *)ctlr {
    if (contentViewController == ctlr)
        return;    
    [NSObject refobjSet:&contentViewController ref:ctlr];
    
    [self.window setContentView:ctlr.view];
}

- (NSWindow*)window {
    if (__window)
        return __window;
    [self windowWillLoad];
    [self loadWindow];
    __window = [super window];
    if (__window != nil)
        [self windowDidLoad];
    /*
    _window = [super window];
    if (ret isnil_) {
        [self windowWillLoad];
        [self loadWindow];
        [super loadWindow];
        if (nil != (ret = [super window])) {
            [self windowDidLoad];
        }
    }
     */
    return __window;
}

- (void)loadWindow {
    WSINSWindow* window = [[WSINSWindow alloc] initWithContentRect:NSZeroRect
                                                         styleMask:0 
                                                           backing:NSBackingStoreBuffered 
                                                             defer:NO];
    [self setWindow:window];
    safe_release(window);
}

- (void)windowWillLoad {
    PASS;
}

- (void)windowDidLoad {
    [self windowIsLoading];
}

- (void)windowIsLoading {
    PASS;
}

@end

@implementation WSINSWindowController

@end

WSI_END_OBJC