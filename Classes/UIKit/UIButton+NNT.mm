
# import "Core.h"
# import "UIButton+NNT.h"
# import "UIColor+NNT.h"
# import "NGGradient.h"
# import "NGColor.h"
# import <QuartzCore/QuartzCore.h>
# import "Graphic+NNT.h"
# import "UIKit.res"
# import "NGImage.h"
# import "UIStyleSheet.h"
# import "../Graphic/shapes/CGRoundedLeftArrowShape.h"

NNT_BEGIN_OBJC

@implementation UIButton (NNT)

NNTUIVIEW_NOTINHERIT_MUST_IMPL;

+ (UIButton*)buttonCloseRedRound {
    UIButton* button = [UIButton buttonWithType:UIButtonTypeCustom];
    NgImage* pngimg = NgImageLoadPngData(png_close_red, sizeof(png_close_red));
    UIImage *img = [UIImage imageWithCGImage:pngimg.image];
    [button setImage:img forState:UIControlStateNormal];
    button.frame = CGRectMake(0, 0, 30, 30);
    return button;
}

+ (UIButton*)buttonCloseGrayRound {
    UIButton* button = [UIButton buttonWithType:UIButtonTypeCustom];
    NgImage* pngimg = NgImageLoadPngData(png_close_gray, sizeof(png_close_gray));
    UIImage *img = [UIImage imageWithCGImage:pngimg.image];
    [button setImage:img forState:UIControlStateNormal];
    button.frame = CGRectMake(0, 0, 30, 30);
    return button;
}

@end

NNTIMPL_CATEGORY(UIButton, NNT);

@interface NNTUIButton ()

- (id)initWithoutTouch;

@end

@implementation NNTUIButton

NNTOBJECT_IMPL_NOSIGNALS;

@synthesize backgroundGradient = _backgroundGradient;
@synthesize isTouched = _isTouched;
@synthesize target = _target, action = _action, action_object = _action_object;
@dynamic backgroundFill, touchedFill;
@dynamic text;
@synthesize styleSheet = _styleSheet, touchedStyleSheet = _touchedStyleSheet;
@synthesize enableFeedback = _enableFeedback;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    __lockposition = 0;
    [self addTarget:self action:@selector(act_touchdown) forControlEvents:UIControlEventTouchDown];
    [self addTarget:self action:@selector(act_touchup) forControlEvents:UIControlEventTouchUpInside];
    [self addTarget:self action:@selector(act_touchup) forControlEvents:UIControlEventTouchUpOutside];
    
    self.touchedFill = [NgFill fillWithColor:[NgColor colorWithRGBA:0x0c0c0c0c]];
    self.enableFeedback = YES;
    
    return self;
}

- (id)initWithoutTouch {
    self = [super initWithFrame:CGRectZero];
    
    [self removeTarget:self action:@selector(act_touchdown) forControlEvents:UIControlEventTouchDown];
    [self removeTarget:self action:@selector(act_touchup) forControlEvents:UIControlEventTouchUpInside];
    [self removeTarget:self action:@selector(act_touchup) forControlEvents:UIControlEventTouchUpOutside];
    
    return self;
}

- (void)dealloc {
    safe_release(_backgroundGradient);
    safe_release(_styleSheet);
    safe_release(_touchedStyleSheet);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (UIStyleSheet*)styleSheet {
    if (_styleSheet == nil)
        _styleSheet = [[UIStyleSheet alloc] init];
    return _styleSheet;
}

- (UIStyleSheet*)touchedStyleSheet {
    if (_touchedStyleSheet == nil)
        _touchedStyleSheet = [[UIStyleSheet alloc] init];
    return _touchedStyleSheet;
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalViewClicked);
}

