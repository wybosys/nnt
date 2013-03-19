
# import "Core.h"
# import "UITextField+NNT.h"
# import "App.h"
# import "UIScreen+NNT.h"
# import "NNTBdb.h"

NNT_BEGIN_OBJC

signal_t kSignalValueChanged = @"::nnt::value::changed";
signal_t kSignalValidChanged = @"::nnt::valid::changed";
signal_t kSignalEditingClear = @"::nnt::ui::editing::clear";
signal_t kSignalEditingReturn = @"::nnt::ui::editing::return";

@implementation UITextField (NNT)

- (void)applyTextStyle:(NgTextStyle*)ts {
    UITextAlignment align;
    switch (ts.alignment)
    {
        case NgAlignmentLeft: align = UITextAlignmentLeft; break;
        case NgAlignmentRight: align = UITextAlignmentRight; break;
        default: align = UITextAlignmentCenter; break;
    }
    self.textAlignment = align;
    self.textColor = [UIColor colorWithCGColor:ts.color.cgColor];
    self.font = [ts uiFont];
}

@end

NNTIMPL_CATEGORY(UITextField, NNT);

NNTDECL_PRIVATE_BEGIN(NNTUITextField, NSObject)
<UITextFieldDelegate>

@property (nonatomic, retain) UIColor *old_background_color, *old_font_color;
@property (nonatomic, assign) BOOL b_str_valid;

- (void)updateByString:(NSString*)str;

NNTDECL_PRIVATE_IMPL(NNTUITextField)

@synthesize old_background_color, old_font_color;
@synthesize b_str_valid;

- (id)init {
    self = [super init];
    
    d_owner.delegate = self;;    
    d_owner.autocapitalizationType = UITextAutocapitalizationTypeNone;
    
    return self;
}

- (void)dealloc {
    zero_release(old_background_color);
    zero_release(old_font_color);
    
    // break.
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [super dealloc];
}

# pragma mark action.

- (void)act_keyboard_opening:(NSNotification*)aNotification {    
    NSDictionary* info = [aNotification userInfo];
    
    CGSize sz_keyboard = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;    
    CGRect frm_window = d_owner.root.bounds;
    CGRect frm_txt = [d_owner.root convertRect:d_owner.frame fromView:d_owner.superview];
    sz_keyboard = [UIScreen convertCurrentSize:sz_keyboard];
    
    int offset = frm_window.size.height - sz_keyboard.height - frm_txt.origin.y - frm_txt.size.height;
    if (offset >= 0)
        return;
        
    // begin animated.
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:[[info objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue]];
    
    [[NNTApplication shared].window offsetX:0 Y:offset];
    
    [UIView commitAnimations];
    
    // for hiding.
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(act_keyboard_hiding:)
                                                 name:UIKeyboardWillHideNotification
                                               object:nil];
}

- (void)act_keyboard_hiding:(NSNotification*)aNotification {
    NSDictionary* info = [aNotification userInfo];
    CGRect crFrm = [NNTApplication shared].window.bounds;
    crFrm.origin = CGPointZero;
    
    // begin animated.
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:[[info objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue]];
    
    [NNTApplication shared].window.frame = crFrm;
    
    [UIView commitAnimations];
    
    // break noti.
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIKeyboardWillHideNotification
                                                  object:nil];
}

- (void)updateByString:(NSString*)curstr {
    
    if (d_owner.inputRestrict) {
        b_str_valid = [curstr matchedByRegex:d_owner.inputRestrict];
    }
    
    if (d_owner.validRestrict) {
        b_str_valid = [curstr matchedByRegex:d_owner.validRestrict];
        if (b_str_valid == NO) {
            if (old_background_color == nil) {
                UIColor *bk = d_owner.backgroundColor;
                self.old_background_color = bk ? bk : (UIColor*)[NSNull null];
            }
            if (old_font_color == nil) {
                self.old_font_color = d_owner.textColor;
            }
            d_owner.backgroundColor = d_owner.invalidBackgroundColor;
            d_owner.textColor = d_owner.invalidFontColor;
        } else {
            if (old_background_color) {
                if ([old_background_color isKindOfClass:[NSNull class]]) {
                    d_owner.backgroundColor = [UIColor clearColor];
                } else {
                    d_owner.backgroundColor = old_background_color;
                }
                self.old_background_color = nil;
            }
            if (old_font_color) {
                d_owner.textColor = old_font_color;
                self.old_font_color = nil;
            }
        }
    }
    
}

