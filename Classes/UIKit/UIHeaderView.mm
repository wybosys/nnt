
# import "Core.h"
# import "UIHeaderView.h"
# import "Layout.h"

WSI_BEGIN_OBJC

signal_t kSignalAction = @"::wsi::action";

@implementation UIHeaderView

@synthesize height = _height;
@synthesize direction = _direction;
@synthesize autoScale = _autoScale;

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalAction);
WSIEVENT_END

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    frame.size.height = [UIScreen mainScreen].bounds.size.height;
    self.frame = frame;
    
    _height = 50;
    _direction = WCGDirectionTop;
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
        
    _normalLabel = [[WSIUILabel alloc] initWithZero];
    [self addSubview:_normalLabel];
    safe_release(_normalLabel);
    
    _actionLabel = [[WSIUILabel alloc] initWithZero];
    [self addSubview:_actionLabel];
    safe_release(_actionLabel);
    
    _normalLabel.textAlignment = UITextAlignmentCenter;
    _actionLabel.textAlignment = UITextAlignmentCenter;
    
    _actionLabel.hidden = YES;
    
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    WSI_USINGCXXNAMESPACE;
    
    CGRectLayoutVBox lyt(self.bounds);
    CGRectLayoutLinear lnr(lyt);
    
    CGRect rc;
    if (_direction == WCGDirectionTop) {
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

WSI_END_OBJC

_CXXVIEW_IMPL(UIHeaderView);
_CXXVIEW_IMPL(UIActivityHeaderView);

