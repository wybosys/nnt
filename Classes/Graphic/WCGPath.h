
# ifndef __WSI_CG_PATH_AE909ADAA47242C5A6F7730EE3FAB99A_H_INCLUDED
# define __WSI_CG_PATH_AE909ADAA47242C5A6F7730EE3FAB99A_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cg)

class Path
{
    
public:
    
    Path()
    : _path(NULL)
    {
        PASS;
    }
    
    Path(CGPathRef ph)
    : _path(ph)
    {
        CGPathRetain(_path);
    }

/*
    Path(CGMutablePathRef ph)
    : _path(ph)
    {
        CGPathRetain(_path);
    }
 */

    ~Path()
    {
        CGPathRelease(_path);
    }
    
    operator CGPathRef() const
    {
        return (CGPathRef)_path;
    }
    
    Path& operator = (CGPathRef r)
    {
        CGPathRelease(_path);
        _path = r;
        CGPathRetain(_path);
        return *this;
    }
    
protected:
    
    CGPathRef _path;
    
};

class MutablePath
{
    
public:
    
    MutablePath()
    {
        _path = CGPathCreateMutable();
    }
    
    MutablePath(CGMutablePathRef ph)
    : _path(ph)
    {
        CGPathRetain(_path);
    }
    
    MutablePath(MutablePath const& r)
    : _path((CGMutablePathRef)r._path)
    {
        CGPathRetain(_path);
    }
    
    ~MutablePath()
    {
        CGPathRelease(_path);
    }
    
    operator CGMutablePathRef() const
    {
        return _path;
    }
    
    operator Path () const
    {
        return Path((CGPathRef)_path);
    }
        
    MutablePath& operator = (CGMutablePathRef r)
    {
        CGPathRelease(_path);
        _path = r;
        CGPathRetain(_path);
        return *this;
    }
    
    void move_to(Point const& pt)
    {
        CGPathMoveToPoint(_path, _mat, pt.x, pt.y);
    }
    
    void line_to(Point const& pt)
    {
        CGPathAddLineToPoint(_path, _mat, pt.x, pt.y);
    }
    
    void add_quadcurve(Point const& cpt, Point const& pt)
    {
        CGPathAddQuadCurveToPoint(_path, _mat, cpt.x, cpt.y, pt.x, pt.y);
    }
    
    void add_curve(Point const& cpt1, Point const& cpt2, Point const& pt)
    {
        CGPathAddCurveToPoint(_path, _mat, cpt1.x, cpt1.y, cpt2.x, cpt2.y, pt.x, pt.y);
    }
    
    void close_sub()
    {
        CGPathCloseSubpath(_path);
    }
    
    void add_rect(Rect const& rc)
    {
        CGPathAddRect(_path, _mat, rc);
    }
    
    void add_ellipse(Rect const& rc)
    {
        CGPathAddEllipseInRect(_path, _mat, rc);
    }
    
    void add_relvarc(Point const& pt, real radius, real startangle, real delta)
    {
        CGPathAddRelativeArc(_path, _mat, pt.x, pt.y, radius, startangle, delta);
    }
    
    void add_arc(Point const& pt, real radius, real startangle, real endangle, bool clockwise)
    {
        CGPathAddArc(_path, _mat, pt.x, pt.y, radius, startangle, endangle, clockwise);
    }
    
    void add_arc(Point const& pt1, Point const& pt2, real radius)
    {
        CGPathAddArcToPoint(_path, _mat, pt1.x, pt1.y, pt2.x, pt2.y, radius);
    }
    
    void add_path(CGMutablePathRef path)
    {
        CGPathAddPath(_path, _mat, path);
    }
    
    AffineTransform& transform()
    {
        return _mat;
    }
    
    void reset()
    {
        CGPathRelease(_path);
        _path = CGPathCreateMutable();
        _mat.set_identity();
    }
    
protected:
    
    CGMutablePathRef _path;
    AffineTransform _mat;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
