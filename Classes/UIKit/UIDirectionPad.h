
# ifndef __NNT_UIKIT_DIRECTIONPAD_AC213FA1C96840C9ABA0EE85ACD97046_H_INCLUDED
# define __NNT_UIKIT_DIRECTIONPAD_AC213FA1C96840C9ABA0EE85ACD97046_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UIDirectionPad : NNTUIView {
    
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

NNT_EXTERN signal_t kSignalPadMoved;

NNT_END_HEADER_OBJC

# endif