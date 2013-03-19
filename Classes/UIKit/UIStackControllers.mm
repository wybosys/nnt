
# import "Core.h"
# import "UIStackControllers.h"

WSI_BEGIN_OBJC

@interface UIStackView : WSIUIView

@property (nonatomic, assign) UIStackControllers* stackController;

@end

@implementation UIStackView

@synthesize stackController;

- (void)layoutSubviews {
    if (stackController.stack.count == 0)
        return;
    
    UIViewController* ctlr = stackController.stack.lastObject;
    ctlr.view.frame = self.bounds;
}

@end

@implementation UIStackControllers

@synthesize stack = _stack;

- (id)init {
    self = [super init];
    
    _stack = [[NSMutableArray alloc] init];
    
    return self;
}

- (void)dealloc {
    safe_release(_stack);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalItemInserted)
WSIEVENT_SIGNAL(kSignalItemRemoved)
WSIEVENT_END

- (void)loadView {
    UIStackView* view = [[UIStackView alloc] initWithZero];
    self.view = view;
    [view release];
    
    view.stackController = self;
}

- (void)add:(UIViewController*)ctlr {
    if ([_stack containsObject:ctlr] == NO) {
        [_stack addObject:ctlr];
    } else {
        return;
    }
    
    UIStackView* view = (UIStackView*)self.view;
    UIView* target = ctlr.view;
    
    // add new.
    [view addSubview:target];
    
    // signal.
    [self emit:kSignalItemInserted result:ctlr];
}

- (UIViewController*)pop {
    if (_stack.count == 0)
        return nil;
    
    // get.
    UIViewController* current = _stack.lastObject;    
    //UIStackView* view = (UIStackView*)self.view;
    UIView* target = current.view;
    
    // remove.
    [target removeFromSuperview];
    [_stack removeObject:[current consign]];
    
    // signal.
    [self emit:kSignalItemRemoved result:current];
    
    return current;
}

@end

WSI_END_OBJC
