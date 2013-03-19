
# import "Core.h"
# import "UIPageRoller.h"
# import "UIPageRollerPage.h"
# import "UIGesture+WSI.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

WSIDECL_PRIVATE_BEGIN(UIPageRoller, WSIObject)

@property (nonatomic, readonly) NSMutableArray* pages;

WSIDECL_PRIVATE_IMPL(UIPageRoller)

@synthesize pages;

- (id)init {
    self = [super init];
    pages = [[NSMutableArray alloc] init];
    return self;
}

- (void)dealloc {
    safe_release(pages);
    [super dealloc];
}

WSIDECL_PRIVATE_END

@interface UIPageRoller ()

- (void)selectPageByIndex:(NSUInteger)idx animated:(BOOL)animated;
- (void)reloadDataWithAnimated:(BOOL)animated;

@end

@implementation UIPageRoller

@synthesize
dataSource = _dataSource,
delegate = _delegate,
numberOfCurrentPage = _numberOfCurrentPage,
currentPage = _currentPage,
pageControl = _pageControl,
pages = _pages;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    WSIDECL_PRIVATE_INIT(UIPageRoller);
    
    _pageControl = [[WSIUIPageControl alloc] initWithZero];
    [self addSubview:_pageControl];
    [_pageControl connect:kSignalSelectChanged sel:@selector(_act_page_changed:) obj:self];
    safe_release(_pageControl);
    
    _dataSource = self;
    _delegate = self;
    
    // ges.
    WSIUISwipeGestureRecognizer* ges_left = [[WSIUISwipeGestureRecognizer alloc] init];
    WSIUISwipeGestureRecognizer* ges_right = [[WSIUISwipeGestureRecognizer alloc] init];
    ges_left.direction = UISwipeGestureRecognizerDirectionLeft;
    ges_right.direction = UISwipeGestureRecognizerDirectionRight;
    [ges_left connect:kSignalGestureActive sel:@selector(_act_gesture_left) obj:self];
    [ges_right connect:kSignalGestureActive sel:@selector(_act_gesture_right) obj:self];
    [self addGestureRecognizer:ges_left];
    [self addGestureRecognizer:ges_right];
    safe_release(ges_left);
    safe_release(ges_right);
    
    // self set.
    self.layer.masksToBounds = YES;

    return self;
}

- (void)dealloc {
    safe_release(_pages);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)layoutSubviews {
    // set page frame.
    if (_currentPage)
        _currentPage.frame = self.bounds;
    
    // set page control frame.
    CGFloat height = 30;
    if ([_dataSource respondsToSelector:@selector(pageRollerHeightOfPageControl:)])
        height = [_dataSource pageRollerHeightOfPageControl:self];
    CGRectLayoutVBox lyt(self.bounds);
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (pixel)height;
    lyt << lnr;
    _pageControl.frame = lyt << lnr;
    [self bringSubviewToFront:_pageControl];
}

- (void)willMoveToSuperview:(UIView *)newSuperview {
    [super willMoveToSuperview:newSuperview];
    
    // may be call while move out.
    if (newSuperview)
        [self reloadDataWithAnimated:NO];
}

- (void)clear {
    _currentPage = nil;
    _numberOfCurrentPage = 0;
    [_pageControl changeCurrentPage:0];
    _pageControl.numberOfPages = 0;    
    [_pages.items removeAllObjects];
    
    for (UIView* each in d_ptr.pages) {
        [each removeFromSuperview];
    }
    [d_ptr.pages removeAllObjects];
}

- (void)reloadData {
    [self reloadDataWithAnimated:YES];
}

- (void)reloadDataWithAnimated:(BOOL)animated {
    NSInteger count = 0;
    if ([_dataSource respondsToSelector:@selector(pageRollerNumberOfPages:)])
        count = [_dataSource pageRollerNumberOfPages:self];
    _pageControl.numberOfPages = count;
    
    [self selectPageByIndex:0 animated:animated];
}

- (void)selectPageByIndex:(NSUInteger)idx animated:(BOOL)animated {
    // reselect current.
    if (_currentPage && _numberOfCurrentPage == idx)
        return;
    
    // over check.
    NSInteger count = _pageControl.numberOfPages;
    if (count == 0)
        return;
    
    NSInteger nidx = idx;
    if (nidx >= count)
        nidx = 0;
    else if ((int)nidx < 0)
        nidx = count - 1;
    
    // change.
    UIRollerPage* page = nil;
    if ([_dataSource respondsToSelector:@selector(pageRollerCreatePage:index:)]) {
        page = [_dataSource pageRollerCreatePage:self index:nidx];
    }
    if (page == nil) {
        // no page got.
        return;
    } else {
        // adjust page and add.
        page.frame = self.bounds;
        
        if (page.superview != self) {
            if ([d_ptr.pages containsObject:page] == NO)
                [d_ptr.pages addObject:page];
            [self addSubview:page];
        }
    }
    
    if (_currentPage) {
        if (_numberOfCurrentPage < (int)idx) {
            [page moveTo:CGRectRightTop2(page.frame)];
            
            if (animated) {
                [UIView beginAnimations:nil context:nil];
            }
            
            // show target.
            [page moveTo:_currentPage.frame.origin];
            
            // hide current.
            [_currentPage moveRightTopTo:_currentPage.frame.origin];
            
            if (animated) {
                [UIView setAnimationDelegate:_currentPage];
                [UIView setAnimationDidStopSelector:@selector(removeFromSuperview)];
                [UIView commitAnimations];
            }
        } else {
            [page moveRightTopTo:_currentPage.frame.origin];
            
            if (animated) {
                [UIView beginAnimations:nil context:nil];
            }
            
            // show target.
            [page moveTo:_currentPage.frame.origin];
            
            // hide current.
            [_currentPage moveTo:CGRectRightTop2(_currentPage.frame)];
            
            if (animated) {
                [UIView setAnimationDelegate:_currentPage];
                [UIView setAnimationDidStopSelector:@selector(removeFromSuperview)];
                [UIView commitAnimations];
            } else {
                [_currentPage removeFromSuperview];
            }
        }
    }
    
    _currentPage = page;
    _numberOfCurrentPage = nidx;
    [_pageControl changeCurrentPage:nidx];

}

// callback.

- (void)_act_page_changed:(WSIEventObj*)evt {
    [self selectPageByIndex:_pageControl.currentPage animated:YES];
}

- (void)_act_gesture_left {
    [self selectPageByIndex:(_numberOfCurrentPage + 1) animated:YES];
}

- (void)_act_gesture_right {
    [self selectPageByIndex:(_numberOfCurrentPage - 1) animated:YES];
}

// datasource.

- (NSInteger)pageRollerNumberOfPages:(UIPageRoller*)roller {
    if (_pages)
        return _pages.count;
    return 0;
}

- (UIRollerPage*)pageRollerCreatePage:(UIPageRoller*)roller index:(NSInteger)idx {
    if (_pages)
        return [_pages objectAtIndex:idx];
    return nil;
}

@end

_CXXVIEW_IMPL_BEGIN(UIPageRoller)

- (NSInteger)pageRollerNumberOfPages:(UIPageRoller*)roller {
    ui::IPageRoller* ctlr = (ui::IPageRoller*)self._cxxobj;
    return ctlr->count();
}

- (UIRollerPage*)pageRollerCreatePage:(UIPageRoller*)roller index:(NSInteger)idx {
    ui::IPageRoller* ctlr = (ui::IPageRoller*)self._cxxobj;
    return ctlr->page(idx);
}

_CXXVIEW_IMPL_END

WSI_END_OBJC
