
# ifndef __NNT_UIKIT_COREPLOT_CPPIEPLOT_75E371869C494858BD3DCD14A7F52174_H_INCLUDED
# define __NNT_UIKIT_COREPLOT_CPPIEPLOT_75E371869C494858BD3DCD14A7F52174_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface CPPieChart (NNT)

- (CGPoint)centerPoint:(CGContextRef)context;

@end

NNTDECL_PRIVATE_HEAD(UICPPieChart);

@interface UICPPieChart : CPPieChart {
    UICPLineStyle *outLine;
    BOOL pieTotal;
    UICPLineStyle *totalOutLine;
    CGFloat totalRadius; //! ratio of radius, 0 - 1.0
    BOOL allowInteractiveRotate; //! allow rotate by user's figure
    
    NNTDECL_PRIVATE(UICPPieChart);
}

@property (nonatomic, retain) UICPLineStyle *outLine;
@property (nonatomic) BOOL pieTotal;
@property (nonatomic, retain) UICPLineStyle *totalOutLine;
@property (nonatomic) CGFloat totalRadius;
@property (nonatomic) BOOL allowInteractiveRotate;

- (void)addIndicator:(UICPIndicatorLayer*)__layer;
- (void)animationTimer;
- (void)stop_AnimationTimer;
@end

@protocol UICPPieChartDataSource <CPPieChartDataSource>
@optional

- (CPFill*)totalFillForPieChart:(CPPieChart *)pieChart;
- (CPLayer*)totalLabelForPieChart:(CPPieChart *)pieChart;

@end

@protocol UICPPieChartDelegate <CPPieChartDelegate>
@optional

- (void)pieChart:(CPPieChart *)plot sliceWasOver:(NSUInteger)index indicator:(UICPIndicatorLayer*)indicator;
- (void)pieChart:(CPPieChart *)plot sliceWasDragging:(NSUInteger)index;
- (void)pieChart:(CPPieChart *)plot sliceWasDraggingEnd:(NSUInteger)index;

@end

NNT_END_HEADER_OBJC

# endif