
# import "Core.h"
# import "NGFillColor.h"
# import "NGFillGradient.h"
# import "NGFillImage.h"
# import "NGFill.h"
# import "NGImage.h"
# import "NGColor.h"

NNT_BEGIN_OBJC

@implementation NgFill

#pragma mark -
#pragma mark init/dealloc

/** @brief Creates and returns a new NgFill instance initialized with a given color.
 *  @param aColor The color.
 *  @return A new NgFill instance initialized with the given color.
 **/
+(NgFill *)fillWithColor:(NgColor *)aColor 
{
	return [[safe_alloc(NgFillColor) initWithColor:aColor] autorelease];
}

/** @brief Creates and returns a new NgFill instance initialized with a given gradient.
 *  @param aGradient The gradient.
 *  @return A new NgFill instance initialized with the given gradient.
 **/
+(NgFill *)fillWithGradient:(NgGradient *)aGradient 
{
	return [[safe_alloc(NgFillGradient) initWithGradient: aGradient] autorelease];
}

/** @brief Creates and returns a new NgFill instance initialized with a given image.
 *  @param anImage The image.
 *  @return A new NgFill instance initialized with the given image.
 **/
+(NgFill *)fillWithImage:(NgImage *)anImage 
{
	return [[safe_alloc(NgFillImage) initWithImage:anImage] autorelease];
}

/** @brief Initializes a newly allocated NgFill object with the provided color.
 *  @param aColor The color.
 *  @return The initialized NgFill object.
 **/
-(id)initWithColor:(NgColor *)aColor 
{
	[self release];
	
	self = [safe_alloc(NgFillColor) initWithColor: aColor];
	
	return self;
}

/** @brief Initializes a newly allocated NgFill object with the provided gradient.
 *  @param aGradient The gradient.
 *  @return The initialized NgFill object.
 **/
-(id)initWithGradient:(NgGradient *)aGradient 
{
	[self release];
	
	self = [safe_alloc(NgFillGradient) initWithGradient: aGradient];
	
	return self;
}

/** @brief Initializes a newly allocated NgFill object with the provided image.
 *  @param anImage The image.
 *  @return The initialized NgFill object.
 **/
-(id)initWithImage:(NgImage *)anImage 
{
	[self release];
	
	self = [safe_alloc(NgFillImage) initWithImage: anImage];
	
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

@implementation NgFill(AbstractMethods)

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


NNT_END_OBJC