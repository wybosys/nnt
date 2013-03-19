
# ifndef __WSI_UIKIT_UISETTINGSITEMS_DC562C74A22842DE8BBD3C08032A99C0_H_INCLUDED
# define __WSI_UIKIT_UISETTINGSITEMS_DC562C74A22842DE8BBD3C08032A99C0_H_INCLUDED

# import "UISwitch+WSI.h"
# import "UISlider+WSI.h"
# import "UITextField+WSI.h"
# import "UITableViewCell+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UISettingsSwitch : WSIUISwitch {
    NSString *_key;
}

@property (nonatomic, retain) NSString *key;

@end

@interface UISettingsSlider : WSIUISlider {
    NSString *_key;
}

@property (nonatomic, retain) NSString *key;

@end

@interface UISettingsTextField : WSIUITextField {
    NSString *_key;
}

@property (nonatomic, retain) NSString *key;

@end

@interface UIToggleTableCell : WSIUITableViewCell {
    UILabel *_label;
    UISettingsSwitch *_toggle;
}

@property (nonatomic, assign) IBOutlet UILabel *label;
@property (nonatomic, assign) IBOutlet UISettingsSwitch *toggle;

+ (id)cell;

@end

WSI_EXTERN signal_t kSignalValueChanged;

@interface UITitleValueTableCell : WSIUITableViewCell

@property (nonatomic, readonly) UILabel* title;
@property (nonatomic, readonly) UILabel* value;

+ (id)cell;

@end

@interface UITextFieldTableCell : WSIUITableViewCell {
    UILabel *_label;
    UISettingsTextField *_textField;
}

@property (nonatomic, assign) IBOutlet UILabel *label;
@property (nonatomic, assign) IBOutlet UISettingsTextField *textField;

+ (id)cell;

@end

@interface UISliderTableCell : WSIUITableViewCell {
    UISettingsSlider *_slider;
    UIImageView *_minImage;
    UIImageView *_maxImage;
}

@property (nonatomic, assign) IBOutlet UISettingsSlider *slider;
@property (nonatomic, assign) IBOutlet UIImageView *minImage;
@property (nonatomic, assign) IBOutlet UIImageView *maxImage;

@end


WSI_END_HEADER_OBJC

# endif