
# ifndef __NNT_UIKIT_UICOVERDRAWERVIEW_FF6C4D93E17B44F1A06E6813CD37B63C_H_INCLUDED
# define __NNT_UIKIT_UICOVERDRAWERVIEW_FF6C4D93E17B44F1A06E6813CD37B63C_H_INCLUDED

# import "UIView+NNT.h"
# import "UICoverDrawer.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UICoverDrawerView);
NNTDECL_EXTERN_CLASS(UICoverDrawer);

@interface UICoverDrawerView : NNTUIView {
    
    //! drawer.
    UICoverDrawer *drawer;
    
    //! scale.
    real scale;
    
    NNTDECL_PRIVATE(UICoverDrawerView);
}

@property (nonatomic, assign) UICoverDrawer *drawer;
@property (nonatomic) real scale;

@end

@interface UICoverDrawer (_extern_)

- (UICoverDrawerItem*)find_item_bylayer_onscreen:(CALayer*)layer;

@end

NNT_END_HEADER_OBJC

# endif