
# import "Core.h"
# import "NSWindowController+NNT.h"
# import "NSWindow+NNT.h"
# import "NSViewController+NNT.h"
# import "NSView+NNT.h"

NNT_BEGIN_OBJC

@implementation NNTNSWindowControllerBase

NNTOBJECT_IMPL;

@synthesize contentViewController;

- (void)dealloc {
    [contentViewController release];
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)setContentViewController:(NNTNSViewController *)ctlr {
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
    NNTNSWindow* window = [[NNTNSWindow alloc] initWithContentRect:NSZeroRect
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

@implementation NNTNSWindowController

@end

NNT_END_OBJC