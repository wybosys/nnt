
# import "Core.h"
# import "UIView+NNT.h"
# import "UITearView.h"
# import "../Store/NNTConfiguration.h"
# import "CoreGraphic+NNT.h"
# import <QuartzCore/QuartzCore.h>
# import "NNTUIObject.h"
# import "Math+NNT.h"
# import "WCGFillImage.h"
# import "UIDesktop.h"
# import "JuiceCocoa++.hpp"

NNT_BEGIN_OBJC

NNTIMPL_CATEGORY(UIView, NNT);

signal_t kSignalViewClicked = @"::wsi::ui::view::clicked";
signal_t kSignalButtonClicked = @"::wsi::ui::view::clicked"; // must same as kSignalViewClicked.
signal_t kSignalSelectChanged = @"::wsi::ui::select::changed";
signal_t kSignalFrameChanged = @"::wsi::ui::frame::changed";
signal_t kSignalBoundsChanged = @"::wsi::ui::bounds::changed";
signal_t kSignalSelected = @"::wsi::ui::selected";
signal_t kSignalDeselected = @"::wsi::ui::selected";
signal_t kSignalPainting = @"::wsi::ui::draw";

NNT_EXTERN bool __need_manual_appear;

real kUITouchDelay = 1.f / 200;
real kUIDragDelay = .5f;
int kUITouchRadius = 10;
CGPoint kUITouchSky = (CGPoint){-999999, -999999};

static CGPoint __gs_view_touchpoint = kUITouchSky;
static BOOL __gs_view_waitingtouch = NO;

@implementation UIView (NNT)

- (id)initWithZero {
    return [self initWithFrame:CGRectZero];
}

- (UIImage*)convertToImage {
    return UIConvertViewToImage(self);
}

- (UIImage*)convertToImage:(UIColor*)backgroundColor {
    return UIConvertViewToImageWithOptions(self, backgroundColor);
}

- (void)moveTo:(CGPoint)pos {
    CGRect rc = self.frame;
    rc.origin = pos;
    [self setFrame:rc];
}

- (void)moveToSize:(CGSize)sz {
    CGRect rc = self.frame;
    rc.size = sz;
    [self setFrame:rc];
}

- (void)moveOffsetX:(CGFloat)offx OffsetY:(CGFloat)offy {
    CGRect rc = self.frame;
    rc.origin.x += offx;
    rc.origin.y += offy;
    [self setFrame:rc];
}

- (void)moveToCenter:(CGPoint)pos {
    CGRect rc = self.frame;
    pos.x -= rc.size.width * .5f;
    pos.y -= rc.size.height * .5f;
    [self moveTo:pos];
}

- (void)moveRightTopTo:(CGPoint)pos {
    CGRect rc = self.frame;
    pos.x -= rc.size.width;
    [self moveTo:pos];
}

- (void)moveToRectCenter:(CGRect)rect {
    CGPoint pt = self.center;
    pt.x -= rect.size.width * .5f;
    pt.y -= rect.size.height * .5f;
    rect.origin = pt;
    [self setFrame:rect];
}

- (void)removeAllSubviews {
    for (UIView *each in self.subviews) {
        [each removeFromSuperview];
    }
}

- (UITearView*)tearHov:(NSInteger)pos spacing:(NSUInteger)height {
    UITearViewHov *tear = [[UITearViewHov alloc] initWith:pos spacing:height];
    tear.targetView = self;
    return [tear autorelease];
}

- (UITearView*)tearVec:(NSInteger)pos spacing:(NSUInteger)width {
    UITearViewVec *tear = [[UITearViewVec alloc] initWith:pos spacing:width];
    tear.targetView = self;
    return [tear autorelease];
}

- (void)freeze {
    self.userInteractionEnabled = NO;
}

- (void)thaw {
    self.userInteractionEnabled = YES;
}

- (CGPoint)clientCenter {
    CGRect rc = self.bounds;
    return CGRectCenterPoint(&rc);
}