# pragma mark delegate

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField {
    return YES;
}

- (BOOL)textFieldShouldClear:(UITextField *)textField {    
    [d_owner emit:kSignalEditingClear];
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)textField {
    return YES;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    [d_owner emit:kSignalEditingReturn];
    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    BOOL suc = YES;
    
    NSString *curstr = textField.text;
    curstr = [curstr stringByReplacingCharactersInRange:range withString:string];
    
    BOOL old_valid = b_str_valid;
    
    if (d_owner.inputRestrict) {
        suc = [curstr matchedByRegex:d_owner.inputRestrict];
        b_str_valid = suc;
    }
    
    if (d_owner.validRestrict) {
        b_str_valid = [curstr matchedByRegex:d_owner.validRestrict];
        if (b_str_valid == NO) {
            if (old_background_color == nil) {
                UIColor *bk = textField.backgroundColor;
                self.old_background_color = bk ? bk : (UIColor*)[NSNull null];
            }
            if (old_font_color == nil) {
                self.old_font_color = textField.textColor;
            }
            textField.backgroundColor = d_owner.invalidBackgroundColor;
            textField.textColor = d_owner.invalidFontColor;
        } else {
            if (old_background_color) {
                if ([old_background_color isKindOfClass:[NSNull class]]) {
                    textField.backgroundColor = [UIColor clearColor];
                } else {
                    textField.backgroundColor = old_background_color;
                }
                self.old_background_color = nil;
            }
            if (old_font_color) {
                textField.textColor = old_font_color;
                self.old_font_color = nil;
            }
        }
    }
    
    if (old_valid != b_str_valid) {
        [d_owner emit:kSignalValidChanged result:curstr];
    }
    
    if (suc) {
        [d_owner emit:kSignalValueChanged result:curstr];
    }

    return suc;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField {
    [d_owner emit:kSignalBeginEditing];
}

- (void)textFieldDidEndEditing:(UITextField *)textField {
    [d_owner emit:kSignalEndEditing];
}

NNTDECL_PRIVATE_END

@interface NNTUITextField ()
@end

@implementation NNTUITextField

NNTOBJECT_IMPL_NOSIGNALS;

@synthesize inputRestrict = _inputRestrict, validRestrict = _validRestrict;
@synthesize invalidFontColor = _invalidFontColor, invalidBackgroundColor = _invalidBackgroundColor;
@dynamic isValid;
@synthesize backgroundFill = _backgroundFill;
@synthesize padding = _padding;

- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    NNTDECL_PRIVATE_INIT(NNTUITextField);
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    NNTDECL_PRIVATE_INIT(NNTUITextField);
    return self;
}

- (void)dealloc {
    zero_release(_inputRestrict);
    zero_release(_validRestrict);
    zero_release(_invalidFontColor);
    zero_release(_invalidBackgroundColor);
    
    NNTOBJECT_DEALLOC;
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)setInputRestrict:(NSString *)str {
    safe_release(_inputRestrict);
    _inputRestrict = [str copy];
}

- (void)setValidRestrict:(NSString *)str {
    safe_release(_validRestrict);
    _validRestrict = [str copy];
    
    if (_invalidBackgroundColor == nil) {
        self.invalidBackgroundColor = [UIColor redColor];
    }
    
    if (_invalidFontColor == nil) {
        self.invalidFontColor = [UIColor whiteColor];
    }
}

- (BOOL)resignFirstResponder {
    BOOL suc = [super resignFirstResponder];
    
    if (suc) {
        // remove opening.
        [[NSNotificationCenter defaultCenter] removeObserver:d_ptr
                                                        name:UIKeyboardWillShowNotification
                                                      object:nil];
        
        // remove hiding while hiding.        
    }
    
    return suc;
}