- (void)drawRect:(CGRect)rect {
    // super draw.
    [super drawRect:rect];
    
    // get context.
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    // draw owner.
    CGContextSaveGState(ctx);
    
    // draw style sheet.
    if (_styleSheet) {
        [_styleSheet drawInContext:ctx inRect:rect];
    }
    
    // draw.
    [self drawButton:ctx rect:rect];
            
    // draw touched.
    if (_enableFeedback &&
        _isTouched &&
        _touchedStyleSheet) {
        [_touchedStyleSheet drawInContext:ctx inRect:rect];
    }
        
    CGContextRestoreGState(ctx);
}

- (void)applyTextStyle:(NgTextStyle*)ts {
    [self.titleLabel applyTextStyle:ts];
    
    // set color.
    UIColor* color = [[UIColor alloc] initWithCGColor:ts.color.cgColor];
    [self setTitleColor:color forState:UIControlStateNormal];
    [color release];
}

- (void)drawButton:(CGContextRef)ctx rect:(CGRect)rc {
    PASS;
}

- (void)setBackgroundFill:(NgFill*)fill {
    self.styleSheet.backgroundFill = fill;
}

- (NgFill*)backgroundFill {
    return self.styleSheet.backgroundFill;
}

- (void)setTouchedFill:(NgFill *)touchedFill {
    self.touchedStyleSheet.backgroundFill = touchedFill;
}

- (NgFill*)touchedFill {
    return self.touchedStyleSheet.backgroundFill;
}
    
- (void)act_touchdown {
    _isTouched = YES;    
    [self setNeedsDisplay];
}

- (void)act_touchup {
    if (_action_object == nil)
        _action_object = self;
    
    if (_isTouched &&
        _target &&
        _action) {
        [_target performSelector:_action withObject:_action_object];
    }
    
    if (_isTouched) {
        [self emit:kSignalViewClicked];
    }
    
    _isTouched = NO;
    [self setNeedsDisplay];
}

- (void)setFrame:(CGRect)frame {
    if (__lockposition > 0)
        return;
    
    // set frame.
    [super setFrame:frame];
    
    // redraw.
    [self setNeedsDisplay];
}

- (void)lockPosition {
    ++__lockposition;
}

- (void)unlockPosition {
    --__lockposition;
}

- (void)setText:(NSString *)str {
    self.titleLabel.text = str;
    [super setTitle:str forState:UIControlStateNormal];    
}

- (NSString*)text {
    return self.titleLabel.text;
}

- (CGSize)textSize {    
    CGSize sz;
    
    NNT_SYNCHRONIZED(self)
    
    NSString* tmpstr = [NSString stringWithFormat:@" %@ ", self.titleLabel.text];
    //sz = [tmpstr sizeWithFont:self.titleLabel.font];
    sz = [tmpstr sizeWithFont:self.titleLabel.font
                     forWidth:0xFFFFFFFF
                lineBreakMode:UILineBreakModeClip];

    
    NNT_SYNCHRONIZED_END
    
    return sz;
}

@end

@implementation UIStyledButton

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _styleSheet = [[UIStyleSheet alloc] init];
    
    return self;
}

@end

@implementation UIButtonClose

@synthesize radius;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
        
    self.radius = 10;
    
    return self;
}

- (void)setRadius:(real)val {
    radius = val;
    
    self.frame = CGRectMake(0, 0, val + val, val + val);
}

