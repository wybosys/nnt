
# ifndef __NNT_UIKIT_MAPABC_C223D4DD3BCB4A03B144CBEA8643D2BC_H_INCLUDED
# define __NNT_UIKIT_MAPABC_C223D4DD3BCB4A03B144CBEA8643D2BC_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(MTMapView);

@interface UIMapAbcView : NNTUIView {    
    
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

NNT_END_HEADER_OBJC

# endif