- (BOOL)canBecomeFirstResponder {
    BOOL ret = [super canBecomeFirstResponder];
    
    if (ret) {
        [[NSNotificationCenter defaultCenter] addObserver:d_ptr
                                                 selector:@selector(act_keyboard_opening:)
                                                     name:UIKeyboardWillShowNotification
                                                   object:nil];
    }
    
    return ret;
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalValueChanged);
    NNTEVENT_SIGNAL(kSignalBeginEditing);
    NNTEVENT_SIGNAL(kSignalEndEditing);
    NNTEVENT_SIGNAL(kSignalValidChanged);
    NNTEVENT_SIGNAL(kSignalEditingReturn);
    NNTEVENT_SIGNAL(kSignalEditingClear);
}

- (void)setText:(NSString *)text {
    if ([self changeText:text])
        [self emit:kSignalValueChanged result:text];
}

- (BOOL)changeText:(NSString*)text {
    NSString *old_text = self.text;
    if ([old_text isEqualToString:text])
        return NO;
    
    // set text.
    [super setText:text];
    
    // check text.
    [d_ptr updateByString:text];
    
    return YES;
}

- (BOOL)isValid {
    return d_ptr.b_str_valid;
}

- (void)drawRect:(CGRect)rect {
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    // draw fill.
    [_backgroundFill fillRect:rect inContext:ctx];
    
    // super draw.
    [super drawRect:rect];
}

# pragma mark override

- (CGRect)textRectForBounds:(CGRect)bounds {
    real th_h = self.font.capHeight - self.font.descender;
    real ah_h = bounds.size.height;
    real off = (ah_h - th_h) * .5f;
    bounds.origin.y += off;

    bounds.origin.x += _padding.left;
    bounds.origin.y += _padding.top;
    bounds.size.width -= _padding.left + _padding.right;
    bounds.size.height -= _padding.top + _padding.bottom;
    
    return bounds;
}

- (CGRect)editingRectForBounds:(CGRect)bounds {
    real th_h = self.font.capHeight - self.font.descender;
    real ah_h = bounds.size.height;
    real off = (ah_h - th_h) * .5f;
    bounds.origin.y += off;
    
    bounds.origin.x += _padding.left;
    bounds.origin.y += _padding.top;
    bounds.size.width -= _padding.left + _padding.right;
    bounds.size.height -= _padding.top + _padding.bottom;

    return bounds;
}

@end

@implementation UISuggestTextField

@synthesize dataSource = _dataSource;
@synthesize sizeSuggestList = _sizeSuggestList;
@synthesize datas = _datas;

- (id)initWithFrame:(CGRect)aFrame {
    self = [super initWithFrame:aFrame];
    
    _dataSource = self;
    _sizeSuggestList = CGSizeZero;

    [self connect:kSignalBeginEditing sel:@selector(act_editing_begin)];
    [self connect:kSignalEndEditing sel:@selector(act_editing_end)];
    
    return self;
}

- (void)dealloc {
    zero_release(_datas);
    [super dealloc];
}

- (NSUInteger)providerNumber:(id)obj {
    return _datas.count;
}

- (id)providerItem:(id)obj index:(NSUInteger)index {
    return [_datas objectAtIndex:index];
}

- (void)doOpenSuggest {
    if (_dataSource == nil)
        return;
    
    NSUInteger const count = [_dataSource providerNumber:self];
    if (count == 0)
        return;
    
    CGRect const rc_self = self.frame;
    
    // calc table size.
    CGRect rc = CGRectMakeSz(_sizeSuggestList);
    if (rc.size.width == 0) {
        rc.size.width = rc_self.size.width;
    }
    
    if (rc.size.height == 0) {
        rc.size.height = 60;
    }
    
    rc.origin = CGRectLeftBottom(&rc_self);
    
    // instance table.
    _items = [[NNTUITableViewController alloc] init];
    
    _items.view.frame = rc;
    _items.view.backgroundColor = [UIColor whiteColor];
    _items.rowHeight = 30;
    
    // connect table's signal.
    [_items connect:kSignalSelectChanged sel:@selector(act_suggest_selected:) obj:self];
    
    // load items.
    NSMutableArray* data = [[NSMutableArray alloc] initWithCapacity:count];
    for (uint i = 0; i < count; ++i) {
        id item = [_dataSource providerItem:self index:i];
        [data addObject:item];
    }
    _items.datas = data;
    zero_release(data);
    
    // add table.
    [self.superview addSubview:_items.view];   
}

