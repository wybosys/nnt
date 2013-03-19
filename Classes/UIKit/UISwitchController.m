
# import "Core.h"
# import "UISwitchView.h"
# import "UISwitchController.h"
# import "../Math/Linear.h"
# import "UIView+WSI.h"

WSI_BEGIN_OBJC

@interface UISwitchController (curl)

- (void)curlPageToPoint:(UISwitchPage*)page pt:(CGPoint)pt;

@end

@interface UISwitchControllerPrivate : NSObject <UIGestureRecognizerDelegate> {
    NSMutableArray *pages;
    UISwitchPage *cur_page, *lst_page;
    UISwitchController *d_owner;
    CGPoint natureBegin;
    UIImage *natureImage;
}

@property (nonatomic, assign) UISwitchController *d_owner;
@property (nonatomic, retain) NSMutableArray *pages;
@property (nonatomic, assign) UISwitchPage *cur_page, *lst_page;
@property (nonatomic, retain) UIImage *natureImage;

- (void)init_page:(UISwitchPage*)__page;

@end

@implementation UISwitchControllerPrivate

@synthesize d_owner;
@synthesize pages, cur_page, lst_page;
@synthesize natureImage;

- (id)init {
    self = [super init];
    
    pages = [NSMutableArray new];
    
    return self;
}

- (void)dealloc {
    cur_page = nil;
    for (UISwitchPage *page in pages) {
        [page.view removeFromSuperview];
    }
    zero_release(pages);
    zero_release(natureImage);
    
    [super dealloc];
}

- (void)init_page:(UISwitchPage *)__page {
    __page.view.userInteractionEnabled = YES;
    
    UIPanGestureRecognizer *ger = nil;
    
    // right
    ger = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(hdl_gesture_transition_page:)];
    ger.minimumNumberOfTouches = d_owner.numberOfGestureTouches;
    [__page.view addGestureRecognizer:ger];
    [ger release];
    
    // left
    ger = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(hdl_gesture_transition_page:)];
    ger.minimumNumberOfTouches = d_owner.numberOfGestureTouches;
    [__page.view addGestureRecognizer:ger];
    [ger release];
    
    // nature curl.
    ger = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(hdl_gesture_transition_page_nature:)];
    ger.minimumNumberOfTouches = d_owner.numberOfGestureTouches;
    [__page.view addGestureRecognizer:ger];
    [ger release];
}

- (UISwitchPage*)next_page {
    if (cur_page == nil)
        return nil;
    if ([d_owner.delegate respondsToSelector:@selector(prefetchNextPage:curpage:)]) {
        return [d_owner.delegate prefetchNextPage:d_owner curpage:cur_page];
    }
    return nil;
}

- (UISwitchPage*)pre_page {
    if (cur_page == nil) 
        return nil;
    if ([d_owner.delegate respondsToSelector:@selector(prefetchPrePage:curpage:)]) {
        return [d_owner.delegate prefetchPrePage:d_owner curpage:cur_page];
    }
    return [d_owner previous_page:cur_page];
}

- (void)setCur_page:(WSIUIViewController *)page {
    if (cur_page == page)
        return;
    id old_page = cur_page;
    cur_page = page;
    
    [d_owner emit:kSignalSelectChanged result:[NSPair pairWith:cur_page second:old_page]];
}

# pragma mark gesture delegate

- (void)hdl_gesture_transition_page:(UIPanGestureRecognizer *)recognizer {
    
    if (UIGestureRecognizerStateEnded != recognizer.state)
        return;
    
    if (cur_page == nil)
        return;
    
    UISwitchPage *old_page = cur_page;
    
    CGPoint pt = [recognizer translationInView:cur_page.view];
    
    UISwitchPage *next = nil;    
    BOOL move_in = YES;
    if (pt.x < 0) {
        next = [self next_page];
    } else if (pt.x > 0) {
        next = [self pre_page];
        move_in = NO;
    } else {
        return;
    }
    
    if (next == nil)
        return;
    
    // show next
    [d_owner set_page:next];
    
    // hide pre
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(hide_lst_page)];
    [UIView setAnimationDuration:0.55];
    
    switch (d_owner.transition) {
        case UISwitchTransitionSlide: {
            if (move_in) {
                old_page.view.center = CGPointMake(-old_page.view.bounds.size.width, old_page.view.center.y);                
            } else {
                old_page.view.center = CGPointMake(old_page.view.bounds.size.width * 1.5f, old_page.view.center.y); 
            }            
        } break;            
        case UISwitchTransitionNatureCurl:
        case UISwitchTransitionCurl: {
            if (move_in) {
                [UIView setAnimationTransition:UIViewAnimationTransitionCurlUp forView:old_page.view cache:YES];
            } else {
                [UIView setAnimationTransition:UIViewAnimationTransitionCurlDown forView:next.view cache:YES];
            }            
        } break;
    }   
    
    //[next.view moveTo:d_owner.view.bounds.origin];
        
    [UIView commitAnimations];
}

