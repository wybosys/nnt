
# ifndef __WSI_UIKIT_ADDRESSBOOKPICKCONTROLLER_03C1B899209147D6AE0AEC09CEBF2F0B_H_INCLUDED
# define __WSI_UIKIT_ADDRESSBOOKPICKCONTROLLER_03C1B899209147D6AE0AEC09CEBF2F0B_H_INCLUDED

# import "UIViewController+WSI.h"
# import <AddressBookUI/AddressBookUI.h>

WSI_BEGIN_HEADER_OBJC

@interface UIAddressBookPickController : ABPeoplePickerNavigationController <ABPeoplePickerNavigationControllerDelegate> {
    WSIOBJECT_DECL;
    
    //! the controller will use to present this controller.
    UIViewController* presentOfController;
    
    //! popover. default is YES.
    BOOL popover;
    
    //! reference view. default is nil.
    UIView *referenceView, *referenceSuperView;
}

WSIOBJECT_PROP;

@property (nonatomic, assign) UIViewController* presentOfController;
@property (nonatomic, assign) BOOL popover;
@property (nonatomic, assign) UIView* referenceView, *referenceSuperView;

- (id)init;
- (id)initWithParentController;
- (id)initWithParentController:(UIViewController*)ctlr;

//! present.
- (void)present;

//! close.
- (void)close;

@end

WSI_EXTERN signal_t kSignalSelectChanged;

WSI_END_HEADER_OBJC

# endif