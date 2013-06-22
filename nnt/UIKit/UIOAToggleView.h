
# ifndef __NNT_UIKIT_OATOGGLEVIEW_A03886BDA3C3481FA94D03B81B8C7B03_H_INCLUDED
# define __NNT_UIKIT_OATOGGLEVIEW_A03886BDA3C3481FA94D03B81B8C7B03_H_INCLUDED

# import "UIFlowView.h"
# import "OAToggle.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UIOAToggleView);

@interface UIOAToggleView : UIFlowView {

    id<OAToggleDelegate> delegate;
    NNTDECL_PRIVATE(UIOAToggleView);
}

@property (nonatomic, assign) id<OAToggleDelegate> delegate;

- (void)refresh;

@end

NNT_END_HEADER_OBJC

# endif