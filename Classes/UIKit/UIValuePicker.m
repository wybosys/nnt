
# import "Core.h"
# import "UIValuePicker.h"
# import "UIValuePickerView.h"
# import "UIButton+NNT.h"
# import "UIViewController+NNT.h"

NNT_BEGIN_OBJC

@implementation UIValuePicker

@synthesize popoverController;
@synthesize pickerController, pickerView;
@synthesize datas;
@synthesize minimumComps;
@synthesize enableNumberWidthDec, enableNumberWidthInc;

- (id)init {
    self = [super init];
    
    pickerController = [[NNTUIViewController alloc] init];
    
    pickerView = [[UIValuePickerView alloc] initWithZero];
    pickerController.view = pickerView;    
    pickerView.backgroundColor = [UIColor blackColor];
    pickerView.frame = CGRectMake(0, 0, 200, 200);        
        
    pickerView.picker.delegate = self;
    pickerView.picker.dataSource = self;        
    pickerView.picker.showsSelectionIndicator = YES;
    
    [pickerView.btnInc connect:kSignalViewClicked sel:@selector(act_number_inc:) obj:self];
    [pickerView.btnDec connect:kSignalViewClicked sel:@selector(act_number_dec:) obj:self];
    
    enableNumberWidthDec = YES;
    enableNumberWidthInc = YES;
    
    _numberMode = NO;
    _hasOpp = NO;
    
    datas = [NSArray new];
    
    popoverController = [[UIPopoverController alloc] initWithContentViewController:pickerController];
    popoverController.popoverContentSize = pickerView.bounds.size;
 
    return self;
}

- (void)dealloc {
    zero_release(popoverController);
    zero_release(pickerController);
    zero_release(pickerView);
    
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalSelectChanged);
NNTEVENT_END

- (void)act_number_inc:(id)obj {
    if (_numberMode) {
        NSMutableArray *tmp_data = [[NSMutableArray alloc] initWithArray:self.datas];
        NSArray *arr_number = [NSArray arrayWithObjects:@"0", @"1", @"2", @"3", @"4", @"5", @"6", @"7", @"8", @"9", nil];
        [tmp_data addObject:arr_number];
        self.datas = tmp_data;
        [tmp_data release];
    }
    
    [pickerView.picker reloadAllComponents];
}

- (void)act_number_dec:(id)obj {
    if (minimumComps >= [self.datas count])
        return;
    
    if (_numberMode) {
        NSMutableArray *tmp_data = [[NSMutableArray alloc] initWithArray:self.datas];
        if ([tmp_data count])
            [tmp_data removeObjectAtIndex:[tmp_data count] - 1];
        self.datas = tmp_data;
        [tmp_data release];
    }
    
    [pickerView.picker reloadAllComponents];
}

- (void)setNumber:(NSNumber *)number {
    int value = [number intValue];  
    
    NSArray *arr_number = [NSArray arrayWithObjects:@"0", @"1", @"2", @"3", @"4", @"5", @"6", @"7", @"8", @"9", nil];
    NSArray *arr_opt = [NSArray arrayWithObjects:@"+", @"-", @"", @"", nil];
    
    NSMutableArray *tmp_datas = [NSMutableArray new];
    if (value >= 0) {
        NSString *str = [[NSNumber numberWithUnsignedInt:value] stringValue];
        for (int i = 0; i < (int)minimumComps - (int)[str length]; ++i) {
            [tmp_datas addObject:arr_number];
        }
        for (uint i = 0; i < [str length]; ++i) {
            [tmp_datas addObject:arr_number];
        }        
    } else {
        NSString *str = [[NSNumber numberWithInt:value] stringValue];
        [tmp_datas addObject:arr_opt];
        for (int i = 1; i < (int)minimumComps - (int)[str length]; ++i) {
            [tmp_datas addObject:arr_number];
        }
        for (uint i = 1; i < [str length]; ++i) {
            [tmp_datas addObject:arr_number];
        }        
    }
    
    self.datas = tmp_datas;
    [tmp_datas release];
    
    [pickerView.picker reloadAllComponents];

    if (value >= 0) {
        NSString *str = [[NSNumber numberWithUnsignedInt:value] stringValue];
        uint offset = 0;
        if ([str length] < minimumComps)
            offset = minimumComps - [str length];
        for (uint i = 0; i < [str length]; ++i) {
            [pickerView.picker selectRow:crd([str characterAtIndex:i]) inComponent:i + offset animated:NO];
        }
        for (uint i = 0; i < offset; ++i) {
            [pickerView.picker selectRow:0 inComponent:i animated:NO];
        }
    } else {
        NSString *str = [[NSNumber numberWithInt:value] stringValue];
        [pickerView.picker selectRow:1 inComponent:0 animated:NO];
        uint offset = 0;
        if ([str length] - 1 < minimumComps)
            offset = minimumComps - [str length] + 1;
        for (uint i = 1; i < [str length]; ++i) {
            [pickerView.picker selectRow:crd([str characterAtIndex:i]) inComponent:i + offset animated:NO];
        }
        for (uint i = 1; i < offset; ++i) {
            [pickerView.picker selectRow:0 inComponent:i animated:NO];
        }
    }

    _hasOpp = value < 0;    
    _numberMode = YES;
}