- (void)drawRect:(CGRect)rect {
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    rect = CGRectDeflateCenter(rect, 1, 1);
    CGContextAddEllipseInRect(ctx, rect);
    
    // fill back.
    CGContextSetFillColorWithColor(ctx, [UIColor blackColor].CGColor);
    CGContextFillPath(ctx);
    
    // draw cross.
    int lenw = rect.size.width * GOLDENRATIO_1_1;
    int lenh = rect.size.height * GOLDENRATIO_1_1;
    CGPoint lt = rect.origin;
    CGPoint rt = CGRectRightTop2(rect);
    CGPoint lb = CGRectLeftBottom2(rect);
    CGPoint rb = CGRectRightBottom2(rect);
    lt.x += lenw;
    lt.y += lenh;
    rt.x -= lenw;
    rt.y += lenh;
    lb.x += lenw;
    lb.y -= lenh;
    rb.x -= lenw;
    rb.y -= lenh;
    CGContextMoveToPoint(ctx, lt.x, lt.y);
    CGContextAddLineToPoint(ctx, rb.x, rb.y);
    CGContextMoveToPoint(ctx, rt.x, rt.y);
    CGContextAddLineToPoint(ctx, lb.x, lb.y);
    CGContextSetStrokeColorWithColor(ctx, [UIColor whiteColor].CGColor);
    CGContextSetLineWidth(ctx, 2);
    CGContextStrokePath(ctx);
    
    // set edge shadow.
    //CGContextSetShadow(ctx, CGSizeMake(1, -3), 10);
    
    // draw edge.
    CGContextAddEllipseInRect(ctx, rect);
    CGContextSetStrokeColorWithColor(ctx, [UIColor whiteColor].CGColor);
    CGContextSetLineWidth(ctx, 2);
    CGContextStrokePath(ctx);
}

@end

@implementation UIClearButton

+ (id)button {
    return [[[UIClearButton alloc] initWithZero] autorelease];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    self.backgroundFill = nil;
    
    return self;
}

@end

@implementation UISystemButton

- (id)initWithButtonType:(UIButtonType)type {
    self = [super initWithoutTouch];
    
    _button = [UIButton buttonWithType:type];
    [self addSubview:_button];
    
    [_button addTarget:self action:@selector(act_touchdown) forControlEvents:UIControlEventTouchDown];
    [_button addTarget:self action:@selector(act_touchup) forControlEvents:UIControlEventTouchUpInside];
    [_button addTarget:self action:@selector(act_touchup) forControlEvents:UIControlEventTouchUpOutside];
    
    return self;
}

- (void)layoutSubviews {
    _button.frame = self.bounds;
}

- (CALayer*)layer {
    return _button.layer;
}

@end

@implementation UIBevelButton

@synthesize innerShadowColor, innerShadowBlur, innerShadowLength;

+ (id)button {
    return [[[UIBevelButton alloc] initWithZero] autorelease];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.innerShadowColor = [NgColor colorWithRGBA:0xFFFFFF20];
    innerShadowLength = 6;
    innerShadowBlur = .1f;
    
    NgGradient *backgroundTop = [NgGradient gradientWithBeginningColor:[NgColor colorWithRGBA:0x00000000]
                                                             endingColor:[NgColor colorWithRGBA:0x00000040] 
                                                                   angle:90];            
    NgGradient *backgroundBottom = [NgGradient gradientWithBeginningColor:[NgColor colorWithRGBA:0x00000060]
                                                                endingColor:[NgColor colorWithRGBA:0x00000000]
                                                                      angle:90];
    self.backgroundGradient = [NSArray arrayWithObjects:backgroundTop, backgroundBottom, nil];
    
    self.layer.borderColor = [UIColor colorWithRGBA:0x00000060].CGColor;
    self.layer.borderWidth = 1.f;
    
    self.titleLabel.shadowColor = [UIColor blackColor];
    self.titleLabel.shadowOffset = CGSizeMake(0, -1);
    
    self.layer.cornerRadius = 5.f;
    self.layer.masksToBounds = YES;
    
    return self;
}

- (void)dealloc {
    safe_release(innerShadowColor);
    [super dealloc];
}

- (void)drawInnerShadow:(CGContextRef)ctx {
    [self drawInnerShadow:ctx rect:self.bounds];
}

- (void)drawInnerShadow:(CGContextRef)ctx rect:(CGRect)rc {
    int radius = self.layer.cornerRadius;
    NgColor *color = [NgColor colorWithCGColor:innerShadowColor.cgColor];
    uint valueColor = [color valueRGBA];
    real alpha_offset = AS_C32P(ceil(RGBA_ALPHA(valueColor) * innerShadowBlur));
    
    NNT_AUTORELEASEPOOL_BEGIN;
    
    for (uint i = 0; i < innerShadowLength; ++i) {
        
        CGContextSetStrokeColorWithColor(ctx, color.cgColor);
        CGContextSetLineWidth(ctx, 2);
        CGContextAddBoundsRect(ctx, rc, radius, YES, YES, YES, YES);
        
        rc.origin.x += 1;
        rc.origin.y += 1;
        rc.size.width -= 2;
        rc.size.height -= 2;
        
        color = [NgColor addWith:[NgColor colorWithCGColor:color.cgColor] r:0 g:0 b:0 a:-alpha_offset];
        
        CGContextStrokePath(ctx);
    }
    
    NNT_AUTORELEASEPOOL_END;
}

