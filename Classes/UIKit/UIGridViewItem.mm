
# import "Core.h"
# import "UIGridViewItem.h"
# import "Layout.h"
# import "CoreGraphic+NNT.h"
# import "UIGridView.h"
# import "UIButton+NNT.h"
# import "UILabel+NNT.h"
# import "UIColor+NNT.h"

NNT_BEGIN_OBJC

@implementation UIGridViewItem

@synthesize scaleToFill = _scaleToFill;
@synthesize content = _content;
@synthesize gridView = _gridView;
@synthesize margin = _margin, selfMargin = _selfMargin;
@synthesize delegate = _delegate;
@synthesize highlightFill = _highlightFill;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.layer.masksToBounds = YES;
    self.scaleToFill = NO;
    self.backgroundColor = [UIColor clearColor];
    self.userInteractionEnabled = YES;
    
    [self connect:kSignalViewClicked sel:@selector(_act_clicked:)];
    
    return self;
}

- (void)dealloc {
    zero_release(_content);
    zero_release(_highlightFill);
    
    [super dealloc];
}

- (void)addSubview:(UIView*)view {
    view.userInteractionEnabled = NO;
    [super addSubview:view];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalContentClicked)
NNTEVENT_END

- (void)setMargin:(CGMargin)margin {
    _margin = margin;
    _selfMargin = YES;
}

- (void)layoutSubviews {
    [self updateLayout:self.bounds];
}

- (void)updateLayout:(CGRect)rc {
    //[super updateLayout:rc];
    
    if (_scaleToFill) {
        if (_selfMargin) {
            rc.origin.x += _margin.left;
            rc.origin.y += _margin.top;
            rc.size.width -= _margin.left + _margin.right;
            rc.size.height -= _margin.top + _margin.bottom;
        } else {
            rc.origin.x += _gridView.margin.left;
            rc.origin.y += _gridView.margin.top;
            rc.size.width -= _gridView.margin.left + _gridView.margin.right;
            rc.size.height -= _gridView.margin.top + _gridView.margin.bottom;
        }                
    }
    
    [_content setFrame:rc];
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    // draw
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextSaveGState(context);
    
    WCGFill *theBkFill = self.backgroundFill;
    if (!theBkFill)
        theBkFill = _gridView.itemBackgroundFill;
    if (theBkFill) {
        [theBkFill fillRect:rect inContext:context];
    }
    
    if ([_delegate respondsToSelector:@selector(gridviewItem:draw:rect:)]) {
        [_delegate gridviewItem:self draw:context rect:rect];
    }
    
    CGContextRestoreGState(context);
}

- (void)drawHighlight:(CGRect)rect ctx:(CGContextRef)ctx {
    // draw high light.
    if (_highlightFill) {
        [_highlightFill fillRect:rect inContext:ctx];
    }    
}

# pragma mark margin event

- (void)_act_clicked:(NNTEventObj*)evt {
    if ([_content hasSignal:kSignalViewClicked]) {
        [_content emit:kSignalViewClicked];
    }
    
    [self emit:kSignalContentClicked result:_content];
}

@end

@interface UIGridViewItem (event)

@end

@implementation UIGridViewItem (event)

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)__event {
    //[content touchesBegan:touches withEvent:__event];
    [super touchesBegan:touches withEvent:__event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)__event {
    //[content touchesEnded:touches withEvent:__event];
    [super touchesEnded:touches withEvent:__event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)__event {
    //[content touchesEnded:touches withEvent:__event];
    [super touchesMoved:touches withEvent:__event];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)__event {
    //[content touchesCancelled:touches withEvent:__event];
    [super touchesCancelled:touches withEvent:__event];
}

@end

@implementation UIGridViewItemWithClose

@synthesize closeButton;
@synthesize closePosition;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        closeButton = [UIButton buttonCloseGrayRound];
        closePosition = CGRectPositionTypeRightTop;
        [closeButton addTarget:self action:@selector(_act_btn_click) forControlEvents:UIControlEventTouchDown];
    }
    return self;
}

- (void)dealloc {    
    [super dealloc];
}

- (void)layoutSubviews {
    [super layoutSubviews];
}

- (void)didMoveToSuperview {
    [self.superview addSubview:closeButton];
}

- (void)setFrame:(CGRect)frame {
    
    int offsetx = closeButton.bounds.size.width * .1f;
    int offsety = closeButton.bounds.size.height * .1f;
    
    CGPoint pt;
    switch (closePosition) {
        default:
        case CGRectPositionTypeRightTop:
            pt = CGRectRightTop(&frame);
            pt.x -= offsetx;
            pt.y += offsety;
            break;
        case CGRectPositionTypeLeftTop:
            pt = frame.origin;
            pt.x += offsetx;
            pt.y += offsety;
            break;
        case CGRectPositionTypeLeftBottom:
            pt = CGRectLeftBottom(&frame);
            pt.x += offsetx;
            pt.y -= offsety;
            break;
        case CGRectPositionTypeRightBottom:
            pt = CGRectRightBottom(&frame);
            pt.x -= offsetx;
            pt.y -= offsety;
            break;
    }
    
    [closeButton moveToCenter:pt];
    
    [super setFrame:frame];
}

# pragma mark action

- (void)_act_btn_click {
    [closeButton removeFromSuperview];
    id <UIGridViewItemWithCloseDelegate> theDelegate = (id <UIGridViewItemWithCloseDelegate>)_delegate;
    if ([theDelegate respondsToSelector:@selector(griditemClose:)]) {
        [theDelegate griditemClose:self];
    }
}

@end

@implementation UIGridViewItemWithLabel

@synthesize label, height;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    NNTUILabel* tmplabel = [[NNTUILabel alloc] initWithZero];
    tmplabel.backgroundColor = [UIColor clearColor];
    tmplabel.textAlignment = UITextAlignmentCenter;
    self.label = tmplabel;
    [tmplabel release];    
    
    height = 25;
    
    return self;
}

- (void)dealloc {
    zero_release(label);
    [super dealloc];
}

- (void)setLabel:(UILabel *)__label {
    [label removeFromSuperview];
    [label release];
    
    label = [__label retain];
    if (label) {
        [self addSubview:label];    
    }
    
    [self setNeedsLayout];
}

- (void)setContent:(UIView*)view {
    [NSObject refobjSet:&_content ref:view];
    [self bringSubviewToFront:self.label];
}

- (void)layoutSubviews {
    wsi::CGRectLayoutVBox lyt(self.bounds);
    lyt.margin = self.margin;
    
    wsi::CGRectLayoutLinear lnr(self.bounds.size.height);
    lnr.add_flex(1);
    lnr.add_pixel(height);
    
    self.content.frame = lyt.add_pixel(lnr.get_comp(0));
    self.label.frame = CGRectIntegral(lyt.add_pixel(lnr.get_comp(1)));
}

@end

_CXXVIEW_IMPL(UIGridViewItem);

NNT_END_OBJC
