
# ifndef __NNT_UIKIT_CGSHADOW_AD5EABBDE6A14A9EA676B22F0469784D_H_INCLUDED
# define __NNT_UIKIT_CGSHADOW_AD5EABBDE6A14A9EA676B22F0469784D_H_INCLUDED

# import "WCGColor.h"

NNT_BEGIN_HEADER_OBJC

# define kCGShadowLineWidth           1.5f

typedef enum {
    SideTypeInner = 0x1,
    SideTypeOutter = 0x2,
    SideTypeDouble = 0x3,
    SideTypeFill = 0x4,
} SideType;

@interface CGShadow : NSObject <NSCopying, NSCoding> {
    
    //! shadow color.
    WCGColor *_shadowColor, *_beginColor, *_endColor;
    
    //! offset.
    CGSize  _offset;
    
    //! direction.
    CGSize _direction;
    
    //! radius.
    CGFloat _radius;
    
    //! opactity.
    CGFloat _opacity;
    
    //! side.
    SideType _sideType;
    
    //! alpha. default 0.33f.
    real _alpha;
    
}

@property (nonatomic, retain) WCGColor *shadowColor, *beginColor, *endColor;
@property (nonatomic, assign) SideType sideType;
@property (nonatomic, assign) CGSize offset, direction;
@property (nonatomic, assign) CGFloat radius;
@property (nonatomic, assign) CGFloat opacity;
@property (nonatomic, assign) real alpha;

//! default shadow.
+ (id)shadow;
+ (id)textShadow;

//! set.
- (void)setInContext:(CGContextRef)ctx;
- (void)setInLayer:(CALayer*)layer;

//! shadow color.
- (WCGColor*)alphaColor;

//! draw.
- (void)drawInContext:(CGContextRef)ctx;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

class Shadow
: public ns::Object<CGShadow>
{
    typedef ns::Object<CGShadow> super;
    
public:
    
    Shadow()
    {
        PASS;
    }
    
    Shadow(objc_type* r)
    : super(r)
    {
        PASS;
    }
    
    Shadow(Shadow const& r)
    : super(r._self)
    {
        PASS;
    }
    
    Shadow(Color const& color)
    {
        this->set_color(color);
    }
    
    void set_offset(Point const& pt)
    {
        this->_self.offset = Size(pt.x, pt.y);
    }
    
    CGSize offset() const
    {
        return this->_self.offset;
    }
    
    void set_direction(Point const& pt)
    {
        this->_self.direction = Size(pt.x, pt.y);
    }
    
    CGSize direction() const
    {
        return this->_self.direction;
    }
    
    void set_radius(real val)
    {
        this->_self.radius = val;
    }
    
    real radius() const
    {
        return this->_self.radius;
    }
    
    void set_opacity(real val)
    {
        this->_self.opacity = val;
    }
    
    real opacity() const
    {
        return this->_self.opacity;
    }
    
    void set_color(Color const& color)
    {
        this->_self.shadowColor = color;
    }
    
    Color color() const
    {
        return this->_self.shadowColor;
    }
    
    Color shadow_color() const
    {
        return [this->_self alphaColor];
    }
    
    void set_alpha(real val)
    {
        this->_self.alpha = val;
    }
    
    real alpha() const
    {
        return this->_self.alpha;
    }
    
    void set_side(SideType st)
    {
        this->_self.sideType = st;
    }
    
    SideType side() const
    {
        return this->_self.sideType;
    }
    
    void stroke(CGContextRef ctx) const
    {
        [this->_self drawInContext:ctx];
    }
    
    void apply(CALayer* layer)
    {
        [this->_self setInLayer:layer];
    }

# ifdef NNT_TARGET_IOS
    
    void apply(UIView* view)
    {
        [this->_self setInLayer:view.layer];
    }

# endif
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif