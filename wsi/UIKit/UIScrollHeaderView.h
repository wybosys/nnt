
# ifndef __WSI_UIKIT_UISCROLLHEADERVIEW_22039D89EB53475A92C125BBD27D635F_H_INCLUDED
# define __WSI_UIKIT_UISCROLLHEADERVIEW_22039D89EB53475A92C125BBD27D635F_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UIPullRefreshHeaderView);
WSIDECL_EXTERN_CLASS(UIPullMoreHeaderView);

enum {
	UITableViewPullRefreshStatePulling = 0,
	UITableViewPullRefreshStateNormal,
	UITableViewPullRefreshStateLoading,	
};
typedef uint UITableViewPullRefreshState;

enum {
    UITableViewPullMoreStatePulling = 0,
    UITableViewPullMoreStateNormal,
    UITableViewPullMoreStateLoading,
};
typedef uint UITableViewPullMoreState;

@protocol WSIUITablePullRefreshDelegate <NSObject>

- (void)RefreshTableHeaderDidTriggerRefresh:(UIPullRefreshHeaderView*)view;
- (BOOL)RefreshTableHeaderDataSourceIsLoading:(UIPullRefreshHeaderView*)view;

@optional

- (NSDate*)RefreshTableHeaderDataSourceLastUpdated:(UIPullRefreshHeaderView*)view;

@end

@protocol WSIUITablePullMoreDelegate <NSObject>

- (void)MoreTableHeaderDidTriggerRefresh:(UIPullMoreHeaderView*)view;
- (BOOL)MoreTableHeaderDataSourceIsLoading:(UIPullMoreHeaderView*)view;

@end

@interface UIPullRefreshHeaderView : WSIUIView {   
    @protected
    id <WSIUITablePullRefreshDelegate> _delegate;
    UITableViewPullRefreshState _state;
    
	UILabel *_lastUpdatedLabel;
	UILabel *_statusLabel;
	CALayer *_arrowImage;
	UIActivityIndicatorView *_activityView;
}

@property (nonatomic, assign) id <WSIUITablePullRefreshDelegate> delegate;

//! refresh.
- (void)refreshLastUpdatedDate;

//! refresh.
- (void)refreshScrollViewDidScroll:(UIScrollView *)scrollView;
- (void)refreshScrollViewDidEndDragging:(UIScrollView *)scrollView;
- (void)refreshScrollViewDataSourceDidFinishedLoading:(UIScrollView *)scrollView;

@end

@interface UIPullMoreHeaderView : WSIUIView {
    
    //! no. of page.
    uint pageno;
    
    //! model of page.
    id model;
    
    @protected
    id<WSIUITablePullMoreDelegate> _delegate;
    UITableViewPullMoreState _state;    
    
    UILabel* _moreLabel;
    UIActivityIndicatorView *_activityView;        
}

@property (nonatomic, assign) id<WSIUITablePullMoreDelegate> delegate;
@property (nonatomic, assign) uint pageno;
@property (nonatomic, retain) id model;

- (void)refreshScrollViewDidScroll:(UIScrollView *)scrollView;
- (void)refreshScrollViewDidEndDragging:(UIScrollView *)scrollView;
- (void)refreshScrollViewDataSourceDidFinishedLoading:(UIScrollView *)scrollView;

@end

WSI_EXTERN signal_t kSignalPullHeaderReload;
WSI_EXTERN signal_t kSignalPullHeaderMore;

WSI_END_HEADER_OBJC

# endif