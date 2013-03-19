
# import "Core.h"
# import "CGStyle.h"

NNT_BEGIN_OBJC

@implementation NgStyle

@synthesize previous = _previous, next = _next;
@synthesize fillable, strokable;

- (id)init {
    self = [super init];
    
    fillable = YES;
    strokable = NO;
    
    return self;
}

- (void)drawInContext:(NgStyleContext*)ctx {
    [_next drawInContext:ctx];
}

- (void)break_previous_next {
    if (_previous)
        _previous.next = _next;
    if (_next)
        _next.previous = _previous;
    _previous = _next = nil;
}

@end

@implementation NgShapeStyle

@synthesize shape = _shape;

- (void)dealloc {
    zero_release(_shape);
    [super dealloc];
}

- (void)drawInContext:(NgStyleContext*)ctx {
    _shape.context = ctx.context;
    [_shape addToPath:ctx.bounds];
    _shape.context = nil;
    
    ctx.shape = _shape;
    [_next drawInContext:ctx];
}

@end

@implementation NgFillStyle

@synthesize fill = _fill;

- (id)init {
    self = [super init];
    fillable = NO;
    strokable = NO;
    return self;
}

- (void)dealloc {
    zero_release(_fill);
    [super dealloc];
}

- (void)drawInContext:(NgStyleContext*)ctx {
    if (_previous && _previous.strokable) {
        [_fill fillPathInContext:ctx.context];
        [_next drawInContext:ctx];
        return;
    } else if (_previous && _previous.fillable) {
        [_fill fillPathInContext:ctx.context];
        [_next drawInContext:ctx];
        return;
    }
    
    [_fill fillRect:ctx.bounds inContext:ctx.context];   
    [_next drawInContext:ctx];
}

@end

@implementation NgStyleSheet

@synthesize styles = _styles;

- (id)init {
    self = [super init];
    
    _styles = [[NSMutableDictionary alloc] init];
    _root = nil;

    return self;
}

- (void)dealloc {
    zero_release(_styles);
    [super dealloc];
}

- (void)addStyle:(NgStyle*)style forKey:(NSString*)key {        
    // over.
    NgStyle* tstyle = (NgStyle*)[_styles objectForKey:key];
    if (tstyle) {
        style.previous = tstyle.previous;
        style.next = tstyle.next;
        if (style.previous)
            style.previous.next = style;
        if (style.next)
            style.next.previous = style;
    }    
    else
    {
        if (_last) {
            _last.next = style;
            style.previous = _last;
        }
        _last = style;
    }
    
    [_styles setObject:style forKey:key];
    
    if (_root == nil || _root == tstyle)
        _root = style;
    if (_last == nil || _last == tstyle)
        _last = style;
}

- (id)styleForKey:(NSString*)key {
    return [_styles objectForKey:key];
}

- (void)removeStyleForKey:(NSString*)key {
    NgStyle* style = (NgStyle*)[_styles objectForKey:key];
    if (style == _root) {
        _root = style.next;
        if (style == _last)
            _last = style.previous;
    }
    else if (style == _last)
        _last = style.previous;
    
    [style break_previous_next];
    
    [_styles removeObjectForKey:key];    
}

- (void)clear {
    [_styles removeAllObjects];
    _root = _last = nil;
}

- (void)drawInContext:(CGContextRef)ctx inRect:(CGRect)rect {
    CGContextSaveGState(ctx);

    NgStyleContext* context = [[NgStyleContext alloc] init];
    context.context = ctx;
    context.bounds = rect;
    [_root drawInContext:context];
    safe_release(context);
                
    CGContextRestoreGState(ctx);
}

@end

NNT_END_OBJC