- (CGRect)rectForLayout {
    return self.bounds;
}

- (CGRect)boundsForLayout {
    return self.bounds;
}

- (CGRect)boundingbox {
    CGRect rc = CGRectZero;
    for (UIView* each in self.subviews) {
        rc = CGRectUnion(rc, each.frame);
    }
    return rc;
}

- (CGRect)convertRectToLogic:(CGRect)rc {
    rc.origin = [self convertPointToLogic:rc.origin];
    rc.size = [self convertSizeToLogic:rc.size];
    return rc;
}

- (CGPoint)convertPointToLogic:(CGPoint)pt {
    CGAffineTransform af = self.transform;
    af = CGAffineTransformInvert(af);
    return CGPointApplyAffineTransform(pt, af);
}

- (CGSize)convertSizeToLogic:(CGSize)sz {
    CGAffineTransform af = self.transform;
    af = CGAffineTransformInvert(af);
    return CGSizeApplyAffineTransform(sz, af);
}

- (CGRect)convertRectToDevice:(CGRect)rc {
    rc.origin = [self convertPointToDevice:rc.origin];
    rc.size = [self convertSizeToDevice:rc.size];
    return rc;
}

- (CGPoint)convertPointToDevice:(CGPoint)pt {
    CGAffineTransform af = self.transform;
    //af = CGAffineTransformInvert(af);
    return CGPointApplyAffineTransform(pt, af);
}

- (CGSize)convertSizeToDevice:(CGSize)sz {
    CGAffineTransform af = self.transform;
    //af = CGAffineTransformInvert(af);
    return CGSizeApplyAffineTransform(sz, af);
}

- (void)setLogicFrame:(CGTransformRect)frame {
    self.transform = frame.transform;
    self.frame = frame.rect;
}

- (CGTransformRect)logicFrame {
    return CGTransformRectMake(self.frame,
                               self.transform);
}

- (void)setLogicBounds:(CGTransformRect)bounds {
    self.transform = bounds.transform;
    self.bounds = bounds.rect;
}

- (CGTransformRect)logicBounds {
    return CGTransformRectMake(self.bounds,
                               self.transform);
}

- (UIWindow*)window {
    UIView* obj = self.superview;
    while (obj)
    {
        if ([obj isKindOfClass:[UIWindow class]])
            return (UIWindow*)obj;
        obj = obj.superview;
    }
    return nil;
}

- (UIView*)root {
    UIView* obj = self.superview;
    UIView* cur = self;
    
    while (obj)
    {
        if ([obj isKindOfClass:[UIWindow class]])
            return cur;
        cur = obj;
        obj = obj.superview;
    }
    
    return nil;
}

@end

UIImage* UIConvertViewToImage(UIView *view) {
    UIGraphicsBeginImageContextWithOptions(view.bounds.size,
                                           view.opaque,
                                           [[UIScreen mainScreen] scale]);
    CGContextRef context = UIGraphicsGetCurrentContext();
    [view.layer renderInContext:context];
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return img;
}

UIImage* UIConvertViewToImageWithOptions(UIView *view, UIColor *backgroundColor) {
    UIGraphicsBeginImageContextWithOptions(view.bounds.size,
                                           view.opaque,
                                           [[UIScreen mainScreen] scale]);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, backgroundColor.CGColor);
    CGContextFillRect(context, view.bounds);
    [view.layer renderInContext:context];
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return img;
}

//static int __gs_global_event_count = 0;

void UIViewEmitGlobalEvent(signal_t signal, UIView* view, NSSet* touches, UIEvent* event) {
    /*
    if ([signal isEqualToString:kSignalTouchesBegin]) {
        ++__gs_global_event_count;
        if (__gs_global_event_count > 1)
            return;
    } else if ([signal isEqualToString:kSignalTouchesEnd]) {
        --__gs_global_event_count;
        if (__gs_global_event_count != 0)
            return;
    }
     */
    
    NNTUIObject *obj = [NNTUIObject shared];

    [obj emit_begin];
    
    // emit signal.
    NSTuple3 *tuple = [[NSTuple3 alloc] initWith:view v1:touches v2:event];
    [obj emit:signal result:tuple];
    [tuple release];
    
    [obj emit_end];
}

