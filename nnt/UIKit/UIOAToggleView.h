
# ifndef __WSI_UIKIT_OATOGGLEVIEW_A03886BDA3C3481FA94D03B81B8C7B03_H_INCLUDED
# define __WSI_UIKIT_OATOGGLEVIEW_A03886BDA3C3481FA94D03B81B8C7B03_H_INCLUDED

# import "UIFlowView.h"
# import "OAToggle.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UIOAToggleView);

@interface UIOAToggleView : UIFlowView {

    id<OAToggleDelegate> delegate;
    WSIDECL_PRIVATE(UIOAToggleView);
}

@property (nonatomic, assign) id<OAToggleDelegate> delegate;

- (void)refresh;

@end

WSI_END_HEADER_OBJC

# endif