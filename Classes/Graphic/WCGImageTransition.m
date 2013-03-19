
# import "Core.h"
# import "WCGImageTransition.h"
# import <QuartzCore/QuartzCore.h>

WSI_BEGIN_OBJC

const CFTimeInterval kWCGImageTransitionDefaultDuration = 1.f;

@interface WCGImageTransitionPrivate : NSObject {
    WCGImageTransition *d_owner;
    
# ifdef WSI_TARGET_IOS
    CADisplayLink *dl;
# endif
    
    CGImageRef image;
    CFTimeInterval timestamp;
}

@property (nonatomic, assign) WCGImageTransition *d_owner;

# ifdef WSI_TARGET_IOS
@property (nonatomic, retain) CADisplayLink *dl;
# endif

@property (nonatomic, assign) CGImageRef image;

- (void)pack;
- (void)unpack;

@end

@implementation WCGImageTransitionPrivate

@synthesize d_owner;

# ifdef WSI_TARGET_IOS
@synthesize dl;
# endif

@synthesize image;

- (id)init {
    self = [super init];
    
# ifdef WSI_TARGET_IOS
    dl = [[CADisplayLink displayLinkWithTarget:self selector:@selector(act_process)] retain];    
# endif
    
    return self;
}

- (void)dealloc {
    
# ifdef WSI_TARGET_IOS
    [dl release];
# endif
    
    if (image) {
        CGImageRelease(image);
    }
    [super dealloc];
}

