
# ifndef __NNT_UIKIT_PAGESWITCHVIEW_322805B066F84A248C6580C98BFB02B8_H_INCLUDED
# define __NNT_UIKIT_PAGESWITCHVIEW_322805B066F84A248C6580C98BFB02B8_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UISwitchController);

@interface UISwitchView : NNTUIView {
    UISwitchController *switcher;
}

@property (nonatomic, assign) UISwitchController *switcher;

@end

NNT_END_HEADER_OBJC

# endif