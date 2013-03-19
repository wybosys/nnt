
# import "Core.h"
# import "UIGridPageController.h"
# import "Layout.h"

WSI_BEGIN_OBJC

@implementation UIGridPage

@dynamic gridView;

- (id)initWithRows:(uint)__rows cols:(uint)__cols {
    self = [super init];
    rows = __rows;
    cols = __cols;
    return self;
}

- (void)loadView {
    UIGridView* view = [[UIGridView alloc] initWithFrame:CGRectZero rows:rows cols:cols];
    self.view = view;
    [view release];
}

- (UIGridView*)gridView {
    return (UIGridView*)self.view;
}

@end

@interface UIGridPageControllerPrivate : NSObject

@property (nonatomic, assign) UIGridPageController *d_owner;

@end

@implementation UIGridPageControllerPrivate

@synthesize d_owner;

@end

@interface UIGridPageControllerView : WSIUIView

@property (nonatomic, readonly) WSIUIPageControl* ctl_page;
@property (nonatomic, assign) UIGridPageController* ctlr_owner;

@end

@implementation UIGridPageControllerView

@synthesize ctl_page;
@synthesize ctlr_owner;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    ctl_page = [[WSIUIPageControl alloc] initWithZero];
    [self addSubview:ctl_page];
    [ctl_page release];
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)layoutSubviews {
    wsi::CGRectLayoutVBox lyt(self.bounds);
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr.add_flex(1);
    lnr.add_pixel(20);
    
    [ctlr_owner cur_page].view.frame = lyt.add_pixel(lnr.start());
    ctl_page.frame = lyt.add_pixel(lnr.next());
}

@end

@interface UIGridPageController ()

- (void)refresh_items_pages;

@end

@implementation UIGridPageController

@synthesize items;
@synthesize rows, cols;
@synthesize pageClass;
@dynamic pageControl;
@dynamic delegate;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(UIGridPageController);
    
    pageClass = [UIGridPage class];
    
    [self connect:kSignalSelectChanged sel:@selector(__act_page_changed:)];
    
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_END

- (void)loadView {
    UIGridPageControllerView* view = [[UIGridPageControllerView alloc] initWithZero];
    view.ctlr_owner = self;
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    PASS;
}

- (void)__act_page_changed:(WSIEventObj*)evt {
    UISwitchPage* page = ((NSPair*)evt.result).first;
    uindex idx = [self index_of:page];  
    if (idx != NSNotFound) {
        UIGridPageControllerView* view = (UIGridPageControllerView*)self.view;
        view.ctl_page.currentPage = idx;
    }
}

- (void)setItems:(NSArray *)__items {
    [self clear];    
    [NSObject refobjSet:&items ref:__items];   
    [self refresh_items_pages];
    [self set_page:[self first_page]];
}

- (void)refresh_items_pages {
    uint const capacity = rows * cols;
    uint const pages = ceil([items count] / (real)capacity);
    for (uint i = 0; i < pages; ++i) {
        UIGridPage* page = (UIGridPage*)[[pageClass alloc] initWithRows:rows cols:cols];
        
        if ([self.delegate respondsToSelector:@selector(gridpagePageCreate:page:)])
            [self.delegate gridpagePageCreate:self page:page];
        
        for (uint j = 0; j < capacity; ++j) {
            UIView* item = (UIView*)[items objectAtIndex:(i * capacity + j) null:nil];
            if (item == nil)
                continue;
            
            [page.gridView addChildView:item];
        }                
        
        [self add_page:page];
        
        if ([self.delegate respondsToSelector:@selector(gridpagePageDidCreated:page:)])
            [self.delegate gridpagePageDidCreated:self page:page];
        
        [page release];
    }
    
    UIGridPageControllerView* view = (UIGridPageControllerView*)self.view;
    view.ctl_page.numberOfPages = pages;
    view.ctl_page.currentPage = 0;
}

- (WSIUIPageControl*)pageControl {
    UIGridPageControllerView* view = (UIGridPageControllerView*)self.view;
    return view.ctl_page;
}

@end

WSI_END_OBJC