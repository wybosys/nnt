
# ifndef __WSI_UIKIT_DIRECTIONPAD_AC213FA1C96840C9ABA0EE85ACD97046_H_INCLUDED
# define __WSI_UIKIT_DIRECTIONPAD_AC213FA1C96840C9ABA0EE85ACD97046_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIDirectionPad : WSIUIView {
    
    //! position.
    CGPoint position;
    
    //! location.
    CGPoint location;
    
    //! color.
    UIColor *color;
}

@property (nonatomic, assign) CGPoint position, location;
@property (nonatomic, retain) UIColor *color;

+ (id)pad;

//! get pad size.
+ (CGSize)sizeForPad;

@end

WSI_EXTERN signal_t kSignalPadMoved;

WSI_END_HEADER_OBJC

# endif