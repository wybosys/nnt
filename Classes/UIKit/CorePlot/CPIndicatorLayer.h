
# ifndef __NNT_UIKIT_COREPLOT_CPINDICATORLAYTER_0007691DDBC7411ABE6E7127FE5A4E11_H_INCLUDED
# define __NNT_UIKIT_COREPLOT_CPINDICATORLAYTER_0007691DDBC7411ABE6E7127FE5A4E11_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(CPIndicatorLayer);

@interface CPIndicatorLayer : CPLayer {
    
    CGFloat positionAngle;
    CPColor* indicatorColor;
    CPColor* indicatorBaseColor;
    CGFloat baseHeight; //! in ratio, 0 - 1.0
    id <NSCopying, NSObject> identifier;
    
    NNTDECL_PRIVATE(CPIndicatorLayer);
}

@property (nonatomic) CGFloat positionAngle;
@property (nonatomic, copy) CPColor *indicatorColor;
@property (nonatomic, copy) CPColor *indicatorBaseColor;
@property (nonatomic) CGFloat baseHeight;
@property (nonatomic, copy) id <NSCopying, NSObject> identifier;

@end

typedef CPIndicatorLayer UICPIndicatorLayer;

NNT_END_HEADER_OBJC

# endif