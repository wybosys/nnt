
# import "Core.h"
# import "UIBarButtonItem+WSI.h"
# import "UIButton+WSI.h"
# import <QuartzCore/QuartzCore.h>
# import "UILabel+WSI.h"

WSI_BEGIN_OBJC

@implementation WSIUIBarButtonItem

WSIOBJECT_IMPL_NOSIGNALS;

+ (id)itemWithCustomView:(id)view {
    WSIUIBarButtonItem *item = [[[WSIUIBarButtonItem alloc] initWithCustomView:view] autorelease];
    return item;
}

- (id)initWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style {
    id ret = [self initWithTitle:title style:style target:self action:@selector(__act_clicked:)];
    return ret;
}

- (id)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem {
    id ret = [self initWithBarButtonSystemItem:systemItem target:self action:@selector(__act_clicked:)];
    return ret;
}

- (id)initWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style target:(id)target action:(SEL)action {    
    self = [super initWithTitle:title style:style target:target action:action];
    return self;
}

- (id)initWithImage:(UIImage *)image style:(UIBarButtonItemStyle)style {
    self = [super initWithImage:image style:style target:nil action:nil];
    if (self == nil)
        return nil;
    
    self.action = @selector(__act_clicked:);
    self.target = self;

    return self;
}

- (id)initWithCustomView:(UIView *)customView {
    self = [super initWithCustomView:customView];
    
    if ([customView hasSignal:kSignalViewClicked]) {
        [customView connect:kSignalViewClicked sel:@selector(__act_clicked:) obj:self];
    }
    
    return self;
}

- (void)dealloc {
    [self.customView disconnect:kSignalViewClicked obj:self];
    
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)__act_clicked:(id)obj {
    [self emit:kSignalViewClicked];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalViewClicked);
}

- (void)setBackgroundColor:(UIColor *)__backgroundColor {
    self.customView.backgroundColor = __backgroundColor;
}

- (void)setBackgroundFill:(WCGFill*)fill {
    if ([self.customView isKindOfClass:[WSIUIButton class]]) {
        WSIUIButton *btn = (WSIUIButton*)self.customView;
        btn.backgroundFill = fill;
    }
}

- (UIColor*)backgroundColor {
    return self.customView.backgroundColor;
}

- (WCGFill*)backgroundFill {
    if ([self.customView isKindOfClass:[WSIUIButton class]]) {
        WSIUIButton *btn = (WSIUIButton*)self.customView;
        return btn.backgroundFill;
    }
    return nil;
}

@end

@implementation WSIUIBarLabelItem

@synthesize label;

- (id)initWithTitle:(NSString *)title {
    label = [[WSIUILabel alloc] initWithFrame:CGRectZero];

    self = [super initWithCustomView:label];
    
    label.backgroundColor = [UIColor clearColor];
    label.text = title;
    
    [label sizeToFit];
    
    return self;
}

- (void)dealloc {
    [label release];
    [super dealloc];
}

@end

WSI_END_OBJC