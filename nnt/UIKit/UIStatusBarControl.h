
# ifndef __WSI_UIKIT_STATUSBAR_68A2F2EE2B864B92994B5537BFD097C9_H_INCLUDED
# define __WSI_UIKIT_STATUSBAR_68A2F2EE2B864B92994B5537BFD097C9_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIStatusBarControl : WSIUIView {
    
    //! from right to left insert item. default is YES.
    BOOL rightToLeft;
    
}

@property (nonatomic, assign) BOOL rightToLeft;

//! init with width.
- (id)initWithWidth:(int)height;

//! get bar's height.
+ (int)barHeight;

@end

WSI_END_HEADER_OBJC

# endif