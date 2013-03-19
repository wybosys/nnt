
# import "Core.h"
# import "UICoverFlow.h"
# import "UICoverFlowItem.h"
# import "UIImageDesktop.h"
# import "UIImageView+WSI.h"
# import "Layout.h"

WSI_BEGIN_OBJC

real kCoverFlowItemFractionReflection = 0.61f;

@implementation UICoverFlowItem

@synthesize fractionReflection = _fractionReflection;
@synthesize imageView = _imageView, reflectionImageView = _reflectionImageView;
@synthesize number = _number;
@synthesize spaceImage = _spaceImage;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.opaque = YES;
    
    _spaceImage = 0;
    _fractionReflection = kCoverFlowItemFractionReflection;
    
    // Image View
    _imageView = [[WSIUIImageView alloc] initWithFrame:self.bounds];
    _reflectionImageView = [[WSIUIImageView alloc] initWithZero];
    
    _imageView.userInteractionEnabled = NO;
    _reflectionImageView.userInteractionEnabled = NO;
    
    _imageView.opaque = YES;
    _reflectionImageView.opaque = YES;
    
    [self addSubview:_imageView];
    [self addSubview:_reflectionImageView];
    
    // while image view changed, make reflection and set cover image.
    [_imageView connect:kSignalImageChanged sel:@selector(act_image_changed:) obj:self];
    
    safe_release(_imageView);
    safe_release(_reflectionImageView);

	return self;
}

- (void)dealloc {
    // break
    [_imageView disconnect:self];
    
	[super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalActiveScale)
WSIEVENT_END

- (void)act_image_changed:(WSIEventObj*)evt {
    UIImage* image = (UIImage*)evt.result;
    
    if (image == nil)
        return;
    
    UIImage* reflection = [image makeImageReflection:_fractionReflection];
    
    if (reflection == nil) {
        trace_msg(@"failed to make reflection image.");
        return;
    }
    
    self.reflectionImageView.image = reflection;
    
    // relayout.
    [self setNeedsLayout];
}

- (void)loadURL:(NSURL*)imageURL {
    [_imageView loadURL:imageURL cache:YES];
}

- (void)setImage:(UIImage *)image {
    _imageView.image = image;
}

- (void)setFrame:(CGRect)newFrame {
	[super setFrame:newFrame];
}

- (void)layoutSubviews {
    WSI_USINGCXXNAMESPACE;
    
    layout::vbox lyt(self.bounds);
    layout::linear lnr(lyt);
    
    lnr << (flex)1;
    lnr << (pixel)_spaceImage;
    
    if (_fractionReflection)
        lnr << (flex)(_fractionReflection);
    
    _imageView.frame = lyt.add_pixel(lnr.start());
    
    lyt.add_pixel(lnr.next());
    
    if (_reflectionImageView.image) {
        _reflectionImageView.frame = lyt.add_pixel(lnr.next());
    } else {
        _reflectionImageView.frame = CGRectZero;
    }
}

- (void)activeScale {
    [self emit:kSignalActiveScale result:self];
    
    [_imageView activeScale];
}

- (CGSize)calcBestSize {
    CGSize sz_img = _imageView.image.size;
    CGSize ret = sz_img;
    if (_reflectionImageView.image) {
        CGSize sz_imgr = _reflectionImageView.image.size;
        ret.height += sz_imgr.height;
    }
    ret.height += _spaceImage;
    return ret;
}

@end

_CXXVIEW_IMPL(UICoverFlowItem);

WSI_END_OBJC
