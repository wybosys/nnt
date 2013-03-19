
# import "Core.h"
# import "UIImageDesktop.h"
# import "UIImageView+WSI.h"
# import "UIButton+WSI.h"

WSI_BEGIN_OBJC

@interface UIImageDesktop ()

- (void)__init;

@end

@implementation UIImageDesktop

@synthesize imageView;
@synthesize padding;
@synthesize isMoving;
@synthesize showClose, buttonClose;

- (void)__init {
    padding = CGPaddingMake(.2f, .2f, .05f, .05f);
    
    _gesrec = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(act_scale:)];
    [self addGestureRecognizer:_gesrec];
    
    self.showClose = YES;
}

- (id)init {
    self = [super init];
    
    WSIUIImageView *img = [[WSIUIImageView alloc] init];
    self.imageView = img;
    [img release];
    
    [img connect:kSignalImageChanged sel:@selector(act_imageloaded:) obj:self];

    [self __init];
    return self;
}

- (id)initWithImage:(UIImage *)image {
    self = [super init];
    
    WSIUIImageView *img = [[WSIUIImageView alloc] initWithImage:image];
    self.imageView = img;
    [img release];
    
    [img connect:kSignalImageChanged sel:@selector(act_imageloaded:) obj:self];
    
    [self __init];    
    return self;
}

- (id)initWithURL:(NSURL *)url cache:(BOOL)cache {
    self = [super init];
    
    WSIUIImageView *img = [[WSIUIImageView alloc] initWithURL:url cache:cache];
    self.imageView = img;
    [img release];
    
    [img connect:kSignalImageChanged sel:@selector(act_imageloaded:) obj:self];
    
    [self __init];    
    return self;
}

- (void)dealloc {
    zero_release(imageView);
    zero_release(_gesrec);
    zero_release(buttonClose);
    [super dealloc];
}

- (void)setShowClose:(BOOL)val {
    if (showClose == val)
        return;
    showClose = val;
    
    if (buttonClose == nil) {
        buttonClose = [[UIButtonClose alloc] initWithZero];
        [buttonClose connect:kSignalButtonClicked sel:@selector(close) obj:self];
        [self addSubview:buttonClose];
    }
    
    if (showClose) {
        buttonClose.hidden = NO;
    } else {
        buttonClose.hidden = YES;
    }
}

- (CGRect)contentFrame {
    if ([self.subviews count] == 0)
        return CGRectZero;
    return imageView.frame;
}

- (NSArray*)contentViews {
    NSMutableArray* arr = [NSMutableArray array];
    [arr addObject:self.imageView];
    return arr;
}

- (void)setImageView:(WSIUIImageView *)__imageView {
    [imageView removeFromSuperview];
    imageView = [__imageView retain];
    imageView.userInteractionEnabled = NO;
    [self addSubview:imageView];
    
    [imageView connect:kSignalImageChanged sel:@selector(act_imageloaded:) obj:self];
}

- (void)centerImage {
    CGRect desk = self.bounds;
    [imageView moveToCenter:CGRectCenterPoint(&desk)];
}

- (void)act_imageloaded:(WSIEventObj*)obj {
    WSIUIImageView *view = (WSIUIImageView*)obj.sender;
    
    CGRect desk = self.bounds;
    CGRect image = CGRectMakeSz(view.image.size);
    CGRect rc = CGRectZero;
    
    real offset_w = desk.size.width * (padding.left + padding.right);
    real offset_h = desk.size.height * (padding.top + padding.bottom);

    rc.size.width = MIN(desk.size.width - offset_w, image.size.width);
    rc.size.height = MIN(desk.size.height - offset_h, image.size.height);
    
    real ratio = image.size.width / (real)image.size.height;
    if (rc.size.width < rc.size.height) {
        rc.size.height = rc.size.width / ratio;
    } else if (rc.size.width >= rc.size.height) {
        rc.size.width = ratio * rc.size.height;
    }
    
    view.frame = rc;
    [view moveToCenter:CGRectCenterPoint(&desk)];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)__event {
    if ([touches count] > 1) {
        [super touchesBegan:touches withEvent:__event];
        return;
    }
    
    if (!isMoving) {
        _pt_moving = [[touches anyObject] locationInView:self];
        isMoving = [self hitTestInContent:_pt_moving];
    }
    
    [super touchesBegan:touches withEvent:__event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)__event {
    if ([touches count] > 1) {
        [super touchesMoved:touches withEvent:__event];
        return;
    }
    
    if (isMoving) {
        CGPoint pt = [[touches anyObject] locationInView:self];
        real dx = pt.x - _pt_moving.x;
        real dy = pt.y - _pt_moving.y;
        
        CGRect rc = imageView.frame;
        rc.origin.x += dx;
        rc.origin.y += dy;
        imageView.frame = rc;
    
        _pt_moving = pt;
    }
    
    [super touchesMoved:touches withEvent:__event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)__event {
    isMoving = NO;
    
    if ([touches count] > 1) {
        [super touchesEnded:touches withEvent:__event];
        return;
    }        
    
    [super touchesEnded:touches withEvent:__event];
}

- (void)act_scale:(UIPinchGestureRecognizer*)ges {
    isMoving = NO;
    
    if (ges.state == UIGestureRecognizerStateBegan) {
        _origin_rc = imageView.frame;
    }
    
    if (ges.state == UIGestureRecognizerStateChanged) {
        CGRect rc = _origin_rc;
        real dx = rc.size.width * (ges.scale - 1);
        real dy = rc.size.height * (ges.scale - 1);
        rc.size.width += dx;
        rc.size.height += dy;
        rc.origin.x -= dx * .5f;
        rc.origin.y -= dy * .5f;
        imageView.frame = rc;
    }
    
}

- (void)layoutSubviews {
    CGRect rc_client = self.bounds;
    CGPoint rt = CGRectRightTop(&rc_client);
    
    rt.y += 20;
    [buttonClose moveRightTopTo:rt];
}

@end

WSI_END_OBJC