- (NSNumber*)getNumber {
    NSNumber *ret = nil;
    if (_numberMode) {
        uint value = 0;
        for (uint i = _hasOpp; i < [pickerView.picker numberOfComponents]; ++i) {
            NSUInteger seled = [pickerView.picker selectedRowInComponent:i];
            value = (value * 10) + seled;
        }
        value *= _hasOpp ? -1 : 1;
        ret = [NSNumber numberWithInt:value];
    }
    return ret;
}

- (void)setEnableNumberWidthInc:(BOOL)__enableNumberWidthInc {
    enableNumberWidthInc = __enableNumberWidthInc;
    pickerView.btnInc.hidden = !enableNumberWidthInc;
}

- (void)setEnableNumberWidthDec:(BOOL)__enableNumberWidthDec {
    enableNumberWidthDec = __enableNumberWidthDec;
    pickerView.btnDec.hidden = !enableNumberWidthDec;
}

# pragma mark -

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    NSInteger ret = 1;
    if ([datas count]) {
        if ([[datas objectAtIndex:0] isKindOfClass:[NSArray class]])
            ret = [datas count];
    }
    return MAX(ret, minimumComps);
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    NSInteger ret = [datas count];
    if ([datas count]) {
        if ([[datas objectAtIndex:0] isKindOfClass:[NSArray class]]) {
            if (component < [datas count])
                ret = [[datas objectAtIndex:component] count];
            else
                ret = 0;
        }
    }
    return ret;
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    NSString *ret = @"";
    if ([datas count]) {
        if ([[datas objectAtIndex:0] isKindOfClass:[NSArray class]]) {
            if (component < [datas count])
                ret = [[datas objectAtIndex:component] objectAtIndex:row];
        } else {
            ret = [datas objectAtIndex:row];
        }
    }
    return ret;
}

- (void)pickerView:(UIPickerView *)__pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {

    id <UIValuePickerDelegate> theDelegate = (id <UIValuePickerDelegate>)popoverController.delegate;

    if ([theDelegate respondsToSelector:@selector(valuePicker:didSelectRow:inComponent:)])
        [theDelegate valuePicker:self didSelectRow:row inComponent:component];

    if ([theDelegate respondsToSelector:@selector(pickerView:didSelectRow:inComponent:)])
        [theDelegate pickerView:__pickerView didSelectRow:row inComponent:component];
    
    [self emit:kSignalSelectChanged];
    
}

- (void)presentPopoverFromRect:(CGRect)rect inView:(UIView *)view permittedArrowDirections:(UIPopoverArrowDirection)arrowDirections animated:(BOOL)animated {
    [self retain];
    [popoverController presentPopoverFromRect:rect inView:view permittedArrowDirections:arrowDirections animated:animated];    
}

- (void)dismissPopoverAnimated:(BOOL)animated {
    [popoverController dismissPopoverAnimated:animated];
    [self release];
}

@end

NNT_END_OBJC