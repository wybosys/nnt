
# ifndef __WSI_UIKIT_UICHARTCONTROLLER_1EA53BB3A39F432EB1875D4BBA73FD71_H_INCLUDED
# define __WSI_UIKIT_UICHARTCONTROLLER_1EA53BB3A39F432EB1875D4BBA73FD71_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UICPXYGraph);
WSIDECL_EXTERN_CLASS(UIChartController);

@protocol UIChartControllerDatasource <NSObject>

- (void)chartControllerInit:(UIChartController*)chart;

@end

@protocol UIChartControllerDelegate <NSObject>

@optional
- (void)chartControllerClear:(UIChartController*)chart;
- (void)chartControllerRefresh:(UIChartController*)chart;

@end

@interface UIChartController : WSIUIViewController <UIChartControllerDatasource, UIChartControllerDelegate> {
    
    //! graph.
    UICPXYGraph *graph;
    
    //! background.
    UIImage *backgroundImage;
    
    //! frame.
    CGRect frame;
    
    id <UIChartControllerDatasource> dataSource;
    id <UIChartControllerDelegate> delegate;
}

@property (nonatomic, retain) UICPXYGraph *graph;
@property (nonatomic, assign) id <UIChartControllerDatasource> dataSource;
@property (nonatomic, assign) id <UIChartControllerDelegate> delegate;
@property (nonatomic, retain) UIImage *backgroundImage;
@property (nonatomic) CGRect frame;

//! clear chart
- (void)clear;

//! refresh chart
- (void)refresh;

@end

WSI_END_HEADER_OBJC

# endif