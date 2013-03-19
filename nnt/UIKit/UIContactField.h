
# ifndef __NNT_UIKIT_CONTACTFIELD_31D54051C67441938468FD8ABB90978C_H_INCLUDED
# define __NNT_UIKIT_CONTACTFIELD_31D54051C67441938468FD8ABB90978C_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UIContactField);

@interface UIContactField : NNTUITextField {
    
    //! button for pick a contact from address book.
    id buttonPicker;
    
    //! list view for live-matching contacts.
    NNTUITableView* tableLiveMatching;
    
    //! popover picker. default is YES.
    BOOL pickerPopover;
    
    NNTDECL_PRIVATE_EX(UIContactField, d_ptr_contact);
}

@property (nonatomic, retain) id buttonPicker;
@property (nonatomic, readonly, retain) NNTUITableView* tableLiveMatching;
@property (nonatomic, assign) BOOL pickerPopover;

@end

NNT_END_HEADER_OBJC

# endif