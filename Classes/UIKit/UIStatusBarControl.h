
# ifndef __NNT_UIKIT_STATUSBAR_68A2F2EE2B864B92994B5537BFD097C9_H_INCLUDED
# define __NNT_UIKIT_STATUSBAR_68A2F2EE2B864B92994B5537BFD097C9_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UIStatusBarControl : NNTUIView {
    
    //! from right to left insert item. default is YES.
    BOOL rightToLeft;
    
}

@property (nonatomic, assign) BOOL rightToLeft;

//! init with width.
- (id)initWithWidth:(int)height;

//! get bar's height.
+ (int)barHeight;

@end

NNT_END_HEADER_OBJC

# endif