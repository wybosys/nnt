
# import "Core.h"
# import "UIBarButtonItem+NNT.h"
# import "UIButton+NNT.h"
# import <QuartzCore/QuartzCore.h>
# import "UILabel+NNT.h"

NNT_BEGIN_OBJC

@implementation NNTUIBarButtonItem

NNTOBJECT_IMPL_NOSIGNALS;

+ (id)itemWithCustomView:(id)view {
    NNTUIBarButtonItem *item = [[[NNTUIBarButtonItem alloc] initWithCustomView:view] autorelease];
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
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)__act_clicked:(id)obj {
    [self emit:kSignalViewClicked];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalViewClicked);
}

- (void)setBackgroundColor:(UIColor *)__backgroundColor {
    self.customView.backgroundColor = __backgroundColor;
}

- (void)setBackgroundFill:(WCGFill*)fill {
    if ([self.customView isKindOfClass:[NNTUIButton class]]) {
        NNTUIButton *btn = (NNTUIButton*)self.customView;
        btn.backgroundFill = fill;
    }
}

- (UIColor*)backgroundColor {
    return self.customView.backgroundColor;
}

- (WCGFill*)backgroundFill {
    if ([self.customView isKindOfClass:[NNTUIButton class]]) {
        NNTUIButton *btn = (NNTUIButton*)self.customView;
        return btn.backgroundFill;
    }
    return nil;
}

@end

@implementation NNTUIBarLabelItem

@synthesize label;

- (id)initWithTitle:(NSString *)title {
    label = [[NNTUILabel alloc] initWithFrame:CGRectZero];

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

NNT_END_OBJC