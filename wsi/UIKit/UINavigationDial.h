
# ifndef __WSI_UIKIT_UIDIALNAVIGATION_52636679239241AEBC49667F5FA85F75_H_INCLUDED
# define __WSI_UIKIT_UIDIALNAVIGATION_52636679239241AEBC49667F5FA85F75_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGFill);
WSIDECL_EXTERN_CLASS(WCGTextStyle);
WSIDECL_EXTERN_CLASS(WSIUIViewController);
WSIDECL_EXTERN_CLASS(CGShadow);

WSIDECL_PRIVATE_HEAD(UINavigationDial);

@protocol UINavigationDialDataSource <NSObject>

@end

@protocol UINavigationDialDelegate <NSObject>

@end

WSIDECL_EXTERN_CLASS(WCALayerDialRingItem);
WSIDECL_EXTERN_CLASS(WCALayerDialLabelRingItem);
WSIDECL_EXTERN_CLASS(WCALayerDialRingCenter);
WSIDECL_EXTERN_CLASS(WCABadgeIndicator);

@interface UINavigationDialItem : WSIObject {
    //! layer.
    WCALayerDialRingItem *layerItem;
    WCALayerDialLabelRingItem *layerLabel;
    WCABadgeIndicator *layerBadge;
    
    //! color.
    UIColor *imageMaskColor;
    
    //! label.
    WCGFill *labelFill;
    WCGTextStyle *labelTextStyle;
    
    //! view controller.
    WSIUIViewController *viewController;
    
    //! badge value.
    NSString *badgeValue;
}

@property (nonatomic, retain) WCALayerDialRingItem      *layerItem;
@property (nonatomic, retain) WCALayerDialLabelRingItem *layerLabel;
@property (nonatomic, retain) WCABadgeIndicator         *layerBadge;
@property (nonatomic, retain) UIColor                   *imageMaskColor;
@property (nonatomic, retain) WSIUIViewController       *viewController;
@property (nonatomic, retain) WCGFill                   *labelFill;
@property (nonatomic, retain) WCGTextStyle              *labelTextStyle;
@property (nonatomic, copy)   NSString                  *badgeValue;

//! refresh.
- (void)setNeedsDisplay;

@end

@interface UINavigationDial : WSIUIView {
    
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
    WCGFill *itemFill;
    
    //! label.
    WCGFill *labelFill;
    WCGTextStyle *labelTextStyle;
    CGSize preferredLabelSize;
    real labelOffset;
    
    //! color.
    WCGFill *dialFill, *centerFill;
    CGShadow* dialInnerShadow, *dialOutterShadow;
    
    //! clockwise. default is YES.
    BOOL clockwise;
    
    //! start angle.
    real startAngle;
    
    //! expanded. default is NO.
    BOOL isExpanded;
    
    WSIDECL_PRIVATE(UINavigationDial);
}

@property (nonatomic, assign) id <UINavigationDialDataSource> dataSource;
@property (nonatomic, assign) id <UINavigationDialDelegate> delegate;
@property (nonatomic, assign) real radiusOuter, radiusInner, radiusCollapse, radiusExpand;
@property (nonatomic, retain) NSArray *items;
@property (nonatomic, retain) UIColor *itemDefaultColor, *itemSelectedColor;
@property (nonatomic, retain) WCGFill *dialFill, *centerFill;
@property (nonatomic, retain) WCGFill *itemFill;
@property (nonatomic, retain) CGShadow* dialInnerShadow, *dialOutterShadow;
@property (nonatomic, retain) CGShadow *itemEdgeShadow;
@property (nonatomic, retain) WCGFill *labelFill;
@property (nonatomic, retain) WCGTextStyle *labelTextStyle;
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

WSI_END_HEADER_OBJC

# endif