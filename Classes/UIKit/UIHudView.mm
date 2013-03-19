
# import "Core.h"
# import "UIHudView.h"
# import "App.h"

WSI_BEGIN_OBJC

@implementation UIHudView

@synthesize label = _label, margin = _margin;
@dynamic content;

- (id)init {
    self = [super init];
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor colorWithRGBA:0x0000007F];
    self.layer.cornerRadius = 5;
    self.layer.masksToBounds = YES;
    
    _label = [[WSIUILabel alloc] initWithZero];
    _label.multiLines = YES;
    _label.textColor = [UIColor whiteColor];
    _label.textAlignment = UITextAlignmentCenter;
    _label.shadowColor = [UIColor blackColor];
    
    [self addSubview:_label];
    
    _margin = CGMarginMake(10, 10, 10, 10);
    
    return self;
}

- (void)dealloc {
    zero_release(_label);
    
    [super dealloc];
}

- (void)layoutSubviews {
    CGRect rc = self.bounds;
    
    rc.origin.x += _margin.left;
    rc.origin.y += _margin.top;
    rc.size.width -= _margin.left + _margin.right;
    rc.size.height -= _margin.top + _margin.bottom;    
    _label.frame = rc;
}

- (NSString*)content {
    return _label.text;
}

- (void)willOpen {
    PASS;
}

- (void)didOpen {
    PASS;
}

- (void)willHide {
    PASS;
}

- (void)didHiden {
    PASS;
}

- (void)setContent:(NSString *)content {
    _label.text = content;
    
    CGSize sz = [_label textsSize];
    sz.height += _margin.top + _margin.bottom;
    sz.width += _margin.left + _margin.right;
    
    [self moveToSize:sz];
    [self setNeedsLayout];
}

@end

@implementation UIHud

@synthesize hud = _hud, desk = _desk;

- (id)init {
    self = [super init];
    
    _hud = [[UIHudView alloc] initWithZero];
    
    return self;
}

- (void)dealloc {
    zero_release(_hud);
    zero_release(_desk);
    
    [super dealloc];
}

- (void)open {
    [self retain];
    
    [_hud willOpen];
    
    UIView* mainView = [WSIApplication shared].rootViewController.view;
        
    _desk = [[WSIUIView alloc] initWithFrame:mainView.bounds];
    CGRect frame = _desk.frame;
    CGPoint cent = CGRectCenterPoint(&frame);
    [_desk addSubview:_hud];
    [_hud moveToCenter:cent];
   
    [mainView addSubview:_desk];
    
    [_hud didOpen];
}

- (void)openone:(NSTimeInterval)val {
    [_hud willOpen];
    
    [self open];
    
    [_hud didOpen];
    
    [self performSelector:@selector(close) withObject:nil afterDelay:val];       
}

- (void)close {
    [_hud performSelectorOnMainThread:@selector(willHide) withObject:nil waitUntilDone:YES];
    
    [_desk removeFromSuperview];
    
    [_hud performSelectorOnMainThread:@selector(didHiden) withObject:nil waitUntilDone:YES];
    
    zero_release(_desk);
    
    [self release];
}

@end

@implementation UIHudProgressView

@synthesize activityView = _activity;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:CGRectMake(0, 0, 80, 80)];
    
    self.label.hidden = YES;
    
    _activity = [[UIActivityIndicatorView alloc] initWithZero];
    [self addSubview:_activity];
    safe_release(_activity);
    
    return self;
}

- (void)layoutSubviews {
    CGRect rc = self.bounds;
    CGPoint pt = CGRectCenterPoint(&rc);
    
    rc.size.width = MIN(rc.size.height, rc.size.width);
    rc.size.width = rc.size.height = rc.size.width * GOLDENRATIO_1 * .5f;
    
    rc = CGRectMoveCenter(rc, pt);
    _activity.frame = rc;
}

- (void)didOpen {
    [_activity startAnimating];
}

- (void)willHide {
    [_activity stopAnimating];
}

@end

_CXXVIEW_IMPL(UIHudView);
_CXXVIEW_IMPL(UIHudProgressView);

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(ui)

static HudProgress* __gs_hud_progress = NULL;
static ulong __gs_hud_progress_counter = 0;

void HudProgress::Show()
{
    if (__gs_hud_progress_counter != 0)
    {
        WSI_ATOMIC_INC(__gs_hud_progress_counter);
        return;
    }
    WSI_ATOMIC_INC(__gs_hud_progress_counter);
    
    __gs_hud_progress = new HudProgress;
    __gs_hud_progress->open();
}

void HudProgress::Hide()
{
    if (__gs_hud_progress_counter == 0)
        return;
    
    WSI_ATOMIC_DEC(__gs_hud_progress_counter);
    
    if (__gs_hud_progress_counter == 0)
    {
        __gs_hud_progress->close();
        safe_delete(__gs_hud_progress);
    }
}

WSI_END_NS
WSI_END_CXX
