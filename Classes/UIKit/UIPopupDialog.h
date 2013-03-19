
# ifndef __NNT_UIKIT_POPUPDIALOG_101B1EBFC60C48A794C4BA52AA9B4E67_H_INCLUDED
# define __NNT_UIKIT_POPUPDIALOG_101B1EBFC60C48A794C4BA52AA9B4E67_H_INCLUDED

# import "UIView+NNT.h"
# import "CoreGraphic+NNT.h"
# import "UIButton+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UIPopupDialog);

@interface UIPopupDialog : NNTUIView {
    
    //! padding to edge.
    CGPadding padding;
    
    //! margin.
    CGMargin margin;
    
    //! yes & cancel button.
    NNTUIButton *btnYes, *btnNo, *btnCancel;
    
    //! content view.
    NNTUIView* content;
    
    //! show close btn. default is NO.
    BOOL showClose;
    
    //! close button.
    NNTUIButton* buttonClose;
    
    //! background view.
    NNTUIView* backgroundView;
    
    NNTDECL_PRIVATE_EX(UIPopupDialog, _d_ptr_popup);
}

@property (nonatomic, assign) CGPadding padding;
@property (nonatomic, assign) CGMargin margin;
@property (nonatomic, retain) NNTUIButton *btnYes, *btnNo, *btnCancel;
@property (nonatomic, retain) NNTUIView* content;
@property (nonatomic, assign) BOOL showClose;
@property (nonatomic, retain) NNTUIButton* buttonClose;
@property (nonatomic, readonly) NNTUIView* backgroundView;

//! open dialog;
- (void)execute;

//! close.
- (void)close;

@end

NNT_EXTERN signal_t kSignalIndexYes;
NNT_EXTERN signal_t kSignalIndexNo;
NNT_EXTERN signal_t kSignalDialogExecute;
NNT_EXTERN signal_t kSignalDialogClose;

NNT_END_HEADER_OBJC

# endif