
# import "Core.h"
# import "NGColorSpace.h"
# import "NGColor.h"

NNT_BEGIN_OBJC


@implementation NgColor

@synthesize cgColor;

- (void)setCgColor:(CGColorRef)color {
    CGColorRetain(color);
    CGColorRelease(cgColor);
    cgColor = color;
}

+ (NgColor*)colorWithARGB:(int)__value {
    return [NgColor colorWithComponentRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(ARGB_ALPHA(__value))];
}

+ (NgColor*)colorWithRGBA:(int)__value {
    return [NgColor colorWithComponentRed:AS_C32P(RGBA_RED(__value)) green:AS_C32P(RGBA_GREEN(__value)) blue:AS_C32P(RGBA_BLUE(__value)) alpha:AS_C32P(RGBA_ALPHA(__value))];
}

+ (NgColor*)colorWithRGB:(int)__value {
    return [NgColor colorWithComponentRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(0xFF)]; 
}

- (id)initWithARGB:(int)__value {
    self = [self initWithComponentRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(ARGB_ALPHA(__value))];
    return self;
}

- (id)initWithRGBA:(int)__value {
    self = [self initWithComponentRed:AS_C32P(RGBA_RED(__value)) green:AS_C32P(RGBA_GREEN(__value)) blue:AS_C32P(RGBA_BLUE(__value)) alpha:AS_C32P(RGBA_ALPHA(__value))];
    return self;
}

- (id)initWithRGB:(int)__value {
    self = [self initWithComponentRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(0xFF)];
    return self;
}

+ (NgColor *)clearColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
        CGColorRef clear = NULL;
        CGFloat values[4] = {0.0, 0.0, 0.0, 0.0}; 
		clear = CGColorCreate([NgColorSpace genericRGBSpace].cgColorSpace, values); 
        color = (NgColor*)[[NgColor alloc] initWithCGColor:clear];
        CGColorRelease(clear);
    }
	return color; 
} 

+ (NgColor *)whiteColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
        color = [[self colorWithGenericGray:1.0] retain];
    }
	return color; 
} 

+ (NgColor *)lightGrayColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[self colorWithGenericGray:2.0/3.0] retain];
    }
	return color; 
}

+ (NgColor *)grayColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
        color = [[self colorWithGenericGray:0.5] retain];
    }
	return color; 
}

+ (NgColor *)darkGrayColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
        color = [[self colorWithGenericGray:1.0/3.0] retain];
    }
	return color; 
}

+ (NgColor *)blackColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
        color = [[self colorWithGenericGray:0.0] retain];
    }
	return color; 
} 

+ (NgColor *)redColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[NgColor alloc] initWithComponentRed:1.0 green:0.0 blue:0.0 alpha:1.0];
    }
	return color; 
} 

+ (NgColor *)greenColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[NgColor alloc] initWithComponentRed:0.0 green:1.0 blue:0.0 alpha:1.0];
    }
	return color; 
}

+ (NgColor *)blueColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[NgColor alloc] initWithComponentRed:0.0 green:0.0 blue:1.0 alpha:1.0];
    }
	return color; 
}

+ (NgColor *)cyanColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[NgColor alloc] initWithComponentRed:0.0 green:1.0 blue:1.0 alpha:1.0];
    }
	return color; 
}

+ (NgColor *)yellowColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[NgColor alloc] initWithComponentRed:1.0 green:1.0 blue:0.0 alpha:1.0];
    }
	return color; 
}

+ (NgColor *)magentaColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[NgColor alloc] initWithComponentRed:1.0 green:0.0 blue:1.0 alpha:1.0];
    }
	return color; 
}

+ (NgColor *)orangeColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[NgColor alloc] initWithComponentRed:1.0 green:0.5 blue:0.0 alpha:1.0];
    }
	return color; 
}

+ (NgColor *)purpleColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[NgColor alloc] initWithComponentRed:0.5 green:0.0 blue:0.5 alpha:1.0];
    }
	return color; 
}

+ (NgColor *)brownColor { 
    static NgColor *color = nil;
    if ( nil == color ) {
		color = [[NgColor alloc] initWithComponentRed:0.6 green:0.4 blue:0.2 alpha:1.0];
    }
	return color; 
}

+ (NgColor *)colorWithCGColor:(CGColorRef)newNgColor {
    return [[[NgColor alloc] initWithCGColor:newNgColor] autorelease];
}

+ (NgColor *)colorWithComponentRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha {
    return [[[NgColor alloc] initWithComponentRed:red green:green blue:blue alpha:alpha] autorelease];
}

+ (NgColor *)colorWithGenericGray:(CGFloat)gray {
	CGFloat values[4] = {gray, gray, gray, 1.0}; 
	CGColorRef colorRef = CGColorCreate([NgColorSpace genericRGBSpace].cgColorSpace, values);
	NgColor *color = (NgColor*)[[NgColor alloc] initWithCGColor:colorRef];
	CGColorRelease(colorRef);
	return [color autorelease];
}

- (id)initWithCGColor:(CGColorRef)newCGColor {
    self = [super init];
    if (self == nil)
        return nil;
    
    CGColorRetain(newCGColor);
    cgColor = newCGColor;

    return self;
}

- (id)initWithComponentRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha {
    self = [super init];
    CGFloat colorComponents[4];
    colorComponents[0] = red;
    colorComponents[1] = green;
    colorComponents[2] = blue;
    colorComponents[3] = alpha;
    cgColor = CGColorCreate([NgColorSpace genericRGBSpace].cgColorSpace, colorComponents);
    return self;
}

- (void)dealloc {
    CGColorRelease(cgColor);
    [super dealloc];
}

- (void)finalize {
    CGColorRelease(cgColor);
	[super finalize];
}

