
# ifndef __WSI_UIKIT_UIFOGVIEW_13A8E82ED5C24481B076E3949A7F561E_H_INCLUDED
# define __WSI_UIKIT_UIFOGVIEW_13A8E82ED5C24481B076E3949A7F561E_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGGradient);

@interface UIFogView : WSIUIView {
    
    WCGGradient *fogColor;
    real fogDepth;
    
}

@property (nonatomic, retain) WCGGradient *fogColor;
@property (nonatomic) real fogDepth;

@end

WSI_END_HEADER_OBJC

# endif