- (void)drawButton:(CGContextRef)ctx rect:(CGRect)rect {
    // draw gradient.
    if ([_backgroundGradient isKindOfClass:[NSArray class]]) {
        uint const count = [(NSArray*)_backgroundGradient count];
        uint comp_height = ceil(rect.size.height / count); 
        
        CGRect rc = CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, comp_height);
        for (uint i = 0; i < count; ++i) {
            NgGradient *gradient = (NgGradient*)[(NSArray*)_backgroundGradient objectAtIndex:i];
            [gradient fillRect:rc inContext:ctx];
            rc.origin.y += comp_height;
        }
    } else if ([_backgroundGradient isKindOfClass:[NgGradient class]]) {
        [(NgGradient*)_backgroundGradient fillRect:rect inContext:ctx];
    } else if ([_backgroundGradient isKindOfClass:[UIColor class]]) {
        [(UIColor*)_backgroundGradient set];
        CGContextFillRect(ctx, rect);
    }
    
    // draw inner shadow.
    if (innerShadowColor) {        
        CGRect rc = rect;
        int radius = self.layer.cornerRadius;
        NgColor *color = [NgColor colorWithCGColor:innerShadowColor.cgColor];
        uint valueColor = [color valueRGBA];
        real alpha_offset = AS_C32P(ceil(RGBA_ALPHA(valueColor) * innerShadowBlur));
        
        NNT_AUTORELEASEPOOL_BEGIN;
        
        for (uint i = 0; i < innerShadowLength; ++i) {
            
            CGContextSetStrokeColorWithColor(ctx, color.cgColor);
            CGContextSetLineWidth(ctx, 2);
            CGContextAddBoundsRect(ctx, rc, radius, YES, YES, YES, YES);
            
            rc.origin.x += 1;
            rc.origin.y += 1;
            rc.size.width -= 2;
            rc.size.height -= 2;
            
            color = [NgColor addWith:[NgColor colorWithCGColor:color.cgColor] r:0 g:0 b:0 a:-alpha_offset];
            
            CGContextStrokePath(ctx);
        }
        
        NNT_AUTORELEASEPOOL_END;
    }
    
    // draw inner edge.
    if (self.layer.borderColor) {
        UIColor *color = [UIColor multiWith:[UIColor colorWithCGColor:self.layer.borderColor] r:1 g:1 b:1 a:.5f];
        CGContextSetStrokeColorWithColor(ctx, color.CGColor);
        CGContextSetLineWidth(ctx, 1);
        CGRect rc = CGRectMake(rect.origin.x + 1, rect.origin.y + 1, rect.size.width - 2, rect.size.height - 2);
        CGContextAddBoundsRect(ctx, rc, self.layer.cornerRadius, YES, YES, YES, YES);
        CGContextStrokePath(ctx);
    }
}

@end

@implementation UIBackButton

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    NgShapeStyle* style = [[NgShapeStyle alloc] init];
    CGRoundedLeftArrowShape* shape = [[CGRoundedLeftArrowShape alloc] init];
    shape.radius = 4.5;
    style.shape = shape;
    safe_release(shape);
    
    style.fillable = YES;
    
    [_styleSheet addStyle:style forKey:@"shape::back"];
    safe_release(style);
    
    return self;
}

@end

@implementation UIStateButton

@synthesize state = _state;

- (void)dealloc {
    zero_release(_fillUnchecked);
    zero_release(_fillChecked);
    zero_release(_fillMixin);
    
    [super dealloc];
}

