
# import "Core.h"
# import "CGRoundedLeftArrowShape.h"
# import "Math+NNT.h"

const CGFloat kArrowPointWidth  = 2.8;
const CGFloat kArrowRadius      = 2;

NNT_BEGIN_OBJC

@implementation CGRoundedLeftArrowShape

@synthesize radius = _radius;

- (void)addToPath:(CGRect)rect {
    [self openPath:rect];
    
    CGFloat fw = rect.size.width;
    CGFloat fh = rect.size.height;
    CGFloat point = floor(fh / kArrowPointWidth);
    CGFloat radius = RAD2ANGLE(_radius);
    CGFloat radius2 = radius * kArrowRadius;
    
    CGContextMoveToPoint(_ctx, 0, floor(fh / 2));
    CGContextAddArcToPoint(_ctx, point, 0, floor(fw - radius), 0, radius2);
    CGContextAddArcToPoint(_ctx, fw, 0, fw, floor(radius), radius);
    CGContextAddArcToPoint(_ctx, fw, fh, floor(point + radius2), fh, radius);
    CGContextAddArcToPoint(_ctx, point, fh, 0, floor(fh / 2), radius2);
    
    [self closePath:rect];
}

- (void)addInverseToPath:(CGRect)rect {
    CGFloat fw = rect.size.width;
    CGFloat fh = rect.size.height;
    CGFloat point = floor(fh/kArrowPointWidth);
    CGFloat radius = RAD2ANGLE(_radius);
    CGFloat radius2 = radius * kArrowRadius;
    
    CGFloat width = 5;
    CGRect shadowRect = CGRectMake(-width, -width, fw + width * 2, fh + width * 2);
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathAddRect(path, nil, shadowRect);
    CGPathCloseSubpath(path);
    
    CGPathMoveToPoint(path, nil, 0, floor(fh / 2));
    CGPathAddArcToPoint(path, nil, point, 0, floor(fw - radius), 0, radius2);
    CGPathAddArcToPoint(path, nil, fw, 0, fw, floor(radius), radius);
    CGPathAddArcToPoint(path, nil, fw, fh, floor(point + radius2), fh, radius);
    CGPathAddArcToPoint(path, nil, point, fh, 0, floor(fh / 2), radius2);
    
    [self openPath:rect];
    CGContextAddPath(_ctx, path);
    [self closePath:rect];
    
    CGPathRelease(path);
}

- (void)addTopEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource {
    CGFloat fw = rect.size.width;
    CGFloat fh = rect.size.height;
    CGFloat point = floor(fh/kArrowPointWidth);
    CGFloat radius = RAD2ANGLE(_radius);
    CGFloat radius2 = radius * kArrowRadius;
    
    CGContextMoveToPoint(_ctx, 0, floor(fh / 2));
    CGContextAddArcToPoint(_ctx, point, 0, floor(fw - radius), 0, radius2);
    
    if (lightSource >= 0 && lightSource <= 90) {
        CGContextAddLineToPoint(_ctx, floor(fw - radius), 0);
        
    } else {
        CGContextAddArcToPoint(_ctx, fw, 0, fw, floor(radius), radius);
    }
}

- (void)addRightEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource {
    CGFloat fw = rect.size.width;
    CGFloat fh = rect.size.height;
    CGFloat radius = RAD2ANGLE(_radius);
    
    if (lightSource >= 0 && lightSource <= 90) {
        CGContextMoveToPoint(_ctx, floor(fw - radius), 0);
        CGContextAddArcToPoint(_ctx, fw, 0, fw, floor(radius), radius);
        
    } else {
        CGContextMoveToPoint(_ctx, fw, radius);
        CGContextAddLineToPoint(_ctx, fw, fh - radius);
    }
}

- (void)addBottomEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource {
    CGFloat fw = rect.size.width;
    CGFloat fh = rect.size.height;
    CGFloat point = floor(fh/kArrowPointWidth);
    CGFloat radius = RAD2ANGLE(_radius);
    CGFloat radius2 = _radius * kArrowRadius;
    
    CGContextMoveToPoint(_ctx, fw, floor(fh - radius));
    CGContextAddArcToPoint(_ctx, fw, fh, floor(point + radius2), fh, radius);
    CGContextAddLineToPoint(_ctx, floor(point + radius2)-1, fh);
}

- (void)addLeftEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource {
    CGFloat fh = rect.size.height;
    CGFloat point = floor(fh/kArrowPointWidth);
    CGFloat radius = RAD2ANGLE(_radius);
    CGFloat radius2 = radius * kArrowRadius;
    
    CGContextMoveToPoint(_ctx, floor(point + radius2), fh);
    CGContextAddArcToPoint(_ctx, point, fh, 0, floor(fh / 2), radius2);
    CGContextAddLineToPoint(_ctx, 0, floor(fh / 2));
}

- (UIEdgeInsets)insetsForSize:(CGSize)size {
    //CGFloat fh = size.height / 3;
    return UIEdgeInsetsMake(0, floor(RAD2ANGLE(_radius)), 0, 0);
}


@end

NNT_END_OBJC