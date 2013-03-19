
# ifndef __NNT_UIKIT_MAP_AMAPVIEW_2BF4B50A0F4A47D89B4EE5812128249F_H_INCLUDED
# define __NNT_UIKIT_MAP_AMAPVIEW_2BF4B50A0F4A47D89B4EE5812128249F_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UIMaMapView);

@interface UIMaMapView : NNTUIView {    
    NNTDECL_PRIVATE(UIMaMapView);
}

@property (nonatomic, assign) BOOL animated;

//! set region for visible.
- (void)setRegion:(CGRect)region animated:(BOOL)animated;

//! set center position.
- (void)setPosition:(CGPoint)location animated:(BOOL)animated;

@end

NNT_END_HEADER_OBJC

# endif