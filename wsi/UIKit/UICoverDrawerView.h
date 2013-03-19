
# ifndef __WSI_UIKIT_UICOVERDRAWERVIEW_FF6C4D93E17B44F1A06E6813CD37B63C_H_INCLUDED
# define __WSI_UIKIT_UICOVERDRAWERVIEW_FF6C4D93E17B44F1A06E6813CD37B63C_H_INCLUDED

# import "UIView+WSI.h"
# import "UICoverDrawer.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UICoverDrawerView);
WSIDECL_EXTERN_CLASS(UICoverDrawer);

@interface UICoverDrawerView : WSIUIView {
    
    //! drawer.
    UICoverDrawer *drawer;
    
    //! scale.
    real scale;
    
    WSIDECL_PRIVATE(UICoverDrawerView);
}

@property (nonatomic, assign) UICoverDrawer *drawer;
@property (nonatomic) real scale;

@end

@interface UICoverDrawer (_extern_)

- (UICoverDrawerItem*)find_item_bylayer_onscreen:(CALayer*)layer;

@end

WSI_END_HEADER_OBJC

# endif