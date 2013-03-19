
# import "Core.h"
# import "UITableView+WSI.h"
# import "UIView+WSI.h"
# import "WSIUIObject.h"
# import "CoreGraphic+WSI.h"
# import "UIScrollHeaderView.h"

WSI_BEGIN_OBJC

static CGPoint __gs_view_touchpoint = (CGPoint){-999999, -999999};
static BOOL __gs_view_waitingtouch = NO;

@interface WSIUITableView (hidden)

- (void)processHeaders;
- (void)scrollHeaders;

@end

@implementation WSIUITableView (hidden)

- (void)processHeaders {
    CGPoint offset = self.contentOffset;
    
    if (topHeaderView && topHeaderView.hidden == NO) {
        if (-offset.y > topHeaderView.height) {
            if ([topHeaderView respondsToSelector:@selector(headerDidAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)topHeaderView;
                [obj headerDidAction:topHeaderView];
            }
        }
    }
    
    if (bottomHeaderView && bottomHeaderView.hidden == NO) {
        CGSize sz = self.contentSize;
        sz.height -= self.bounds.size.height;
        if (offset.y > sz.height + bottomHeaderView.height) {
            if ([bottomHeaderView respondsToSelector:@selector(headerDidAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)bottomHeaderView;
                [obj headerDidAction:bottomHeaderView];
            }
        }
    }
}

- (void)scrollHeaders {
    CGPoint offset = self.contentOffset;
    
    if (topHeaderView) {
        if (offset.y < 0 && topHeaderView.hidden == YES) {
            topHeaderView.hidden = NO;
            [topHeaderView setNeedsDisplay];
            [self bringSubviewToFront:topHeaderView];
            
            if ([topHeaderView respondsToSelector:@selector(headerBeginAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)topHeaderView;
                [obj headerBeginAction:topHeaderView];
            }
            
        } else if (offset.y >= 0 && topHeaderView.hidden == NO) {
            topHeaderView.hidden = YES;
            
            if ([topHeaderView respondsToSelector:@selector(headerEndAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)topHeaderView;
                [obj headerEndAction:topHeaderView];
            }
        } else if (topHeaderView.hidden == NO) {
            if ([topHeaderView respondsToSelector:@selector(headerMovedAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)topHeaderView;
                [obj headerMovedAction:topHeaderView];
            }
            
            if (-offset.y > topHeaderView.height) {
                if ([topHeaderView respondsToSelector:@selector(headerWillAction:)]) {
                    id<UIHeaderView> obj = (id<UIHeaderView>)topHeaderView;
                    [obj headerWillAction:topHeaderView];
                }
            }
        }
    }
    
    if (bottomHeaderView) {
        CGSize sz = self.contentSize;
        sz.height -= self.bounds.size.height;
        if (offset.y > sz.height && bottomHeaderView.hidden == YES) {
            bottomHeaderView.hidden = NO;
            [bottomHeaderView setNeedsDisplay];
            [self bringSubviewToFront:bottomHeaderView];
            
            if ([bottomHeaderView respondsToSelector:@selector(headerBeginAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)bottomHeaderView;
                [obj headerBeginAction:bottomHeaderView];
            }
        } else if (offset.y <= sz.height && bottomHeaderView.hidden == NO) {
            bottomHeaderView.hidden = YES;
            
            if ([bottomHeaderView respondsToSelector:@selector(headerEndAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)bottomHeaderView;
                [obj headerEndAction:bottomHeaderView];
            } 
        } else if (bottomHeaderView.hidden == NO) {
            if ([bottomHeaderView respondsToSelector:@selector(headerMovedAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)bottomHeaderView;
                [obj headerMovedAction:bottomHeaderView];
            }
            
            if (offset.y > sz.height + bottomHeaderView.height) {
                if ([bottomHeaderView respondsToSelector:@selector(headerWillAction:)]) {
                    id<UIHeaderView> obj = (id<UIHeaderView>)bottomHeaderView;
                    [obj headerWillAction:bottomHeaderView];
                }
            }
        }
    }
}

@end

@implementation WSIUITableView

@synthesize pullRefreshHeader, pullMoreHeader;
@synthesize isPullRefreshHeaderReloading, isPullMoreHeaderloading;
@synthesize sendGlobalEvent;
@synthesize topHeaderView, bottomHeaderView;

- (id)initWithFrame:(CGRect)frame style:(UITableViewStyle)style {
    self = [super initWithFrame:frame style:style];
    
    sendGlobalEvent = YES;
    self.backgroundColor = [UIColor clearColor];
    
    return self;
}

- (UIPullRefreshHeaderView*)enablePullRefreshHeader {    
    if (pullRefreshHeader)
        return pullRefreshHeader;
    pullRefreshHeader = [[UIPullRefreshHeaderView alloc] initWithZero];
    [self addSubview:pullRefreshHeader];
    pullRefreshHeader.delegate = self;    
    return pullRefreshHeader;
}

- (UIPullMoreHeaderView*)enablePullMoreHeader {
    if (pullMoreHeader)
        return pullMoreHeader;
    pullMoreHeader = [[UIPullMoreHeaderView alloc] initWithZero];
    [self addSubview:pullMoreHeader];
    pullMoreHeader.delegate = self;    
    return pullMoreHeader;
}

- (void)setTopHeaderView:(UIHeaderView*)view {
    [topHeaderView retain];
    [topHeaderView removeFromSuperview];
    [self addSubview:view];
    [topHeaderView release];
    topHeaderView = view;
    topHeaderView.hidden = YES;
    topHeaderView.direction = WCGDirectionTop;
}

- (void)setBottomHeaderView:(UIHeaderView*)view {
    [bottomHeaderView retain];
    [bottomHeaderView removeFromSuperview];
    [self addSubview:view];
    [bottomHeaderView release];
    bottomHeaderView = view;
    bottomHeaderView.hidden = YES;
    bottomHeaderView.direction = WCGDirectionBottom;
}

- (void)dealloc {
    self.delegate = nil;
    self.dataSource = nil;
    
    if (pullRefreshHeader) {
        pullRefreshHeader.delegate = nil;
    }
    
    if (pullMoreHeader) {
        pullMoreHeader.delegate = nil;
    }
    
    zero_release(pullRefreshHeader);
    zero_release(pullMoreHeader);
    
    [super dealloc];
}

- (void)setBounds:(CGRect)bounds {
    [super setBounds:bounds];
    
    CGRect rc_client = self.rectForLayout;
    
    if (pullRefreshHeader) {
        pullRefreshHeader.frame = CGRectMake(0, -rc_client.size.height, rc_client.size.width, rc_client.size.height);
    }
    
    if (pullMoreHeader) {
        pullMoreHeader.frame = CGRectMake(0, rc_client.size.height, rc_client.size.width, rc_client.size.height);
    }
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    if (topHeaderView && topHeaderView.hidden == NO) {
        CGRect rc_top = topHeaderView.frame;
        rc_top.origin = CGPointZero;
        rc_top.origin.y -= rc_top.size.height;;
        rc_top.size.width = self.bounds.size.width;
        topHeaderView.frame = rc_top;
    }
    
    if (bottomHeaderView && bottomHeaderView.hidden == NO) {
        CGRect rc_bot = bottomHeaderView.frame;
        rc_bot.origin = CGPointMake(0, MAX(self.contentSize.height, self.bounds.size.height));
        rc_bot.size.width = self.bounds.size.width;
        bottomHeaderView.frame = rc_bot;
    }
}

WSIOBJECT_IMPL_NOSIGNALS;

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalPullHeaderReload)
    WSIEVENT_SIGNAL(kSignalPullHeaderMore)
    WSIEVENT_SIGNAL(kSignalViewClicked);
    WSIEVENT_SIGNAL(kSignalTouchesBegin);
    WSIEVENT_SIGNAL(kSignalTouchesEnd);
    WSIEVENT_SIGNAL(kSignalTouchesCancel);
    WSIEVENT_SIGNAL(kSignalTouchesMoved);
}

- (void)startPullRefreshHeader {    
    [self enablePullRefreshHeader];
    [pullRefreshHeader refreshScrollViewDidScroll:self];
}

- (void)startPullMoreHeader {
    if (pullMoreHeader == nil)
        return;
    [pullMoreHeader refreshScrollViewDidScroll:self];
}

- (void)endPullRefreshHeader {        
    [pullRefreshHeader refreshScrollViewDidEndDragging:self];
}

- (void)endPullMoreHeader {
    if (pullMoreHeader == nil)
        return;
    [pullMoreHeader refreshScrollViewDidEndDragging:self];
}

- (void)removePullRefreshHeader {
    [pullRefreshHeader removeFromSuperview];
    zero_release(pullRefreshHeader);
}

- (void)removePullMoreHeader {
    [pullMoreHeader removeFromSuperview];
    zero_release(pullMoreHeader);
}

- (void)reloadDataSourceByPullRefreshHeader {
	isPullRefreshHeaderReloading = YES;
    [self emit:kSignalPullHeaderReload result:pullRefreshHeader];
    [pullRefreshHeader emit:kSignalPullHeaderReload result:pullRefreshHeader];
}

- (void)loadDataSourceByPullMoreHeader {
    isPullMoreHeaderloading = YES;
    [self emit:kSignalPullHeaderMore result:pullMoreHeader.model];
    [pullMoreHeader emit:kSignalPullHeaderMore result:pullMoreHeader.model];
}

- (void)didFinishedLoadingByPullRefreshHeader {    
    isPullRefreshHeaderReloading = NO;
	[pullRefreshHeader refreshScrollViewDataSourceDidFinishedLoading:self];
}

- (void)didFinishedLoadingByPullMoreHeader {
    isPullMoreHeaderloading = NO;
    [pullMoreHeader refreshScrollViewDataSourceDidFinishedLoading:self];
}

- (void)RefreshTableHeaderDidTriggerRefresh:(UIPullRefreshHeaderView*)view {	
    [self reloadDataSourceByPullRefreshHeader];
	[self performSelector:@selector(didFinishedLoadingByPullRefreshHeader) withObject:nil afterDelay:1.5f];
}

- (BOOL)RefreshTableHeaderDataSourceIsLoading:(UIPullRefreshHeaderView*)view {	
	return isPullRefreshHeaderReloading; // should return if data source model is reloading
}

- (NSDate*)RefreshTableHeaderDataSourceLastUpdated:(UIPullRefreshHeaderView*)view {
    return [NSDate date];
}

- (void)MoreTableHeaderDidTriggerRefresh:(UIPullMoreHeaderView *)view {
    [self loadDataSourceByPullMoreHeader];
    [self performSelector:@selector(didFinishedLoadingByPullMoreHeader) withObject:nil afterDelay:1.5f];
}

- (BOOL)MoreTableHeaderDataSourceIsLoading:(UIPullMoreHeaderView *)view {
    return isPullMoreHeaderloading;
}

# pragma mark touch event

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesBegan:touches withEvent:event];
    
    __gs_view_waitingtouch = TRUE;  
    __gs_view_touchpoint = [[touches anyObject] locationInView:self];
    
    if (sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesBegin, self, touches, event);
    [self emit:kSignalTouchesBegin result:touches data:event];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesCancelled:touches withEvent:event];
    
    __gs_view_waitingtouch = NO;
    
    if (sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesCancel, self, touches, event);
    [self emit:kSignalTouchesCancel result:touches data:event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesEnded:touches withEvent:event];
    
    if (__gs_view_waitingtouch == NO)
        return;
    
    CGPoint pt = [[touches anyObject] locationInView:self];
    if (CGPointEqualWithPrecise(pt, __gs_view_touchpoint, kUITouchRadius)) {
        [self emit:kSignalViewClicked result:touches data:event];
    }
    
    if (sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesEnd, self, touches, event);
    [self emit:kSignalTouchesEnd result:touches data:event];
    
    __gs_view_touchpoint = kUITouchSky;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesMoved:touches withEvent:event];
    
    if (sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesMoved, self, touches, event);
    [self emit:kSignalTouchesMoved result:touches data:event];
}

@end

WSI_END_OBJC