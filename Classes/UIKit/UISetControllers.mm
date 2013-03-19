
# import "Core.h"
# import "UISetControllers.h"

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

@interface UISetView : NNTUIView {
    UIView *_current;
}

@property (nonatomic, assign) UIView* current;

@end

@implementation UISetView

@synthesize current = _current;

- (void)layoutSubviews {
    _current.frame = self.bounds;
}

@end

@implementation UISetControllers

@synthesize set = _set, current = _current, holdOthers = _holdOthers;

- (id)init {
    self = [super init];
    
    _set = [[NSMutableSet alloc] init];
    _holdOthers = NO;
    
    return self;
}

- (void)dealloc {
    safe_release(_set);
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalItemInserted)
NNTEVENT_SIGNAL(kSignalItemRemoved)
NNTEVENT_END

- (void)loadView {
    UISetView* view = [[UISetView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)add:(UIViewController*)ctlr {    
    if ([_set containsObject:ctlr] == NO) {
        [_set addObject:ctlr];
    }
    
    UISetView* view = (UISetView*)self.view;
    UIView* target = ctlr.view;
    if (target == view.current)
        return;
    
    // add new.
    target.frame = view.bounds;
    [view addSubview:target];
    
    // remove old.
    if (view.current && !_holdOthers) {
        view.current.frame = CGRectZero;
        [view.current removeFromSuperview];
    }
    
    // set.
    view.current = target;
    _current = ctlr;
    
    // signal.
    [self emit:kSignalItemInserted result:ctlr];
}

@end

NNT_END_OBJC