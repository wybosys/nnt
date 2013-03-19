
# import "Core.h"
# import "WCGTextStyle.h"

# ifdef WSI_TARGET_MAC
# import "NSFont+WCG.h"
# endif

# import "WCGDefines.h"

WSI_BEGIN_OBJC

/**	@cond */
@interface WCGTextStyle ()

@property (readwrite, copy, nonatomic)   NSString *fontName;
@property (readwrite, assign, nonatomic) CGFloat fontSize; 
@property (readwrite, assign, nonatomic) WCGFontType fontType;
@property (readwrite, copy, nonatomic)   WCGColor *color;
@property (readwrite, assign, nonatomic) WCGAlignment alignment;
@property (readwrite, assign, nonatomic) IOSEXPRESS(UILineBreakMode) MACEXPRESS(NSLineBreakMode) linebreak;
@property (readwrite, copy, nonatomic)   CGShadow *textShadow;
@property (readwrite, assign, nonatomic) BOOL scaleToFit;
@property (readwrite, assign, nonatomic) real scaleToFitOffset, scaleToFitMax;
@property (readwrite, assign, nonatomic) real charRotation;

@end
/**	@endcond */

/** @brief Immutable wrapper for various text style properties.
 *
 *  If you need to customize properties, you should create a WCGMutableTextStyle.
 **/

@implementation WCGTextStyle

/** @property fontSize
 *  @brief The font size.
 **/
@synthesize fontSize;

@synthesize fontType;

/** @property fontName
 *  @brief The font name.
 **/
@synthesize fontName;

/** @property color
 *  @brief The current text color.
 **/
@synthesize color;

/** @property alignment.
 **/
@synthesize alignment;

/** @property line break mode.
 **/
@synthesize linebreak;

/** @property shadow.
 **/
@synthesize textShadow;

@synthesize scaleToFit;
@synthesize scaleToFitOffset;
@synthesize scaleToFitMax;

@synthesize charRotation;

#pragma mark -
#pragma mark Factory Methods

+ (id)textStyle {
	return [[[self alloc] init] autorelease];
}

#pragma mark -
#pragma mark Initialization and teardown

- (id)init {
    self = [super init];
    if (self == nil)
        return nil;
    
    fontName = @"Helvetica";
    fontSize = 12.0;
    fontType = WCGFontTypeRegular;
    color = [[WCGColor blackColor] retain];
    linebreak = IOSEXPRESS(UILineBreakModeMiddleTruncation) MACEXPRESS(NSLineBreakByTruncatingMiddle);
    textShadow = nil;
    scaleToFit = NO;
    scaleToFitOffset = 0;
    scaleToFitMax = 99999;
    alignment = WCGAlignmentCenter;
    charRotation = 0;

	return self;
}

-(void)dealloc {
	[fontName release];
	[color release];
    [textShadow release];
	[super dealloc];
}

#pragma mark -
#pragma mark NSCoding methods

- (void)encodeWithCoder:(NSCoder *)coder {
	[coder encodeObject:self.fontName forKey:@"fontName"];
	[coder encodeDouble:self.fontSize forKey:@"fontSize"];
    [coder encodeInt:self.fontType forKey:@"fontType"];
	[coder encodeObject:self.color forKey:@"color"];
    [coder encodeObject:self.textShadow forKey:@"textShadow"];
    [coder encodeInt:self.scaleToFit forKey:@"scaleToFit"];
    [coder encodeFloat:self.scaleToFitOffset forKey:@"scaleToFitOffset"];
    [coder encodeInt:self.alignment forKey:@"alignment"];
    [coder encodeInt:self.linebreak forKey:@"linebreak"];
    [coder encodeFloat:self.scaleToFitMax forKey:@"scaleToFitMax"];
    [coder encodeFloat:self.charRotation forKey:@"charRotation"];
}

- (id)initWithCoder:(NSCoder *)coder {
	self = [super init];
    if (self == nil)
        return self;
    
    self->fontName = [[coder decodeObjectForKey:@"fontName"] copy];
    self->fontSize = [coder decodeDoubleForKey:@"fontSize"];
    self->fontType = [coder decodeIntForKey:@"fontType"];
    self->color = [[coder decodeObjectForKey:@"color"] copy];
    self->textShadow = [[coder decodeObjectForKey:@"textShadow"] copy];
    self->scaleToFit = [coder decodeIntForKey:@"scaleToFit"];
    self->scaleToFitOffset = [coder decodeFloatForKey:@"scaleToFitOffset"];
    self->alignment = (WCGAlignment)[coder decodeIntForKey:@"alignment"];
    self->linebreak = (UILineBreakMode)[coder decodeIntForKey:@"linebreak"];
    self->scaleToFitMax = [coder decodeFloatForKey:@"scaleToFitMax"];
    self->charRotation = [coder decodeFloatForKey:@"charRotation"];

    return self;
}

#pragma mark -
#pragma mark Copying

- (id)copyWithZone:(NSZone *)zone {
	WCGTextStyle *newCopy = [[WCGTextStyle allocWithZone:zone] init];
	newCopy->fontName = [self->fontName copy];
	newCopy->color = [self->color copy];
	newCopy->fontSize = self->fontSize;
    newCopy->fontType = self->fontType;
    newCopy->textShadow = [self->textShadow copy];
    newCopy->scaleToFit = self->scaleToFit;
    newCopy->scaleToFitOffset = self->scaleToFitOffset;
    newCopy->alignment = self->alignment;
    newCopy->linebreak = self->linebreak;
    newCopy->scaleToFitMax = self->scaleToFitMax;
    newCopy->charRotation = self->charRotation;
	return newCopy;
}

- (id)mutableCopyWithZone:(NSZone *)zone {
	WCGTextStyle *newCopy = [[WCGMutableTextStyle allocWithZone:zone] init];
	newCopy->fontName = [self->fontName copy];
	newCopy->color = [self->color copy];
	newCopy->fontSize = self->fontSize;
    newCopy->fontType = self->fontType;
    newCopy->textShadow = [self->textShadow copy];
    newCopy->scaleToFit = self->scaleToFit;
    newCopy->scaleToFitOffset = self->scaleToFitOffset;
    newCopy->alignment = self->alignment;
    newCopy->linebreak = self->linebreak;
    newCopy->scaleToFitMax = self->scaleToFitMax;
    newCopy->charRotation = self->charRotation;
	return newCopy;
}

# ifdef WSI_TARGET_IOS

- (UIFont*)uiFont {
    NSString *theFontName = self.fontName;
    switch (self.fontType) {
        default: break;
        case WCGFontTypeBold: theFontName = [theFontName stringByAppendingString:@"-Bold"]; break;
        case WCGFontTypeItalic: theFontName = [theFontName stringByAppendingString:@"-Italic"]; break;
        case WCGFontTypeBoldItalic: theFontName = [theFontName stringByAppendingString:@"-BoldItalic"]; break;
    }
    
    UIFont *theFont = [UIFont fontWithName:theFontName size:self.fontSize];
    return theFont;
}

# endif

# ifdef WSI_TARGET_MAC

- (NSDictionary*)uiFontAttributes {
    NSString *theFontName = self.fontName;
    switch (self.fontType) {
        default: break;
        case WCGFontTypeBold: theFontName = [theFontName stringByAppendingString:@"-Bold"]; break;
        case WCGFontTypeItalic: theFontName = [theFontName stringByAppendingString:@"-Italic"]; break;
        case WCGFontTypeBoldItalic: theFontName = [theFontName stringByAppendingString:@"-BoldItalic"]; break;
    }
    
    NSFont *theFont = [NSFont fontWithName:theFontName size:self.fontSize];
    return [theFont getAttributes];
}

# endif

- (CGSize)sizeOfString:(NSString *)string {
    
# ifdef WSI_TARGET_IOS
	UIFont *theFont = [UIFont fontWithName:self.fontName size:self.fontSize];
	CGSize textSize = [string sizeWithFont:theFont];	
# endif
    
# ifdef WSI_TARGET_MAC
    NSFont* theFont = [NSFont fontWithName:self.fontName size:self.fontSize];
    NSDictionary* attrs = [theFont getAttributes];
    NSSize textSize = [string sizeWithAttributes:attrs];
# endif
    
	return ::wsi::cg::conv(textSize);
}

@end

@implementation WCGMutableTextStyle

/** @property fontSize
 *  @brief The font size.
 **/
@dynamic fontSize;

/** @property fontName
 *  @brief The font name.
 **/
@dynamic fontName;

/** @property color
 *  @brief The current text color.
 **/
@dynamic color;

// @property alignment.
@dynamic alignment;

// @property linebreak.
@dynamic linebreak;

// @property shadow.
@dynamic textShadow;

@dynamic fontType;

@dynamic scaleToFitOffset;

@dynamic scaleToFit;

@dynamic scaleToFitMax;

@dynamic charRotation;

@end


WSI_END_OBJC
