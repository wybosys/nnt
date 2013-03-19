
# ifndef __WSI_UIKIT_UIIMAGEDESKTOP_A3BC9B1BD8CF4481BA0D10FD853A0525_H_INCLUDED
# define __WSI_UIKIT_UIIMAGEDESKTOP_A3BC9B1BD8CF4481BA0D10FD853A0525_H_INCLUDED

# import "UIDesktop.h"
# import "CoreGraphic+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSIUIButton);

WSIDECL_EXTERN_CLASS(WSIUIImageView);

@interface UIImageDesktop : WSIUIDesktop {

    //! image view.
    WSIUIImageView *imageView;
    
    //! padding in percent, default is .1, .1, .1, .1.
    CGPadding padding;
    
    //! is moving.
    BOOL isMoving;
    
    //! show close button. default is YES.
    BOOL showClose;
    WSIUIButton* buttonClose;
    
    @private
    CGPoint _pt_moving;
    UIPinchGestureRecognizer *_gesrec;
    CGRect _origin_rc;
}

@property (nonatomic, retain) WSIUIImageView *imageView;
@property (nonatomic, assign) CGPadding padding;
@property (nonatomic, assign) BOOL isMoving;
@property (nonatomic, assign) BOOL showClose;
@property (nonatomic, retain) WSIUIButton* buttonClose;

//! init.
- (id)init;
- (id)initWithImage:(UIImage*)image;
- (id)initWithURL:(NSURL*)url cache:(BOOL)cache;

//! center image view.
- (void)centerImage;

@end

WSI_END_HEADER_OBJC

# endif