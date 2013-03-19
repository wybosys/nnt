
# ifndef __NNT_NNTCG_NgGRADIENT_CB39A2189FAD4CC7AF3E583B506CD790_H_INCLUDED
# define __NNT_NNTCG_NgGRADIENT_CB39A2189FAD4CC7AF3E583B506CD790_H_INCLUDED

# import "NGDefines.h"

NNT_BEGIN_HEADER_OBJC

/**
 *	@brief A structure representing one node in a linked list of RGBA colors.
 **/
typedef struct _NgGradientElement {
    // color.
	NgRGBAColor color;

    // Gradient position (0 ≤ position ≤ 1)
	CGFloat position;
	
    // Pointer to the next NgGradientElement in the list (last element == NULL)
	struct _NgGradientElement *nextElement;
    
} NgGradientElement;

/**
 *	@brief Enumeration of blending modes
 **/
typedef enum _NgBlendingMode {
    // Linear blending mode
	NgLinearBlendingMode,
    
    // Chromatic blending mode
	NgChromaticBlendingMode,
    
    // Inverse chromatic blending mode
	NgInverseChromaticBlendingMode,
    
} NgGradientBlendingMode;

/**
 *	@brief Enumeration of gradient types
 **/
typedef enum _NgGradientType {
    // Axial gradient
	NgGradientTypeAxial,
    
    // Radial gradient
	NgGradientTypeRadial,
    
} NgGradientType;

@class NgColorSpace;
@class NgColor;

@interface NgGradient : NSObject <NSCopying, NSCoding> {
    
    NgGradientBlendingMode _blendingMode;
    CGFloat _angle;	// angle in degrees
	NgGradientType _gradientType;
    
@private
	NgColorSpace *_colorspace;
	NgGradientElement *_elementList;
	CGFunctionRef _gradientFunction;
}

@property (nonatomic, assign, readonly) NgGradientBlendingMode blendingMode;
@property (nonatomic, assign) CGFloat angle;
@property (nonatomic, assign) NgGradientType gradientType;

+ (NgGradient *)gradientWithBeginningColor:(NgColor *)begin endingColor:(NgColor *)end;
+ (NgGradient *)gradientWithBeginningColor:(NgColor *)begin endingColor:(NgColor *)end angle:(CGFloat)angle;
+ (NgGradient *)gradientWithBeginningColor:(NgColor *)begin endingColor:(NgColor *)end beginningPosition:(CGFloat)beginningPosition endingPosition:(CGFloat)endingPosition;

+ (NgGradient *)aquaSelectedGradient;
+ (NgGradient *)aquaNormalGradient;
+ (NgGradient *)aquaPressedGradient;

+ (NgGradient *)unifiedSelectedGradient;
+ (NgGradient *)unifiedNormalGradient;
+ (NgGradient *)unifiedPressedGradient;
+ (NgGradient *)unifiedDarkGradient;

+ (NgGradient *)sourceListSelectedGradient;
+ (NgGradient *)sourceListUnselectedGradient;

+ (NgGradient *)rainbowGradient;
+ (NgGradient *)hydrogenSpectrumGradient;

- (NgGradient *)gradientWithAlphaComponent:(CGFloat)alpha;
- (NgGradient *)gradientWithBlendingMode:(NgGradientBlendingMode)mode;

- (NgGradient *)addColorStop:(NgColor *)color atPosition:(CGFloat)position;	// positions given relative to [0,1]
- (NgGradient *)removeColorStopAtIndex:(NSUInteger)index;
- (NgGradient *)removeColorStopAtPosition:(CGFloat)position;

- (CGColorRef)newColorStopAtIndex:(NSUInteger)index;
- (CGColorRef)newColorAtPosition:(CGFloat)position;

- (void)drawSwatchInRect:(CGRect)rect inContext:(CGContextRef)context;
- (void)fillRect:(CGRect)rect inContext:(CGContextRef)context;
- (void)fillPathInContext:(CGContextRef)context;
- (void)strokeInContext:(CGContextRef)context;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NGColor.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

class Gradient
: public ::nnt::ns::Object<NgGradient>
{
public:
    
    Gradient()
    {
        PASS;
    }
    
    //! angle in rad.
    Gradient(cg::Color const& begin,
             cg::Color const& end,
             real pos_begin,
             real pos_end,
             real angle = 0);
    
    void fill_path(CGContextRef ctx) const
    {
        [this->_self fillPathInContext:ctx];
    }
    
    void fill_rect(CGContextRef ctx, CGRect const& rc) const
    {
        [this->_self fillRect:rc inContext:ctx];
    }
    
    void stroke(CGContextRef ctx) const
    {
        [this->_self strokeInContext:ctx];
    }
    
    //! angle in rad.
    void set_angle(real angle);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif