
# ifndef __WSI_UIKIT_CONTACTFIELD_31D54051C67441938468FD8ABB90978C_H_INCLUDED
# define __WSI_UIKIT_CONTACTFIELD_31D54051C67441938468FD8ABB90978C_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UIContactField);

@interface UIContactField : WSIUITextField {
    
    //! button for pick a contact from address book.
    id buttonPicker;
    
    //! list view for live-matching contacts.
    WSIUITableView* tableLiveMatching;
    
    //! popover picker. default is YES.
    BOOL pickerPopover;
    
    WSIDECL_PRIVATE_EX(UIContactField, d_ptr_contact);
}

@property (nonatomic, retain) id buttonPicker;
@property (nonatomic, readonly, retain) WSIUITableView* tableLiveMatching;
@property (nonatomic, assign) BOOL pickerPopover;

@end

WSI_END_HEADER_OBJC

# endif