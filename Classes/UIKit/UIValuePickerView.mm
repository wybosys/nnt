
# import "Core.h"
# import "UIValuePickerView.h"
# import "Layout.h"
# import "UIPickerView+WSI.h"
# import "UIButton+WSI.h"

WSI_BEGIN_OBJC

@implementation UIValuePickerView

@synthesize picker;
@synthesize btnDec, btnInc;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    picker = [[WSIUIPickerView alloc] initWithZero];
    [self addSubview:picker];
    
    btnInc = [[UIBevelButton alloc] initWithZero];
    btnDec = [[UIBevelButton alloc] initWithZero];
    btnInc.backgroundColor = [UIColor greenColor];
    btnDec.backgroundColor = [UIColor redColor];
    [btnInc setTitle:@"+" forState:UIControlStateNormal];
    [btnDec setTitle:@"-" forState:UIControlStateNormal];
    [self addSubview:btnInc];
    [self addSubview:btnDec];
    
    return self;
}

- (void)dealloc {
    zero_release(picker);
    zero_release(btnInc);
    zero_release(btnDec);
    
    [super dealloc];
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    
    wsi::CGRectLayoutVBox lyt(frame);
    picker.frame = lyt.add_pixel(175);
    
    wsi::CGRectLayoutHBox lyt_panel(lyt.fill());
    lyt_panel.margin.left = 5;
    btnInc.frame = lyt_panel.add_pixel(30);
    btnDec.frame = lyt_panel.add_pixel(30);
}

@end

WSI_END_OBJC