- (void)setStateFill:(NgFill*)fill forState:(UIButtonState)state {
    if (_fillChecked == nil && _fillMixin == nil && _fillUnchecked == nil) {
        _fillChecked = [fill retain];
        _fillMixin = [fill retain];
        _fillUnchecked = [fill retain];
        return;
    }
    
    switch (state)
    {
        case UIButtonStateUnchecked: [NSObject refobjSet:&_fillUnchecked ref:fill]; break;
        case UIButtonStateChecked: [NSObject refobjSet:&_fillChecked ref:fill]; break;
        case UIButtonStateMixin: [NSObject refobjSet:&_fillMixin ref:fill]; break;
    }
}

- (void)setStateTextStyle:(NgTextStyle*)ts forState:(UIButtonState)state {
    if (_tsUnchecked == nil && _tsChecked == nil && _tsMixin == nil) {
        _tsUnchecked = [ts retain];
        _tsChecked = [ts retain];
        _tsMixin = [ts retain];
        return;
    }
    
    switch (state)
    {
        case UIButtonStateUnchecked: [NSObject refobjSet:&_tsUnchecked ref:ts]; break;
        case UIButtonStateChecked: [NSObject refobjSet:&_tsChecked ref:ts]; break;
        case UIButtonStateMixin: [NSObject refobjSet:&_tsMixin ref:ts]; break;
    }
}

- (void)setState:(UIButtonState)state {
    _state = state;
    
    switch (_state)
    {
        case UIButtonStateUnchecked: {            
            self.backgroundFill = _fillUnchecked; 
            if (_tsUnchecked)
                [self applyTextStyle:_tsUnchecked];
        } break;
        case UIButtonStateChecked: {            
            self.backgroundFill = _fillChecked; 
            if (_tsChecked)
                [self applyTextStyle:_tsChecked];
        } break;
        case UIButtonStateMixin: {            
            self.backgroundFill = _fillMixin; 
            if (_tsMixin)
                [self applyTextStyle:_tsMixin];
        } break;
    }
}

@end

@implementation UIButtonGroup

@synthesize buttons = _buttons;
@synthesize selected = _sel;

- (id)init {
    self = [super init];
    _buttons = [[NSMutableArray alloc] init];
    return self;
}

- (void)dealloc {
    [self clear];
    zero_release(_buttons);
    [super dealloc];
}

- (void)add:(UIButton*)btn {
    [_buttons addObject:btn];
    
    if ([btn conformsToProtocol:@protocol(UIStateButton)]) {
        id<UIStateButton> obj = (id<UIStateButton>)btn;
        obj.state = UIButtonStateUnchecked;
    }
    
    // link.
    [btn connect:kSignalButtonClicked sel:@selector(act_btnclick:) obj:self];
}

- (void)clear {
    for (UIButton* each in _buttons) {
        [each disconnect:self];
    }
    _sel = nil;
}

- (void)act_btnclick:(NNTEventObj*)evt {
    if (_sel && [_sel conformsToProtocol:@protocol(UIStateButton)]) {
        id<UIStateButton> obj = (id<UIStateButton>)_sel;
        obj.state = UIButtonStateUnchecked;
        [_sel setNeedsDisplay];
    }
    
    UIButton* btn = (UIButton*)evt.sender;
    _sel = btn;
    
    if (_sel && [_sel conformsToProtocol:@protocol(UIStateButton)]) {
        id<UIStateButton> obj = (id<UIStateButton>)_sel;
        obj.state = UIButtonStateChecked;
        [_sel setNeedsDisplay];
    }
}

- (void)setSelected:(UIButton*)btn {
    [btn emit:kSignalButtonClicked];
}

@end

_CXXVIEW_IMPL(UIClearButton);
_CXXVIEW_IMPL(UISystemButton);
_CXXVIEW_IMPL(UIBevelButton);
_CXXVIEW_IMPL(UIStateButton);

NNT_END_OBJC