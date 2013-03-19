
# ifndef __WSI_UIKIT_MAP_AMAPVIEW_2BF4B50A0F4A47D89B4EE5812128249F_H_INCLUDED
# define __WSI_UIKIT_MAP_AMAPVIEW_2BF4B50A0F4A47D89B4EE5812128249F_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UIMaMapView);

@interface UIMaMapView : WSIUIView {    
    WSIDECL_PRIVATE(UIMaMapView);
}

@property (nonatomic, assign) BOOL animated;

//! set region for visible.
- (void)setRegion:(CGRect)region animated:(BOOL)animated;

//! set center position.
- (void)setPosition:(CGPoint)location animated:(BOOL)animated;

@end

WSI_END_HEADER_OBJC

# endif