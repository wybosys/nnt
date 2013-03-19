
# import "Core.h"
# import "WCGColor.h"
# import "WCGFillColor.h"

WSI_BEGIN_OBJC

@interface WCGFillColor()

@property (nonatomic, readwrite, copy) WCGColor *_fillColor;

@end

@implementation WCGFillColor

@synthesize _fillColor;

- (id)initWithColor:(WCGColor *)aColor {
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
	WCGFillColor *copy = [[[self class] allocWithZone:zone] init];
	copy->_fillColor = [self->_fillColor copyWithZone:zone];
	
	return copy;
}

- (Class)classForCoder {
	return [WCGFill class];
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

WSI_END_OBJC
