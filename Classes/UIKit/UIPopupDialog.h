
# ifndef __WSI_UIKIT_POPUPDIALOG_101B1EBFC60C48A794C4BA52AA9B4E67_H_INCLUDED
# define __WSI_UIKIT_POPUPDIALOG_101B1EBFC60C48A794C4BA52AA9B4E67_H_INCLUDED

# import "UIView+WSI.h"
# import "CoreGraphic+WSI.h"
# import "UIButton+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UIPopupDialog);

@interface UIPopupDialog : WSIUIView {
    
    //! padding to edge.
    CGPadding padding;
    
    //! margin.
    CGMargin margin;
    
    //! yes & cancel button.
    WSIUIButton *btnYes, *btnNo, *btnCancel;
    
    //! content view.
    WSIUIView* content;
    
    //! show close btn. default is NO.
    BOOL showClose;
    
    //! close button.
    WSIUIButton* buttonClose;
    
    //! background view.
    WSIUIView* backgroundView;
    
    WSIDECL_PRIVATE_EX(UIPopupDialog, _d_ptr_popup);
}

@property (nonatomic, assign) CGPadding padding;
@property (nonatomic, assign) CGMargin margin;
@property (nonatomic, retain) WSIUIButton *btnYes, *btnNo, *btnCancel;
@property (nonatomic, retain) WSIUIView* content;
@property (nonatomic, assign) BOOL showClose;
@property (nonatomic, retain) WSIUIButton* buttonClose;
@property (nonatomic, readonly) WSIUIView* backgroundView;

//! open dialog;
- (void)execute;

//! close.
- (void)close;

@end

WSI_EXTERN signal_t kSignalIndexYes;
WSI_EXTERN signal_t kSignalIndexNo;
WSI_EXTERN signal_t kSignalDialogExecute;
WSI_EXTERN signal_t kSignalDialogClose;

WSI_END_HEADER_OBJC

# endif