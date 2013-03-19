
# import "Core.h"
# import "UITextView+NNT.h"

NNT_BEGIN_OBJC


@implementation NNTUITextView

NNTOBJECT_IMPL;

- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.autocapitalizationType = UITextAutocapitalizationTypeNone;

    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)appendLine:(NSString *)line {
    NSString* str = [NSString stringWithFormat:@"%@\n%@", self.text, line];
    self.text = str;
}

- (void)applyTextStyle:(WCGTextStyle*)ts {
    UITextAlignment align;
    switch (ts.alignment)
    {
        case WCGAlignmentLeft: align = UITextAlignmentLeft; break;
        case WCGAlignmentRight: align = UITextAlignmentRight; break;
        default: align = UITextAlignmentCenter; break;
    }
    self.textAlignment = align;
    self.textColor = [UIColor colorWithCGColor:ts.color.cgColor];
    self.font = [ts uiFont];
}

- (void)scrollToEnd {
    [self scrollRangeToVisible:NSMakeRange(self.text.length, 1)];
}

- (BOOL)resignFirstResponder {
    BOOL suc = [super resignFirstResponder];
    
    if (suc) {
        // remove opening.
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:UIKeyboardDidShowNotification
                                                      object:nil];
        
        // remove hiding while hiding.
    }
    
    return suc;
}

- (BOOL)becomeFirstResponder {
    BOOL suc = [super becomeFirstResponder];
    
    if (suc) {
        // for opening.
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(act_keyboard_opening:)
                                                     name:UIKeyboardDidShowNotification
                                                   object:nil];
    }
    
    return suc;
}

- (void)act_keyboard_opening:(NSNotification*)aNotification {
    NSDictionary* info = [aNotification userInfo];
    
    CGSize sz_keyboard = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;
    CGRect frm_window = [NNTApplication shared].window.boundsOnScreen;
    CGRect frm_txt = [[NNTApplication shared].window locationIn:self];
    sz_keyboard = [UIScreen convertCurrentSize:sz_keyboard];
    
    int offset = frm_window.size.height - sz_keyboard.height - frm_txt.origin.y - frm_txt.size.height;
    if (offset >= 0)
        return;
    
    // begin animated.
    [[NNTApplication shared].window offsetX:0 Y:offset];
    
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


@end

NNT_END_OBJC
