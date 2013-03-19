
# ifndef __WSI_UIKIT_UISETTINGSSPECIFIER_42CA6FEBD5654D4BB6A3976CFE10AC4C_H_INCLUDED
# define __WSI_UIKIT_UISETTINGSSPECIFIER_42CA6FEBD5654D4BB6A3976CFE10AC4C_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UISettingsReader);

@interface UISettingsSpecifier : NSObject {
 
    NSDictionary    *_specifierDict;
    NSDictionary    *_multipleValuesDict;
	UISettingsReader *_settingsReader;
    
}

@property (nonatomic, retain) NSDictionary  *specifierDict;
@property (nonatomic, assign) UISettingsReader *settingsReader;

- (id)initWithSpecifier:(NSDictionary*)specifier;
- (NSString*)localizedObjectForKey:(NSString*)key;
- (NSString*)title;
- (NSString*)key;
- (NSString*)type;
- (NSString*)titleForCurrentValue:(id)currentValue;
- (NSInteger)multipleValuesCount;
- (NSArray*)multipleValues;
- (NSArray*)multipleTitles;
- (NSString*)file;
- (id)defaultValue;
- (id)defaultStringValue;
- (BOOL)defaultBoolValue;
- (id)trueValue;
- (id)falseValue;
- (float)minimumValue;
- (float)maximumValue;
- (NSString*)minimumValueImage;
- (NSString*)maximumValueImage;
- (BOOL)isSecure;
- (UIKeyboardType)keyboardType;
- (UITextAutocapitalizationType)autocapitalizationType;
- (UITextAutocorrectionType)autoCorrectionType;
- (NSString*)footerText;
- (Class)viewControllerClass;
- (SEL)viewControllerSelector;
- (Class)buttonClass;
- (SEL)buttonAction;

@end

WSI_END_HEADER_OBJC

# endif