- (void)hdl_gesture_transition_page_nature:(UIPanGestureRecognizer *)recognizer {
    if (d_owner.transition != UISwitchTransitionNatureCurl) {
        [self performSelector:@selector(hdl_gesture_transition_page:) withObject:recognizer];
        return;
    }
    
    CGPoint pt = [recognizer translationInView:d_owner.view];
    
    switch (recognizer.state) {
        default: break;
        case UIGestureRecognizerStateBegan: {
            natureBegin = pt;
        } break;
        case UIGestureRecognizerStateChanged: {
            BOOL move_in = (pt.x - natureBegin.x) < 0 || (pt.y - natureBegin.y) < 0;
            
            UISwitchPage *page = nil;
            if (move_in) {
                page = cur_page;
            } else {
                page = [self pre_page];
            }
            
            if (natureImage == nil) {
                self.natureImage = [page.view convertToImage];
            }
            
            CGLine line;
            line.start = natureBegin;
            line.end = pt;
            if (YES || CGLineIsHov(&line)) {
                CGPoint pt_center = CGLineCenter(&line);
                pt_center.y = 0;
                [d_owner curlPageToPoint:page pt:pt_center];
            } else if (CGLineIsVec(&line)) {
                CGPoint pt_center = CGLineCenter(&line);
                pt_center.x = 0;
                [d_owner curlPageToPoint:page pt:pt_center];
            } else {
                
            }
        } break;
        case UIGestureRecognizerStateEnded: {
            self.natureImage = nil;
        } break;
    }
}

# pragma mark animation

- (void)hide_lst_page {
    if (lst_page) {
        lst_page.view.hidden = YES;
    }
}

@end

@interface UISwitchController ()

- (void)__init;

@end

@implementation UISwitchController

@dynamic cur_page;
@synthesize delegate;
@synthesize transition;
@synthesize numberOfGestureTouches;

- (void)__init {
    transition = UISwitchTransitionCurl;
    delegate = self;
    numberOfGestureTouches = 2;
}

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT_EX(UISwitchController, d_ptr_ctr);    
    [self __init];
    return self;
}

- (id)initWithView:(UISwitchView *)__view {
    self = [self init];
    
    self.view = __view;
    __view.switcher = self;
    
    return self;
}

- (void)dealloc {
    UISwitchView *view = (UISwitchView*)self.view;
    view.switcher = nil;
    WSIDECL_PRIVATE_DEALLOC_EX(d_ptr_ctr);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalSelectChanged)
WSIEVENT_END

