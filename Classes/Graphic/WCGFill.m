
# import "Core.h"
# import "WCGFillColor.h"
# import "WCGFillGradient.h"
# import "WCGFillImage.h"
# import "WCGFill.h"
# import "WCGImage.h"
# import "WCGColor.h"

WSI_BEGIN_OBJC

@implementation WCGFill

#pragma mark -
#pragma mark init/dealloc

/** @brief Creates and returns a new WCGFill instance initialized with a given color.
 *  @param aColor The color.
 *  @return A new WCGFill instance initialized with the given color.
 **/
+(WCGFill *)fillWithColor:(WCGColor *)aColor 
{
	return [[safe_alloc(WCGFillColor) initWithColor:aColor] autorelease];
}

/** @brief Creates and returns a new WCGFill instance initialized with a given gradient.
 *  @param aGradient The gradient.
 *  @return A new WCGFill instance initialized with the given gradient.
 **/
+(WCGFill *)fillWithGradient:(WCGGradient *)aGradient 
{
	return [[safe_alloc(WCGFillGradient) initWithGradient: aGradient] autorelease];
}

/** @brief Creates and returns a new WCGFill instance initialized with a given image.
 *  @param anImage The image.
 *  @return A new WCGFill instance initialized with the given image.
 **/
+(WCGFill *)fillWithImage:(WCGImage *)anImage 
{
	return [[safe_alloc(WCGFillImage) initWithImage:anImage] autorelease];
}

/** @brief Initializes a newly allocated WCGFill object with the provided color.
 *  @param aColor The color.
 *  @return The initialized WCGFill object.
 **/
-(id)initWithColor:(WCGColor *)aColor 
{
	[self release];
	
	self = [safe_alloc(WCGFillColor) initWithColor: aColor];
	
	return self;
}

/** @brief Initializes a newly allocated WCGFill object with the provided gradient.
 *  @param aGradient The gradient.
 *  @return The initialized WCGFill object.
 **/
-(id)initWithGradient:(WCGGradient *)aGradient 
{
	[self release];
	
	self = [safe_alloc(WCGFillGradient) initWithGradient: aGradient];
	
	return self;
}

/** @brief Initializes a newly allocated WCGFill object with the provided image.
 *  @param anImage The image.
 *  @return The initialized WCGFill object.
 **/
-(id)initWithImage:(WCGImage *)anImage 
{
	[self release];
	
	self = [safe_alloc(WCGFillImage) initWithImage: anImage];
	
	return self;
}

#pragma mark -
#pragma mark NSCopying methods

-(id)copyWithZone:(NSZone *)zone
{
	// do nothing--implemented in subclasses
	return nil;
}

#pragma mark -
#pragma mark NSCoding methods

-(void)encodeWithCoder:(NSCoder *)coder
{
	// do nothing--implemented in subclasses
}

-(id)initWithCoder:(NSCoder *)coder
{
	// do nothing--implemented in subclasses
	return nil;
}

@end

#pragma mark -

@implementation WCGFill(AbstractMethods)

#pragma mark -
#pragma mark Drawing

/** @brief Draws the gradient into the given graphics context inside the provided rectangle.
 *  @param theRect The rectangle to draw into.
 *  @param theContext The graphics context to draw into.
 **/
-(void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext
{
	// do nothing--subclasses override to do drawing here
}

/** @brief Draws the gradient into the given graphics context clipped to the current drawing path.
 *  @param theContext The graphics context to draw into.
 **/
-(void)fillPathInContext:(CGContextRef)theContext
{
	// do nothing--subclasses override to do drawing here
}

@end


WSI_END_OBJC