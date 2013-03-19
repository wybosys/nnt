
# import "Core.h"
# import "NGLineStyle.h"
# import "NGColor.h"
# import "CoreGraphic+NNT.h"

NNT_BEGIN_OBJC

/**	@cond */
@interface NgLineStyle ()

@property (nonatomic, readwrite, assign) CGLineCap lineCap;
@property (nonatomic, readwrite, assign) CGLineJoin lineJoin;
@property (nonatomic, readwrite, assign) CGFloat miterLimit;
@property (nonatomic, readwrite, assign) CGFloat lineWidth;
@property (nonatomic, readwrite, retain) NSArray *dashPattern;
@property (nonatomic, readwrite, assign) CGFloat patternPhase;
@property (nonatomic, readwrite, retain) NgColor *lineColor;

@end
/**	@endcond */

/** @brief Immutable wrapper for various line drawing properties.
 *
 *	@see See Apple's <a href="http://developer.apple.com/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/dq_paths/dq_paths.html#//apple_ref/doc/uid/TP30001066-CH211-TPXREF105">Quartz 2D</a>
 *	and <a href="http://developer.apple.com/documentation/GraphicsImaging/Reference/CGContext/Reference/reference.html">CGContext</a> 
 *	documentation for more information about each of these properties.
 *
 *  In general, you will want to create a NgMutableLineStyle if you want to customize properties.
 **/

@implementation NgLineStyle

/** @property lineCap
 *  @brief The style for the endpoints of lines drawn in a graphics context.
 **/
@synthesize lineCap;

/** @property lineJoin
 *  @brief The style for the joins of connected lines in a graphics context.
 **/
@synthesize lineJoin;

/** @property miterLimit
 *  @brief The miter limit for the joins of connected lines in a graphics context.
 **/
@synthesize miterLimit;

/** @property lineWidth
 *  @brief The line width for a graphics context.
 **/
@synthesize lineWidth;

/** @property dashPattern
 *  @brief The dash-and-space pattern for the line.
 **/
@synthesize dashPattern;

/** @property patternPhase
 *  @brief The starting phase of the line dash pattern.
 **/
@synthesize patternPhase;

/** @property lineColor
 *  @brief The current stroke color in a context.
 **/
@synthesize lineColor;

#pragma mark -
#pragma mark init/dealloc

/** @brief Creates and returns a new NgLineStyle instance.
 *  @return A new NgLineStyle instance.
 **/
+ (id)lineStyle
{
    return [[[self alloc] init] autorelease];
}

- (id)init
{
    self = [super init];
	if (self == nil)
        return nil;

    lineCap = kCGLineCapButt;
    lineJoin = kCGLineJoinMiter;
    miterLimit = 10.0;
    lineWidth = 1.0;
    dashPattern = nil;
    patternPhase = 0.0;
    lineColor = [[NgColor blackColor] retain];

	return self;
}

- (id)initWithLineStyle:(NgLineStyle *)ls {
    self.lineCap = ls.lineCap;
    self.lineJoin = ls.lineJoin;
    self.miterLimit = ls.miterLimit;
    self.lineWidth = ls.lineWidth;
    self.dashPattern = ls.dashPattern;
    self.patternPhase = ls.patternPhase;
    self.lineColor = ls.lineColor;
    
    return self;
}

-(void)dealloc
{
    [lineColor release];
	[dashPattern release];
	[super dealloc];
}

#pragma mark -
#pragma mark Drawing

/** @brief Sets all of the line drawing properties in the given graphics context.
 *  @param theContext The graphics context.
 **/
-(void)setLineStyleInContext:(CGContextRef)theContext
{
	CGContextSetLineCap(theContext, lineCap);
	CGContextSetLineJoin(theContext, lineJoin);
	CGContextSetMiterLimit(theContext, miterLimit);
	CGContextSetLineWidth(theContext, lineWidth);
	if ( dashPattern.count > 0 ) {
		CGFloat *dashLengths = (CGFloat *)calloc(dashPattern.count, sizeof(CGFloat));
        
		NSUInteger dashCounter = 0;
		for ( NSNumber *currentDashLength in dashPattern ) {
			dashLengths[dashCounter++] = [currentDashLength doubleValue];
		}
		
		CGContextSetLineDash(theContext, patternPhase, dashLengths, dashPattern.count);
		free(dashLengths);
	}
	CGContextSetStrokeColorWithColor(theContext, lineColor.cgColor);
}

#pragma mark -
#pragma mark NSCopying methods

-(id)copyWithZone:(NSZone *)zone
{
    NgLineStyle *styleCopy = [[NgLineStyle allocWithZone:zone] init];
 	
	styleCopy->lineCap = self->lineCap;
	styleCopy->lineJoin = self->lineJoin;
	styleCopy->miterLimit = self->miterLimit;
	styleCopy->lineWidth = self->lineWidth;
	styleCopy->dashPattern = [self->dashPattern copy];
	styleCopy->patternPhase = self->patternPhase;
    styleCopy->lineColor = [self->lineColor copy];
    
    return styleCopy;
}

-(id)mutableCopyWithZone:(NSZone *)zone
{
    NgLineStyle *styleCopy = [[NgMutableLineStyle allocWithZone:zone] init];
 	
	styleCopy->lineCap = self->lineCap;
	styleCopy->lineJoin = self->lineJoin;
	styleCopy->miterLimit = self->miterLimit;
	styleCopy->lineWidth = self->lineWidth;
	styleCopy->dashPattern = [self->dashPattern copy];
	styleCopy->patternPhase = self->patternPhase;
    styleCopy->lineColor = [self->lineColor copy];
    
    return styleCopy;
}

IOSEXPRESS(
- (void)setLineStyleInView:(UIView*)view {
    [self setLineStyleInLayer:view.layer];
}
);

- (void)setLineStyleInLayer:(CALayer*)layer {
    layer.borderColor = self.lineColor.cgColor;
    layer.borderWidth = self.lineWidth;
}

@end

@implementation NgMutableLineStyle

/** @property lineCap
 *  @brief The style for the endpoints of lines drawn in a graphics context.
 **/
@dynamic lineCap;

/** @property lineJoin
 *  @brief The style for the joins of connected lines in a graphics context.
 **/
@dynamic lineJoin;

/** @property miterLimit
 *  @brief The miter limit for the joins of connected lines in a graphics context.
 **/
@dynamic miterLimit;

/** @property lineWidth
 *  @brief The line width for a graphics context.
 **/
@dynamic lineWidth;

/** @property dashPattern
 *  @brief The dash-and-space pattern for the line.
 **/
@dynamic dashPattern;

/** @property patternPhase
 *  @brief The starting phase of the line dash pattern.
 **/
@dynamic patternPhase;

/** @property lineColor
 *  @brief The current stroke color in a context.
 **/
@dynamic lineColor;

@end


NNT_END_OBJC