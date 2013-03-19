
# import "Core.h"
# import "UIHeaderView.h"
# import "Layout.h"

NNT_BEGIN_OBJC

signal_t kSignalAction = @"::nnt::action";

@implementation UIHeaderView

@synthesize height = _height;
@synthesize direction = _direction;
@synthesize autoScale = _autoScale;

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalAction);
NNTEVENT_END

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    frame.size.height = [UIScreen mainScreen].bounds.size.height;
    self.frame = frame;
    
    _height = 50;
    _direction = NgDirectionTop;
    _autoScale = YES;
    
    return self;
}

- (void)headerBeginAction:(UIHeaderView*)view {
    PASS;
}

- (void)headerEndAction:(UIHeaderView*)view {
    PASS;
}

- (void)headerWillAction:(UIHeaderView*)view {
    PASS;
}

- (void)headerDidAction:(UIHeaderView*)view {
    [self emit:kSignalAction];
}

- (void)headerMovedAction:(UIHeaderView*)view {
    PASS;
}

@end

@implementation UIActivityHeaderView

@synthesize normalLabel = _normalLabel, actionLabel = _actionLabel;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
        
    _normalLabel = [[NNTUILabel alloc] initWithZero];
    [self addSubview:_normalLabel];
    safe_release(_normalLabel);
    
    _actionLabel = [[NNTUILabel alloc] initWithZero];
    [self addSubview:_actionLabel];
    safe_release(_actionLabel);
    
    _normalLabel.textAlignment = UITextAlignmentCenter;
    _actionLabel.textAlignment = UITextAlignmentCenter;
    
    _actionLabel.hidden = YES;
    
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    NNT_USINGCXXNAMESPACE;
    
    CGRectLayoutVBox lyt(self.bounds);
    CGRectLayoutLinear lnr(lyt);
    
    CGRect rc;
    if (_direction == NgDirectionTop) {
        lnr << (flex)1 << (pixel)_height;
        lyt << lnr;
        rc = lyt << lnr;
    } else {
        lnr << (pixel)_height << (flex)1;
        rc = lyt << lnr;
    }
    
    _normalLabel.frame = rc;
    _actionLabel.frame = rc;
}

- (void)headerWillAction:(UIHeaderView*)view {
    _normalLabel.hidden = YES;
    _actionLabel.hidden = NO;
}

- (void)headerMovedAction:(UIHeaderView*)view {
    _normalLabel.hidden = NO;
    _actionLabel.hidden = YES;
}

@end

NNT_END_OBJC

_CXXVIEW_IMPL(UIHeaderView);
_CXXVIEW_IMPL(UIActivityHeaderView);

