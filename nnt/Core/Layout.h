
# ifndef __NNT_LAYOUT_A6584424B660411E8BAA70740AA758D7_H_INCLUDED
# define __NNT_LAYOUT_A6584424B660411E8BAA70740AA758D7_H_INCLUDED

# import "../Graphic/NGBase.h"

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

typedef real _flex_t;
typedef int _pixel_t;

typedef class _flex { public: _flex(_flex_t d) : val(d) {} _flex_t val; } flex;
typedef class _pixel { public: _pixel(_pixel_t d) : val(d) {} _pixel_t val; } pixel;

class _whar
{
public:
    
    typedef real value_type;
    
    _whar(value_type _w, value_type _h)
    : w(_w), h(_h)
    {
        PASS;
    }
    
    _whar operator () (value_type _w, value_type _h) const
    {
        return _whar(_w, _h);
    }
    
    value_type w, h;
    
};

static const _whar whar = _whar(0, 0);

typedef struct {} _clear;
static const _clear clear = _clear();

typedef CGRect rect_type;
typedef CGPoint point_type;

class CGRectLayoutLinear;

class CGRectLayout 
{
    
public:    
        
    CGRectLayout();
    CGRectLayout(rect_type);    
    CGRectLayout(rect_type, int space);
    CGRectLayout(rect_type, CGMargin const& mrg, CGPadding const& pad);
    ~CGRectLayout();
    
public:
    
    //! set space.
    void set_space(int);
    
    //! move to
    void move_to(int __x, int __y);
    
    //! get percent
    float percent_w(float) const;
    float percent_h(float) const;
    float fpercent_w(float) const;
    float fpercent_h(float) const;
    
    //! reset
    void reset();
    
    //! get position.
    point_type get_position() const;
    
public:
    
    //! padding.
    CGPadding padding;
    
    //! margin for item.
    CGMargin margin;
    
    //! rc.
    rect_type const& get_rc() const;
    void set_rc(rect_type const&);
    
    //! set margin.
    void set_margin(real x, real y)
    {
        margin.left = margin.right = x;
        margin.top = margin.bottom = y;
    }
    
protected:
    
    rect_type rc, rc_;
    int _offset_x, _offset_y;
    
};

class CGRectLayoutHBox
: public CGRectLayout
{
    
public:
    
    CGRectLayoutHBox();
    CGRectLayoutHBox(rect_type, int space = 0);
    CGRectLayoutHBox(rect_type, CGMargin const& mrg, CGPadding const& pad = CGPaddingZero);
    
public:
    
    //! add percent
    rect_type add_percent(float __per);
    rect_type add_fpercent(float __per);
    
    //! add pixel
    rect_type add_pixel(_pixel_t __pix);
    
    //! stride pixel.
    rect_type stride_pixel(_pixel_t __pix);
    
    //! add pixel from end.
    rect_type radd_pixel(_pixel_t __pix);
    
    //! stride pixel from end.
    rect_type rstride_pixel(_pixel_t __pix);
    
    //! the rect for fill left space
    rect_type fill();
    
};

class CGRectLayoutVBox
: public CGRectLayout
{
    
public:
    
    CGRectLayoutVBox();
    CGRectLayoutVBox(rect_type, int space = 0);
    CGRectLayoutVBox(rect_type, CGMargin const& mrg, CGPadding const& pad = CGPaddingZero);
    
public:
    
    //! add percent
    rect_type add_percent(float __per);
    rect_type add_fpercent(float __per);
    
    //! add pixel
    rect_type add_pixel(_pixel_t __pix);
    
    //! stride pixel.
    rect_type stride_pixel(_pixel_t __pix);
    
    //! add pixel from end.
    rect_type radd_pixel(_pixel_t __pix);
    
    //! stride pixel from end.
    rect_type rstride_pixel(_pixel_t __pix);
    
    //! the rect for fill left space
    rect_type fill();
    
};

NNT_BEGIN_NS(lb)