@implementation UIViewGlobalEvent

+ (NNTUIView*)getViewFrom:(NNTEventObj*)event {
    NSTuple3 *tuple = (NSTuple3*)event.result;
    return tuple.v0;
}

+ (NSSet*)getTouchesFrom:(NNTEventObj*)event {
    NSTuple3 *tuple = (NSTuple3*)event.result;
    return tuple.v1;
}

+ (UIEvent*)getEventFrom:(NNTEventObj*)event {
    NSTuple3 *tuple = (NSTuple3*)event.result;
    return tuple.v2;
}

@end

@implementation NNTUIView 

NNTOBJECT_IMPL_NOSIGNALS;

@synthesize sendGlobalEvent = _sendGlobalEvent;
@synthesize backgroundFill = _backgroundFill;
@synthesize orientation = _orientation;
@synthesize identity = _identity;
@synthesize needAssistantView = _needAssistantView;
@dynamic shouldAssistantView;
@synthesize funcAssistantView, blockAssistantView;
@synthesize subControllers = _subControllers;
@synthesize isPainting = _isPainting;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];

    _sendGlobalEvent = YES;
    _needAssistantView = NO;
    _isPainting = NO;
    _orientation = (UIInterfaceOrientation)UIDeviceOrientationUnknown;
    
    // set empty backgroud color.
    self.backgroundColor = [UIColor clearColor];
    
    return self;
}

+ (id)view:(CGRect)frame {
    return [[[NNTUIView alloc] initWithFrame:frame] autorelease];
}

- (void)dealloc {
    zero_release(_backgroundFill);
    zero_release(_identity);
    zero_release(_lock);
    zero_release(_subControllers);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalViewClicked)
    NNTEVENT_SIGNAL(kSignalFrameChanged)
    NNTEVENT_SIGNAL(kSignalBoundsChanged)
    NNTEVENT_SIGNAL(kSignalTouchesBegin)
    NNTEVENT_SIGNAL(kSignalTouchesCancel)
    NNTEVENT_SIGNAL(kSignalTouchesEnd)
    NNTEVENT_SIGNAL(kSignalTouchesMoved)
    NNTEVENT_SIGNAL(kSignalTouchesOffset)
    NNTEVENT_SIGNAL(kSignalPainting)
}

- (void)lockPosition {
    NNT_SYNCHRONIZED(self)
    ++__lockposition;
    NNT_SYNCHRONIZED_END
}

- (void)unlockPosition {
    NNT_SYNCHRONIZED(self)
    --__lockposition;
    NNT_SYNCHRONIZED_END
}

- (void)drawRect:(CGRect)rect {
    _isPainting = YES;
    
    // draw super.
    [super drawRect:rect];
    
    // get graphic.
    ::juice::cocoa::Graphics gra = ::juice::cocoa::Graphics::Current(rect);
    
    // draw background image.
    ::juice::cocoa::Fill fl(_backgroundFill);
    fl.fill(gra, gra.bounds());
    
    // draw other.
    gra.push_state();
    
    // draw push state.
    if (CGRectContainsPoint(rect, __gs_view_touchpoint)) {
        [self drawHighlight:rect ctx:gra];
    }
    
    // call other.
    [self paintRect:rect context:gra];
    
    // signal.
    [self emit:kSignalPainting];
    
    gra.pop_state();
    
    _isPainting = NO;
}

- (void)paintRect:(CGRect)rect context:(CGContextRef)ctx {
    PASS;
}

- (void)drawHighlight:(CGRect)rect ctx:(CGContextRef)ctx {
    PASS;
}

