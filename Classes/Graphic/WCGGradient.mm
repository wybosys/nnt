
# import "Core.h"
# import "WCGGradient.h"
# import "WCGColorSpace.h"
# import "WCGColor.h"
# import "WCGUtils.h"
# import "Math+WSI.h"

WSI_BEGIN_OBJC

@interface WCGGradient()

@property (nonatomic, retain, readwrite) WCGColorSpace *colorspace;
@property (nonatomic, assign, readwrite) WCGGradientBlendingMode blendingMode;

-(void)commonInit;
-(void)addElement:(WCGGradientElement*)newElement;

-(CGShadingRef)newAxialGradientInRect:(CGRect)rect;
-(CGShadingRef)newRadialGradientInRect:(CGRect)rect context:(CGContextRef)context;

-(WCGGradientElement *)elementAtIndex:(NSUInteger)index;

-(WCGGradientElement)removeElementAtIndex:(NSUInteger)index;
-(WCGGradientElement)removeElementAtPosition:(CGFloat)position;
-(void)removeAllElements;

@end

static void linearEvaluation(void *info, const CGFloat *in, CGFloat *out);
static void chromaticEvaluation(void *info, const CGFloat *in, CGFloat *out);
static void inverseChromaticEvaluation(void *info, const CGFloat *in, CGFloat *out);
static void transformRGB_HSV(CGFloat *components);
static void transformHSV_RGB(CGFloat *components);
static void resolveHSV(CGFloat *color1, CGFloat *color2);

#pragma mark -

@implementation WCGGradient

/** @property colorspace 
 *  @brief The colorspace for the gradient colors.
 **/
@synthesize colorspace = _colorspace;

/** @property blendingMode
 *  @brief The color blending mode used to create the gradient.
 **/
@synthesize blendingMode = _blendingMode;

/** @property angle
 *  @brief The axis angle of an axial gradient, expressed in degrees.
 **/
@synthesize angle = _angle;

/** @property gradientType 
 *  @brief The gradient type.
 **/
@synthesize gradientType = _gradientType;

#pragma mark -
#pragma mark Initialization

- (id)init {
    self = [super init];
    if (self == nil)
        return nil;

    [self commonInit];
    
    self.blendingMode = WCGLinearBlendingMode;
    
    _angle = 0.f;
    _gradientType = WCGGradientTypeAxial;

    return self;
}

- (void)commonInit {
	_colorspace = [[WCGColorSpace genericRGBSpace] retain];
    _elementList = NULL;
}

- (void)dealloc {
	[_colorspace release];
	CGFunctionRelease(_gradientFunction);
	[self removeAllElements];
    [super dealloc];
}

- (void)finalize {
	CGFunctionRelease(_gradientFunction);
	[self removeAllElements];
	[super finalize];
}

- (id)copyWithZone:(NSZone *)zone {
    WCGGradient *copy = [[[self class] allocWithZone:zone] init];
	
    WCGGradientElement *currentElement = _elementList;
    while (currentElement != NULL) {
        [copy addElement:currentElement];
        currentElement = currentElement->nextElement;
    }
	
	copy.blendingMode = self.blendingMode;
	copy->_angle = _angle;
	copy->_gradientType = _gradientType;
	
    return (copy);
}

- (void)encodeWithCoder:(NSCoder *)coder {
    if ( [coder allowsKeyedCoding] ) {
        NSUInteger count = 0;
        WCGGradientElement *currentElement = _elementList;
        while (currentElement != NULL) {
            [coder encodeValueOfObjCType:@encode(double) at:&(currentElement->color.red)];
            [coder encodeValueOfObjCType:@encode(double) at:&(currentElement->color.green)];
            [coder encodeValueOfObjCType:@encode(double) at:&(currentElement->color.blue)];
            [coder encodeValueOfObjCType:@encode(double) at:&(currentElement->color.alpha)];
            [coder encodeValueOfObjCType:@encode(double) at:&(currentElement->position)];
            
            count++;
            currentElement = currentElement->nextElement;
        }
        [coder encodeInteger:count forKey:@"WCGGradientElementCount"];
        [coder encodeInt:_blendingMode forKey:@"WCGGradientBlendingMode"];
        [coder encodeDouble:_angle forKey:@"WCGGradientAngle"];
        [coder encodeInt:_gradientType forKey:@"WCGGradientType"];
	} else {
        [NSException raise:NSInvalidArchiveOperationException format:@"Only supports NSKeyedArchiver coders"];
	}
}

- (id)initWithCoder:(NSCoder *)coder {
    self = [super init];
    if (self == nil)
        return nil;

    [self commonInit];
		
    _gradientType = (WCGGradientType)[coder decodeIntForKey:@"WCGGradientType"];
    _angle = [coder decodeDoubleForKey:@"WCGGradientAngle"];
    self.blendingMode = (WCGGradientBlendingMode)[coder decodeIntForKey:@"WCGGradientBlendingMode"];
    
    NSUInteger count = [coder decodeIntegerForKey:@"WCGGradientElementCount"];
    
    while (count != 0) {
        WCGGradientElement newElement;
        
        [coder decodeValueOfObjCType:@encode(double) at:&(newElement.color.red)];
        [coder decodeValueOfObjCType:@encode(double) at:&(newElement.color.green)];
        [coder decodeValueOfObjCType:@encode(double) at:&(newElement.color.blue)];
        [coder decodeValueOfObjCType:@encode(double) at:&(newElement.color.alpha)];
        [coder decodeValueOfObjCType:@encode(double) at:&(newElement.position)];
        
        count--;
        [self addElement:&newElement];
    }
    
    return self;
}

#pragma mark -
#pragma mark Factory Methods

/** @brief Creates and returns a new WCGGradient instance initialized with an axial linear gradient between two given colors.
 *  @param begin The beginning color.
 *  @param end The ending color.
 *  @return A new WCGGradient instance initialized with an axial linear gradient between the two given colors.
 **/
+ (WCGGradient *)gradientWithBeginningColor:(WCGColor *)begin endingColor:(WCGColor *)end {
	return [self gradientWithBeginningColor:begin endingColor:end beginningPosition:0.0 endingPosition:1.0];
}

+ (WCGGradient *)gradientWithBeginningColor:(WCGColor *)begin endingColor:(WCGColor *)end angle:(CGFloat)angle {
	WCGGradient *ret = [self gradientWithBeginningColor:begin endingColor:end beginningPosition:0.0 endingPosition:1.0];
    if (ret) {
        ret.angle = angle;
    }
    return ret;
}

/** @brief Creates and returns a new WCGGradient instance initialized with an axial linear gradient between two given colors, at two given normalized positions.
 *  @param begin The beginning color.
 *  @param end The ending color.
 *  @param beginningPosition The beginning position (0 ≤ beginningPosition ≤ 1).
 *  @param endingPosition The ending position (0 ≤ endingPosition ≤ 1).
 *  @return A new WCGGradient instance initialized with an axial linear gradient between the two given colors, at two given normalized positions.
 **/
