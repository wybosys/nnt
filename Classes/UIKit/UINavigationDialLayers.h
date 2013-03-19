
# ifndef __NNT_UIKIT_UINAVIGATIONDIALLAYERS_F3EBAD050CB24156A271D889DB7D6037_H_INCLUDED
# define __NNT_UIKIT_UINAVIGATIONDIALLAYERS_F3EBAD050CB24156A271D889DB7D6037_H_INCLUDED

# import "NGLayer.h"
# import "NGTextLayer.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgLayerDialRingItem);
NNTDECL_EXTERN_CLASS(CGShadow);

@interface NgLayerDialRingCenter : NgLayer {
    real radiusCollapse;
    real radiusExpend;
    real radius;
}

@property (nonatomic, assign) real radiusCollapse, radiusExpend;
@property (nonatomic, readonly) real radius;

- (void)setRadius:(real)val;

@end

@interface NgLayerDialRing : NgLayer {
    
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

@interface NgLayerDialRingItem : NgLayer {
    
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
    NgLayer *layerBadge;
}

@property (nonatomic, assign) CGImageRef image;
@property (nonatomic, retain) CGShadow *edgeShadow;
@property (nonatomic, assign) real scaleImage, deflate;
@property (nonatomic, retain) UIColor *imageMaskColor;
@property (nonatomic, assign) NgLayer *layerBadge;

@end

@interface NgLayerDialLabelRing : NgLayer {
    
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

@interface NgLayerDialLabelRingItem : NgTextLayer

//! adapt for content, default is YES.
@property (nonatomic, assign) BOOL adaptContent;

//! preferred size.
@property (nonatomic, assign) CGSize preferredSize;

//! offset.
@property (nonatomic, assign) real offset;

@end

NNT_END_HEADER_OBJC

# endif