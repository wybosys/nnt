
# import "Core.h"
# import "UINavigationBar+NNT.h"
# import "UINavigationController+NNT.h"
# import "NGFill.h"

NNT_BEGIN_CXX

// objc swizzle.
class Swizzle_UINavigationBar
{
public:
    
    Swizzle_UINavigationBar()
    {
        // init.
        layout.cls = [UINavigationBar class];
        layout.default_impl = class_getImplementation(layout.cls, @selector(layoutSubviews));
        layout.next_impl = class_getImplementation(layout.cls, @selector(layoutSubviewsAndUpdateTabbar));
        
        // replace method.
        class_swizzleMethod(layout.cls, @selector(layoutSubviews), @selector(layoutSubviewsAndUpdateTabbar));
    }
    
    objc_swizzle_t layout;
    
};

static Swizzle_UINavigationBar __gs_swizzle_UINavigationBar;

NNT_END_CXX

NNT_BEGIN_OBJC

/*
 not entering.
@implementation UINavigationBar (UIViewRendering)

- (void)drawRect:(CGRect)rect {
    
}

@end
 */

@implementation CANavigationBarFillLayer

@synthesize fill;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(fill);
    [super dealloc];
}

- (void)drawInContext:(CGContextRef)ctx {
    CGRect rc = self.bounds;
    [fill fillRect:rc inContext:ctx];
}

@end

@implementation UINavigationBar (NNT)

/*
- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];    
    [self updateTabBar];
}
 */

/*
- (void)setBounds:(CGRect)bounds {
    [super setBounds:bounds];    
    [self updateTabBar];
}
 */

- (void)layoutSubviewsAndUpdateTabbar {
    (::nnt::__gs_swizzle_UINavigationBar.layout.default_impl)(self, nil);
    
    [self updateTabBar];
}

- (void)updateTabBar {
    CANavigationBarFillLayer* layer = nil;
    for (CALayer* each in self.layer.sublayers) {
        if ([each isKindOfClass:[CANavigationBarFillLayer class]]) {
            layer = (CANavigationBarFillLayer*)each;
            break;
        }
    }
    
    if (layer == nil)
        return;
    
    static int __gs_index = ([[UIDevice currentDevice].systemVersion doubleValue] >= 5.0) ? 1 : 0;
    
    CGRect rc = self.layer.bounds;
    layer.frame = rc;
    [layer retain];
    [layer removeFromSuperlayer];
    [self.layer insertSublayer:layer atIndex:__gs_index];
    [layer release];
    [layer setNeedsDisplay];
}

@end

@implementation NNTUINavigationItem

NNTOBJECT_IMPL;

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

@end

NNTIMPL_CATEGORY(UINavigationBar, NNT);

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ui)

void NavigationBar::set_background(cg::Fill const& fill)
{
    (**_ctlr).topbarBackgroundFill = fill;
}

NNT_END_NS
NNT_END_CXX