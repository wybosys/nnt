
# ifndef __WSI_UIKIT_MAPABC_C223D4DD3BCB4A03B144CBEA8643D2BC_H_INCLUDED
# define __WSI_UIKIT_MAPABC_C223D4DD3BCB4A03B144CBEA8643D2BC_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(MTMapView);

@interface UIMapAbcView : WSIUIView {    
    
    //! animated. default is NO.
    BOOL animated;
    
    @protected
    MTMapView* _mapabc;
    CGRect _region;
    CGPoint _coordcenter;
}

@property (nonatomic, assign) BOOL animated;
@property (nonatomic, readonly) MTMapView* mapabc;

- (void)setRegion:(CGRect)region;
- (void)setCenterCoordinate:(CGPoint)coordcenter;

@end

WSI_END_HEADER_OBJC

# endif