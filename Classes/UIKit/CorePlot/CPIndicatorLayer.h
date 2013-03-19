
# ifndef __WSI_UIKIT_COREPLOT_CPINDICATORLAYTER_0007691DDBC7411ABE6E7127FE5A4E11_H_INCLUDED
# define __WSI_UIKIT_COREPLOT_CPINDICATORLAYTER_0007691DDBC7411ABE6E7127FE5A4E11_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(CPIndicatorLayer);

@interface CPIndicatorLayer : CPLayer {
    
    CGFloat positionAngle;
    CPColor* indicatorColor;
    CPColor* indicatorBaseColor;
    CGFloat baseHeight; //! in ratio, 0 - 1.0
    id <NSCopying, NSObject> identifier;
    
    WSIDECL_PRIVATE(CPIndicatorLayer);
}

@property (nonatomic) CGFloat positionAngle;
@property (nonatomic, copy) CPColor *indicatorColor;
@property (nonatomic, copy) CPColor *indicatorBaseColor;
@property (nonatomic) CGFloat baseHeight;
@property (nonatomic, copy) id <NSCopying, NSObject> identifier;

@end

typedef CPIndicatorLayer UICPIndicatorLayer;

WSI_END_HEADER_OBJC

# endif