- (void)setFrame:(CGRect)frame {
    // check can't move.
    if (__lockposition > 0)
        return;
    
    // had changed.
    if (CGRectEqualToRect(self.frame, frame))
        return;
    
    // set.
    [super setFrame:frame];
    
    // signal.
    [self emit:kSignalFrameChanged data:&frame];
}

- (void)setBounds:(CGRect)bounds {
    // had changed.
    if (CGRectEqualToRect(self.bounds, bounds))
        return;
    
    // set.
    [super setBounds:bounds];
    
    // move assisant view.
    if (__assistant_view) {
        if ([__assistant_view isKindOfClass:[NSArray class]]) {
            for (UIView *each in (NSArray*)__assistant_view)
                each.frame = self.bounds;
        } else {
            __assistant_view.frame = self.bounds;
        }
    }
    
    // emit message.
    [self emit:kSignalBoundsChanged data:&bounds];
    
    // update layout.
    [self updateLayout:bounds];
}

- (void)scaleToBackgroundImage {
    if (_backgroundFill && [_backgroundFill isKindOfClass:[WCGFillImage class]]) {
        WCGFillImage* theFill = (WCGFillImage*)_backgroundFill;
        CGRect rc = self.frame;
        rc.size = theFill.image.size;
        self.frame = rc;
    }
}

- (void)lock {
    if (_lock == nil) {
        _lock = [[NNTNSLock alloc] init];
    }
    [_lock lock];
}

- (void)unlock {
    if (_lock == nil) {
        @throw [NSException exceptionWithName:@"lock-unlock" reason:@"lost lock action" userInfo:NULL];
    }
    [_lock unlock];
}

- (BOOL)tryLock {
    if (_lock == nil) {
        _lock = [[NNTNSLock alloc] init];
    }
    return [_lock tryLock];
}

- (void)didMoveToSuperview {
    if (self.needAssistantView && self.shouldAssistantView) {
        
        if (__assistant_view == nil)
            __assistant_view = [[self assistantView] retain];
# ifdef NNT_BLOCKS
        if (__assistant_view == nil && blockAssistantView)
            __assistant_view = [blockAssistantView(self) retain];
# endif
        if (__assistant_view == nil && funcAssistantView)
            __assistant_view = [(*funcAssistantView)(self) retain];
        
        if (__assistant_view) {
            UIView *tgt_view = nil;
            if ([__assistant_view isKindOfClass:[NSArray class]]) {
                tgt_view = [(NSArray*)__assistant_view objectAtIndex:0 null:nil];
            } else {
                tgt_view = __assistant_view;         
            }            
            
            if ([tgt_view supportSignalSlot]) {
                [tgt_view connect:kSignalViewClicked sel:@selector(act_assistant_clicked:) obj:self];
            }
            
            [self addSubview:tgt_view];
            [self bringSubviewToFront:tgt_view];
            tgt_view.frame = self.bounds;
        }
    }
}

- (void)act_assistant_clicked:(NNTEventObj*)obj {    
    UIView *view = (UIView*)obj.sender;           
    
    // show next view.
    if ([__assistant_view isKindOfClass:[NSArray class]]) {
        UIView *next = [(NSArray*)__assistant_view objectAtNext:view];
        if (next) {
            if ([next supportSignalSlot]) {
                [next connect:kSignalViewClicked sel:@selector(act_assistant_clicked:) obj:self];
            }
            
            [self addSubview:next];
            [self bringSubviewToFront:next];
            next.frame = self.bounds;
        } else {            
            zero_release(__assistant_view);
            self.shouldAssistantView = NO;
        }
    } else {       
        zero_release(__assistant_view);        
        self.shouldAssistantView = NO;
    }
    
    // remove pre view.
    [view removeFromSuperview]; 
}

- (BOOL)isLandscape {
    return UIDeviceOrientationIsLandscape(self.orientation);
}

- (BOOL)isPortrait {
    return UIDeviceOrientationIsPortrait(self.orientation);
}

