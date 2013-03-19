
# import "Core.h"
# import "NGFillImage.h"
# import "NGImage.h"

NNT_BEGIN_OBJC

@interface NgFillImage()

@property (nonatomic, readwrite, copy) NgImage *_fillImage;

@end

@implementation NgFillImage

@synthesize _fillImage;
@dynamic image;

- (id)initWithImage:(NgImage *)anImage {
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
	NgFillImage *copy = [[[self class] allocWithZone:zone] init];
	copy->_fillImage = [self->_fillImage copyWithZone:zone];
	
	return copy;
}

- (Class)classForCoder {
	return [NgFill class];
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

- (NgImage*)image {
    return _fillImage;
}

@end

NNT_END_OBJC
