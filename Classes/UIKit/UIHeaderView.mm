
# import "Core.h"
# import "UIHeaderView.h"
# import "Layout.h"
# import "Configuration+NNT.h"

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

@implementation UILogoHeaderView

@synthesize timeLine = _timeLine, logo = _logo;

- (void)dealloc {
    safe_release(_timeLine);
    safe_release(_logo);
    [super dealloc];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _height = 80;
    
    self.backgroundColor = [UIColor whiteColor];
    
    _timeLine = [[NNTUILabel alloc] initWithZero];
    _timeLine.textAlignment = UITextAlignmentCenter;
    [self addSubview:_timeLine];
    
    _logo = [[NNTUIImageView alloc] initWithZero];
    _logo.backgroundColor = [UIColor redColor];
    [self addSubview:_logo];
    
    return self;
}

- (void)layoutSubviews {
    NNT_USINGCXXNAMESPACE
    layout::vbox lyt_main(self.bounds);
    layout::linear lnr_main(lyt_main);
    
    CGRect rc;
    if (_direction == NgDirectionTop) {
        lnr_main << (flex)1 << (pixel)_height;
        lyt_main << lnr_main;
        rc = lyt_main << lnr_main;
    } else {
        lnr_main << (pixel)_height << (flex)1;
        rc = lyt_main << lnr_main;
        lyt_main << lnr_main;
    }
    
    {
        layout::hbox lyt_action(rc);
        layout::linear lnr_action(lyt_action);
        
        lnr_action << (flex)1 << (flex)3;
        
        _logo.frame = CGRectDeflateCenter(lyt_action << lnr_action, 5, 5);
        
        {
            layout::vbox lyt_status(CGRectDeflateCenter(lyt_action << lnr_action, 5, 5));
            layout::linear lnr_status(lyt_status);
            
            lnr_status << (flex)1 << (flex)1;
            CGRect rc_status = lyt_status << lnr_status;
            _normalLabel.frame = rc_status;
            _actionLabel.frame = rc_status;
            
            _timeLine.frame = lyt_status << lnr_status;
        }
    }
}

- (void)headerBeginAction:(UIHeaderView *)view {
    NNT_USINGCXXNAMESPACE
    store::Configuration* config = &store::Configuration::shared();
    NSString *date = config->get_obj(@"timeline");
    
    if (![date notEmpty])
        _timeLine.text = [self timeString];
    else
        _timeLine.text = date;
}

- (void)headerEndAction:(UIHeaderView *)view {
    NNT_USINGCXXNAMESPACE
    _timeLine.text = [self timeString];
    store::Configuration* config = &store::Configuration::shared();
    config->set_obj(@"timeline", _timeLine.text);
}

- (void)headerDidAction:(UIHeaderView *)view {
    
}

- (void)headerWillAction:(UIHeaderView *)view {
    _normalLabel.hidden = YES;
    _actionLabel.hidden = NO;
}

- (void)headerMovedAction:(NNTUIView *)view {
    _normalLabel.hidden = NO;
    _actionLabel.hidden = YES;
}

- (NSString *)timeString {
    [NSDateFormatter setDefaultFormatterBehavior:NSDateFormatterBehaviorDefault];
    NSDateFormatter *fmat = [[[NSDateFormatter alloc] init] autorelease];
    [fmat setDateStyle:NSDateFormatterShortStyle];
    [fmat setTimeStyle:NSDateFormatterShortStyle];
    NSString *ret = [NSString stringWithFormat:@"上次更新 : %@", [fmat stringFromDate:[NSDate date]]];
    return ret;
}

@end

NNT_END_OBJC

_CXXVIEW_IMPL(UIHeaderView);
_CXXVIEW_IMPL(UIActivityHeaderView);