- (void)doCloseSuggest {
    if (_items == nil)
        return;
    
    // remove table.
    [_items.view removeFromSuperview];
    zero_release(_items);
}

# pragma mark actions

- (void)act_editing_begin {    
    [self doOpenSuggest];
}

- (void)act_editing_end {
    [self doCloseSuggest];
}

- (void)act_suggest_selected:(NNTEventObj*)evt {
    NNTUITableViewCell* cell = (NNTUITableViewCell*)evt.result;
    self.text = cell.textLabel.text;
    
    [self doCloseSuggest];
}

@end

@implementation UIHistoryTextField

@synthesize identity = _identity;
@synthesize serialDelegate = _serialDelegate;
@synthesize limitCount = _limitCount;

- (id)initWithFrame:(CGRect)aFrame {
    self = [super initWithFrame:aFrame];
    
    self.serialDelegate = self;
    self.limitCount = NSNotFound;
    
    return self;
}

- (void)dealloc {
    zero_release(_identity);
    [super dealloc];
}

# define DB_NAME @".nnt.ui.history.textfield"

- (BOOL)serialOut:(id)obj identity:(NSString*)idr data:(NSData*)data {
    NNTBdb* db = [[NNTBdb alloc] initWith:DB_NAME type:NSAppVarDirectory];
    if (db == nil)
        return NO;
    
    BOOL suc = [db over:data key:[idr dataUsingEncoding:NSUTF8StringEncoding]];
    
    safe_release(db);
    return suc;
}

- (NSData*)serialIn:(id)obj identity:(NSString*)idr {
    NNTBdb* db = [[NNTBdb alloc] initWith:DB_NAME type:NSAppVarDirectory];
    if (db == nil)
        return nil;
    
    NSArray* result = [db get:[idr dataUsingEncoding:NSUTF8StringEncoding]];
    NSData* ret = nil;
    if (result.count)
        ret = [result objectAtIndex:0];
    
    safe_release(db);
    return ret;
}

// override.

- (void)doOpenSuggest {
    // load.
    if (_identity &&
        _serialDelegate) {
        
        NSData* da = [_serialDelegate serialIn:self identity:self.identity];
        if (da) {
            NSString* str = [[NSString alloc] initWithData:da encoding:NSUTF8StringEncoding];
            NSArray* items = (NSArray*)[NNTObject json_decode:str];
            safe_release(str);
            
            self.datas = items;
        }
    }
    
    // super.
    [super doOpenSuggest];
}

- (void)doCloseSuggest {
    NSString* input = self.text;
    if ([input notEmpty]) {
        
        if (_identity &&
            _serialDelegate) {
            
            NSData* da = [_serialDelegate serialIn:self identity:self.identity];
            if (da) {
                NSString* str = [[NSString alloc] initWithData:da encoding:NSUTF8StringEncoding];
                NSArray* items = (NSArray*)[NNTObject json_decode:str];
                
                NSMutableArray* saves = [[NSMutableArray alloc] init];
                [saves addObjectsFromArray:items];
                
                // insert object.
                [saves insertObject:input atIndex:0];
                
                // uni array.
                NSArray* result = [saves uniqueArray];
                if (_limitCount != NSNotFound) {
                    NSRange rang;
                    rang.location = 0;
                    rang.length = MIN(_limitCount, result.count);
                    result = [result subarrayWithRange:rang];
                }
                
                // save.
                NSString* str_json = [NNTObject json_encode:result];
                [_serialDelegate serialOut:self identity:self.identity data:[str_json dataUsingEncoding:NSUTF8StringEncoding]];
                
                safe_release(saves);
                safe_release(str);
            } else {
                
                NSArray* saves = [NSArray arrayWithObject:input];
                NSString* str_json = [NNTObject json_encode:saves];
                [_serialDelegate serialOut:self identity:self.identity data:[str_json dataUsingEncoding:NSUTF8StringEncoding]];
                
            }
            
        }
        
    }
    
    // super.
    [super doCloseSuggest];
}

@end

NNT_END_OBJC