- (void)pack {
    if (timestamp)
        return;
    timestamp = 0;
    d_owner.counter = 0;
    
    id<WCGImageTransitionDelegate> delegate = d_owner.delegate;
    if ([delegate respondsToSelector:@selector(imageTransitionBegin:)])
        [delegate imageTransitionBegin:d_owner];
    
# ifdef WSI_TARGET_IOS
    [dl addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
# endif
}

- (void)unpack {
    if (timestamp == 0)
        return;
    timestamp = 0;
    d_owner.counter = 0;        
    
# ifdef WSI_TARGET_IOS
    [dl removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
# endif
    
    id<WCGImageTransitionDelegate> delegate = d_owner.delegate;
    if ([delegate respondsToSelector:@selector(imageTransitionEnd:)])
        [delegate imageTransitionEnd:d_owner];
}

- (void)act_process {
    
# ifdef WSI_TARGET_IOS
    if (timestamp == 0)
        timestamp = dl.timestamp;
    if ((dl.timestamp - timestamp) > d_owner.duration) {
        [d_owner stop];
        return;
    }
# endif
    
    CGImageRef img_default = d_owner.image_default;
    
    CGSize sz_def = CGSizeMake(CGImageGetWidth(img_default), CGImageGetHeight(img_default));
    CGSize sz_tgt = sz_def;
    
    CGColorSpaceRef colorspace = CGImageGetColorSpace(img_default);
    uint percomp = (uint)CGImageGetBitsPerComponent(img_default);
    
    // get default pixels
    CGContextRef ctx_def = CGBitmapContextCreate(nil, 
                                                 sz_def.width, 
                                                 sz_def.height, 
                                                 percomp, 
                                                 0, 
                                                 colorspace, 
                                                 kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(ctx_def, CGRectMake(0, 0, sz_def.width, sz_def.height), img_default);
    argb_t const *pixs_def = CGBitmapContextGetData(ctx_def);
    
    CGContextRef ctx_tgt = CGBitmapContextCreate(nil,
                                                 sz_tgt.width, 
                                                 sz_tgt.height, 
                                                 percomp, 
                                                 0,
                                                 colorspace, 
                                                 kCGImageAlphaPremultipliedLast);
    argb_t *pixs_tgt = CGBitmapContextGetData(ctx_tgt);
    
    ulong const width_tgt = CGBitmapContextGetBytesPerRow(ctx_tgt) * 8 / CGBitmapContextGetBitsPerPixel(ctx_tgt);
    
    WCGImageTransitionLineOffset offset_l = d_owner.offset_left, offset_r = d_owner.offset_right;
    void *offset_context = d_owner.offset_context;
    uint counter = d_owner.counter;
    
    WCGImageTransitionLineOffsetParam param;
    param.counter = counter;
    param.ctx = offset_context;
    
# ifdef WSI_TARGET_IOS
    param.time = dl.timestamp - timestamp;
# endif
    
    param.velocity = d_owner.velocity;
    
    // process
    argb_t const* pix_def = pixs_def;
    argb_t *pix_tgt = pixs_tgt;    
    for (param.row = 0; param.row < sz_tgt.height; ++param.row) {
        (*d_owner.proc_line)(pix_tgt, pix_def, 
                             (*offset_l)(&param),
                             (*offset_r)(&param),
                             (uint)width_tgt);
        pix_tgt += width_tgt;
        pix_def += width_tgt;
    }
    
    // get image
    if (image) {
        CGImageRelease(image);
    }
    image = CGBitmapContextCreateImage(ctx_tgt);
    
    id<WCGImageTransitionDelegate> delegate = d_owner.delegate;
    if ([delegate respondsToSelector:@selector(imageTransition:image:param:)])
        [delegate imageTransition:d_owner image:image param:&param];
    
    // release
    CGContextRelease(ctx_def);
    CGContextRelease(ctx_tgt);
    
    // other
    ++d_owner.counter;
}

@end

@implementation WCGImageTransition

@dynamic image;
@synthesize image_default;
@synthesize proc_line;
@synthesize duration, frame_duration, fps;
@synthesize delegate;
@synthesize offset_left, offset_right, offset_context;
@synthesize counter;
@synthesize frame_interval;
@synthesize velocity;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WCGImageTransition);
    
    proc_line = (WCGImageTransitionLineProc)kARGBLineDoubleInsetProc;
    duration = kWCGImageTransitionDefaultDuration;
    offset_left = offset_right = kOffsetZero;
    
    return self;
}

- (id)initWithCGImage:(CGImageRef)__image {
    self = [self init];
    self.image_default = __image;
    return self;
}

- (void)dealloc {
    [self clear];
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)clear {
    if (image_default) {
        CGImageRelease(image_default);
        image_default = NULL;
    }
}

- (void)setImage_default:(CGImageRef)__image {
    CGImageRelease(image_default);
    image_default = __image;
    CGImageRetain(image_default);
}

- (void)start {
    [d_ptr pack];
}

- (void)stop {
    [d_ptr unpack];
}

- (CGImageRef)image {
    return d_ptr.image;
}

- (CFTimeInterval)frame_duration {
# ifdef WSI_TARGET_IOS
    return d_ptr.dl.duration;
# endif
    
    return 0;
}

- (real)fps {
# ifdef WSI_TARGET_IOS
    return 1 / d_ptr.dl.duration;
# endif
    
    return 0;
}

- (void)setFrame_interval:(NSInteger)__frame_interval {
    frame_interval = __frame_interval;
    
# ifdef WSI_TARGET_IOS
    d_ptr.dl.frameInterval = __frame_interval;
# endif
}

@end

void kARGBLineDoubleInsetProc(argb_t* des, argb_t const* src, int left, int right, uint len) {
    real u = (len - left - right) / (real)len;
    for (int i = left; i < len - right; ++i) {
        int x0 = (i - left) / u;
        argb_t v0 = (argb_t)ARGB_MUL(src[x0].v, 1 - u);
        argb_t v1 = (argb_t)ARGB_MUL(src[x0 + 1].v, u);
        des[i].v = ARGB_ADD_ARGB(v0.v, v1.v);
    }
}

int kOffsetZero(WCGImageTransitionLineOffsetParam* param) {
    return 0;
}

WSI_END_OBJC