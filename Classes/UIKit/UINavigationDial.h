
# ifndef __NNT_UIKIT_UIDIALNAVIGATION_52636679239241AEBC49667F5FA85F75_H_INCLUDED
# define __NNT_UIKIT_UIDIALNAVIGATION_52636679239241AEBC49667F5FA85F75_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgFill);
NNTDECL_EXTERN_CLASS(NgTextStyle);
NNTDECL_EXTERN_CLASS(NNTUIViewController);
NNTDECL_EXTERN_CLASS(CGShadow);

NNTDECL_PRIVATE_HEAD(UINavigationDial);

@protocol UINavigationDialDataSource <NSObject>

@end

@protocol UINavigationDialDelegate <NSObject>

@end

NNTDECL_EXTERN_CLASS(NgLayerDialRingItem);
NNTDECL_EXTERN_CLASS(NgLayerDialLabelRingItem);
NNTDECL_EXTERN_CLASS(NgLayerDialRingCenter);
NNTDECL_EXTERN_CLASS(NgBadgeIndicator);

@interface UINavigationDialItem : NNTObject {
    //! layer.
    NgLayerDialRingItem *layerItem;
    NgLayerDialLabelRingItem *layerLabel;
    NgBadgeIndicator *layerBadge;
    
    //! color.
    UIColor *imageMaskColor;
    
    //! label.
    NgFill *labelFill;
    NgTextStyle *labelTextStyle;
    
    //! view controller.
    NNTUIViewController *viewController;
    
    //! badge value.
    NSString *badgeValue;
}

@property (nonatomic, retain) NgLayerDialRingItem      *layerItem;
@property (nonatomic, retain) NgLayerDialLabelRingItem *layerLabel;
@property (nonatomic, retain) NgBadgeIndicator         *layerBadge;
@property (nonatomic, retain) UIColor                   *imageMaskColor;
@property (nonatomic, retain) NNTUIViewController       *viewController;
@property (nonatomic, retain) NgFill                   *labelFill;
@property (nonatomic, retain) NgTextStyle              *labelTextStyle;
@property (nonatomic, copy)   NSString                  *badgeValue;

//! refresh.
- (void)setNeedsDisplay;

@end

@interface UINavigationDial : NNTUIView {
    
    //! delegate & data-source.
    id <UINavigationDialDataSource> dataSource;
    id <UINavigationDialDelegate> delegate;
    
    //! radius.
    real radiusOuter, radiusInner;
    real radiusCollapse, radiusExpand;
    
    //! items.
    NSArray *items;
    
    //! item color.
    UIColor *itemDefaultColor, *itemSelectedColor;
    CGShadow *itemEdgeShadow;
    NgFill *itemFill;
    
    //! label.
    NgFill *labelFill;
    NgTextStyle *labelTextStyle;
    CGSize preferredLabelSize;
    real labelOffset;
    
    //! color.
    NgFill *dialFill, *centerFill;
    CGShadow* dialInnerShadow, *dialOutterShadow;
    
    //! clockwise. default is YES.
    BOOL clockwise;
    
    //! start angle.
    real startAngle;
    
    //! expanded. default is NO.
    BOOL isExpanded;
    
    NNTDECL_PRIVATE(UINavigationDial);
}

@property (nonatomic, assign) id <UINavigationDialDataSource> dataSource;
@property (nonatomic, assign) id <UINavigationDialDelegate> delegate;
@property (nonatomic, assign) real radiusOuter, radiusInner, radiusCollapse, radiusExpand;
@property (nonatomic, retain) NSArray *items;
@property (nonatomic, retain) UIColor *itemDefaultColor, *itemSelectedColor;
@property (nonatomic, retain) NgFill *dialFill, *centerFill;
@property (nonatomic, retain) NgFill *itemFill;
@property (nonatomic, retain) CGShadow* dialInnerShadow, *dialOutterShadow;
@property (nonatomic, retain) CGShadow *itemEdgeShadow;
@property (nonatomic, retain) NgFill *labelFill;
@property (nonatomic, retain) NgTextStyle *labelTextStyle;
@property (nonatomic, assign) CGSize preferredLabelSize;
@property (nonatomic, assign) BOOL clockwise;
@property (nonatomic, assign) real startAngle;
@property (nonatomic, assign) BOOL isExpanded;
@property (nonatomic, assign) real labelOffset;

//! show label.
- (void)showLabel:(BOOL)val;

@end

extern NSString *kSignalValueChanged;

@interface UINavigationDial (interactive)

//! hit test.
- (BOOL)hitTest:(CGPoint)pt;

//! rotate angle(rad).
- (void)rotateAngle:(real)angle animated:(BOOL)animated;
- (void)rotateToAngle:(real)angle animated:(BOOL)animated;

@end

extern NSString *kSignalDialClicked;

NNT_END_HEADER_OBJC

# endif