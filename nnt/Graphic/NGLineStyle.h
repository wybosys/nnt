
# ifndef __NNT_CG_CGLINESTYLE_A0A92DCFC4F249C08C9520D9CD2157B1_H_INCLUDED
# define __NNT_CG_CGLINESTYLE_A0A92DCFC4F249C08C9520D9CD2157B1_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@class NgColor;

@interface NgLineStyle : NSObject <NSCopying, NSMutableCopying> {
@private
	CGLineCap lineCap;
    //	CGLineDash lineDash; // We should make a struct to keep this information
	CGLineJoin lineJoin;
	CGFloat miterLimit;
	CGFloat lineWidth;
	NSArray *dashPattern;
	CGFloat patternPhase;
    //	StrokePattern; // We should make a struct to keep this information
    NgColor *lineColor;
}

@property (nonatomic, readonly, assign) CGLineCap lineCap;
@property (nonatomic, readonly, assign) CGLineJoin lineJoin;
@property (nonatomic, readonly, assign) CGFloat miterLimit;
@property (nonatomic, readonly, assign) CGFloat lineWidth;
@property (nonatomic, readonly, retain) NSArray *dashPattern;
@property (nonatomic, readonly, assign) CGFloat patternPhase;
@property (nonatomic, readonly, retain) NgColor *lineColor;

- (id)init;
- (id)initWithLineStyle:(NgLineStyle*)ls;

/// @name Factory Methods
/// @{
+ (id)lineStyle;
///	@}

/// @name Drawing
/// @{
- (void)setLineStyleInContext:(CGContextRef)theContext;
///	@}

//! set in view.
IOSEXPRESS(
- (void)setLineStyleInView:(UIView*)view;
);

//! set in layer.
- (void)setLineStyleInLayer:(CALayer*)layer;

@end

@interface NgMutableLineStyle : NgLineStyle {
    
}

@property (nonatomic, readwrite, assign) CGLineCap lineCap;
@property (nonatomic, readwrite, assign) CGLineJoin lineJoin;
@property (nonatomic, readwrite, assign) CGFloat miterLimit;
@property (nonatomic, readwrite, assign) CGFloat lineWidth;
@property (nonatomic, readwrite, retain) NSArray *dashPattern;
@property (nonatomic, readwrite, assign) CGFloat patternPhase;
@property (nonatomic, readwrite, retain) NgColor *lineColor;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NGColor.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

template <typename styleT>
class _LineStyle
: public ns::Object<styleT>
{
    typedef _LineStyle<styleT> self_type;
    typedef ns::Object<styleT> super;
    
public:
    
    _LineStyle()
    {
        PASS;
    }
    
    _LineStyle(styleT* ls)
    : super(ls)
    {
        PASS;
    }
    
    CGLineCap cap() const
    {
        return this->_self.lineCap;
    }
    
    CGLineJoin join() const
    {
        return this->_self.lineJoin;
    }
    
    CGFloat miterlimit() const
    {
        return this->_self.miterLimit;
    }
    
    CGFloat width() const
    {
        return this->_self.lineWidth;
    }
    
    Color color() const
    {
        return this->_self.lineColor;
    }
    
};

class MutableLineStyle
: public _LineStyle<NgMutableLineStyle>
{
    typedef _LineStyle<NgMutableLineStyle> super;
    
public:
    
    MutableLineStyle()
    {
        PASS;
    }
    
    MutableLineStyle(NgMutableLineStyle* r)
    : super(r)
    {
        PASS;
    }
    
    void set_cap(CGLineCap val)
    {
        this->_self.lineCap = val;
    }
    
    void set_join(CGLineJoin val)
    {
        this->_self.lineJoin = val;
    }
    
    void set_miterlimit(real val)
    {
        this->_self.miterLimit = val;
    }
    
    void set_width(real val)
    {
        this->_self.lineWidth = val;
    }
    
    void set_color(Color const& color)
    {
        this->_self.lineColor _assign_ color;
    }
    
};

class LineStyle
: public _LineStyle<NgLineStyle>
{
    typedef _LineStyle<NgLineStyle> super;
    
public:
    
    LineStyle()
    {
        PASS;
    }
    
    LineStyle(MutableLineStyle const& r)
    : super((NgLineStyle*)r)
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif