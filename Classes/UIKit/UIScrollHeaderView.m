
# import "Core.h"
# import "UIScrollHeaderView.h"
# import "UIKit.res"

WSI_BEGIN_OBJC

signal_t kSignalPullHeaderReload = @"::wsi::ui::tableview::pull::reload";
signal_t kSignalPullHeaderMore = @"::wsi::ui::tableview::pull::moreload";

# define TEXT_COLOR	 [UIColor colorWithRed:87.0/255.0 green:108.0/255.0 blue:137.0/255.0 alpha:1.0]
# define BACKGROUND_COLOR  [UIColor colorWithRed:226.0/255.0 green:231.0/255.0 blue:237.0/255.0 alpha:1.0]
# define FLIP_ANIMATION_DURATION 0.18f

@interface UIPullRefreshHeaderView ()

- (void)setState:(UITableViewPullRefreshState)aState;

@end

@implementation UIPullRefreshHeaderView

@synthesize delegate = _delegate;

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalPullHeaderReload)
WSIEVENT_END

- (id)initWithFrame:(CGRect)frame  {
    self = [super initWithFrame:frame];
    if (self == nil)
        return nil;
    
    self.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    self.backgroundColor = BACKGROUND_COLOR;
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0.0f, frame.size.height - 30.0f, self.frame.size.width, 20.0f)];
    label.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    label.font = [UIFont systemFontOfSize:12.0f];
    label.textColor = TEXT_COLOR;
    label.shadowColor = [UIColor colorWithWhite:0.9f alpha:1.0f];
    label.shadowOffset = CGSizeMake(0.0f, 1.0f);
    label.backgroundColor = [UIColor clearColor];
    label.textAlignment = UITextAlignmentCenter;
    [self addSubview:label];
    _lastUpdatedLabel=label;
    [label release];
    
    label = [[UILabel alloc] initWithFrame:CGRectMake(0.0f, frame.size.height - 48.0f, self.frame.size.width, 20.0f)];
    label.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    label.font = [UIFont boldSystemFontOfSize:13.0f];
    label.textColor = TEXT_COLOR;
    label.shadowColor = [UIColor colorWithWhite:0.9f alpha:1.0f];
    label.shadowOffset = CGSizeMake(0.0f, 1.0f);
    label.backgroundColor = [UIColor clearColor];
    label.textAlignment = UITextAlignmentCenter;
    [self addSubview:label];
    _statusLabel=label;
    [label release];
    
    CALayer *layer = [CALayer layer];
    layer.frame = CGRectMake(25.0f, frame.size.height - 65.0f, 30.0f, 55.0f);
    layer.contentsGravity = kCAGravityResizeAspect;
    layer.contents = (id)WCGImageLoadPngData(png_arrow_blue, sizeof(png_arrow_blue));
    
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 40000
    if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
        layer.contentsScale = [[UIScreen mainScreen] scale];
    }
#endif
    
    [[self layer] addSublayer:layer];
    _arrowImage=layer;
    
    UIActivityIndicatorView *view = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    view.frame = CGRectMake(25.0f, frame.size.height - 38.0f, 20.0f, 20.0f);
    [self addSubview:view];
    _activityView = view;
    [view release];
    
    [self setState:UITableViewPullRefreshStateNormal];
	
    return self;
}

- (void)refreshLastUpdatedDate {
    
    if ([_delegate respondsToSelector:@selector(RefreshTableHeaderDataSourceLastUpdated:)]) {
		
		NSDate *date = [_delegate RefreshTableHeaderDataSourceLastUpdated:self];
		
		[NSDateFormatter setDefaultFormatterBehavior:NSDateFormatterBehaviorDefault];
        NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init] autorelease];
		[dateFormatter setDateStyle:NSDateFormatterShortStyle];
		[dateFormatter setTimeStyle:NSDateFormatterShortStyle];
        
		_lastUpdatedLabel.text = [NSString stringWithFormat:_W(@"Last Updated: %@"), [dateFormatter stringFromDate:date]];
		[[NSUserDefaults standardUserDefaults] setObject:_lastUpdatedLabel.text forKey:@"WSIUIRefreshTableView_LastRefresh"];
		[[NSUserDefaults standardUserDefaults] synchronize];
		
	} else {
		
		_lastUpdatedLabel.text = nil;
	}
}

- (void)refreshScrollViewDidScroll:(UIScrollView *)scrollView {
    
    if (_state == UITableViewPullRefreshStateLoading) {
		
		CGFloat offset = MAX(scrollView.contentOffset.y * -1, 0);
		offset = MIN(offset, 60);
		scrollView.contentInset = UIEdgeInsetsMake(offset, 0.0f, 0.0f, 0.0f);
		
	} else if (scrollView.isDragging) {
		
		BOOL _loading = NO;
		if ([_delegate respondsToSelector:@selector(RefreshTableHeaderDataSourceIsLoading:)]) {
			_loading = [_delegate RefreshTableHeaderDataSourceIsLoading:self];
		}
		
		if (_state == UITableViewPullRefreshStatePulling && scrollView.contentOffset.y > -65.0f && scrollView.contentOffset.y < 0.0f && !_loading) {
			[self setState:UITableViewPullRefreshStateNormal];
		} else if (_state == UITableViewPullRefreshStateNormal && scrollView.contentOffset.y < -65.0f && !_loading) {
			[self setState:UITableViewPullRefreshStatePulling];
		}
		
		if (scrollView.contentInset.top != 0) {
			scrollView.contentInset = UIEdgeInsetsZero;
		}
	}
}

- (void)refreshScrollViewDidEndDragging:(UIScrollView *)scrollView {
    
    BOOL _loading = NO;
	if ([_delegate respondsToSelector:@selector(RefreshTableHeaderDataSourceIsLoading:)]) {
		_loading = [_delegate RefreshTableHeaderDataSourceIsLoading:self];
	}
	
	if (scrollView.contentOffset.y <= - 65.0f && !_loading) {
		
		if ([_delegate respondsToSelector:@selector(RefreshTableHeaderDidTriggerRefresh:)]) {
			[_delegate RefreshTableHeaderDidTriggerRefresh:self];
		}
		
		[self setState:UITableViewPullRefreshStateLoading];
		[UIView beginAnimations:nil context:NULL];
		[UIView setAnimationDuration:0.2];
		scrollView.contentInset = UIEdgeInsetsMake(60.0f, 0.0f, 0.0f, 0.0f);
		[UIView commitAnimations];
	}
}

- (void)refreshScrollViewDataSourceDidFinishedLoading:(UIScrollView *)scrollView {
    
    [UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDuration:.3];
	[scrollView setContentInset:UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f)];
	[UIView commitAnimations];
	
	[self setState:UITableViewPullRefreshStateNormal];
}

- (void)dealloc {
	_delegate = nil;
	_activityView = nil;
	_statusLabel = nil;
	_arrowImage = nil;
	_lastUpdatedLabel = nil;
    [super dealloc];
}

- (void)setState:(UITableViewPullRefreshState)aState{	
	switch (aState) {
		case UITableViewPullRefreshStatePulling: {	
			_statusLabel.text = _W(@"Release to refresh...");
			[CATransaction begin];
			[CATransaction setAnimationDuration:FLIP_ANIMATION_DURATION];
			_arrowImage.transform = CATransform3DMakeRotation((M_PI / 180.0) * 180.0f, 0.0f, 0.0f, 1.0f);
			[CATransaction commit];			
        } break;
		case UITableViewPullRefreshStateNormal: {
			if (_state == UITableViewPullRefreshStatePulling) {
				[CATransaction begin];
				[CATransaction setAnimationDuration:FLIP_ANIMATION_DURATION];
				_arrowImage.transform = CATransform3DIdentity;
				[CATransaction commit];
			}			
            
			_statusLabel.text = _W(@"Pull down to refresh...");
			[_activityView stopAnimating];
			[CATransaction begin];
			[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions]; 
			_arrowImage.hidden = NO;
			_arrowImage.transform = CATransform3DIdentity;
			[CATransaction commit];
			
			[self refreshLastUpdatedDate];
			
        } break;
		case UITableViewPullRefreshStateLoading: {			
			_statusLabel.text = _W(@"Loading...");
			[_activityView startAnimating];
			[CATransaction begin];
			[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions]; 
			_arrowImage.hidden = YES;
			[CATransaction commit];			
        } break;
		default: break;
	}
	
	_state = aState;
}

@end

@interface UIPullMoreHeaderView ()

- (void)setState:(UITableViewPullMoreState)aState;

@end

@implementation UIPullMoreHeaderView

@synthesize delegate = _delegate;
@synthesize pageno, model;

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalPullHeaderMore)
WSIEVENT_END

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self == nil)
        return nil;
    
    self.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    self.backgroundColor = BACKGROUND_COLOR;
    
    UILabel *label = [[UILabel alloc] initWithZero];
    label.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    label.font = [UIFont systemFontOfSize:12.0f];
    label.textColor = TEXT_COLOR;
    label.shadowColor = [UIColor colorWithWhite:0.9f alpha:1.0f];
    label.shadowOffset = CGSizeMake(0.0f, 1.0f);
    label.backgroundColor = [UIColor clearColor];
    label.textAlignment = UITextAlignmentCenter;
    [self addSubview:label];
    _moreLabel = label;
    [label release];
    
    UIActivityIndicatorView *view = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    [self addSubview:view];
    _activityView = view;
    [view release];
    
    [self setState:UITableViewPullRefreshStateNormal];
    
    return self;
}

- (void)dealloc {
    zero_release(model);
    
    [super dealloc];
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
}

- (void)layoutSubviews {
    CGRect rc_client = self.bounds;
    _moreLabel.frame = CGRectMake(0, 0, rc_client.size.width, 20.0f);
    _activityView.frame = CGRectMake(25.f, 0, 20.0f, 20.0f);
}

- (void)refreshScrollViewDidScroll:(UIScrollView *)scrollView {
    //CGRect rc_content = CGRectMakeSz(scrollView.contentSize);
    CGRect rc_content = self.rectForLayout;
    
    CGPoint lt = CGRectLeftBottom(&rc_content);
    [self moveTo:lt];
    
    if (_state == UITableViewPullMoreStateLoading) {		
		CGFloat offset = MAX(scrollView.contentOffset.y * -1, 0);
		offset = MIN(offset, 60);
		scrollView.contentInset = UIEdgeInsetsMake(offset, 0.0f, 0.0f, 0.0f);		
	} else if (scrollView.isDragging) {		
		BOOL _loading = NO;
		if ([_delegate respondsToSelector:@selector(MoreTableHeaderDataSourceIsLoading:)]) {
			_loading = [_delegate MoreTableHeaderDataSourceIsLoading:self];
		}		
        if (!_loading) {
            int doff = scrollView.contentSize.height - scrollView.bounds.size.height;
            if (_state == UITableViewPullMoreStatePulling && (int)scrollView.contentOffset.y <= doff ) {
                [self setState:UITableViewPullMoreStateNormal];
            } else if (_state == UITableViewPullMoreStateNormal && (int)scrollView.contentOffset.y > doff && (int)scrollView.contentOffset.y > 0) {
                [self setState:UITableViewPullMoreStatePulling];
            }		
        }
		if (scrollView.contentInset.top != 0) {
			scrollView.contentInset = UIEdgeInsetsZero;
		}
	}
}

- (void)refreshScrollViewDidEndDragging:(UIScrollView *)scrollView {
    BOOL _loading = NO;
	if ([_delegate respondsToSelector:@selector(MoreTableHeaderDataSourceIsLoading:)]) {
		_loading = [_delegate MoreTableHeaderDataSourceIsLoading:self];
	}
	
    int doff = scrollView.contentSize.height - scrollView.bounds.size.height;
	if ((int)scrollView.contentOffset.y > doff && !_loading) {		
		if ([_delegate respondsToSelector:@selector(MoreTableHeaderDidTriggerRefresh:)]) {
			[_delegate MoreTableHeaderDidTriggerRefresh:self];
		}
		
		[self setState:UITableViewPullMoreStateLoading];
        
		[UIView beginAnimations:nil context:NULL];
		[UIView setAnimationDuration:.5f];
		scrollView.contentInset = UIEdgeInsetsMake(0, 0, 60.f, 0);
		[UIView commitAnimations];
	}
}

- (void)refreshScrollViewDataSourceDidFinishedLoading:(UIScrollView *)scrollView {    
    [UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDuration:.5f];
	scrollView.contentInset = UIEdgeInsetsMake(0, 0, 0, 0);
	[UIView commitAnimations];
	
	[self setState:UITableViewPullMoreStateNormal];
}

- (void)setState:(UITableViewPullMoreState)aState{	
	switch (aState) {
		case UITableViewPullMoreStatePulling: {	
			_moreLabel.text = _W(@"Release to load more...");
        } break;
		case UITableViewPullMoreStateNormal: {
			_moreLabel.text = _W(@"Pull down to load more...");
			[_activityView stopAnimating];			
        } break;
		case UITableViewPullMoreStateLoading: {			
			_moreLabel.text = _W(@"Loading...");
			[_activityView startAnimating];
        } break;
		default: break;
	}
	
	_state = aState;
}

@end

WSI_END_OBJC