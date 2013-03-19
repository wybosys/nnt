
# import "Core.h"
# import "WCGFillImage.h"
# import "WCGImage.h"

NNT_BEGIN_OBJC

@interface WCGFillImage()

@property (nonatomic, readwrite, copy) WCGImage *_fillImage;

@end

@implementation WCGFillImage

@synthesize _fillImage;
@dynamic image;

- (id)initWithImage:(WCGImage *)anImage {
    self = [super init];
	if ( self ) {
		_fillImage = [anImage retain];
	}
	return self;
}

- (void)dealloc {
	[_fillImage release];
	[super dealloc];
}

- (void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext {
	[self._fillImage drawInRect:theRect inContext:theContext];
}

- (void)fillPathInContext:(CGContextRef)theContext {
	CGContextSaveGState(theContext);
	
	CGRect bounds = CGContextGetPathBoundingBox(theContext);
	CGContextClip(theContext);
	[self._fillImage drawInRect:bounds inContext:theContext];
    
	CGContextRestoreGState(theContext);
}

- (void)fillPathInContext:(CGContextRef)theContext inRect:(CGRect)theRect {
    CGContextSaveGState(theContext);
    
    CGContextClip(theContext);
    [self._fillImage drawInRect:theRect inContext:theContext];
 
    CGContextRestoreGState(theContext);
}

- (id)copyWithZone:(NSZone *)zone {
	WCGFillImage *copy = [[[self class] allocWithZone:zone] init];
	copy->_fillImage = [self->_fillImage copyWithZone:zone];
	
	return copy;
}

- (Class)classForCoder {
	return [WCGFill class];
}

- (void)encodeWithCoder:(NSCoder *)coder {
	[coder encodeObject:self._fillImage forKey:@"fillImage"];
}

- (id)initWithCoder:(NSCoder *)coder {
    self = [super init];
    if ( self ) {
		_fillImage = [[coder decodeObjectForKey:@"fillImage"] retain];
	}
    return self;
}

- (WCGImage*)image {
    return _fillImage;
}

@end

NNT_END_OBJC
