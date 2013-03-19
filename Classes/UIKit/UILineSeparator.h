
# ifndef __WSI_UIKIT_LINESEPARATOR_A15BB916F7324A89A09E5033C2260CB5_H_INCLUDED
# define __WSI_UIKIT_LINESEPARATOR_A15BB916F7324A89A09E5033C2260CB5_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGMutableLineStyle);

@interface UILineSeparator : WSIUIView {
    
    //! line style.
    WCGMutableLineStyle* _lineStyle;
    
}

@property (nonatomic, retain) WCGMutableLineStyle* lineStyle;

- (id)initWithLineStyle:(WCGLineStyle*)ls;
- (id)initWithDashPattern:(NSArray*)pat;

@end

@interface UIHovLineSeparator : UILineSeparator

@end

@interface UIVecLineSeparator : UILineSeparator

@end

WSI_END_HEADER_OBJC

# endif