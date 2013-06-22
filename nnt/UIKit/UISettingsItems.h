
# ifndef __NNT_UIKIT_UISETTINGSITEMS_DC562C74A22842DE8BBD3C08032A99C0_H_INCLUDED
# define __NNT_UIKIT_UISETTINGSITEMS_DC562C74A22842DE8BBD3C08032A99C0_H_INCLUDED

# import "UISwitch+NNT.h"
# import "UISlider+NNT.h"
# import "UITextField+NNT.h"
# import "UITableViewCell+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UISettingsSwitch : NNTUISwitch {
    NSString *_key;
}

@property (nonatomic, retain) NSString *key;

@end

@interface UISettingsSlider : NNTUISlider {
    NSString *_key;
}

@property (nonatomic, retain) NSString *key;

@end

@interface UISettingsTextField : NNTUITextField {
    NSString *_key;
}

@property (nonatomic, retain) NSString *key;

@end

@interface UIToggleTableCell : NNTUITableViewCell {
    UILabel *_label;
    UISettingsSwitch *_toggle;
}

@property (nonatomic, assign) IBOutlet UILabel *label;
@property (nonatomic, assign) IBOutlet UISettingsSwitch *toggle;

+ (id)cell;

@end

NNT_EXTERN signal_t kSignalValueChanged;

@interface UITitleValueTableCell : NNTUITableViewCell

@property (nonatomic, readonly) UILabel* title;
@property (nonatomic, readonly) UILabel* value;

+ (id)cell;

@end

@interface UITextFieldTableCell : NNTUITableViewCell {
    UILabel *_label;
    UISettingsTextField *_textField;
}

@property (nonatomic, assign) IBOutlet UILabel *label;
@property (nonatomic, assign) IBOutlet UISettingsTextField *textField;

+ (id)cell;

@end

@interface UISliderTableCell : NNTUITableViewCell {
    UISettingsSlider *_slider;
    UIImageView *_minImage;
    UIImageView *_maxImage;
}

@property (nonatomic, assign) IBOutlet UISettingsSlider *slider;
@property (nonatomic, assign) IBOutlet UIImageView *minImage;
@property (nonatomic, assign) IBOutlet UIImageView *maxImage;

@end


NNT_END_HEADER_OBJC

# endif