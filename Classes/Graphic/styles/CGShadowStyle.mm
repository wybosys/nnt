
# import "Core.h"
# import "CGShadowStyle.h"
# import "../../Util/VersionString.h"

NNT_BEGIN_OBJC

@implementation WCGShadowStyle

@synthesize blur = _bluc, color = _color, offset = _offset;

- (void)dealloc {
    zero_release(_color);
    [super dealloc];
}

- (void)drawInContext:(WCGStyleContext*)context {
    CGFloat blurSize = round(_blur / 2);
    UIEdgeInsets inset = UIEdgeInsetsMake(blurSize, blurSize, blurSize, blurSize);
    if (_offset.width < 0) {
        inset.left += fabs(_offset.width) + blurSize*2;
        inset.right -= blurSize;
        
    } else if (_offset.width > 0) {
        inset.right += fabs(_offset.width) + blurSize*2;
        inset.left -= blurSize;
    }
    if (_offset.height < 0) {
        inset.top += fabs(_offset.height) + blurSize*2;
        inset.bottom -= blurSize;
        
    } else if (_offset.height > 0) {
        inset.bottom += fabs(_offset.height) + blurSize*2;
        inset.top -= blurSize;
    }
    
    CGContextRef ctx = context.context;
    //context.frame = CGRectInsetWithInset(context.frame, inset);
    context.bounds = CGRectInsetWithInset(context.bounds, inset);
    
    CGContextSaveGState(ctx);
    
    // Due to a bug in OS versions 3.2 and 4.0, the shadow appears upside-down. It pains me to
    // write this, but a lot of research has failed to turn up a way to detect the flipped shadow
    // programmatically
    float shadowYOffset = -_offset.height;
    NSString *osVersion = [UIDevice currentDevice].systemVersion;
    if (versionStringCompare(osVersion, @"3.2") != NSOrderedAscending) {
        shadowYOffset = _offset.height;
    }
    
    //[context.shape addToPath:context.frame];
    CGContextSetShadowWithColor(ctx, CGSizeMake(_offset.width, shadowYOffset), _blur,
                                _color.cgColor);
    CGContextBeginTransparencyLayer(ctx, nil);
    [self.next drawInContext:context];
    CGContextEndTransparencyLayer(ctx);
    
    CGContextRestoreGState(ctx);
}

@end

NNT_END_OBJC