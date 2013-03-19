
# ifndef __NNT_UIKIT_WCALAYER_98B15EB4A4F345F5AE98E0E75C260522_H_INCLUDED
# define __NNT_UIKIT_WCALAYER_98B15EB4A4F345F5AE98E0E75C260522_H_INCLUDED

# import <QuartzCore/CALayer.h>
# import "WCGDefines.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(WCGFill);
NNTDECL_EXTERN_CLASS(WCALayerTheme);

@interface CALayer (WCA)

//! move funcitons.
- (void)moveTo:(CGPoint)pt;
- (void)moveToSize:(CGSize)size;
- (void)moveToCenter:(CGPoint)pt;

//! animations.
- (void)freeze;
- (void)thaw;

//! get center of layer.
- (CGPoint)centerPoint;
- (CGPoint)clientCenterPoint;

//! set theme.
- (void)applyTheme:(WCALayerTheme*)theme;

@end

NNTDECL_CATEGORY(CALayer, WCA);

@interface WCALayer : CALayer {
    
    //! fill.
    WCGFill *backgroundFill;
    
    //! theme.
    WCALayerTheme *theme;
    
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@property (nonatomic, retain) WCGFill *backgroundFill;
@property (nonatomic, retain) WCALayerTheme *theme;

//! init.
- (id)init;

//! owner draw.
- (void)ownerDraw:(CGRect)rect context:(CGContextRef)context;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "WCAObject.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ca)

NNT_BEGIN_NS(tpl)

template <typename objcT>
class Border
: public Object<objcT>
{
    typedef Object<objcT> super;
    
public:
    
    Border(objcT* r)
    : super(r)
    {
        PASS;
    }
    
    void set_width(real v)
    {
        this->_self.borderWidth = v;
    }
    
    real width() const
    {
        return this->_self.borderWidth;
    }
    
    void set_color(cg::Color const& c)
    {
        this->_self.borderColor = c;
    }
    
    cg::Color color() const
    {
        return this->_self.borderColor;
    }
    
};

template <typename objcT>
class Layer
: public Object<objcT>
{
    typedef Object<objcT> super;
    
public:
    
    typedef Border<objcT> border_type;
    
    Layer()
    {
        PASS;
    }
    
    Layer(objcT* r)
    : super(r)
    {
        PASS;
    }
    
    ~Layer()
    {
        PASS;
    }
    
    void set_bounds(cg::Rect const& rc)
    {
        this->_self.bounds = rc;
    }
    
    cg::Rect bounds() const
    {
        return this->_self.bounds;
    }
    
    void set_position(cg::Point const& pt)
    {
        this->_self.position = pt;
    }
    
    cg::Point position() const
    {
        return this->_self.position;
    }
    
    void set_zpos(real v)
    {
        this->_self.zPosition = v;
    }
    
    real zpos() const
    {
        return this->_self.zPosition;
    }
    
    void set_anchor(cg::Point const& pt)
    {
        this->_self.anchorPoint = pt;
    }
    
    cg::Point anchor() const
    {
        return this->_self.anchorPoint;
    }
    
    void set_anchorz(real v)
    {
        this->_self.anchorPointZ = v;
    }
    
    real anchorz() const
    {
        return this->_self.anchorPointZ;
    }
    
    void set_transform(cg::Transform const& mat)
    {
        this->_self.transform = mat;
    }
    
    cg::Transform transform() const
    {
        return this->_self.transform;
    }
    
    void set_transform(cg::AffineTransform const& mat)
    {
        [this->_self setAffineTransform:mat];
    }
    
    cg::AffineTransform transform_affine() const
    {
        return [this->_self affineTransform];
    }
    
    void set_subtransform(cg::Transform const& mat)
    {
        this->_self.sublayerTransform = mat;
    }
    
    cg::Transform subtransform() const
    {
        return this->_self.sublayerTransform;
    }
    
    void set_frame(cg::Rect const& rc)
    {
        this->_self.frame = rc;
    }
    
    cg::Rect frame() const
    {
        return this->_self.frame;
    }
    
    void set_visible(bool show = true)
    {
        this->_self.hidden = !show;
    }
    
    bool is_visible() const
    {
        return !this->_self.hidden;
    }
    
    void set_dside(bool val)
    {
        this->_self.doubleSided = val;
    }
    
    bool is_dside() const
    {
        return this->_self.doubleSided;
    }
    
    void set_clip(bool v = true)
    {
        this->_self.masksToBounds = v;
    }
    
    bool is_clip() const
    {
        return this->_self.masksToBounds;
    }
    
    void set_corner(real val)
    {
        this->_self.cornerRadius = val;
    }
    
    real corner() const
    {
        return this->_self.cornerRadius;
    }
    
    border_type& border()
    {
        if (_border.get() == NULL)
            _border.reset(new border_type(this->_self));
        return *_border;
    }
    
    template <typename filterT>
    void use_filter(filterT const& ft)
    {
        wtl::const_pointer<filterT> ptr(ft);
        [this->_self applyFilter:*ptr];
    }
    
    template <typename shapeT>
    void use_mask(shapeT const& sp)
    {
        wtl::const_pointer<shapeT> ptr(sp);
        this->_self.mask = *ptr;
    }
    
    void set_opacity(real v)
    {
        this->_self.opacity = v;
    }
    
protected:
    
    core::auto_ptr<border_type> _border;
    
};

NNT_END_NS

class Layer
: public tpl::Layer<CALayer>
{
    typedef tpl::Layer<CALayer> super;
    
public:
    
    Layer()
    {
        PASS;
    }
    
    Layer(objc_type* r)
    : super(r)
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
