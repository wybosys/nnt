
# ifndef __NNT_UIKIT_UIIMAGEDESKTOP_A3BC9B1BD8CF4481BA0D10FD853A0525_H_INCLUDED
# define __NNT_UIKIT_UIIMAGEDESKTOP_A3BC9B1BD8CF4481BA0D10FD853A0525_H_INCLUDED

# import "UIDesktop.h"
# import "CoreGraphic+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTUIButton);

NNTDECL_EXTERN_CLASS(NNTUIImageView);

@interface UIImageDesktop : NNTUIDesktop {

    //! image view.
    NNTUIImageView *imageView;
    
    //! padding in percent, default is .1, .1, .1, .1.
    CGPadding padding;
    
    //! is moving.
    BOOL isMoving;
    
    //! show close button. default is YES.
    BOOL showClose;
    NNTUIButton* buttonClose;
    
    @private
    CGPoint _pt_moving;
    UIPinchGestureRecognizer *_gesrec;
    CGRect _origin_rc;
}

@property (nonatomic, retain) NNTUIImageView *imageView;
@property (nonatomic, assign) CGPadding padding;
@property (nonatomic, assign) BOOL isMoving;
@property (nonatomic, assign) BOOL showClose;
@property (nonatomic, retain) NNTUIButton* buttonClose;

//! init.
- (id)init;
- (id)initWithImage:(UIImage*)image;
- (id)initWithURL:(NSURL*)url cache:(BOOL)cache;

//! center image view.
- (void)centerImage;

@end

NNT_END_HEADER_OBJC

# endif