- (void)loadView {
    UISwitchView *view = [[UISwitchView alloc] initWithZero];
    self.view = view;
    view.switcher = self;
    [view release];
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

- (void)add_page:(UISwitchPage *)__ctl {
    if (__ctl == nil)
        return;
    [d_ptr_ctr init_page:__ctl];
    [d_ptr_ctr.pages addObject:__ctl];
    if (__ctl.view) {
        __ctl.view.hidden = YES;
        [__ctl.view moveTo:self.view.bounds.origin];
        [self.view insertSubview:__ctl.view atIndex:0];
    }
}

- (void)set_page:(UISwitchPage *)__ctl event:(BOOL)__evt {
    if (__evt && [self.delegate respondsToSelector:@selector(shouldSwitchPage:pre:next:)]) {
        if (NO == [self.delegate shouldSwitchPage:self pre:d_ptr_ctr.cur_page next:__ctl]) {
            return;
        }
    }
    
    d_ptr_ctr.lst_page = d_ptr_ctr.cur_page;
    d_ptr_ctr.cur_page = __ctl;
    
    [d_ptr_ctr.lst_page viewWillDisappear:YES];
    [d_ptr_ctr.cur_page viewWillAppear:YES];
    
    if (__ctl.view) {
        UIView* view = __ctl.view;
        view.hidden = NO;
        view.frame = self.view.bounds;
        [view setNeedsDisplay];
    }
    
    if (__evt && [self.delegate respondsToSelector:@selector(didSwitchPage:page:)]) {
        [self.delegate didSwitchPage:self page:__ctl];
    }
    
    [d_ptr_ctr.lst_page viewDidDisappear:YES];
    [d_ptr_ctr.cur_page viewDidAppear:YES];
   
}

- (void)set_page:(UISwitchPage *)__ctl {
    if (__ctl == nil) {
        trace_msg(@"skip select a null controller.");
        return;
    }
    
    [self set_page:__ctl event:YES];
}

- (void)swap_page:(UISwitchPage *)__tgt {    
    if (__tgt == nil) {
        trace_msg(@"skip select a null controller.");
        return;
    }
    
    UISwitchPage *old_page = d_ptr_ctr.cur_page;    
    
    uint idx_old = [self index_of:old_page];
    uint idx_next = [self index_of:__tgt];
    if (idx_old == idx_next)
        return;
    BOOL move_in = idx_old < idx_next;
    
    [old_page viewWillDisappear:YES];
    [__tgt viewWillAppear:YES];
    
    [self set_page:__tgt];
    
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDelegate:d_ptr_ctr];
    [UIView setAnimationDidStopSelector:@selector(hide_lst_page)];
    [UIView setAnimationDuration:0.55f];
    
    switch (transition) {
        case UISwitchTransitionSlide: {
            if (move_in) {
                old_page.view.center = CGPointMake(-old_page.view.bounds.size.width, old_page.view.center.y);                
            } else {
                old_page.view.center = CGPointMake(old_page.view.bounds.size.width * 1.5f, old_page.view.center.y); 
            }   
            [__tgt.view moveTo:self.view.bounds.origin];
        } break;
        case UISwitchTransitionNatureCurl:
        case UISwitchTransitionCurl: {
            if (move_in) {
                [UIView setAnimationTransition:UIViewAnimationTransitionCurlUp forView:old_page.view cache:YES];
            } else {
                [UIView setAnimationTransition:UIViewAnimationTransitionCurlDown forView:__tgt.view cache:YES];
            }   
        } break;
    }
    
    [UIView commitAnimations];
    
    [old_page viewDidDisappear:YES];
    [__tgt viewDidAppear:YES];
}

- (NSUInteger)count {
    return [d_ptr_ctr.pages count];
}

- (UISwitchPage*)page_at:(NSUInteger)__index {
    if (__index >= [self count]) return nil;
    return [d_ptr_ctr.pages objectAtIndex:__index];
}

- (UISwitchPage*)first_page {
    if ([self count]) {
        return [d_ptr_ctr.pages objectAtIndex:0];
    }
    return nil;
}

- (UISwitchPage*)cur_page {
    return d_ptr_ctr.cur_page;
}

- (void)freeze_page {
    for (UISwitchPage *each in d_ptr_ctr.pages) {
        each.view.userInteractionEnabled = NO;
    }
}

- (void)thaw_page {
    for (UISwitchPage *each in d_ptr_ctr.pages) {
        each.view.userInteractionEnabled = YES;
    }
}

- (NSInteger)index_of:(UISwitchPage *)__ctl {
    return [d_ptr_ctr.pages indexOfObject:__ctl];
}

- (void)clear {
    d_ptr_ctr.cur_page = nil;
    d_ptr_ctr.lst_page = nil;
    
    for (UISwitchPage *page in d_ptr_ctr.pages) {
        [page.view removeFromSuperview];
    }
    [d_ptr_ctr.pages removeAllObjects];
}

- (UISwitchPage*)previous_page:(UISwitchPage *)__page {
    if (0 == [self index_of:__page]) return nil;
    UISwitchPage *page = [self page_at:[self index_of:__page] - 1];
    return page;
}

- (UISwitchPage*)next_page:(UISwitchPage *)__page {
    if ([self count] == [self index_of:__page] + 1) return nil;
    UISwitchPage *page = [self page_at:[self index_of:__page] + 1];
    return page;
}

- (UISwitchPage*)prefetchNextPage:(UISwitchController *)__ctl curpage:(UISwitchPage *)__cur {
    return [self next_page:__cur];
}

- (UISwitchPage*)prefetchPrePage:(UISwitchController *)__ctl curpage:(UISwitchPage *)__cur {
    return [self previous_page:__cur];
}

@end

@implementation UISwitchController (curl)

- (void)curlPageToPoint:(UISwitchPage*)page pt:(CGPoint)pt {
    page.view.backgroundColor = [UIColor whiteColor];
}

@end

WSI_END_OBJC