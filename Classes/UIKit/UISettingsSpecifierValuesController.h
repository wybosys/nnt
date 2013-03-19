
# ifndef __NNT_UIKIT_UISETTINGSSPECIFIERVALUESCONTROLLER_E25D429739A3475E8D1A3949E58D4914_H_INCLUDED
# define __NNT_UIKIT_UISETTINGSSPECIFIERVALUESCONTROLLER_E25D429739A3475E8D1A3949E58D4914_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UISettingsSpecifier);
NNTDECL_EXTERN_CLASS(UISettingsReader);
NNTDECL_EXTERN_PROTOCOL(UISettingsStore);
NNTDECL_EXTERN_CLASS(NNTUITableView);

@interface UISettingsSpecifierValuesController : NNTUIViewController {
    
    NNTUITableView				*_tableView;
    
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

NNT_END_HEADER_OBJC

# endif