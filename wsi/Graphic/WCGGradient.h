
# ifndef __WSI_WSICG_WCGGRADIENT_CB39A2189FAD4CC7AF3E583B506CD790_H_INCLUDED
# define __WSI_WSICG_WCGGRADIENT_CB39A2189FAD4CC7AF3E583B506CD790_H_INCLUDED

# import "WCGDefines.h"

WSI_BEGIN_HEADER_OBJC

/**
 *	@brief A structure representing one node in a linked list of RGBA colors.
 **/
typedef struct _WCGGradientElement {
    // color.
	WCGRGBAColor color;

    // Gradient position (0 ≤ position ≤ 1)
	CGFloat position;
	
    // Pointer to the next WCGGradientElement in the list (last element == NULL)
	struct _WCGGradientElement *nextElement;
    
} WCGGradientElement;

/**
 *	@brief Enumeration of blending modes
 **/
typedef enum _WCGBlendingMode {
    // Linear blending mode
	WCGLinearBlendingMode,
    
    // Chromatic blending mode
	WCGChromaticBlendingMode,
    
    // Inverse chromatic blending mode
	WCGInverseChromaticBlendingMode,
    
} WCGGradientBlendingMode;

/**
 *	@brief Enumeration of gradient types
 **/
typedef enum _WCGGradientType {
    // Axial gradient
	WCGGradientTypeAxial,
    
    // Radial gradient
	WCGGradientTypeRadial,
    
} WCGGradientType;

@class WCGColorSpace;
@class WCGColor;

@interface WCGGradient : NSObject <NSCopying, NSCoding> {
    
    WCGGradientBlendingMode _blendingMode;
    CGFloat _angle;	// angle in degrees
	WCGGradientType _gradientType;
    
@private
	WCGColorSpace *_colorspace;
	WCGGradientElement *_elementList;
	CGFunctionRef _gradientFunction;
}

@property (nonatomic, assign, readonly) WCGGradientBlendingMode blendingMode;
@property (nonatomic, assign) CGFloat angle;
@property (nonatomic, assign) WCGGradientType gradientType;

+ (WCGGradient *)gradientWithBeginningColor:(WCGColor *)begin endingColor:(WCGColor *)end;
+ (WCGGradient *)gradientWithBeginningColor:(WCGColor *)begin endingColor:(WCGColor *)end angle:(CGFloat)angle;
+ (WCGGradient *)gradientWithBeginningColor:(WCGColor *)begin endingColor:(WCGColor *)end beginningPosition:(CGFloat)beginningPosition endingPosition:(CGFloat)endingPosition;

+ (WCGGradient *)aquaSelectedGradient;
+ (WCGGradient *)aquaNormalGradient;
+ (WCGGradient *)aquaPressedGradient;

+ (WCGGradient *)unifiedSelectedGradient;
+ (WCGGradient *)unifiedNormalGradient;
+ (WCGGradient *)unifiedPressedGradient;
+ (WCGGradient *)unifiedDarkGradient;

+ (WCGGradient *)sourceListSelectedGradient;
+ (WCGGradient *)sourceListUnselectedGradient;

+ (WCGGradient *)rainbowGradient;
+ (WCGGradient *)hydrogenSpectrumGradient;

- (WCGGradient *)gradientWithAlphaComponent:(CGFloat)alpha;
- (WCGGradient *)gradientWithBlendingMode:(WCGGradientBlendingMode)mode;

- (WCGGradient *)addColorStop:(WCGColor *)color atPosition:(CGFloat)position;	// positions given relative to [0,1]
- (WCGGradient *)removeColorStopAtIndex:(NSUInteger)index;
- (WCGGradient *)removeColorStopAtPosition:(CGFloat)position;

- (CGColorRef)newColorStopAtIndex:(NSUInteger)index;
- (CGColorRef)newColorAtPosition:(CGFloat)position;

- (void)drawSwatchInRect:(CGRect)rect inContext:(CGContextRef)context;
- (void)fillRect:(CGRect)rect inContext:(CGContextRef)context;
- (void)fillPathInContext:(CGContextRef)context;
- (void)strokeInContext:(CGContextRef)context;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "WCGColor.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cg)

class Gradient
: public ::wsi::ns::Object<WCGGradient>
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif