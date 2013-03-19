
# ifndef __WSI_UIKIT_UISETTINGSSPECIFIERVALUESCONTROLLER_E25D429739A3475E8D1A3949E58D4914_H_INCLUDED
# define __WSI_UIKIT_UISETTINGSSPECIFIERVALUESCONTROLLER_E25D429739A3475E8D1A3949E58D4914_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UISettingsSpecifier);
WSIDECL_EXTERN_CLASS(UISettingsReader);
WSIDECL_EXTERN_PROTOCOL(UISettingsStore);
WSIDECL_EXTERN_CLASS(WSIUITableView);

@interface UISettingsSpecifierValuesController : WSIUIViewController {
    
    WSIUITableView				*_tableView;
    
    UISettingsSpecifier			*_currentSpecifier;
    NSIndexPath                 *_checkedItem;
	UISettingsReader	        *_settingsReader;
    id<UISettingsStore>      	_settingsStore;
    
}

@property (nonatomic, retain) IBOutlet UITableView *tableView;
@property (nonatomic, retain) NSIndexPath *checkedItem;
@property (nonatomic, retain) UISettingsSpecifier *currentSpecifier;
@property (nonatomic, retain) UISettingsReader *settingsReader;
@property (nonatomic, retain) id<UISettingsStore> settingsStore;

@end

WSI_END_HEADER_OBJC

# endif