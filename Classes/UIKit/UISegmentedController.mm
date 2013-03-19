
# import "Core.h"
# import "Layout.h"
# import "UISegmentedController.h"
# import "UIView+NNT.h"
# import "UISegmentedControl+NNT.h"

NNT_BEGIN_OBJC

@interface UISegmentedView : NNTUIView

@property (nonatomic, assign) UIView* seg;
@property (nonatomic, assign) UIView* content;
@property (nonatomic, assign) UISegmentedControlPosition segmentedPosition;
@property (nonatomic, assign) CGPadding segmentedPadding;
@property (nonatomic, assign) CGRect segmentedFrame;

- (void)updateLayout;

@end

@implementation UISegmentedView

@synthesize seg, content, segmentedPosition, segmentedPadding, segmentedFrame;

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    
    [self updateLayout];
}
 
- (void)updateLayout {
    wsi::CGRectLayoutVBox lyt(self.bounds);
    wsi::CGRectLayoutLinear lnr(self.bounds.size.height);
    
    CGRect const rc_seg = segmentedFrame;
    real off_t = rc_seg.size.height * segmentedPadding.top;
    real off_b = rc_seg.size.height * segmentedPadding.bottom;
    
    if (segmentedPosition == UISegmentedControlPositionTop) {                
        
        lnr.add_pixel(off_t);
        lnr.add_pixel(rc_seg.size.height - off_t - off_b);
        lnr.add_pixel(off_b);
        lnr.add_flex(1);
        
        lyt.add_pixel(0);
        
        CGRect rc = lyt.add_pixel(lnr.get_comp(1));
        real off_l = rc.size.width * segmentedPadding.left;
        real off_r = rc.size.width * segmentedPadding.right;
        rc = CGRectAdd(rc, off_l, 0, -off_l - off_r, 0);
        
        lyt.add_pixel(2);
        
        seg.frame = rc;
        content.frame = lyt.add_pixel(lnr.get_comp(3));
        
    } else {
        
        lnr.add_flex(1);
        lnr.add_pixel(off_t);
        lnr.add_pixel(rc_seg.size.height - off_t - off_b);
        lnr.add_pixel(off_b);
        
        content.frame = lyt.add_pixel(lnr.get_comp(0));
        lyt.add_pixel(lnr.get_comp(1));
        
        CGRect rc = lyt.add_pixel(lnr.get_comp(2));
        real off_l = rc.size.width * segmentedPadding.left;
        real off_r = rc.size.width * segmentedPadding.right;
        rc = CGRectAdd(rc, off_l, 0, -off_l - off_r, 0);
        seg.frame = rc;
    }
}

@end

@interface UISegmentedController (hidden)

@end

@implementation UISegmentedController (hidden)

- (UIViewController*)find_by_view:(UIView*)view {
    for (UIViewController* each in itemsViewController) {
        if (each.view == view) {
            return each;
        }
    }
    return nil;
}

@end

@implementation UISegmentedController

@synthesize segmentedControl;
@synthesize itemsViewController;
@synthesize segmentedPosition;
@synthesize segmentedPadding;
@synthesize segmentedFrame;

- (id)initWithItems:(NSArray *)items {
    self = [super init];
    
    segmentedPadding = CGPaddingZero;
    
    itemsViewController = [items retain];
    
    // collect titles from items.
    NSMutableArray *titles = [[NSMutableArray alloc] initWithCapacity:[items count]];
    for (UIViewController *each in items) {
        [titles addObject:each.title];
    }
    segmentedControl = [[NNTUISegmentedControl alloc] initWithItems:titles custom:YES];    
    [segmentedControl connect:kSignalSelectChanged sel:@selector(act_selected_changed) obj:self];
    [titles release];
    
    self.segmentedFrame = CGRectMake(0, 0, 0, 50);
    
    segmentedControl.selectedSegmentIndex = 0;
    if ([[UIDevice currentDevice].systemVersion doubleValue] >= 5.0) {
        [self act_selected_changed];
    }
    
    return self;
}

- (void)dealloc {
    zero_release(itemsViewController);
    zero_release(segmentedControl);
    
    [super dealloc];
}

- (void)setSegmentedFrame:(CGRect)frame {
    UISegmentedView *view = (UISegmentedView*)self.view;

    segmentedFrame = frame;
    segmentedControl.frame = frame;
    view.segmentedFrame = frame;
}

- (void)act_selected_changed {
    UISegmentedView *view = (UISegmentedView*)self.view;
    
    // hide current.
    if (view.content) {
        UIViewController *ctlr = [self find_by_view:view.content];
        if (ctlr) {
            [ctlr viewDidDisappear:YES];
        }
        [view.content removeFromSuperview];
    }
    
    // show selected.
    UIViewController *ctlr = [itemsViewController objectAtIndex:segmentedControl.selectedSegmentIndex];
    [view addSubview:ctlr.view];
    view.content = ctlr.view;    
    
    [view updateLayout];
    [ctlr viewDidAppear:YES];
}

- (void)loadView {
    UISegmentedView *view = [[UISegmentedView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UISegmentedView *view = (UISegmentedView*)self.view;    
    view.seg = segmentedControl;    
    [view addSubview:segmentedControl];
}

- (void)setSegmentedPosition:(UISegmentedControlPosition)pos {
    if (segmentedPosition == pos)
        return;
    
    segmentedPosition = pos;
    
    UISegmentedView *view = (UISegmentedView*)self.view;
    view.segmentedPosition = pos;
}

- (void)setSegmentedPadding:(CGPadding)val {
    segmentedPadding = val;
    UISegmentedView *view = (UISegmentedView*)self.view;
    view.segmentedPadding = val;
}

@end

NNT_END_OBJC