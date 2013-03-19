
# import "Core.h"
# import "QzEffect.h"

NNT_BEGIN_OBJC

NSTimeInterval kQzEffectDuration = 0.35f;
signal_t kSignalEffectComplete = @"::nnt::ui::effect::complete";

@interface QzEffect ()

@property (nonatomic, retain) CALayer* layer;

@end

@implementation QzEffect

@synthesize layer = _layer;
@synthesize duration = _duration;
@synthesize next = _next, accord = _accord;
@synthesize repeat = _repeat, reverse = _reverse;
@synthesize recur = _recur;

- (id)init {
    self = [super init];
    
    _duration = kQzEffectDuration;
    _repeat = 0;
    _reverse = NO;
    _recur = 0;
    
    return self;
}

- (void)dealloc {
    safe_release(_layer);
    safe_release(_next);
    safe_release(_accord);
    
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalEffectComplete)
NNTEVENT_END

- (void)active:(CALayer *)layer {
    // set in layer.
    self.layer = layer;
    
    // prepare before animate.
    [self prepare];
    
    // begin animate.
    [self begin];
    
    // animating.
    [self active];
    
    // end animating.
    [self end];
}

- (void)activeInView:(UIView *)view {
    [self active:view.layer];
}

- (void)prepare {
    _accord.layer = self.layer;
    [_accord prepare];
}

- (void)begin {
    [self retain];
    
    // begin ani.
    [UIView beginAnimations:nil context:self];
}

- (void)active {    
    [_accord active];
}

- (void)end {
    // commit ani.
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(_act_complete)];
    
    [UIView setAnimationDuration:_duration];
    if (_repeat)
        [UIView setAnimationRepeatCount:_repeat];
    if (_reverse)
        [UIView setAnimationRepeatAutoreverses:_reverse];
    
    [UIView commitAnimations];
}

- (void)_act_complete {
    bool complete = true;
    
    // run next.
    if (_next) {
        [_next active:_layer];
    }
    
    // repeat ?
    if (_recur != 0) {
        if (_recur != -1)
            --_recur;
        [self active:_layer];
        complete = false;
    } else {
        complete &= true;
    }
    
    if (complete == false)
        return;
    
    // signal.
    [self emit:kSignalEffectComplete];
    
    // free memory.
    [self release];
}

@end

NNTIMPL_OBJCXX_WRAPPER_BEGIN(QzEffect)

- (void)active:(CALayer *)layer {
    [super active:layer];
    
    if (self._cxxobj) {
        ::nnt::use< ::nnt::qz::tpl::IEffect> obj(self._cxxobj);
        obj->active(layer);
    }
}

- (void)prepare {
    [super prepare];
    
    if (self._cxxobj) {
        ::nnt::use< ::nnt::qz::tpl::IEffect> obj(self._cxxobj);
        obj->prepare();
    }
}

- (void)begin {
    [super begin];
    
    if (self._cxxobj) {
        ::nnt::use< ::nnt::qz::tpl::IEffect> obj(self._cxxobj);
        obj->begin();
    }
}

- (void)active {
    [super active];
    
    if (self._cxxobj) {
        ::nnt::use< ::nnt::qz::tpl::IEffect> obj(self._cxxobj);
        obj->active();
    }
}

- (void)end {
    [super end];
    
    if (self._cxxobj) {
        ::nnt::use< ::nnt::qz::tpl::IEffect> obj(self._cxxobj);
        obj->end();
    }
}

NNTIMPL_OBJCXX_WRAPPER_END

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(qz)

NNT_BEGIN_NS(effect)

Fadein::Fadein()
: from(0), to(1)
{
    
}

void Fadein::prepare()
{
    _layer().opacity = from;
}

void Fadein::active()
{
    _layer().opacity = to;
}

Fadeout::Fadeout()
{
    from = 1;
    to = 0;
}

Shadow::Shadow()
{
    from.set_opacity(0);
}

void Shadow::prepare()
{
    from.apply(_layer());
}

void Shadow::active()
{
    to.apply(_layer());
}

Scale::Scale()
{
    from = 1;
    to = 1.2f;
}

void Scale::prepare()
{
    _layer().transform = CATransform3DMakeScale(from, from, from);
}

void Scale::active()
{
    _layer().transform = CATransform3DMakeScale(to, to, to);
}

Tremble::Tremble()
: _now(0)
{
    range = .1f;
    rand = true;
    set_duration(.05f);
}

Tremble::~Tremble()
{
    stop();
}

void Tremble::prepare()
{
    if (_now == 0)
    {
        _now = M_PI * range;
        _mat = _layer().transform;
    }
    else
    {
        if (_now > 0)
            _now = -M_PI * range;
        else
            _now = M_PI * range;
    }
    
    _now *= rand01();
}

void Tremble::active()
{
    _layer().transform = CATransform3DMakeRotation(_now, 1, 1, 1);
}

void Tremble::start()
{
    set_recur(-1);
}

void Tremble::stop()
{
    set_recur(0);
    
    _layer().transform = _mat;
}

Translation::Translation()
{
    
}

void Translation::prepare()
{
    if (from == cg::Point::Zero() &&
        to == cg::Point::Zero())
    {
        from = to = _layer().frame.origin;
    }
    
    [_layer() moveTo:from];
}

void Translation::active()
{
    [_layer() moveTo:to];
}

Slide::Slide()
: in(true)
{
    
}

void Slide::prepare()
{
    super::prepare();
    
    if (in)
    {
        switch (direction)
        {
            case LEFT:
            {
                from.x -= _layer().frame.size.width;
            } break;
            case RIGHT:
            {
                from.x += _layer().frame.size.width;
            } break;
            case TOP:
            {
                from.y -= _layer().frame.size.height;
            } break;
            case BOTTOM:
            {
                from.y += _layer().frame.size.height;
            } break;
        }
        
        [_layer() moveTo:from];
    }
    else
    {
        switch (direction)
        {
            case LEFT:
            {
                to.x -= _layer().frame.size.width;
            } break;
            case RIGHT:
            {
                to.x += _layer().frame.size.width;
            } break;
            case TOP:
            {
                to.y -= _layer().frame.size.height;
            } break;
            case BOTTOM:
            {
                to.y += _layer().frame.size.height;
            } break;
        }
    }
}

Popout::Popout()
{
    
}

void Popout::prepare()
{
    _layer().transform = CATransform3DMakeScale(.8f, .8f, .8f);
}

void Popout::active()
{
    _layer().transform = CATransform3DMakeScale(1.f, 1.f, 1.f);
}

Popin::Popin()
{
    
}

void Popin::prepare()
{
    _layer().transform = CATransform3DMakeScale(1.2f, 1.2f, 1.2f);
    _layer().opacity = 0;
}

void Popin::active()
{
    _layer().transform = CATransform3DMakeScale(1.f, 1.f, 1.f);
    _layer().opacity = 1.f;
}

NNT_END_NS

NNT_END_NS
NNT_END_CXX
