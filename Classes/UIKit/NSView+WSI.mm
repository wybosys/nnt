
# import "Core.h"
# import "NSView+NNT.h"
# import "Graphic+NNT.h"

NNT_BEGIN_OBJC

@implementation NSView (NNT)

- (id)initWithZero {
    self = [self initWithFrame:NSZeroRect];
    return self;
}

- (void)moveToCenter:(NSPoint)pos {
    NSRect rc = self.frame;
    pos.x -= rc.size.width * .5f;
    pos.y -= rc.size.height * .5f;
    [self moveTo:pos];
}

- (void)moveTo:(NSPoint)pos {
    NSRect rc = self.frame;
    rc.origin = pos;
    [self setFrame:rc];
}

@end

@implementation NNTNSView

@synthesize backgroundFill;

NNTOBJECT_IMPL;

- (void)dealloc {
    [backgroundFill release];
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect {
    CGContextRef ctx = NgGetCurrentContext();
    
    if (backgroundFill) {
        [backgroundFill fillRect: ::nnt::cg::conv(dirtyRect)
                       inContext:ctx];
    }
}

- (void)resizeSubviewsWithOldSize:(NSSize)oldBoundsSize {    
    [self layoutSubviews];
}

- (void)layoutSubviews {
    PASS;
}

@end

@implementation _cxx_nsview_wrapper

@synthesize _cxxobj;

- (void)dealloc {
    if (_cxxobj)
        _cxxobj->Destroy();
    [super dealloc];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    if (_cxxobj)
        _cxxobj->layout_subviews();
}

- (void)drawRect:(NSRect)rect {
    [super drawRect:rect];
    
    if (_cxxobj)
        _cxxobj->draw(NgGetCurrentContext(), rect);
}

- (void*)object {
    return _cxxobj->cxxobject();
}

@end

NNT_END_OBJC
