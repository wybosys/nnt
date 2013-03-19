
# import "Core.h"
# import "NGColor.h"
# import "NGFillColor.h"

NNT_BEGIN_OBJC

@interface NgFillColor()

@property (nonatomic, readwrite, copy) NgColor *_fillColor;

@end

@implementation NgFillColor

@synthesize _fillColor;

- (id)initWithColor:(NgColor *)aColor {
    self = [super init];
	if ( self ) {
        _fillColor = [aColor retain];
	}
	return self;
}

- (void)dealloc {
    [_fillColor release];
	[super dealloc];
}

- (void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext {
	CGContextSaveGState(theContext);
	CGContextSetFillColorWithColor(theContext, self._fillColor.cgColor);
	CGContextFillRect(theContext, theRect);
	CGContextRestoreGState(theContext);
}

- (void)fillPathInContext:(CGContextRef)theContext {
	CGContextSaveGState(theContext);
	CGContextSetFillColorWithColor(theContext, self._fillColor.cgColor);
	CGContextFillPath(theContext);
	CGContextRestoreGState(theContext);
}

- (id)copyWithZone:(NSZone *)zone {
	NgFillColor *copy = [[[self class] allocWithZone:zone] init];
	copy->_fillColor = [self->_fillColor copyWithZone:zone];
	
	return copy;
}

- (Class)classForCoder {
	return [NgFill class];
}

- (void)encodeWithCoder:(NSCoder *)coder {
	[coder encodeObject:self._fillColor forKey:@"fillColor"];
}

- (id)initWithCoder:(NSCoder *)coder {
    self = [super init];
    if ( self ) {
		_fillColor = [[coder decodeObjectForKey:@"fillColor"] retain];
	}
    return self;
}

@end

NNT_END_OBJC
