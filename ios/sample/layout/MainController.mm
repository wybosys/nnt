
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN_OBJC

@class NntLayout;
@class NntVBoxLayout;
@class NntHBoxLayout;

@interface NntLinear : NSObject {
    int _full, _relv;
    NSMutableArray* _segs;
    bool _changed;
    int _iter;
    bool _priority;
}

+ (id)linearWithLayout:(NntLayout*)layout;

- (id)initWithLayout:(NntLayout*)layout;
- (id)initWithVBoxLayout:(NntVBoxLayout*)layout;
- (id)initWithHBoxLayout:(NntHBoxLayout*)layout;

- (id)addFlex:(real)flex;
- (id)addPixel:(real)pixel;

- (BOOL)started;
- (real)start;
- (real)next;
- (real)prev;

@end

@interface NntLayout : NSObject {
    CGRect _rc_origin, _rc_work;
    real _offset_x, _offset_y;
    CGMargin _margin;
    CGPadding _padding;
    real _space;
}

@property (nonatomic, readonly) CGRect rect;

- (id)initWithRect:(CGRect)rc withSpacing:(real)space;
- (void)reset;
- (CGRect)addLinear:(NntLinear*)lnr;
- (CGRect)stridePixel:(real)pixel;

@end

@interface NntVBoxLayout : NntLayout

+ (id)layoutWithRect:(CGRect)rc withSpacing:(real)space;

@end

@interface NntHBoxLayout : NntLayout

+ (id)layoutWithRect:(CGRect)rc withSpacing:(real)space;

@end

@implementation NntLayout

@dynamic rect;

- (id)initWithRect:(CGRect)rc withSpacing:(real)space {
    self = [super init];
    
    [self reset];
    
    if (space == 0)
    {
        _margin = CGMarginZero;
        _padding = CGPaddingZero;
        _rc_origin = _rc_work = rc;
    }
    else
    {
        [self setSpace:space];
        [self setOriginRect:rc];
    }
    
    return self;
}

- (CGRect)rect {
    return _rc_work;
}

- (void)reset {
    _offset_x = _offset_y = 0;
    _rc_work = _rc_origin;
}

- (void)setSpace:(real)v {
    _padding = CGPaddingMake(v, 0, v, 0);
    _margin = CGMarginMake(0, v, 0, v);
}

- (void)setOriginRect:(CGRect)rc {
    _rc_origin = _rc_work = rc;
    
    // offset rect.
    if (CGPaddingEqualToPadding(_padding, CGPaddingZero) == false)
    {
        _rc_work.origin.x += _padding.left;
        _rc_work.origin.y += _padding.top;
        _rc_work.size.width -= CGPaddingGetWidth(&_padding);
        _rc_work.size.height -= CGPaddingGetHeight(&_padding);
    }
}

- (CGRect)addLinear:(NntLinear *)lnr {
    real pix = lnr.started ? lnr.next : lnr.start;
    return [self stridePixel:pix];
}

- (CGRect)stridePixel:(real)pixel {
    return CGRectZero;
}

@end

@implementation NntVBoxLayout

+ (id)layoutWithRect:(CGRect)rc withSpacing:(real)space {
    return [[[NntVBoxLayout alloc] initWithRect:rc withSpacing:space] autorelease];
}

- (CGRect)stridePixel:(real)pixel {
    CGRect ret;
    int height = pixel;
    _offset_y += height;
    ret.origin.x = _rc_work.origin.x + _margin.left;
    ret.origin.y = _rc_work.origin.y + _margin.top;
    _rc_work.origin.y += height;
    ret.size.width = _rc_work.size.width - _margin.left - _margin.right;
    ret.size.height = height - _margin.top - _margin.bottom;
    return ret;
}

@end

@implementation NntHBoxLayout

+ (id)layoutWithRect:(CGRect)rc withSpacing:(real)space {
    return [[[NntHBoxLayout alloc] initWithRect:rc withSpacing:space] autorelease];
}

- (CGRect)stridePixel:(real)pixel {
    CGRect ret;
    int width = pixel;
    _offset_x += width;
    ret.origin.x = _rc_work.origin.x + _margin.left;
    ret.origin.y = _rc_work.origin.y + _margin.top;
    _rc_work.origin.x += width;
    ret.size.width = width - _margin.left - _margin.right;
    ret.size.height = _rc_work.size.height - _margin.top - _margin.bottom;
    return ret;
}

@end

@interface NntLinearSegment : NSObject {
    @public

    bool ispixel;
    union {
        real pixel;
        real flex;
    } value;
    real result;
    void *ctx;
}

@end

@implementation NntLinearSegment

@end

@implementation NntLinear

