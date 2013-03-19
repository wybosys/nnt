
# import "Core.h"
# import "CGInnerShadowStyle.h"
# import "../../Util/VersionString.h"

WSI_BEGIN_OBJC

@implementation WCGInnerShadowStyle

- (void)drawInContext:(WCGStyleContext*)context {
    CGContextRef ctx = context.context;
    
    CGContextSaveGState(ctx);
    
    [context.shape addToPath:context.bounds];
    CGContextClip(ctx);
    
    [context.shape addInverseToPath:context.bounds];
    [[UIColor whiteColor] setFill];
    
    // Due to a bug in OS versions 3.2 and 4.0, the shadow appears upside-down. It pains me to
    // write this, but a lot of research has failed to turn up a way to detect the flipped shadow
    // programmatically
    float shadowYOffset = -_offset.height;
    NSString *osVersion = [UIDevice currentDevice].systemVersion;
    if (versionStringCompare(osVersion, @"3.2") != NSOrderedAscending) {
        shadowYOffset = _offset.height;
    }
    
    CGContextSetShadowWithColor(ctx, CGSizeMake(_offset.width, shadowYOffset), _blur,
                                _color.cgColor);
    CGContextEOFillPath(ctx);
    CGContextRestoreGState(ctx);
    
    [_next drawInContext:context];
}

@end

WSI_END_OBJC