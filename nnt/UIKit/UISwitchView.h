
# ifndef __WSI_UIKIT_PAGESWITCHVIEW_322805B066F84A248C6580C98BFB02B8_H_INCLUDED
# define __WSI_UIKIT_PAGESWITCHVIEW_322805B066F84A248C6580C98BFB02B8_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UISwitchController);

@interface UISwitchView : WSIUIView {
    UISwitchController *switcher;
}

@property (nonatomic, assign) UISwitchController *switcher;

@end

WSI_END_HEADER_OBJC

# endif