- (NgColor *)colorWithAlphaComponent:(CGFloat)alpha {
    CGColorRef newCgColor = CGColorCreateCopyWithAlpha(self.cgColor, alpha);
    NgColor *newColor = [NgColor colorWithCGColor:newCgColor];
    CGColorRelease(newCgColor);
    return newColor;
}

- (void)encodeWithCoder:(NSCoder *)coder {
	const CGFloat *colorComponents = CGColorGetComponents(self.cgColor);	
	[coder encodeDouble:colorComponents[0] forKey:@"redComponent"];
	[coder encodeDouble:colorComponents[1] forKey:@"greenComponent"];
	[coder encodeDouble:colorComponents[2] forKey:@"blueComponent"];
	[coder encodeDouble:colorComponents[3] forKey:@"alphaComponent"];
}

- (id)initWithCoder:(NSCoder *)coder {
	self = [super init];
    if (self == nil)
        return nil;

    CGFloat colorComponents[4];
    colorComponents[0] = [coder decodeDoubleForKey:@"redComponent"];
    colorComponents[1] = [coder decodeDoubleForKey:@"greenComponent"];
    colorComponents[2] = [coder decodeDoubleForKey:@"blueComponent"];
    colorComponents[3] = [coder decodeDoubleForKey:@"alphaComponent"];
    cgColor = CGColorCreate([NgColorSpace genericRGBSpace].cgColorSpace, colorComponents);

    return self;
}

#pragma mark -
#pragma mark NSCopying methods

- (id)copyWithZone:(NSZone *)zone {
    CGColorRef cgColorCopy = NULL;
    if ( cgColor ) cgColorCopy = CGColorCreateCopy(cgColor);
    NgColor *colorCopy = (NgColor*)[[[self class] allocWithZone:zone] initWithCGColor:cgColorCopy];
    CGColorRelease(cgColorCopy);
    return colorCopy;
}

#pragma mark -
#pragma mark Color comparison

- (BOOL)isEqual:(id)object {
	if ( self == object ) {
		return YES;
	}
	else if ([object isKindOfClass:[self class]]) {
		return CGColorEqualToColor(self.cgColor, ((NgColor *)object).cgColor);
	}
	else {
		return NO;
	}
}

- (NSUInteger)hash {
	// Equal objects must hash the same.
	CGFloat theHash = 0.0;
	CGFloat multiplier = 256.0;
    
	CGColorRef theColor = self.cgColor;
	size_t numberOfComponents = CGColorGetNumberOfComponents(theColor);
	const CGFloat *colorComponents = CGColorGetComponents(theColor);
	
	for (NSUInteger i = 0; i < numberOfComponents; i++) {
		theHash += multiplier * colorComponents[i];
		multiplier *= 256.0;
	}
	
	return (NSUInteger)theHash;
}

@end

# pragma mark -
# pragma mark color add

@implementation NgColor (add)

+ (NgColor*)multiWith:(NgColor*)color r:(float)__r g:(float)__g b:(float)__b {
    return [NgColor multiWith:color r:__r g:__g b:__b a:1.f];
}

+ (NgColor*)multiWith:(NgColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    real const* _comps = CGColorGetComponents(color.cgColor);
    real comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] *= __r;
    comps[1] *= __g;
    comps[2] *= __b;
    comps[3] *= __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(color.cgColor), comps);
    NgColor *ret = [safe_alloc(NgColor) initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];   
}

+ (NgColor*)addWith:(NgColor*)color r:(float)__r g:(float)__g b:(float)__b {
    return [NgColor addWith:color r:__r g:__g b:__b a:0.f];
}

+ (NgColor*)addWith:(NgColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    real const* _comps = CGColorGetComponents(color.cgColor);
    real comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] += __r;
    comps[1] += __g;
    comps[2] += __b;
    comps[3] += __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(color.cgColor), comps); 
    NgColor *ret = [safe_alloc(NgColor) initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];
}

- (uint)valueRGBA {
    CGFloat const* _comps = CGColorGetComponents(self.cgColor);
    return RGBA(_comps[0] * 255, _comps[1] * 255, _comps[2] * 255, _comps[3] * 255);
}

- (uint)valueARGB {
    CGFloat const* _comps = CGColorGetComponents(self.cgColor);
    return ARGB(_comps[0] * 255, _comps[1] * 255, _comps[2] * 255, _comps[3] * 255);   
}

- (uint)valueRGB {
    real const* _comps = CGColorGetComponents(self.cgColor);
    return RGB(_comps[0] * 255, _comps[1] * 255, _comps[2] * 255);
}

- (NgColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b {
    real const* _comps = CGColorGetComponents(self.cgColor);
    real comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] *= __r;
    comps[1] *= __g;
    comps[2] *= __b;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(self.cgColor), comps);
    NgColor *ret = [safe_alloc(NgColor) initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];
}

- (NgColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    real const* _comps = CGColorGetComponents(self.cgColor);
    real comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] *= __r;
    comps[1] *= __g;
    comps[2] *= __b;
    comps[3] *= __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(self.cgColor), comps);
    NgColor *ret = [safe_alloc(NgColor) initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];
}

- (CGFloat)redComponent {
 	const CGFloat *colorComponents = CGColorGetComponents(self.cgColor);
    return colorComponents[0];
}

- (CGFloat)greenComponent {
    const CGFloat *colorComponents = CGColorGetComponents(self.cgColor);
    return colorComponents[1];
}

- (CGFloat)blueComponent {
    const CGFloat *colorComponents = CGColorGetComponents(self.cgColor);
    return colorComponents[2];
}

- (CGFloat)alphaComponent {
    const CGFloat *colorComponents = CGColorGetComponents(self.cgColor);
    return colorComponents[3];
}

@end

NNT_END_OBJC