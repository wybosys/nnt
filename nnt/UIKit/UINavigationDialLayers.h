
# ifndef __WSI_UIKIT_UINAVIGATIONDIALLAYERS_F3EBAD050CB24156A271D889DB7D6037_H_INCLUDED
# define __WSI_UIKIT_UINAVIGATIONDIALLAYERS_F3EBAD050CB24156A271D889DB7D6037_H_INCLUDED

# import "WCALayer.h"
# import "CATextLayer+WCA.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCALayerDialRingItem);
WSIDECL_EXTERN_CLASS(CGShadow);

@interface WCALayerDialRingCenter : WCALayer {
    real radiusCollapse;
    real radiusExpend;
    real radius;
}

@property (nonatomic, assign) real radiusCollapse, radiusExpend;
@property (nonatomic, readonly) real radius;

- (void)setRadius:(real)val;

@end

@interface WCALayerDialRing : WCALayer {
    
    //! geomerty.
    real radiusOutter;
    real radiusInner;
    real diameterOuter;
    
    //! shadow.
    CGShadow *ringShadowOuter, *ringShadowInner;
    
    //! items.
    NSArray *itemLayers;
    
    //! start angle.
    real startAngle;
}

@property (nonatomic, assign) real radiusOutter, radiusInner, diameterOuter;
@property (nonatomic, retain) CGShadow *ringShadowOuter, *ringShadowInner;
@property (nonatomic, retain) NSArray *itemLayers;
@property (nonatomic, assign) real startAngle;

- (void)relayoutItems;

@end

@interface WCALayerDialRingItem : WCALayer {
    
    //! image.
    CGImageRef image;
    
    //! shadow.
    CGShadow *edgeShadow;
    
    //! scale image in percent. default is .2f.
    real scaleImage;
    
    //! inflate item in percent, default is .2f;
    real deflate;
    
    //! image mask color.
    UIColor *imageMaskColor;
    
    //! layer of badge.
    WCALayer *layerBadge;
}

@property (nonatomic, assign) CGImageRef image;
@property (nonatomic, retain) CGShadow *edgeShadow;
@property (nonatomic, assign) real scaleImage, deflate;
@property (nonatomic, retain) UIColor *imageMaskColor;
@property (nonatomic, assign) WCALayer *layerBadge;

@end

@interface WCALayerDialLabelRing : WCALayer {
    
    //! radius.
    real radius, diameter;
    
    //! array of items;
    NSArray *itemLayers;
    
    //! start angle.
    real startAngle;
    
    //! clockwise.
    BOOL clockwise;
}

@property (nonatomic, assign) real radius;
@property (nonatomic, readonly) real diameter;
@property (nonatomic, retain) NSArray *itemLayers;
@property (nonatomic, assign) real startAngle;
@property (nonatomic, assign) BOOL clockwise;

- (void)relayoutItems;

@end

@interface WCALayerDialLabelRingItem : WCATextLayer

//! adapt for content, default is YES.
@property (nonatomic, assign) BOOL adaptContent;

//! preferred size.
@property (nonatomic, assign) CGSize preferredSize;

//! offset.
@property (nonatomic, assign) real offset;

@end

WSI_END_HEADER_OBJC

# endif