
# import "Core.h"
# import "CorePlot+NNT.h"

NNT_BEGIN

@implementation CPGraphHostingView (NNT)

@end

@interface UICPGraphHostingViewPrivate : NSObject {
    UICPGraphHostingView *d_owner;
    
    BOOL _allowTap;
    UITapGestureRecognizer *rgr_tap;
}

@property (nonatomic, assign) UICPGraphHostingView *d_owner;
@property (nonatomic, setter=_setAllowTap:) BOOL allowTap;
@property (nonatomic, retain) UITapGestureRecognizer *rgr_tap;

@end

@implementation UICPGraphHostingViewPrivate

@synthesize d_owner;
@synthesize allowTap = _allowTap;
@synthesize rgr_tap;

- (id)init {
    self = [super init];
    _allowTap = NO;
    return self;
}

- (void)dealloc {
    [rgr_tap release];
    [super dealloc];
}

- (void)_setAllowTap:(BOOL)__b {
    if (_allowTap == __b) return;
    _allowTap = __b;
    
    if (rgr_tap) {
        [d_owner removeGestureRecognizer:self.rgr_tap];
        self.rgr_tap = nil;
    } else {
        rgr_tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleTap:)];
        [d_owner addGestureRecognizer:self.rgr_tap];
    }
}

# pragma mark -
# pragma mark tap gesture

- (void)handleTap:(UITapGestureRecognizer *)sender {
    
}

@end

@implementation UICPGraphHostingView

@dynamic allowTap;
@synthesize backgroundImage;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(UICPGraphHostingView);
    
    self.allowTap = NO;
    self.backgroundColor = [UIColor clearColor];
    
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    
    [backgroundImage release];
    
    [super dealloc];
}

- (BOOL)getAllowTap {
    return d_ptr.allowTap;
}

- (void)setAllowTap:(BOOL)__allowTap {
    d_ptr.allowTap = __allowTap;
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSaveGState(context);
    
    if (backgroundImage) {
        [backgroundImage drawInRect:rect];
    }
    
    CGContextRestoreGState(context);
}

@end

NNT_END