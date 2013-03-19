
# ifndef __NNT_UIKIT_LINESEPARATOR_A15BB916F7324A89A09E5033C2260CB5_H_INCLUDED
# define __NNT_UIKIT_LINESEPARATOR_A15BB916F7324A89A09E5033C2260CB5_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgMutableLineStyle);

@interface UILineSeparator : NNTUIView {
    
    //! line style.
    NgMutableLineStyle* _lineStyle;
    
}

@property (nonatomic, retain) NgMutableLineStyle* lineStyle;

- (id)initWithLineStyle:(NgLineStyle*)ls;
- (id)initWithDashPattern:(NSArray*)pat;

@end

@interface UIHovLineSeparator : UILineSeparator

@end

@interface UIVecLineSeparator : UILineSeparator

@end

NNT_END_HEADER_OBJC

# endif