typedef ::nnt::CGRectLayoutHBox CGRectLayoutHBox;

class CGRectLayoutVBox
: public ::nnt::CGRectLayoutVBox
{
    typedef ::nnt::CGRectLayoutVBox super;
    
public:
    
    CGRectLayoutVBox()
    : super()
    {}
    
    CGRectLayoutVBox(rect_type rc, int space = 0)
    : super(rc, space)
    {}
    
    CGRectLayoutVBox(rect_type rc, CGMargin const& mrg, CGPadding const& pad = CGPaddingZero)
    : super(rc, mrg, pad)
    {}
    
    rect_type add_percent(float __per)
    {
        rect_type rc = super::add_percent(__per);
        return this->_lb(rc);
    }
    
    rect_type add_fpercent(float __per)
    {
        rect_type rc = super::add_fpercent(__per);
        return this->_lb(rc);
    }
    
    rect_type add_pixel(_pixel_t __pix)
    {
        rect_type rc = super::add_pixel(__pix);
        return this->_lb(rc);
    }
    
    rect_type stride_pixel(_pixel_t __pix)
    {
        rect_type rc = super::stride_pixel(__pix);
        return this->_lb(rc);
    }
    
    rect_type radd_pixel(_pixel_t __pix)
    {
        rect_type rc = super::radd_pixel(__pix);
        return this->_lb(rc);
    }
    
    rect_type rstride_pixel(_pixel_t __pix)
    {
        rect_type rc = super::rstride_pixel(__pix);
        return this->_lb(rc);
    }
    
protected:
    
    rect_type _lb(rect_type& rc)
    {
        rc.origin.y = this->rc_.origin.y + (this->rc_.origin.y - rc.origin.y) + (this->rc_.size.height - rc.size.height);
        return rc;
    }
    
};

NNT_END_NS

class CGRectLayoutLinear
{
    
    struct _seg {
        bool ispixel;
        union {
            _pixel_t pixel;
            _flex_t flex;
        } value;
        _pixel_t result;
        void *ctx;
    };
    
    typedef CGRectLayoutLinear self_type;
    
public:
    
    CGRectLayoutLinear(_pixel_t = 0);
    CGRectLayoutLinear(CGRectLayoutVBox const&);
    CGRectLayoutLinear(CGRectLayoutHBox const&);
    ~CGRectLayoutLinear();
    
    typedef core::vector<_seg>::const_iterator const_iterator;
    typedef core::vector<_seg>::const_reverse_iterator const_reverse_iterator;
    typedef core::vector<_seg>::iterator iterator;
    typedef core::vector<_seg>::reverse_iterator reverse_iterator;
    
public:
    
    //! add pixel.
    //! @return id.
    uint add_pixel(_pixel_t);
    
    //! add flex like Qooxdoo do.
    //! @return id.
    uint add_flex(_flex_t);
    
    //! add aspect ratio.
    //! @return id.
    uint add_ar(_whar const&);
        
    //! add seg
    uint add_seg();
    
    //! size
    size_t size() const;
    
    //! clear
    void clear();
    
    void reset()
    {
        clear();
    }
    
    //! set full
    void set_full(int);
    void set_full(CGRectLayoutVBox const&);
    void set_full(CGRectLayoutHBox const&);
    
    //! get pixel width.
    _pixel_t get_comp(uint idx) const;
    
    //! resize
    void resize(uint);
    
    //! iterator
    const_iterator begin() const;
    const_iterator end() const;
    
    static _pixel_t value(const_iterator const*);
    static _pixel_t value(const_iterator);
    static _pixel_t value(const_reverse_iterator const*);
    static _pixel_t value(const_reverse_iterator);
    
    //! iterator value.
    _pixel_t start();
    _pixel_t next();
    _pixel_t prev();
    
    //! operator.
    self_type& operator << (flex val)
    {
        this->add_flex(val.val);
        return *this;
    }
    
    self_type& operator << (pixel val)
    {
        this->add_pixel(val.val);
        return *this;
    }
    
