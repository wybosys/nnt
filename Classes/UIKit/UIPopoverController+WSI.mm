
# import "Core.h"
# import "UIPopoverController+WSI.h"

WSI_BEGIN_OBJC

@interface WSIUIPopoverController ()

- (void)reset;

@end

@implementation WSIUIPopoverController

@dynamic contentViewController;
@synthesize popoverArrowDirection = _popoverArrowDirection;
@dynamic popoverVisible;
@dynamic popoverContentSize;
@synthesize cxxobj;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    if (cxxobj)
        cxxobj->drop();
    
    safe_release(_popover);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalDismiss)
WSIEVENT_END

- (void)setContentViewController:(UIViewController *)contentViewController {
    [self reset];
    
    _popover = [[UIPopoverController alloc] initWithContentViewController:contentViewController];
    _popover.delegate = self;
}

- (UIViewController*)contentViewController {
    return _popover.contentViewController;
}

- (BOOL)popoverVisible {
    return _popover.popoverVisible;
}

- (UIPopoverArrowDirection)popoverArrowDirection {
    return _popover.popoverArrowDirection;
}

- (void)setPopoverContentSize:(CGSize)popoverContentSize {
    _popover.popoverContentSize = popoverContentSize;
}

- (CGSize)popoverContentSize {
    return _popover.popoverContentSize;
}

- (void)setPopoverContentSize:(CGSize)size animated:(BOOL)animated {
    [_popover setPopoverContentSize:size animated:animated];
}

- (void)reset {
    if (_popover) {
        zero_release(_popover);
    }
}

- (void)presentPopoverFromRect:(CGRect)rect inView:(UIView *)view permittedArrowDirections:(UIPopoverArrowDirection)arrowDirections animated:(BOOL)animated {
    [_popover presentPopoverFromRect:rect inView:view permittedArrowDirections:arrowDirections animated:animated];
    
    [self retain];
}

- (void)presentPopoverFromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated {
    [_popover presentPopoverFromRect:rect inView:view permittedArrowDirections:_popoverArrowDirection animated:animated];
    
    [self retain];
}

- (void)presentPopoverFromBarButtonItem:(UIBarButtonItem *)item permittedArrowDirections:(UIPopoverArrowDirection)arrowDirections animated:(BOOL)animated {
    [_popover presentPopoverFromBarButtonItem:item permittedArrowDirections:arrowDirections animated:animated];
    
    [self retain];
}

- (void)presentPopoverFromBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated {
    [_popover presentPopoverFromBarButtonItem:item permittedArrowDirections:_popoverArrowDirection animated:animated];
    
    [self retain];
}

- (void)dismissPopoverAnimated:(BOOL)animated {
    [_popover dismissPopoverAnimated:animated];
}

// delegate.

- (BOOL)popoverControllerShouldDismissPopover:(UIPopoverController *)popoverController {
    return YES;
}

- (void)popoverControllerDidDismissPopover:(UIPopoverController *)popoverController {
    [self emit:kSignalDismiss];
    
    [self release];
}

@end

WSI_END_OBJC