+ (id)linearWithLayout:(NntLayout *)layout {
    return [[[NntLinear alloc] initWithLayout:layout] autorelease];
}

- (id)init {
    self = [super init];
    
    _segs = [[NSMutableArray alloc] init];
    
    return self;
}

- (void)dealloc {
    [_segs release];
    [super dealloc];
}

- (id)initWithLayout:(NntLayout *)layout {
    if ([layout isKindOfClass:[NntVBoxLayout class]])
        return [self initWithVBoxLayout:(NntVBoxLayout*)layout];
    return [self initWithHBoxLayout:(NntHBoxLayout*)layout];
}

- (id)initWithVBoxLayout:(NntVBoxLayout*)layout {
    self = [self init];
    
    _changed = NO;
    _iter = NSNotFound;
    _priority = NO;
    _full = layout.rect.size.height;
    _relv = layout.rect.size.width;
    
    return self;
}

- (id)initWithHBoxLayout:(NntHBoxLayout*)layout {
    self = [self init];
    
    _changed = NO;
    _iter = NSNotFound;
    _priority = YES;
    _full = layout.rect.size.width;
    _relv = layout.rect.size.height;
    
    return self;
}

- (id)addFlex:(real)flex {
    _changed = true;
    
    NntLinearSegment* value = [[NntLinearSegment alloc] init];
    value->ispixel = false;
    value->value.flex = flex;
    value->result = 0;
    value->ctx = 0;
    [_segs addObject:value];
    [value release];
    
    return self;
}

- (id)addPixel:(real)pixel {
    _changed = true;
    
    NntLinearSegment* value = [[NntLinearSegment alloc] init];
    value->ispixel = true;
    value->value.pixel = pixel;
    value->result = 0;
    value->ctx = 0;
    [_segs addObject:value];
    [value release];
    
    return self;
}

- (id)addWharWidth:(real)width withHeight:(real)height {
    real pix;
    if (_priority)
        pix = _relv * (width / height);
    else
        pix = _relv * (height / width);
    [self addPixel:pix];
    return self;
}

- (BOOL)started {
    return _iter != NSNotFound;
}

- (void)recalc {
    if (_changed == false)
        return;
    _changed = false;
    
    real sum_pix = 0;
    real sum_flex = 0;
    
    for (NntLinearSegment* each in _segs)
    {
        if (each->ispixel)
            sum_pix += each->value.pixel;
        else
            sum_flex += each->value.flex;
    }
    
    sum_flex = sum_flex ? sum_flex : 1;
    
    real full_flex = _full - sum_pix;
    real each_flex = full_flex / sum_flex;
    
    for (NntLinearSegment* each in _segs)
    {
        if (each->ispixel)
            each->result = each->value.pixel;
        else
            each->result = each->value.flex * each_flex;
    }
}

- (real)start {
    [self recalc];
    
    _iter = 0;
    NntLinearSegment* seg = [_segs objectAtIndex:_iter];
    return seg->result;
}

- (real)next {
    ++_iter;
    NntLinearSegment* seg = [_segs objectAtIndex:_iter];
    return seg->result;
}

- (real)prev {
    --_iter;
    NntLinearSegment* seg = [_segs objectAtIndex:_iter];
    return seg->result;
}

@end

NNTAPP_END_OBJC

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Gray());
    
    add_sub(r0);
    add_sub(r1);
    add_sub(r2);
    
    r0.set_background(ui::Color::Red());
    r1.set_background(ui::Color::Green());
    r2.set_background(ui::Color::Blue());
}

void MainView::layout_subviews()
{
    /*
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    
    CGRectLayoutHBox lytr(lyt << lnr);
    CGRectLayoutLinear lnrr(lytr);
    lnrr << (flex)1 << whar(16, 9) << (flex)1;
    r0.set_frame(lytr << lnrr);
    r1.set_frame(lytr << lnrr);
    r2.set_frame(lytr << lnrr);
     */
    
    NntVBoxLayout* lyt = [NntVBoxLayout layoutWithRect:bounds() withSpacing:0];
    NntLinear* lnr = [NntLinear linearWithLayout:lyt];
    [[[lnr addFlex:1] addFlex:1] addFlex:1];
    
    [lyt addLinear:lnr];
    NntHBoxLayout* lytr = [NntHBoxLayout layoutWithRect:[lyt addLinear:lnr] withSpacing:0];
    NntLinear* lnrr = [NntLinear linearWithLayout:lytr];
    [[[lnrr addFlex:1] addWharWidth:16 withHeight:9] addFlex:1];
    
    r0.set_frame([lytr addLinear:lnrr]);
    r1.set_frame([lytr addLinear:lnrr]);
    r2.set_frame([lytr addLinear:lnrr]);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

NNTAPP_END
