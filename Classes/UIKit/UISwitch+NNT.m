
# import "Core.h"
# import "UISwitch+NNT.h"
# import "Graphic+NNT.h"

NNT_BEGIN_OBJC

signal_t kSignalButtonCloseClicked = @"::nnt::ui::image::close";

@implementation NNTUISwitch

NNTOBJECT_IMPL_NOSIGNALS;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    [self addTarget:self action:@selector(__act_value_changed) forControlEvents:UIControlEventValueChanged];
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalValueChanged);
}

- (void)__act_value_changed {
    if (self.on) {
        [self emit:kSignalValueChanged result:NSNumberYes];
    } else {
        [self emit:kSignalValueChanged result:NSNumberNo];
    }
}

@end

@interface UIImageSwitch ()

- (void)__init;

@end

@implementation UIImageSwitch

@synthesize colorFalse, imageFalse, image, value;
@synthesize showClose, buttonClose;

- (void)__init {
    self.colorFalse = [UIColor grayColor];
    value = NO;
    
    [[self connect:kSignalViewClicked sel:@selector(__act_clicked)] mainThread];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    [self __init];
    return self;
}

- (void)dealloc {
    zero_release(colorFalse);
    zero_release(imageFalse);
    zero_release(image);
    [buttonClose release];
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalValueChanged)
NNTEVENT_SIGNAL(kSignalButtonCloseClicked)
NNTEVENT_END

- (void)__act_clicked {
    value = !value;
    
    if (value) {
        [self emit:kSignalValueChanged result:NSNumberYes];
    } else {
        [self emit:kSignalValueChanged result:NSNumberNo];
    }
    
    //[self setNeedsDisplay];
}

- (void)setShowClose:(BOOL)__showClose {
    
    if (showClose == __showClose)
        return;
    showClose = __showClose;
    
    if (showClose) {
        if (buttonClose == nil) {
            buttonClose = [[UIButtonClose alloc] initWithZero];
            
            [self addSubview:buttonClose];
            
            [buttonClose connect:kSignalButtonClicked sel:@selector(close) obj:self];
            
        } else {
            buttonClose.hidden = NO;
        }
    } else {
        buttonClose.hidden = YES;
    }
}

- (void)close {
    
    [self emit:kSignalButtonCloseClicked result:self];
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    if (value) {
        [image drawInRect:rect];
    } else {
        if (imageFalse) {
            [imageFalse drawInRect:rect];
        } else {            
            UIGraphicsBeginImageContext(image.size);
            CGContextRef ctx = UIGraphicsGetCurrentContext();   
            CGRect rc_img = CGRectMakePtSz(CGPointZero, image.size);  
            
            CGContextSaveGState(ctx);
            
            //[image drawInRect:rc_img];
            CGContextDrawImageOri(ctx, rc_img, image.CGImage);
            
            //CGContextSetBlendMode(ctx, kCGBlendModeSourceAtop);
            CGContextSetBlendMode(ctx, kCGBlendModeColor);
            CGContextSetFillColorWithColor(ctx, colorFalse.CGColor);
            CGContextFillRect(ctx, rc_img);
            
            // draw mask.
            CGContextSetBlendMode(ctx, kCGBlendModeDestinationIn);
            //[image drawInRect:rc_img];            
            CGContextDrawImageOri(ctx, rc_img, image.CGImage);
                        
            CGContextRestoreGState(ctx);
            
            self.imageFalse = UIGraphicsGetImageFromCurrentImageContext();
            UIGraphicsEndImageContext();
            
            [imageFalse drawInRect:rect];
        }
    }
}

- (void)layoutSubviews {
    
    CGRect rc_client = self.bounds;
    if (buttonClose) {
        CGPoint pt = CGRectRightTop(&rc_client);
        pt.x -= 5;
        pt.y += 5;
        [buttonClose moveToCenter:pt];
    }
}

@end

NNT_END_OBJC