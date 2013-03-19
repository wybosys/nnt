
# ifndef __NNT_UIKIT_UISCROLLHEADERVIEW_22039D89EB53475A92C125BBD27D635F_H_INCLUDED
# define __NNT_UIKIT_UISCROLLHEADERVIEW_22039D89EB53475A92C125BBD27D635F_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UIPullRefreshHeaderView);
NNTDECL_EXTERN_CLASS(UIPullMoreHeaderView);

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

@protocol NNTUITablePullRefreshDelegate <NSObject>

- (void)RefreshTableHeaderDidTriggerRefresh:(UIPullRefreshHeaderView*)view;
- (BOOL)RefreshTableHeaderDataSourceIsLoading:(UIPullRefreshHeaderView*)view;

@optional

- (NSDate*)RefreshTableHeaderDataSourceLastUpdated:(UIPullRefreshHeaderView*)view;

@end

@protocol NNTUITablePullMoreDelegate <NSObject>

- (void)MoreTableHeaderDidTriggerRefresh:(UIPullMoreHeaderView*)view;
- (BOOL)MoreTableHeaderDataSourceIsLoading:(UIPullMoreHeaderView*)view;

@end

@interface UIPullRefreshHeaderView : NNTUIView {   
    @protected
    id <NNTUITablePullRefreshDelegate> _delegate;
    UITableViewPullRefreshState _state;
    
	UILabel *_lastUpdatedLabel;
	UILabel *_statusLabel;
	CALayer *_arrowImage;
	UIActivityIndicatorView *_activityView;
}

@property (nonatomic, assign) id <NNTUITablePullRefreshDelegate> delegate;

//! refresh.
- (void)refreshLastUpdatedDate;

//! refresh.
- (void)refreshScrollViewDidScroll:(UIScrollView *)scrollView;
- (void)refreshScrollViewDidEndDragging:(UIScrollView *)scrollView;
- (void)refreshScrollViewDataSourceDidFinishedLoading:(UIScrollView *)scrollView;

@end

@interface UIPullMoreHeaderView : NNTUIView {
    
    //! no. of page.
    uint pageno;
    
    //! model of page.
    id model;
    
    @protected
    id<NNTUITablePullMoreDelegate> _delegate;
    UITableViewPullMoreState _state;    
    
    UILabel* _moreLabel;
    UIActivityIndicatorView *_activityView;        
}

@property (nonatomic, assign) id<NNTUITablePullMoreDelegate> delegate;
@property (nonatomic, assign) uint pageno;
@property (nonatomic, retain) id model;

- (void)refreshScrollViewDidScroll:(UIScrollView *)scrollView;
- (void)refreshScrollViewDidEndDragging:(UIScrollView *)scrollView;
- (void)refreshScrollViewDataSourceDidFinishedLoading:(UIScrollView *)scrollView;

@end

NNT_EXTERN signal_t kSignalPullHeaderReload;
NNT_EXTERN signal_t kSignalPullHeaderMore;

NNT_END_HEADER_OBJC

# endif