# pragma mark view touch

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    __gs_view_waitingtouch = TRUE;  
    __gs_view_touchpoint = [[touches anyObject] locationInView:self];
    
    // global signal emit.
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesBegin, self, touches, event);
    
    // self signal emit.
    [self emit:kSignalTouchesBegin result:touches data:event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    // global signal emit.
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesMoved, self, touches, event);
    
    // self signal emit.
    [self emit:kSignalTouchesMoved result:touches data:event];
    
    // emit offset.
    CGPoint offset = [(UITouch*)[touches anyObject] offset];
    [self emit:kSignalTouchesOffset result:touches data:&offset];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    if (__gs_view_waitingtouch == NO)
        return;
    
    CGPoint pt = [[touches anyObject] locationInView:self];
    if (CGPointEqualWithPrecise(pt, __gs_view_touchpoint, kUITouchRadius)) {
        [self emit:kSignalViewClicked result:touches data:event];
    }
    
    // global signal emit.
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesEnd, self, touches, event);
    
    // self signal emit.
    [self emit:kSignalTouchesEnd result:touches data:event];
    
    __gs_view_touchpoint = kUITouchSky;
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    __gs_view_waitingtouch = NO;

    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesCancel, self, touches, event);
    [self emit:kSignalTouchesCancel result:touches data:event];
}

# pragma mark assistant

- (void)setShouldAssistantView:(BOOL)val {
    if (_identity == nil)
        return;
    NNTConfiguration *conf = [NNTConfiguration shared];
    NSString *key = [_identity stringByAppendingString:@"::assist::enable"];
    if (val) {
        [conf set:key val:@"1"];
    } else {
        [conf set:key val:@"0"];
    }
}

- (BOOL)shouldAssistantView {
    if (_identity == nil)
        return NO;
    NNTConfiguration *conf = [NNTConfiguration shared];
    NSString *key = [_identity stringByAppendingString:@"::assist::enable"];
    NSString *str = [conf get:key];
    if (str == nil)
        return YES;
    return [str isEqualToString:@"1"];
}

- (UIView*)assistantView {
    if (self.shouldAssistantView == NO)
        return nil;
    return nil;
}

- (void)setAssistantView:(UIView *)view {
    if (__assistant_view) {
        [__assistant_view removeFromSuperview];
    }
    [NSObject refobjSet:&__assistant_view obj:&view];
}

- (void)updateLayout:(CGRect)rect {
    PASS;
}

- (CGRect)extent {
    return self.frame;
}

- (void)setExtent:(CGRect)rc {
    self.frame = rc;
}

- (void)addSubController:(UIViewController*)ctlr {
    if (_subControllers &&
        [_subControllers indexOfObject:ctlr] != NSNotFound)
        return;
    
    if (_subControllers == nil)
        _subControllers = [[NSMutableArray alloc] init];
    
    // add view.
    UIView* view = ctlr.view;
    [self addSubview:view];
    
    // insert to contain.
    [(NSMutableArray*)_subControllers addObject:ctlr];
}

- (void)removeSubController:(UIViewController *)ctlr {
    if (_subControllers == nil ||
        [_subControllers indexOfObject:ctlr] == NSNotFound)
        return;
    
    [ctlr.view removeFromSuperview];
    
    [(NSMutableArray*)_subControllers removeObject:ctlr];
}

@end

@implementation _cxx_uiview_wrapper

@synthesize _cxxobj;

- (void)dealloc {
    if (_cxxobj)
        _cxxobj->destroy();
    [super dealloc];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    if (_cxxobj) {
        _cxxobj->layout_subviews();
        
        // adjust orientation.
        _cxxobj->layout_orientation(self.orientation);
    }
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    if (_cxxobj)
        _cxxobj->draw(UIGraphicsGetCurrentContext(), rect);
}

- (void*)object {
    return _cxxobj->cxxobject();
}

- (void)viewTheme:(UIView*)view changeTheme:(UITheme*)theme {
    _cxxobj->theme(::wsi::ui::Theme(theme));
}

@end

NNT_END_OBJC