    self_type& operator << (_whar const& val)
    {
        this->add_ar(val);
        return *this;
    }
    
    self_type& operator << (_clear const& obj)
    {
        this->clear();
        return *this;
    }
    
    //! sum the pixels.
    _pixel_t pixels() const;
    
    //! sum the flexes.
    _flex_t flexes() const;
    
    //! if is started.
    bool started() const
    {
        return _iter != NULL;
    }
    
protected:
    
    void _recalc();
    
    //! resize with seg
    void resize(uint, _seg const&);
    
    //! seg at
    _seg& seg_at(uint);
    _seg const& seg_at(uint) const;
    
protected:
    
    _pixel_t _full, _relv;
    core::vector<_seg> _segs;
    bool _changed;
    const_iterator* _iter;
    bool _priority;
    
    friend class CGRectLayoutGrid;
};

class CGRectLayoutHFlow
: public CGRectLayout
{
    
public:
    
    CGRectLayoutHFlow(rect_type const&, int __stdheight);
    ~CGRectLayoutHFlow();
    
    //! add percent
    rect_type add_percent(float);
    rect_type add_percent(float, int);
    
    //! add pixel
    rect_type add_pixel(_pixel_t);
    rect_type add_pixel(_pixel_t, int __height);
    
    //! get rc
    rect_type const& get_rc() const;
    
    //! get bbox height.
    real bbox_height() const;
    
protected:
    
    int _stdheight;
    
};

class CGRectLayoutGrid
{
    
    typedef CGRectLayoutLinear::_seg _seg;
    
public:
    
    CGRectLayoutGrid();
    CGRectLayoutGrid(uint rows, uint cols);
    CGRectLayoutGrid(uint rows, uint cols, rect_type const&);
    ~CGRectLayoutGrid();
    
    //! set
    void set_rows(uint);
    void set_cols(uint);
    void set_rc(rect_type const&);
    
    //! get
    uint get_rows() const;
    uint get_cols() const;
    rect_type const& get_rc() const;
    
    //! set
    void set_pixel(uint row, uint col, int pixel, void* ctx = NULL);
    void set_flex(uint row, uint col, _flex_t flex, void* ctx = NULL);
    void set_ctx(uint row, uint col, void* ctx);
    
    void set_pixel_col(uint col, int pixel);
    void set_flex_col(uint col, _flex_t flex);
    void set_pixel_row(uint row, int pixel);
    void set_flex_row(uint row, _flex_t flex);
    
    //! get value
    uint value(uint row) const;
    uint value(uint row, uint col) const;
    void* get_ctx(uint row, uint col) const;
    
protected:
    
    _seg& seg_at(uint row, uint col);
    _seg const& seg_at(uint row, uint col) const;        
    
protected:

    rect_type _rc;
    uint _rows, _cols;
    core::vector<CGRectLayoutLinear> _hlnrs;
    CGRectLayoutLinear _vlnr;
    
};

inline_impl uint CGRectLayoutGrid::get_rows() const
{
    return _rows;
}

inline_impl uint CGRectLayoutGrid::get_cols() const
{
    return _cols;
}

inline_impl CGRect const& CGRectLayoutGrid::get_rc() const
{
    return _rc;
}

template <typename layout>
static rect_type operator << (layout& lyt, CGRectLayoutLinear& lnr)
{
    _pixel_t pix = lnr.started() ? lnr.next() : lnr.start();
    return lyt.stride_pixel(pix);
}

// type redefine.

NNT_BEGIN_NS(layout)

typedef CGRectLayoutVBox vbox;
typedef CGRectLayoutHBox hbox;
typedef CGRectLayoutLinear linear;
typedef CGRectLayoutGrid grid;
typedef CGRectLayoutHFlow hflow;

NNT_END_NS

NNT_END_HEADER_CXX

NNT_BEGIN_HEADER_C
using ::nnt::flex;
using ::nnt::pixel;
NNT_END_HEADER_C

# endif
# endif