+ (WCGGradient *)gradientWithBeginningColor:(WCGColor *)begin endingColor:(WCGColor *)end beginningPosition:(CGFloat)beginningPosition endingPosition:(CGFloat)endingPosition {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    WCGGradientElement color2;
	
	color1.color = WCGRGBAColorFromCGColor(begin.cgColor);
	color2.color = WCGRGBAColorFromCGColor(end.cgColor);
	
    color1.position = beginningPosition;
    color2.position = endingPosition;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with the Aqua selected gradient.
 *  @return A new WCGGradient instance initialized with the Aqua selected gradient.
 **/
+ (WCGGradient *)aquaSelectedGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red   = 0.58;
    color1.color.green = 0.86;
    color1.color.blue  = 0.98;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red   = 0.42;
    color2.color.green = 0.68;
    color2.color.blue  = 0.90;
    color2.color.alpha = 1.00;
    color2.position = 0.5;
	
    WCGGradientElement color3;
    color3.color.red   = 0.64;
    color3.color.green = 0.80;
    color3.color.blue  = 0.94;
    color3.color.alpha = 1.00;
    color3.position = 0.5;
	
    WCGGradientElement color4;
    color4.color.red   = 0.56;
    color4.color.green = 0.70;
    color4.color.blue  = 0.90;
    color4.color.alpha = 1.00;
    color4.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
    [newInstance addElement:&color3];
    [newInstance addElement:&color4];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with the Aqua normal gradient.
 *  @return A new WCGGradient instance initialized with the Aqua normal gradient.
 **/
+ (WCGGradient *)aquaNormalGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red = color1.color.green = color1.color.blue  = 0.95;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red = color2.color.green = color2.color.blue  = 0.83;
    color2.color.alpha = 1.00;
    color2.position = 0.5;
	
    WCGGradientElement color3;
    color3.color.red = color3.color.green = color3.color.blue  = 0.95;
    color3.color.alpha = 1.00;
    color3.position = 0.5;
	
    WCGGradientElement color4;
    color4.color.red = color4.color.green = color4.color.blue  = 0.92;
    color4.color.alpha = 1.00;
    color4.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
    [newInstance addElement:&color3];
    [newInstance addElement:&color4];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with the Aqua pressed gradient.
 *  @return A new WCGGradient instance initialized with the Aqua pressed gradient.
 **/
+ (WCGGradient *)aquaPressedGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red = color1.color.green = color1.color.blue  = 0.80;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red = color2.color.green = color2.color.blue  = 0.64;
    color2.color.alpha = 1.00;
    color2.position = 0.5;
	
    WCGGradientElement color3;
    color3.color.red = color3.color.green = color3.color.blue  = 0.80;
    color3.color.alpha = 1.00;
    color3.position = 0.5;
	
    WCGGradientElement color4;
    color4.color.red = color4.color.green = color4.color.blue  = 0.77;
    color4.color.alpha = 1.00;
    color4.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
    [newInstance addElement:&color3];
    [newInstance addElement:&color4];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with the unified selected gradient.
 *  @return A new WCGGradient instance initialized with the unified selected gradient.
 **/
+ (WCGGradient *)unifiedSelectedGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red = color1.color.green = color1.color.blue  = 0.85;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red = color2.color.green = color2.color.blue  = 0.95;
    color2.color.alpha = 1.00;
    color2.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with the unified normal gradient.
 *  @return A new WCGGradient instance initialized with the unified normal gradient.
 **/
+ (WCGGradient *)unifiedNormalGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red = color1.color.green = color1.color.blue  = 0.75;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red = color2.color.green = color2.color.blue  = 0.90;
    color2.color.alpha = 1.00;
    color2.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with the unified pressed gradient.
 *  @return A new WCGGradient instance initialized with the unified pressed gradient.
 **/
+ (WCGGradient *)unifiedPressedGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red = color1.color.green = color1.color.blue  = 0.60;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red = color2.color.green = color2.color.blue  = 0.75;
    color2.color.alpha = 1.00;
    color2.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with the unified dark gradient.
 *  @return A new WCGGradient instance initialized with the unified dark gradient.
 **/
+ (WCGGradient *)unifiedDarkGradient
{
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red = color1.color.green = color1.color.blue  = 0.68;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red = color2.color.green = color2.color.blue  = 0.83;
    color2.color.alpha = 1.00;
    color2.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with the source list selected gradient.
 *  @return A new WCGGradient instance initialized with the source list selected gradient.
 **/
+ (WCGGradient *)sourceListSelectedGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red   = 0.06;
    color1.color.green = 0.37;
    color1.color.blue  = 0.85;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red   = 0.30;
    color2.color.green = 0.60;
    color2.color.blue  = 0.92;
    color2.color.alpha = 1.00;
    color2.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with the source list unselected gradient.
 *  @return A new WCGGradient instance initialized with the source list unselected gradient.
 **/
+ (WCGGradient *)sourceListUnselectedGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red   = 0.43;
    color1.color.green = 0.43;
    color1.color.blue  = 0.43;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red   = 0.60;
    color2.color.green = 0.60;
    color2.color.blue  = 0.60;
    color2.color.alpha = 1.00;
    color2.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with a rainbow gradient.
 *  @return A new WCGGradient instance initialized with a rainbow gradient.
 **/
+(WCGGradient *)rainbowGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    WCGGradientElement color1;
    color1.color.red   = 1.00;
    color1.color.green = 0.00;
    color1.color.blue  = 0.00;
    color1.color.alpha = 1.00;
    color1.position = 0.0;
	
    WCGGradientElement color2;
    color2.color.red   = 0.54;
    color2.color.green = 0.00;
    color2.color.blue  = 1.00;
    color2.color.alpha = 1.00;
    color2.position = 1.0;
	
    [newInstance addElement:&color1];
    [newInstance addElement:&color2];
	
    newInstance.blendingMode = WCGChromaticBlendingMode;
	
    return [newInstance autorelease];
}

/** @brief Creates and returns a new WCGGradient instance initialized with a hydrogen spectrum gradient.
 *  @return A new WCGGradient instance initialized with a hydrogen spectrum gradient.
 **/
+(WCGGradient *)hydrogenSpectrumGradient {
    WCGGradient *newInstance = [[self alloc] init];
	
    struct {CGFloat hue; CGFloat position; CGFloat width;} colorBands[4];
	
    colorBands[0].hue = 22;
    colorBands[0].position = 0.145;
    colorBands[0].width = 0.01;
	
    colorBands[1].hue = 200;
    colorBands[1].position = 0.71;
    colorBands[1].width = 0.008;
	
    colorBands[2].hue = 253;
    colorBands[2].position = 0.885;
    colorBands[2].width = 0.005;
	
    colorBands[3].hue = 275;
    colorBands[3].position = 0.965;
    colorBands[3].width = 0.003;
	
    for( NSUInteger i = 0; i < 4; i++ ) {
		CGFloat color[4];
		color[0] = colorBands[i].hue - 180.0 * colorBands[i].width;
		color[1] = 1.0;
		color[2] = 0.001;
		color[3] = 1.0;
		transformHSV_RGB(color);
		
		WCGGradientElement fadeIn;
		fadeIn.color.red   = color[0];
		fadeIn.color.green = color[1];
		fadeIn.color.blue  = color[2];
		fadeIn.color.alpha = color[3];
		fadeIn.position = colorBands[i].position - colorBands[i].width;
		
		color[0] = colorBands[i].hue;
		color[1] = 1.0;
		color[2] = 1.0;
		color[3] = 1.0;
		transformHSV_RGB(color);
		
		WCGGradientElement band;
		band.color.red   = color[0];
		band.color.green = color[1];
		band.color.blue  = color[2];
		band.color.alpha = color[3];
		band.position = colorBands[i].position;
		
		color[0] = colorBands[i].hue + 180.0 * colorBands[i].width;
		color[1] = 1.0;
		color[2] = 0.001;
		color[3] = 1.0;
		transformHSV_RGB(color);
		
		WCGGradientElement fadeOut;
		fadeOut.color.red   = color[0];
		fadeOut.color.green = color[1];
		fadeOut.color.blue  = color[2];
		fadeOut.color.alpha = color[3];
		fadeOut.position = colorBands[i].position + colorBands[i].width;
		
		[newInstance addElement:&fadeIn];
		[newInstance addElement:&band];
		[newInstance addElement:&fadeOut];
    }
	
    newInstance.blendingMode = WCGChromaticBlendingMode;
	
    return [newInstance autorelease];
}


#pragma mark -
#pragma mark Modification

/** @brief Copies the current gradient and sets a new alpha value.
 *  @param alpha The alpha component (0 ≤ alpha ≤ 1).
 *	@return A copy of the current gradient with the new alpha value.
 **/
- (WCGGradient *)gradientWithAlphaComponent:(CGFloat)alpha {
    WCGGradient *newGradient = [[[self class] alloc] init];
	
    WCGGradientElement *curElement = _elementList;
    WCGGradientElement tempElement;
	
    while (curElement != NULL) {
        tempElement = *curElement;
        tempElement.color.alpha = alpha;
        [newGradient addElement:&tempElement];
		
        curElement = curElement->nextElement;
    }
	
	newGradient.blendingMode = self.blendingMode;
	newGradient.angle = self.angle;
	newGradient.gradientType = self.gradientType;
    
    return [newGradient autorelease];
}

/** @brief Copies the current gradient and sets a new blending mode.
 *  @param mode The blending mode.
 *	@return A copy of the current gradient with the new blending mode.
 **/
- (WCGGradient *)gradientWithBlendingMode:(WCGGradientBlendingMode)mode {
    WCGGradient *newGradient = [self copy];  
    newGradient.blendingMode = mode;
    return [newGradient autorelease];
}

/** @brief Copies the current gradient and adds a color stop.
 *
 *	Adds a color stop with <tt>color</tt> at <tt>position</tt> in elementList.
 *	If two elements are at the same position then it is added immediately after the one that was there already.
 *
 *  @param color The color.
 *  @param position The color stop position (0 ≤ position ≤ 1).
 *	@return A copy of the current gradient with the new color stop.
 **/
- (WCGGradient *)addColorStop:(WCGColor *)color atPosition:(CGFloat)position {
    WCGGradient *newGradient = [self copy];
    WCGGradientElement newGradientElement;
	
    //put the components of color into the newGradientElement - must make sure it is a RGB color (not Gray or CMYK)
	newGradientElement.color = WCGRGBAColorFromCGColor(color.cgColor);
    newGradientElement.position = position;
	
    //Pass it off to addElement to take care of adding it to the elementList
    [newGradient addElement:&newGradientElement];
	
    return [newGradient autorelease];
}

/** @brief Copies the current gradient and removes the color stop at <tt>position</tt> from elementList.
 *  @param position The color stop position (0 ≤ position ≤ 1).
 *	@return A copy of the current gradient with the color stop removed.
 **/
- (WCGGradient *)removeColorStopAtPosition:(CGFloat)position {
    WCGGradient *newGradient = [self copy];
    WCGGradientElement removedElement = [newGradient removeElementAtPosition:position];
	
    if ( isnan(removedElement.position) ) {
        [NSException raise:NSRangeException format:@"-[%@ removeColorStopAtPosition:]: no such colorStop at position (%g)", [self class], position];
	}
	
    return [newGradient autorelease];
}

/** @brief Copies the current gradient and removes the color stop at <tt>index</tt> from elementList.
 *  @param index The color stop index.
 *	@return A copy of the current gradient with the color stop removed.
 **/
- (WCGGradient *)removeColorStopAtIndex:(NSUInteger)index {
    WCGGradient *newGradient = [self copy];
    WCGGradientElement removedElement = [newGradient removeElementAtIndex:index];
	
    if ( isnan(removedElement.position) ) {
		[NSException raise:NSRangeException format:@"-[%@ removeColorStopAtIndex:]: index (%i) beyond bounds", [self class], (int)index];
	}
	
    return [newGradient autorelease];
}

#pragma mark -
#pragma mark Information

/** @brief Gets the color at color stop <tt>index</tt> from elementList.
 *  @param index The color stop index.
 *  @return The color at color stop <tt>index</tt>.
 **/
- (CGColorRef)newColorStopAtIndex:(NSUInteger)index {
    WCGGradientElement *element = [self elementAtIndex:index];
	
    if (element != NULL) {
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
		CGFloat colorComponents[4] = {element->color.red, element->color.green, element->color.blue, element->color.alpha};
		return CGColorCreate(self.colorspace.cgColorSpace, colorComponents);
#else
        return CGColorCreateGenericRGB(element->color.red, element->color.green, element->color.blue, element->color.alpha);
#endif
		
	}
	
    [NSException raise:NSRangeException format:@"-[%@ colorStopAtIndex:]: index (%i) beyond bounds", [self class], (int)index];
	
    return NULL;
}

/** @brief Gets the color at an arbitrary position in the gradient.
 *  @param position The color stop position (0 ≤ position ≤ 1).
 *  @return The  color at <tt>position</tt> in gradient.
 **/
- (CGColorRef)newColorAtPosition:(CGFloat)position {
    CGFloat components[4] = {0.0, 0.0, 0.0, 0.0};
	CGColorRef gradientColor;
	
    switch ( self.blendingMode ) {
        case WCGLinearBlendingMode:
			linearEvaluation(&_elementList, &position, components);
			break;
        case WCGChromaticBlendingMode:
			chromaticEvaluation(&_elementList, &position, components);
			break;
        case WCGInverseChromaticBlendingMode:
			inverseChromaticEvaluation(&_elementList, &position, components);
			break;
    }
    
	if (  0.0 != components[3] ) {
		//undo premultiplication that CG requires
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
		CGFloat colorComponents[4] = {components[0] / components[3], components[1] / components[3], components[2] / components[3], components[3]};
		gradientColor = CGColorCreate(self.colorspace.cgColorSpace, colorComponents);
#else
		gradientColor = CGColorCreateGenericRGB(components[0] / components[3], components[1] / components[3], components[2] / components[3], components[3]);
#endif
		
	}
	else {
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
		CGFloat colorComponents[4] = {components[0], components[1], components[2], components[3]};
		gradientColor = CGColorCreate(self.colorspace.cgColorSpace, colorComponents);
#else
		gradientColor = CGColorCreateGenericRGB(components[0], components[1], components[2], components[3]);
#endif
	}
	
	return gradientColor;
}

#pragma mark -
#pragma mark Drawing

/** @brief Draws the gradient into the given graphics context inside the provided rectangle.
 *  @param rect The rectangle to draw into.
 *  @param context The graphics context to draw into.
 **/
- (void)drawSwatchInRect:(CGRect)rect inContext:(CGContextRef)context {
    [self fillRect:rect inContext:context];
}

/** @brief Draws the gradient into the given graphics context inside the provided rectangle.
 *  @param rect The rectangle to draw into.
 *  @param context The graphics context to draw into.
 **/
- (void)fillRect:(CGRect)rect inContext:(CGContextRef)context {
	CGShadingRef myCGShading = NULL;
	
    CGContextSaveGState(context);
	
    CGContextClipToRect(context, *(CGRect *)&rect);
	
	switch ( self.gradientType ) {
		case WCGGradientTypeAxial:
			myCGShading = [self newAxialGradientInRect:rect];
			break;
		case WCGGradientTypeRadial:
			myCGShading = [self newRadialGradientInRect:rect context:context];
			break;
	}
	
    CGContextDrawShading(context, myCGShading);
	
    CGShadingRelease(myCGShading);
    CGContextRestoreGState(context);
}

/** @brief Draws the gradient into the given graphics context clipped to the current drawing path.
 *  @param context The graphics context to draw into.
 **/
- (void)fillPathInContext:(CGContextRef)context {
	if (CGContextIsPathEmpty(context))
        return;
    
    CGShadingRef myCGShading = NULL;
		
    CGContextSaveGState(context);
    
    CGRect bounds = CGContextGetPathBoundingBox(context);
    CGContextClip(context);
    
    switch ( self.gradientType ) {
        case WCGGradientTypeAxial:
            myCGShading = [self newAxialGradientInRect:bounds];
            break;
        case WCGGradientTypeRadial:
            myCGShading = [self newRadialGradientInRect:bounds context:context];
            break;
    }
    
    CGContextDrawShading(context, myCGShading);
    
    CGShadingRelease(myCGShading);
    CGContextRestoreGState(context);
}

/** @brief stroke the gradient into the given graphics context to the current drawing path.
 *  @param context the graphics context to draw into.
 **/
- (void)strokeInContext:(CGContextRef)context {
    if (CGContextIsPathEmpty(context))
        return;
    
    //CGContextSaveGState(context);
    CGContextReplacePathWithStrokedPath(context);
    [self fillPathInContext:context];
    //CGContextRestoreGState(context);
}

#pragma mark -
#pragma mark Private Methods

- (CGShadingRef)newAxialGradientInRect:(CGRect)rect {
    // First Calculate where the beginning and ending points should be
    CGPoint startPoint, endPoint;
	
    if ( self.angle == 0.0 )	{
        startPoint = CGPointMake(CGRectGetMinX(rect), CGRectGetMinY(rect));	// right of rect
        endPoint   = CGPointMake(CGRectGetMaxX(rect), CGRectGetMinY(rect));	// left  of rect
    }
	else if ( self.angle == 90.0 ) {
        startPoint = CGPointMake(CGRectGetMinX(rect), CGRectGetMinY(rect));	// bottom of rect
        endPoint   = CGPointMake(CGRectGetMinX(rect), CGRectGetMaxY(rect));	// top    of rect
    }
	else { // ok, we'll do the calculations now
        CGFloat x, y;
        CGFloat sina, cosa, tana;
		
        CGFloat length;
        CGFloat deltax, deltay;
		
        CGFloat rangle = self.angle * M_PI / 180.0;	//convert the angle to radians
		
        if ( fabs(tan(rangle)) <= 1.0 ) {  //for range [-45,45], [135,225]
            x = CGRectGetWidth(rect);
            y = CGRectGetHeight(rect);
            
            sina = sin(rangle);
            cosa = cos(rangle);
            tana = tan(rangle);
            
            length = x / fabs(cosa) + (y - x * fabs(tana)) * fabs(sina);
            
            deltax = length * cosa / 2.0;
            deltay = length * sina / 2.0;
		} else {		//for range [45,135], [225,315]
            x = CGRectGetHeight(rect);
            y = CGRectGetWidth(rect);
            
			rangle -= M_PI_2;
			
            sina = sin(rangle);
            cosa = cos(rangle);
            tana = tan(rangle);
            
            length = x / fabs(cosa) + (y - x * fabs(tana)) * fabs(sina);
            
            deltax = -length * sina / 2.0;
            deltay = length * cosa / 2.0;
        }
		
        startPoint = CGPointMake(CGRectGetMidX(rect) - deltax, CGRectGetMidY(rect) - deltay);
        endPoint   = CGPointMake(CGRectGetMidX(rect) + deltax, CGRectGetMidY(rect) + deltay);
    }
	
    // Calls to CoreGraphics
    CGShadingRef myCGShading = CGShadingCreateAxial(self.colorspace.cgColorSpace,
                                                    startPoint,
                                                    endPoint,
                                                    _gradientFunction,
                                                    false,
                                                    false);
	
	return myCGShading;
}

- (CGShadingRef)newRadialGradientInRect:(CGRect)rect context:(CGContextRef)context {
    CGPoint startPoint, endPoint;
    CGFloat startRadius, endRadius;
    CGFloat scalex, scaley;
	
    startPoint = endPoint = CGPointMake(CGRectGetMidX(rect), CGRectGetMidY(rect));
	
	startRadius = -1.0;
    if ( CGRectGetHeight(rect)>CGRectGetWidth(rect) ) {
        scalex = CGRectGetWidth(rect)/CGRectGetHeight(rect);
        startPoint.x /= scalex;
        endPoint.x /= scalex;
        scaley = 1.0;
        endRadius = CGRectGetHeight(rect) / 2.0;
    }
	else {
        scalex = 1.0;
        scaley = CGRectGetHeight(rect) / CGRectGetWidth(rect);
        startPoint.y /= scaley;
        endPoint.y /= scaley;
        endRadius = CGRectGetWidth(rect) / 2.0;
    }
	
	CGContextScaleCTM(context, scalex, scaley);
	
    CGShadingRef myCGShading = CGShadingCreateRadial(self.colorspace.cgColorSpace,
                                                     startPoint,
                                                     startRadius,
                                                     endPoint,
                                                     endRadius,
                                                     _gradientFunction,
                                                     true,
                                                     true);
	
	return myCGShading;
}

-(void)setBlendingMode:(WCGGradientBlendingMode)mode {
    _blendingMode = mode;
	
    // Choose what blending function to use
    void *evaluationFunction = NULL;
    switch ( _blendingMode ) {
        case WCGLinearBlendingMode:
			evaluationFunction = (void*)&linearEvaluation;
			break;
        case WCGChromaticBlendingMode:
			evaluationFunction = (void*)&chromaticEvaluation;
			break;
        case WCGInverseChromaticBlendingMode:
			evaluationFunction = (void*)&inverseChromaticEvaluation;
			break;
    }
	
    // replace the current CoreGraphics Function with new one
    if ( _gradientFunction != NULL ) {
        CGFunctionRelease(_gradientFunction);
	}
	
    CGFunctionCallbacks evaluationCallbackInfo = {0 , (CGFunctionEvaluateCallback)evaluationFunction, NULL};	// Version, evaluator function, cleanup function
	
    static const CGFloat input_value_range   [2] = { 0, 1 };					// range  for the evaluator input
    static const CGFloat output_value_ranges [8] = { 0, 1, 0, 1, 0, 1, 0, 1 };	// ranges for the evaluator output (4 returned values)
	
    _gradientFunction = CGFunctionCreate(&_elementList,					//the two transition colors
                                         1, input_value_range  ,		//number of inputs (just fraction of progression)
                                         4, output_value_ranges,		//number of outputs (4 - RGBa)
                                         &evaluationCallbackInfo);		//info for using the evaluator function
}

- (void)addElement:(WCGGradientElement *)newElement {
    if ( _elementList == NULL || newElement->position < _elementList->position ) {
        WCGGradientElement *tmpNext = _elementList;
        _elementList = (WCGGradientElement*)malloc(sizeof(WCGGradientElement));
        if ( _elementList ) {
            *_elementList = *newElement;
            _elementList->nextElement = tmpNext;
        } 
    }
	else {
        WCGGradientElement *curElement = _elementList;
		
        while ( curElement->nextElement != NULL && 
			   !((curElement->position <= newElement->position) && 
				 (newElement->position < curElement->nextElement->position)) ) {
                   curElement = curElement->nextElement;
               }
		
        WCGGradientElement *tmpNext = curElement->nextElement;
        curElement->nextElement = (WCGGradientElement*)malloc(sizeof(WCGGradientElement));
        *(curElement->nextElement) = *newElement;
        curElement->nextElement->nextElement = tmpNext;
    }
}

- (WCGGradientElement)removeElementAtIndex:(NSUInteger)index {
    WCGGradientElement removedElement;
	
    if ( _elementList != NULL ) {
        if ( index == 0 ) {
            WCGGradientElement *tmpNext = _elementList;
            _elementList = _elementList->nextElement;
            
            removedElement = *tmpNext;
            free(tmpNext);
            
            return removedElement;
        }
		
        NSUInteger count = 1;		//we want to start one ahead
        WCGGradientElement *currentElement = _elementList;
        while ( currentElement->nextElement != NULL ) {
            if ( count == index ) {
                WCGGradientElement *tmpNext  = currentElement->nextElement;
                currentElement->nextElement = currentElement->nextElement->nextElement;
                
                removedElement = *tmpNext;
                free(tmpNext);
				
                return removedElement;
            }
			
            count++;
            currentElement = currentElement->nextElement;
        }
    }
	
    // element is not found, return empty element
    removedElement.color.red   = 0.0;
    removedElement.color.green = 0.0;
    removedElement.color.blue  = 0.0;
    removedElement.color.alpha = 0.0;
    removedElement.position = NAN;
    removedElement.nextElement = NULL;
	
    return removedElement;
}

- (WCGGradientElement)removeElementAtPosition:(CGFloat)position {
    WCGGradientElement removedElement;
	
    if ( _elementList != NULL ) {
        if ( _elementList->position == position ) {
            WCGGradientElement *tmpNext = _elementList;
            _elementList = _elementList->nextElement;
            
            removedElement = *tmpNext;
            free(tmpNext);
            
            return removedElement;
        }
		else {
            WCGGradientElement *curElement = _elementList;
            while ( curElement->nextElement != NULL ) {
                if ( curElement->nextElement->position == position ) {
                    WCGGradientElement *tmpNext = curElement->nextElement;
                    curElement->nextElement = curElement->nextElement->nextElement;
                    
                    removedElement = *tmpNext;
                    free(tmpNext);
					
                    return removedElement;
                }
            }
        }
    }
	
    // element is not found, return empty element
    removedElement.color.red   = 0.0;
    removedElement.color.green = 0.0;
    removedElement.color.blue  = 0.0;
    removedElement.color.alpha = 0.0;
    removedElement.position = NAN;
    removedElement.nextElement = NULL;
	
    return removedElement;
}

-(void)removeAllElements {
    while (_elementList != NULL) {
        WCGGradientElement *elementToRemove = _elementList;
        _elementList = _elementList->nextElement;
        free(elementToRemove);
	}
}

- (WCGGradientElement *)elementAtIndex:(NSUInteger)index {
    NSUInteger count = 0;
    WCGGradientElement *currentElement = _elementList;
	
    while ( currentElement != NULL ) {
        if ( count == index ) {
            return currentElement;
		}
		
        count++;
        currentElement = currentElement->nextElement;
    }
	
    return NULL;
}

#pragma mark -
#pragma mark Core Graphics

void linearEvaluation (void *info, const CGFloat *in, CGFloat *out) 
{
    CGFloat position = *in;
	
    if ( *(WCGGradientElement **)info == NULL ) {
        out[0] = out[1] = out[2] = out[3] = 1.0;
        return;
    }
	
    //This grabs the first two colors in the sequence
    WCGGradientElement *color1 = *(WCGGradientElement **)info;
    WCGGradientElement *color2 = color1->nextElement;
	
    //make sure first color and second color are on other sides of position
    while ( color2 != NULL && color2->position < position ) {
        color1 = color2;
        color2 = color1->nextElement;
    }
    //if we don't have another color then make next color the same color
    if ( color2 == NULL ) {
        color2 = color1;
    }
	
    //----------FailSafe settings----------
    //color1->red   = 1; color2->red   = 0;
    //color1->green = 1; color2->green = 0;
    //color1->blue  = 1; color2->blue  = 0;
    //color1->alpha = 1; color2->alpha = 1;
    //color1->position = 0.5;
    //color2->position = 0.5;
    //-------------------------------------
	
    if ( position <= color1->position ) {
        out[0] = color1->color.red; 
        out[1] = color1->color.green;
        out[2] = color1->color.blue;
        out[3] = color1->color.alpha;
    }
	else if ( position >= color2->position ) {
        out[0] = color2->color.red; 
        out[1] = color2->color.green;
        out[2] = color2->color.blue;
        out[3] = color2->color.alpha;
    }
	else {
        //adjust position so that it goes from 0 to 1 in the range from color 1 & 2's position 
        position = (position-color1->position)/(color2->position - color1->position);
		
        out[0] = (color2->color.red   - color1->color.red  )*position + color1->color.red; 
        out[1] = (color2->color.green - color1->color.green)*position + color1->color.green;
        out[2] = (color2->color.blue  - color1->color.blue )*position + color1->color.blue;
        out[3] = (color2->color.alpha - color1->color.alpha)*position + color1->color.alpha;
    }
	
    //Premultiply the color by the alpha.
    out[0] *= out[3];
    out[1] *= out[3];
    out[2] *= out[3];
}

//Chromatic Evaluation - 
//	This blends colors by their Hue, Saturation, and Value(Brightness) right now I just 
//	transform the RGB values stored in the WCGGradientElements to HSB, in the future I may
//	streamline it to avoid transforming in and out of HSB colorspace *for later*
//
//	For the chromatic blend we shift the hue of color1 to meet the hue of color2. To do
//	this we will add to the hue's angle (if we subtract we'll be doing the inverse
//	chromatic...scroll down more for that). All we need to do is keep adding to the hue
//  until we wrap around the colorwheel and get to color2.
void chromaticEvaluation(void *info, const CGFloat *in, CGFloat *out)
{
    CGFloat position = *in;
	
    if ( *(WCGGradientElement **)info == NULL ) {
        out[0] = out[1] = out[2] = out[3] = 1.0;
        return;
    }
	
    // This grabs the first two colors in the sequence
    WCGGradientElement *color1 = *(WCGGradientElement **)info;
    WCGGradientElement *color2 = color1->nextElement;
	
    CGFloat c1[4];
    CGFloat c2[4];
	
    // make sure first color and second color are on other sides of position
    while ( color2 != NULL && color2->position < position ) {
        color1 = color2;
        color2 = color1->nextElement;
    }
    
    // if we don't have another color then make next color the same color
    if ( color2 == NULL ) {
        color2 = color1;
    }
	
    c1[0] = color1->color.red; 
    c1[1] = color1->color.green;
    c1[2] = color1->color.blue;
    c1[3] = color1->color.alpha;
	
    c2[0] = color2->color.red; 
    c2[1] = color2->color.green;
    c2[2] = color2->color.blue;
    c2[3] = color2->color.alpha;
	
    transformRGB_HSV(c1);
    transformRGB_HSV(c2);
    resolveHSV(c1,c2);
	
    if ( c1[0] > c2[0] ) { // if color1's hue is higher than color2's hue then
		c2[0] += 360.0;   // we need to move c2 one revolution around the wheel
	}
	
    if ( position <= color1->position ) {
        out[0] = c1[0]; 
        out[1] = c1[1];
        out[2] = c1[2];
        out[3] = c1[3];
    }
	else if ( position >= color2->position ) {
        out[0] = c2[0]; 
        out[1] = c2[1];
        out[2] = c2[2];
        out[3] = c2[3];
    }
	else {
        //adjust position so that it goes from 0 to 1 in the range from color 1 & 2's position 
        position = (position-color1->position)/(color2->position - color1->position);
		
        out[0] = (c2[0] - c1[0])*position + c1[0]; 
        out[1] = (c2[1] - c1[1])*position + c1[1];
        out[2] = (c2[2] - c1[2])*position + c1[2];
        out[3] = (c2[3] - c1[3])*position + c1[3];
    }
	
    transformHSV_RGB(out);
	
    //Premultiply the color by the alpha.
    out[0] *= out[3];
    out[1] *= out[3];
    out[2] *= out[3];
}

// Inverse Chromatic Evaluation - 
//	Inverse Chromatic is about the same story as Chromatic Blend, but here the Hue
//	is strictly decreasing, that is we need to get from color1 to color2 by decreasing
//	the 'angle' (i.e. 90º -> 180º would be done by subtracting 270º and getting -180º...
//	which is equivalent to 180º mod 360º
void inverseChromaticEvaluation(void *info, const CGFloat *in, CGFloat *out)
{
    CGFloat position = *in;
	
    if (*(WCGGradientElement **)info == NULL) {
        out[0] = out[1] = out[2] = out[3] = 1;
        return;
    }
	
    // This grabs the first two colors in the sequence
    WCGGradientElement *color1 = *(WCGGradientElement **)info;
    WCGGradientElement *color2 = color1->nextElement;
	
    CGFloat c1[4];
    CGFloat c2[4];
	
    //make sure first color and second color are on other sides of position
    while ( color2 != NULL && color2->position < position ) {
        color1 = color2;
        color2 = color1->nextElement;
    }
    
    // if we don't have another color then make next color the same color
    if ( color2 == NULL ) {
        color2 = color1;
    }
	
    c1[0] = color1->color.red; 
    c1[1] = color1->color.green;
    c1[2] = color1->color.blue;
    c1[3] = color1->color.alpha;
	
    c2[0] = color2->color.red; 
    c2[1] = color2->color.green;
    c2[2] = color2->color.blue;
    c2[3] = color2->color.alpha;
	
    transformRGB_HSV(c1);
    transformRGB_HSV(c2);
    resolveHSV(c1,c2);
	
    if ( c1[0] < c2[0] ) //if color1's hue is higher than color2's hue then 
        c1[0] += 360.0;	//	we need to move c2 one revolution back on the wheel
	
	
    if ( position <= color1->position ) {
        out[0] = c1[0]; 
        out[1] = c1[1];
        out[2] = c1[2];
        out[3] = c1[3];
    }
    else if ( position >= color2->position ) {
        out[0] = c2[0]; 
        out[1] = c2[1];
        out[2] = c2[2];
        out[3] = c2[3];
    }
    else {
        //adjust position so that it goes from 0 to 1 in the range from color 1 & 2's position 
        position = (position-color1->position)/(color2->position - color1->position);
		
        out[0] = (c2[0] - c1[0])*position + c1[0]; 
        out[1] = (c2[1] - c1[1])*position + c1[1];
        out[2] = (c2[2] - c1[2])*position + c1[2];
        out[3] = (c2[3] - c1[3])*position + c1[3];
    }
	
    transformHSV_RGB(out);
	
    // Premultiply the color by the alpha.
    out[0] *= out[3];
    out[1] *= out[3];
    out[2] *= out[3];
}

void transformRGB_HSV(CGFloat *components) //H,S,B -> R,G,B
{
    CGFloat H = NAN, S, V;
    CGFloat R = components[0];
	CGFloat G = components[1];
	CGFloat B = components[2];
	
    CGFloat MAX = R > G ? (R > B ? R : B) : (G > B ? G : B);
	CGFloat MIN = R < G ? (R < B ? R : B) : (G < B ? G : B);
	
	if ( MAX == R ) {
        if ( G >= B ) {
            H = 60.0 * (G - B) / (MAX - MIN) + 0.0;
		}
		else {
            H = 60.0 * (G - B) / (MAX - MIN) + 360.0;
		}
	}
	else if ( MAX == G ) {
		H = 60 * (B - R) / (MAX - MIN) + 120.0;
	}
	else if ( MAX == B ) {
		H = 60 * (R - G) / (MAX - MIN) + 240.0;
	}
	
    S = MAX == 0 ? 0 : 1 - MIN/MAX;
    V = MAX;
	
    components[0] = H;
    components[1] = S;
    components[2] = V;
}

void transformHSV_RGB(CGFloat *components) //H,S,B -> R,G,B
{
	CGFloat R = 0.0, G = 0.0, B = 0.0;
	CGFloat H = fmod(components[0], 360.0);	//map to [0,360)
	CGFloat S = components[1];
	CGFloat V = components[2];
	
	int Hi = (int)floor(H / 60.0) % 6;
	CGFloat f  = H / 60.0 - Hi;
	CGFloat p  = V * (1.0 - S);
	CGFloat q  = V * (1.0 - f * S);
	CGFloat t  = V * (1.0 - (1.0 - f) * S);
	
	switch ( Hi) {
		case 0:
			R = V;
			G = t;
			B = p;
			break;
		case 1:
			R = q;
			G = V;
			B = p;
			break;
		case 2:
			R = p;
			G = V;
			B = t;
			break;
		case 3:
			R = p;
			G = q;
			B = V;
			break;
		case 4:
			R = t;
			G = p;
			B = V;
			break;
		case 5:
			R = V;
			G = p;
			B = q;
			break;
    }
	
	components[0] = R;
	components[1] = G;
	components[2] = B;
}

void resolveHSV(CGFloat *color1, CGFloat *color2)	// H value may be undefined (i.e. graycale color)
{                                               //	we want to fill it with a sensible value
	if ( isnan(color1[0]) && isnan(color2[0]) ) {
		color1[0] = color2[0] = 0;
	}
	else if ( isnan(color1[0]) ) {
		color1[0] = color2[0];
	}
	else if ( isnan(color2[0]) ) {
		color2[0] = color1[0];
	}
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(cg)

Gradient::Gradient(cg::Color const& begin,
                   cg::Color const& end,
                   real pos_begin,
                   real pos_end,
                   real angle)
{
    WCGGradientElement color1;
    WCGGradientElement color2;
    
    color1.color = WCGRGBAColorFromCGColor(begin);
    color2.color = WCGRGBAColorFromCGColor(end);
    
    color1.position = pos_begin;
    color2.position = pos_end;
    
    [this->_self addElement:&color1];
    [this->_self addElement:&color2];
    
    this->_self.angle = RAD2ANGLE(angle);
}

void Gradient::set_angle(real angle)
{
    this->_self.angle = RAD2ANGLE(angle);
}

WSI_END_NS
WSI_END_CXX
