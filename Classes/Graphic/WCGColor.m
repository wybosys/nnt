
# import "Core.h"
# import "WCGColorSpace.h"
# import "WCGColor.h"

WSI_BEGIN_OBJC


@implementation WCGColor

@synthesize cgColor;

- (void)setCgColor:(CGColorRef)color {
    CGColorRetain(color);
    CGColorRelease(cgColor);
    cgColor = color;
}

+ (WCGColor*)colorWithARGB:(int)__value {
    return [WCGColor colorWithComponentRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(ARGB_ALPHA(__value))];
}

+ (WCGColor*)colorWithRGBA:(int)__value {
    return [WCGColor colorWithComponentRed:AS_C32P(RGBA_RED(__value)) green:AS_C32P(RGBA_GREEN(__value)) blue:AS_C32P(RGBA_BLUE(__value)) alpha:AS_C32P(RGBA_ALPHA(__value))];
}

+ (WCGColor*)colorWithRGB:(int)__value {
    return [WCGColor colorWithComponentRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(0xFF)]; 
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

+ (WCGColor *)clearColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
        CGColorRef clear = NULL;
        CGFloat values[4] = {0.0, 0.0, 0.0, 0.0}; 
		clear = CGColorCreate([WCGColorSpace genericRGBSpace].cgColorSpace, values); 
        color = (WCGColor*)[[WCGColor alloc] initWithCGColor:clear];
        CGColorRelease(clear);
    }
	return color; 
} 

+ (WCGColor *)whiteColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
        color = [[self colorWithGenericGray:1.0] retain];
    }
	return color; 
} 

+ (WCGColor *)lightGrayColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[self colorWithGenericGray:2.0/3.0] retain];
    }
	return color; 
}

+ (WCGColor *)grayColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
        color = [[self colorWithGenericGray:0.5] retain];
    }
	return color; 
}

+ (WCGColor *)darkGrayColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
        color = [[self colorWithGenericGray:1.0/3.0] retain];
    }
	return color; 
}

+ (WCGColor *)blackColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
        color = [[self colorWithGenericGray:0.0] retain];
    }
	return color; 
} 

+ (WCGColor *)redColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[WCGColor alloc] initWithComponentRed:1.0 green:0.0 blue:0.0 alpha:1.0];
    }
	return color; 
} 

+ (WCGColor *)greenColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[WCGColor alloc] initWithComponentRed:0.0 green:1.0 blue:0.0 alpha:1.0];
    }
	return color; 
}

+ (WCGColor *)blueColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[WCGColor alloc] initWithComponentRed:0.0 green:0.0 blue:1.0 alpha:1.0];
    }
	return color; 
}

+ (WCGColor *)cyanColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[WCGColor alloc] initWithComponentRed:0.0 green:1.0 blue:1.0 alpha:1.0];
    }
	return color; 
}

+ (WCGColor *)yellowColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[WCGColor alloc] initWithComponentRed:1.0 green:1.0 blue:0.0 alpha:1.0];
    }
	return color; 
}

+ (WCGColor *)magentaColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[WCGColor alloc] initWithComponentRed:1.0 green:0.0 blue:1.0 alpha:1.0];
    }
	return color; 
}

+ (WCGColor *)orangeColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[WCGColor alloc] initWithComponentRed:1.0 green:0.5 blue:0.0 alpha:1.0];
    }
	return color; 
}

+ (WCGColor *)purpleColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[WCGColor alloc] initWithComponentRed:0.5 green:0.0 blue:0.5 alpha:1.0];
    }
	return color; 
}

+ (WCGColor *)brownColor { 
    static WCGColor *color = nil;
    if ( nil == color ) {
		color = [[WCGColor alloc] initWithComponentRed:0.6 green:0.4 blue:0.2 alpha:1.0];
    }
	return color; 
}

+ (WCGColor *)colorWithCGColor:(CGColorRef)newWCGColor {
    return [[[WCGColor alloc] initWithCGColor:newWCGColor] autorelease];
}

+ (WCGColor *)colorWithComponentRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha {
    return [[[WCGColor alloc] initWithComponentRed:red green:green blue:blue alpha:alpha] autorelease];
}

+ (WCGColor *)colorWithGenericGray:(CGFloat)gray {
	CGFloat values[4] = {gray, gray, gray, 1.0}; 
	CGColorRef colorRef = CGColorCreate([WCGColorSpace genericRGBSpace].cgColorSpace, values);
	WCGColor *color = (WCGColor*)[[WCGColor alloc] initWithCGColor:colorRef];
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
    cgColor = CGColorCreate([WCGColorSpace genericRGBSpace].cgColorSpace, colorComponents);
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

- (WCGColor *)colorWithAlphaComponent:(CGFloat)alpha {
    CGColorRef newCgColor = CGColorCreateCopyWithAlpha(self.cgColor, alpha);
    WCGColor *newColor = [WCGColor colorWithCGColor:newCgColor];
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
    cgColor = CGColorCreate([WCGColorSpace genericRGBSpace].cgColorSpace, colorComponents);

    return self;
}

#pragma mark -
#pragma mark NSCopying methods

- (id)copyWithZone:(NSZone *)zone {
    CGColorRef cgColorCopy = NULL;
    if ( cgColor ) cgColorCopy = CGColorCreateCopy(cgColor);
    WCGColor *colorCopy = (WCGColor*)[[[self class] allocWithZone:zone] initWithCGColor:cgColorCopy];
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
		return CGColorEqualToColor(self.cgColor, ((WCGColor *)object).cgColor);
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

@implementation WCGColor (add)

+ (WCGColor*)multiWith:(WCGColor*)color r:(float)__r g:(float)__g b:(float)__b {
    return [WCGColor multiWith:color r:__r g:__g b:__b a:1.f];
}

+ (WCGColor*)multiWith:(WCGColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    real const* _comps = CGColorGetComponents(color.cgColor);
    real comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] *= __r;
    comps[1] *= __g;
    comps[2] *= __b;
    comps[3] *= __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(color.cgColor), comps);
    WCGColor *ret = [safe_alloc(WCGColor) initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];   
}

+ (WCGColor*)addWith:(WCGColor*)color r:(float)__r g:(float)__g b:(float)__b {
    return [WCGColor addWith:color r:__r g:__g b:__b a:0.f];
}

+ (WCGColor*)addWith:(WCGColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    real const* _comps = CGColorGetComponents(color.cgColor);
    real comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] += __r;
    comps[1] += __g;
    comps[2] += __b;
    comps[3] += __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(color.cgColor), comps); 
    WCGColor *ret = [safe_alloc(WCGColor) initWithCGColor:ref];
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

- (WCGColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b {
    real const* _comps = CGColorGetComponents(self.cgColor);
    real comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] *= __r;
    comps[1] *= __g;
    comps[2] *= __b;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(self.cgColor), comps);
    WCGColor *ret = [safe_alloc(WCGColor) initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];
}

- (WCGColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    real const* _comps = CGColorGetComponents(self.cgColor);
    real comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] *= __r;
    comps[1] *= __g;
    comps[2] *= __b;
    comps[3] *= __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(self.cgColor), comps);
    WCGColor *ret = [safe_alloc(WCGColor) initWithCGColor:ref];
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

WSI_END_OBJC