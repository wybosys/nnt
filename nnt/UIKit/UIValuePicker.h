
# ifndef __WSI_UIKIT_UIVALUEPICKER_1FCD93BC28B64DB8B8D05406FDE09566_H_INCLUDED
# define __WSI_UIKIT_UIVALUEPICKER_1FCD93BC28B64DB8B8D05406FDE09566_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UIValuePickerView);
WSIDECL_EXTERN_CLASS(UIValuePicker);

@protocol UIValuePickerDelegate <UIPopoverControllerDelegate>
@optional

- (void)valuePicker:(UIValuePicker *)__pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component;
- (void)pickerView:(UIPickerView *)__pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component;

@end

@interface UIValuePicker : WSIObject <UIPickerViewDelegate, UIPickerViewDataSource> {
    
    //! popover.
    UIPopoverController* popoverController;
    
    //! picker.
    UIViewController *pickerController;
    UIValuePickerView *pickerView;
    
    //! datas, if is NSArray[NSArray,...] will be a multi-comps picker. other is single comp picker.
    NSArray *datas;
    
    //! minimum comps. default is 0.
    NSUInteger minimumComps;
    
    //! allow inc\dec number's width. default is YES.
    BOOL enableNumberWidthInc;
    BOOL enableNumberWidthDec;
    
    @private
    BOOL _numberMode;
    BOOL _hasOpp;
}

@property (nonatomic, readonly) UIPopoverController* popoverController;
@property (nonatomic, readonly) UIViewController *pickerController;
@property (nonatomic, readonly) UIValuePickerView *pickerView;
@property (nonatomic, retain) NSArray *datas;
@property (nonatomic, assign) NSUInteger minimumComps;
@property (nonatomic, assign) BOOL enableNumberWidthInc, enableNumberWidthDec;

- (void)setNumber:(NSNumber*)number;
- (NSNumber*)getNumber;

// others.
- (void)presentPopoverFromRect:(CGRect)rect inView:(UIView *)view permittedArrowDirections:(UIPopoverArrowDirection)arrowDirections animated:(BOOL)animated;
- (void)dismissPopoverAnimated:(BOOL)animated;

@end

WSI_END_HEADER_OBJC

# endif