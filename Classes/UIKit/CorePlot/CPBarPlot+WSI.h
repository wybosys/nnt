
# ifndef __NNT_UIKIT_CPBARPLOT_16E1FFB3B5044E76950EF5F21D40ED80_H_INCLUDED
# define __NNT_UIKIT_CPBARPLOT_16E1FFB3B5044E76950EF5F21D40ED80_H_INCLUDED

# import "CPBarLayer.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(CGShadow);
NNTDECL_EXTERN_CLASS(CGAnimation);

@interface CPBarPlot (NNT)

@end

NNTDECL_PRIVATE_HEAD(UICPBarPlot);

@interface UICPBarPlot : CPBarPlot {
    NNTDECL_PRIVATE(UICPBarPlot);
    
    BOOL allowInteractiveMoveIndicator;
    UICPMutableLineStyle *indicatorLiveLineStyle;
    CGFloat indicatorLiveLineOffset;
    CGShadow *barShadow;
    CGAnimation *barAnimation;
    
    BOOL movingSelectedEnable;
}

@property (nonatomic) BOOL allowInteractiveMoveIndicator;
@property (nonatomic, retain) UICPMutableLineStyle *indicatorLiveLineStyle;
@property (nonatomic) CGFloat indicatorLiveLineOffset;
@property (nonatomic, retain) CGShadow *barShadow;
@property (nonatomic, retain) CGAnimation *barAnimation;
@property (nonatomic) BOOL movingSelectedEnable;

//! add a indicator.
- (void)addIndicator:(UICPIndicatorLayer*)indicator;

//! get bar layer
- (CPBarLayer*)barLayer:(NSUInteger)idx;

@end

@protocol UICPBarPlotDataSource <CPBarPlotDataSource>

@optional

- (CGShadow*)barShadowFillForBarPlot:(UICPBarPlot*)plot recordIndex:(NSUInteger)index;
- (CGAnimation*)barAnimationForBarPlot:(UICPBarPlot*)plot recordIndex:(NSUInteger)index;

@end

@protocol UICPBarPlotDelegate <CPBarPlotDelegate>

@optional

//! if no selected, return NSNotFound, or return the bar index.
- (void)barPlot:(CPBarPlot *)plot barWasUnselectedAtRecordIndex:(NSUInteger)index;

@end

NNT_END_HEADER_OBJC

# endif