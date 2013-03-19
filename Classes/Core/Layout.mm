
# import "Core.h"
# import "Layout.h"

NNT_BEGIN_CXX

CGRectLayout::CGRectLayout()
{
    this->reset();
    
    margin = CGMarginZero;
    padding = CGPaddingZero;
    
    memset(&this->rc, 0, sizeof(CGRect));
}

CGRectLayout::CGRectLayout(rect_type __rc) 
{
    this->reset();
    
    margin = CGMarginZero;
    padding = CGPaddingZero;
    
    this->rc_ = this->rc = __rc;
}

CGRectLayout::CGRectLayout(rect_type __rc, CGMargin const& mrg, CGPadding const& pad)
{
    this->reset();
    
    margin = mrg;
    padding = pad;
    
    this->set_rc(__rc);
}

CGRectLayout::CGRectLayout(rect_type __rc, int space)
{
    this->reset();
    
    if (space == 0)
    {
        margin = CGMarginZero;
        padding = CGPaddingZero;
        this->rc_ = this->rc = __rc;
    }
    else
    {
        this->set_space(space);
        this->set_rc(__rc);
    }       
}

CGRectLayout::~CGRectLayout() 
{
    PASS;
}

rect_type const& CGRectLayout::get_rc() const 
{
    return this->rc;
}

void CGRectLayout::set_rc(const rect_type & __rc) 
{
    this->rc_ = this->rc = __rc;
    
    // offset rect.
    if (CGPaddingEqualToPadding(padding, CGPaddingZero) == false) 
    {
        this->rc.origin.x += padding.left;
        this->rc.origin.y += padding.top;
        this->rc.size.width -= CGPaddingGetWidth(&padding);
        this->rc.size.height -= CGPaddingGetHeight(&padding);
    }
}

void CGRectLayout::reset() 
{
    _offset_x = _offset_y = 0;
    this->rc = this->rc_;
}

void CGRectLayout::set_space(int v)
{
    this->padding = CGPaddingMake(v, 0, v, 0);
    this->margin = CGMarginMake(0, v, 0, v);
}

float CGRectLayout::percent_w(float __per) const 
{
    return (this->rc.size.width - this->_offset_x - this->margin.left - this->margin.right) * __per;
}

float CGRectLayout::percent_h(float __per) const 
{
    return (this->rc.size.height - this->_offset_y - this->margin.top - this->margin.bottom) * __per;
}

float CGRectLayout::fpercent_w(float __per) const 
{
    return this->rc.size.width * __per;
}

float CGRectLayout::fpercent_h(float __per) const 
{
    return this->rc.size.height * __per;
}

void CGRectLayout::move_to(int __x, int __y) 
{
    this->rc.origin.x = __x;
    this->rc.origin.y = __y;
}

point_type CGRectLayout::get_position() const 
{
    point_type ret;
    ret.x = this->rc.origin.x + this->margin.left;
    ret.y = this->rc.origin.y + this->margin.top;
    return ret;
}

CGRectLayoutHBox::CGRectLayoutHBox() 
{
    PASS;    
}

CGRectLayoutHBox::CGRectLayoutHBox(rect_type __rc, int space)
: CGRectLayout(__rc, space)
{
    PASS;
}

CGRectLayoutHBox::CGRectLayoutHBox(rect_type __rc, CGMargin const& mrg, CGPadding const& pad)
: CGRectLayout(__rc, mrg, pad)
{
    PASS;   
}

rect_type CGRectLayoutHBox::add_percent(float __per) 
{
    rect_type ret;
    int width = (int)this->percent_w(__per);
    this->_offset_x += width;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.x += width;
    ret.size.width = width - this->margin.left - this->margin.right;
    ret.size.height = this->rc.size.height - this->margin.top - this->margin.bottom;
    return ret;
}

rect_type CGRectLayoutHBox::add_fpercent(float __per) 
{
    rect_type ret;
    int width = (int)this->fpercent_w(__per);
    this->_offset_x += width;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.x += width;
    ret.size.width = width - this->margin.left - this->margin.right;
    ret.size.height = this->rc.size.height - this->margin.top - this->margin.bottom;
    return ret;
}

rect_type CGRectLayoutHBox::add_pixel(int __pix) 
{
    rect_type ret;
    int width = __pix;
    this->_offset_x += width;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.x += width;
    ret.size.width = width;
    ret.size.height = this->rc.size.height;
    return ret;
}

rect_type CGRectLayoutHBox::stride_pixel(int __pix) 
{
    rect_type ret;
    int width = __pix;
    this->_offset_x += width;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.x += width;
    ret.size.width = width - this->margin.left - this->margin.right;
    ret.size.height = this->rc.size.height - this->margin.top - this->margin.bottom;
    return ret;
}

rect_type CGRectLayoutHBox::radd_pixel(int __pix) 
{
    rect_type ret;
    int width = this->rc_.size.width - this->_offset_x - __pix;
    this->_offset_x += width;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.x += width;
    ret.size.width = width;
    ret.size.height = this->rc.size.height;
    return ret;
}

rect_type CGRectLayoutHBox::rstride_pixel(int __pix) 
{
    rect_type ret;
    int width = this->rc_.size.width - this->_offset_x - __pix;
    this->_offset_x += width;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.x += width;
    ret.size.width = width - this->margin.left - this->margin.right;
    ret.size.height = this->rc.size.height - this->margin.top - this->margin.bottom;
    return ret;
}

rect_type CGRectLayoutHBox::fill() 
{
    rect_type ret;
    int width = this->rc_.size.width - this->_offset_x;
    this->_offset_x += width;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.x += width;
    ret.size.width = width - this->margin.left - this->margin.right;
    ret.size.height = this->rc.size.height - this->margin.top - this->margin.bottom;
    return ret;
}

CGRectLayoutVBox::CGRectLayoutVBox() 
{
    PASS;
}

CGRectLayoutVBox::CGRectLayoutVBox(rect_type __rc, int space)
: CGRectLayout(__rc, space)
{
    PASS;
}

CGRectLayoutVBox::CGRectLayoutVBox(rect_type __rc, CGMargin const& mrg, CGPadding const& pad)
: CGRectLayout(__rc, mrg, pad)
{
    PASS;   
}

rect_type CGRectLayoutVBox::add_percent(float __per) 
{
    rect_type ret;
    int height = (int)this->percent_h(__per);
    this->_offset_y += height;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.y += height;
    ret.size.width = this->rc.size.width - this->margin.left - this->margin.right;
    ret.size.height = height - this->margin.top - this->margin.bottom;
    return ret;
}

rect_type CGRectLayoutVBox::add_fpercent(float __per) 
{
    rect_type ret;
    int height = (int)this->fpercent_h(__per);
    this->_offset_y += height;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.y += height;
    ret.size.width = this->rc.size.width - this->margin.left - this->margin.right;
    ret.size.height = height - this->margin.top - this->margin.bottom;
    return ret;
}

rect_type CGRectLayoutVBox::add_pixel(int __pix) 
{
    rect_type ret;
    int height = __pix;
    this->_offset_y += height;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.y += height;
    ret.size.width = this->rc.size.width;
    ret.size.height = height;
    return ret;
}

rect_type CGRectLayoutVBox::stride_pixel(int __pix) 
{
    rect_type ret;
    int height = __pix;
    this->_offset_y += height;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.y += height;
    ret.size.width = this->rc.size.width - this->margin.left - this->margin.right;
    ret.size.height = height - this->margin.top - this->margin.bottom;
    return ret;
}

rect_type CGRectLayoutVBox::radd_pixel(int __pix) 
{
    rect_type ret;
    int height = this->rc_.size.height - this->_offset_y - __pix;
    this->_offset_y += height;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.y += height;
    ret.size.width = this->rc.size.width;
    ret.size.height = height;
    return ret;
}

rect_type CGRectLayoutVBox::rstride_pixel(int __pix) 
{
    rect_type ret;
    int height = this->rc_.size.height - this->_offset_y - __pix;
    this->_offset_y += height;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.y += height;
    ret.size.width = this->rc.size.width - this->margin.left - this->margin.right;
    ret.size.height = height - this->margin.top - this->margin.bottom;
    return ret;
}

rect_type CGRectLayoutVBox::fill() 
{
    rect_type ret;
    int height = this->rc_.size.height - this->_offset_y;
    this->_offset_y += height;
    ret.origin.x = this->rc.origin.x + this->margin.left;
    ret.origin.y = this->rc.origin.y + this->margin.top;
    this->rc.origin.y += height;
    ret.size.width = this->rc.size.width - this->margin.left - this->margin.right;
    ret.size.height = height - this->margin.top - this->margin.bottom;
    return ret;
}

CGRectLayoutLinear::CGRectLayoutLinear(_pixel_t __full) 
: _changed(false), _full(__full), _iter(NULL), _priority(true)
{
    PASS;
}

CGRectLayoutLinear::CGRectLayoutLinear(CGRectLayoutVBox const& lyt)
: _changed(false), _iter(NULL), _priority(false)
{
    _full = lyt.get_rc().size.height;
    _relv = lyt.get_rc().size.width;
}

CGRectLayoutLinear::CGRectLayoutLinear(CGRectLayoutHBox const& lyt)
: _changed(false), _iter(NULL), _priority(true)
{
    _full = lyt.get_rc().size.width;
    _relv = lyt.get_rc().size.height;
}

CGRectLayoutLinear::~CGRectLayoutLinear() 
{
    delete _iter;
}

void CGRectLayoutLinear::clear() 
{
    _segs.clear();
    _changed = true;
    safe_delete(_iter);
}

size_t CGRectLayoutLinear::size() const 
{
    return _segs.size();
}

void CGRectLayoutLinear::set_full(int __value) 
{
    _changed = true;
    _full = __value;
}

void CGRectLayoutLinear::set_full(CGRectLayoutVBox const& lyt) 
{
    this->set_full(lyt.get_rc().size.height);
}

void CGRectLayoutLinear::set_full(CGRectLayoutHBox const& lyt) 
{
    this->set_full(lyt.get_rc().size.width);
}

void CGRectLayoutLinear::resize(uint sz) 
{
    if (_segs.size() == sz)
        return;
    _changed = true;
    _segs.resize(sz);
}

void CGRectLayoutLinear::resize(uint sz, const ::nnt::CGRectLayoutLinear::_seg & __seg) 
{
    if (_segs.size() == sz)
        return;
    _changed = true;
    _segs.resize(sz, __seg);
}

uint CGRectLayoutLinear::add_flex(_flex_t flex)
{
    _changed = true;
    _seg value;
    value.ispixel = false;
    value.value.flex = flex;
    value.result = 0;
    value.ctx = 0;
    _segs.push_back(value);
    return (_pixel_t)this->size() - 1;
}

uint CGRectLayoutLinear::add_pixel(_pixel_t pixel) 
{
    _changed = true;
    _seg value;
    value.ispixel = true;
    value.value.pixel = pixel;
    value.result = 0;
    value.ctx = 0;
    _segs.push_back(value);
    return (uint)this->size() - 1;
}

uint CGRectLayoutLinear::add_ar(_whar const& ar)
{
    _pixel_t pix;
    if (_priority)
        pix = _relv * (ar.w / ar.h);
    else
        pix = _relv * (ar.h / ar.w);
    return add_pixel(pix);
}

uint CGRectLayoutLinear::add_seg() 
{
    _changed = true;
    _seg value;
    value.ispixel = true;
    value.value.pixel = 0;
    value.result = 0;
    value.ctx = 0;
    _segs.push_back(value);
    return (uint)this->size() - 1;
}

void CGRectLayoutLinear::_recalc() 
{
    if (_changed == false)
        return;
    _changed = false;
    
    _pixel_t sum_pix = 0;
    _flex_t sum_flex = 0;
    
    core::vector<_seg>::iterator iter = _segs.begin();
    for (; iter != _segs.end(); ++iter)
    {
        _seg& seg = *iter;
        if (seg.ispixel) 
            sum_pix += seg.value.pixel;
        else 
            sum_flex += seg.value.flex;
    }
    
    sum_flex = sum_flex ? sum_flex : 1;
    
    _flex_t full_flex = _full - sum_pix;
    real each_flex = full_flex / sum_flex;
    
    for (iter = _segs.begin(); iter != _segs.end(); ++iter)
    {
        _seg& seg = *iter;
        if (seg.ispixel) 
            seg.result = seg.value.pixel;
        else 
            seg.result = seg.value.flex * each_flex;
    }
}

_pixel_t CGRectLayoutLinear::get_comp(uint idx) const 
{
    const_cast<CGRectLayoutLinear*>(this)->_recalc();
    return _segs.at(idx).result;
}

CGRectLayoutLinear::const_iterator CGRectLayoutLinear::begin() const 
{
    const_cast<CGRectLayoutLinear*>(this)->_recalc();
    return _segs.begin();
}

CGRectLayoutLinear::const_iterator CGRectLayoutLinear::end() const 
{
    return _segs.end();
}

_pixel_t CGRectLayoutLinear::start() 
{
    if (_iter == NULL)
        _iter = new const_iterator;
    *_iter = this->begin();
    return this->value(_iter);
}

_pixel_t CGRectLayoutLinear::next() 
{
    ++(*_iter);
    return this->value(_iter);
}

_pixel_t CGRectLayoutLinear::prev() 
{
    --(*_iter);
    return this->value(_iter);
}

_pixel_t CGRectLayoutLinear::value(const_iterator const* iter) 
{
    return (*iter)->result;
}

_pixel_t CGRectLayoutLinear::value(const_iterator iter) 
{
    return iter->result;
}

_pixel_t CGRectLayoutLinear::value(const_reverse_iterator const* iter) 
{
    return (*iter)->result;
}

_pixel_t CGRectLayoutLinear::value(const_reverse_iterator iter) 
{
    return iter->result;
}

CGRectLayoutLinear::_seg& CGRectLayoutLinear::seg_at(uint n) 
{
    return _segs.at(n);
}

CGRectLayoutLinear::_seg const& CGRectLayoutLinear::seg_at(uint n) const 
{
    return _segs.at(n);
}

_pixel_t CGRectLayoutLinear::pixels() const 
{
    _pixel_t sum_pix = 0;
    
    core::vector<_seg>::const_iterator iter = _segs.begin();
    for (; iter != _segs.end(); ++iter) {
        _seg const& seg = *iter;
        if (seg.ispixel) 
            sum_pix += seg.value.pixel;
    }
    
    return sum_pix;
}

_flex_t CGRectLayoutLinear::flexes() const 
{
    _flex_t sum_flex = 0;
    
    core::vector<_seg>::const_iterator iter = _segs.begin();
    for (; iter != _segs.end(); ++iter) {
        _seg const& seg = *iter;
        if (!seg.ispixel)
            sum_flex += seg.value.flex;
    }
    
    return sum_flex;
}

CGRectLayoutHFlow::CGRectLayoutHFlow(rect_type const& __rc, int __stdheight)
: _stdheight(__stdheight)
{
    this->rc_ = __rc;
    this->reset();
}

CGRectLayoutHFlow::~CGRectLayoutHFlow() 
{
    PASS;    
}

rect_type const& CGRectLayoutHFlow::get_rc() const 
{
    return this->rc;
}

rect_type CGRectLayoutHFlow::add_percent(float __per) 
{
    return this->add_percent(__per, this->_stdheight);
}

rect_type CGRectLayoutHFlow::add_pixel(int __d) 
{
    return this->add_pixel(__d, this->_stdheight);
}

rect_type CGRectLayoutHFlow::add_percent(float __per, int __height) 
{
    rect_type ret;
    ret.size.width = this->fpercent_w(__per);
    ret.size.height = __height;
    if (rc.origin.x + _offset_x + margin.left + margin.right + ret.size.width > rc.origin.x + rc.size.width) {
        int grow_y = MAX(_stdheight, __height) + margin.top + margin.bottom;
        if (rc.origin.y + _offset_y + grow_y > rc.origin.y + rc.size.height) {
            rc.size.height = _offset_y + grow_y;
        }
        ret.origin.x = 0 + margin.left;
        ret.origin.y = _offset_y + margin.top;
        _offset_x = 0;
        _offset_y = _offset_y + grow_y;
        return ret;
    }
    ret.origin.x = _offset_x;
    ret.origin.y = _offset_y;
    _offset_x = _offset_x + ret.size.width + margin.left;
    return ret;
}

rect_type CGRectLayoutHFlow::add_pixel(int __d, int __height) 
{
    rect_type ret;
    ret.size.width = __d;
    ret.size.height = __height;
    if (rc.origin.x + _offset_x + margin.left + margin.right + ret.size.width > rc.origin.x + rc.size.width) {
        int grow_y = MAX(_stdheight, __height) + margin.top + margin.bottom;
        if (rc.origin.y + _offset_y + grow_y > rc.origin.y + rc.size.height) {
            rc.size.height = _offset_y + grow_y;
        }
        ret.origin.x = 0 + margin.left;
        ret.origin.y = _offset_y + margin.top;
        _offset_x = 0;
        _offset_y = _offset_y + grow_y;
        return ret;
    }
    ret.origin.x = _offset_x;
    ret.origin.y = _offset_y;
    _offset_x = _offset_x + ret.size.width + margin.left;
    return ret;
}

real CGRectLayoutHFlow::bbox_height() const 
{
    return _offset_y;
}

CGRectLayoutGrid::CGRectLayoutGrid() 
: _rows(0), _cols(0)
{
    this->set_cols(0);
    this->set_rows(0);
}

CGRectLayoutGrid::CGRectLayoutGrid(uint __rows, uint __cols) 
: _rows(0), _cols(0)
{
    this->set_cols(__cols);
    this->set_rows(__rows);
}

CGRectLayoutGrid::CGRectLayoutGrid(uint __rows, uint __cols, rect_type const& rc) 
: _rows(0), _cols(0)
{
    this->set_cols(__cols);
    this->set_rows(__rows);
    this->set_rc(rc);
}

CGRectLayoutGrid::~CGRectLayoutGrid() 
{
    PASS;
}

void CGRectLayoutGrid::set_rows(uint __rows) 
{
    CGRectLayoutLinear lnr;
    _seg seg;
    seg.ispixel = false;
    seg.value.flex = 1;
    seg.ctx = NULL;
    seg.result = 0;
    lnr.resize(_cols, seg);
    _hlnrs.resize(__rows, lnr);
    _vlnr.resize(__rows, seg);
    _rows = __rows;
}

void CGRectLayoutGrid::set_cols(uint __cols) 
{
    _seg seg;
    seg.ispixel = false;
    seg.value.flex = 1;
    seg.ctx = NULL;
    seg.result = 0;
    for (uint i = 0; i < _rows; ++i)
    {
        _hlnrs[i].resize(__cols, seg);
    }
    _cols = __cols;
}

void CGRectLayoutGrid::set_rc(const rect_type & __rc) 
{
    _vlnr.set_full(__rc.size.height);
    for (uint i = 0; i < _rows; ++i)
    {
        _hlnrs[i].set_full(__rc.size.width);
    }
    _rc = __rc;
}

CGRectLayoutGrid::_seg& CGRectLayoutGrid::seg_at(uint row, uint col) 
{
    CGRectLayoutLinear& lnr = _hlnrs.at(row);
    return (CGRectLayoutGrid::_seg&)lnr.seg_at(col);
}

CGRectLayoutGrid::_seg const& CGRectLayoutGrid::seg_at(uint row, uint col) const 
{
    CGRectLayoutLinear const& lnr = _hlnrs.at(row);
    return (CGRectLayoutGrid::_seg const&)lnr.seg_at(col);
}

void CGRectLayoutGrid::set_pixel(uint row, uint col, int pixel, void* ctx) 
{
    CGRectLayoutLinear& lnr = _hlnrs.at(row);
    _seg& seg = (CGRectLayoutGrid::_seg&)lnr.seg_at(col);
    seg.ispixel = true;
    seg.value.pixel = pixel;
    seg.ctx = ctx;
    lnr._changed = true;
}

void CGRectLayoutGrid::set_flex(uint row, uint col, _flex_t flex, void* ctx) 
{
    CGRectLayoutLinear& lnr = _hlnrs.at(row);
    _seg& seg = (CGRectLayoutGrid::_seg&)lnr.seg_at(col);
    seg.ispixel = false;
    seg.value.flex = flex;
    seg.ctx = ctx;
    lnr._changed = true;
}

void CGRectLayoutGrid::set_ctx(uint row, uint col, void *ctx) 
{
    CGRectLayoutLinear& lnr = _hlnrs.at(row);
    _seg& seg = (CGRectLayoutGrid::_seg&)lnr.seg_at(col);
    seg.ctx = ctx;
}

uint CGRectLayoutGrid::value(uint row) const 
{
    return _vlnr.get_comp(row);
}

uint CGRectLayoutGrid::value(uint row, uint col) const 
{
    CGRectLayoutLinear const& lnr = _hlnrs.at(row);
    return lnr.get_comp(col);
}

void* CGRectLayoutGrid::get_ctx(uint row, uint col) const 
{
    CGRectLayoutLinear const& lnr = _hlnrs.at(row);
    _seg const& seg = (CGRectLayoutGrid::_seg const&)lnr.seg_at(col);
    return seg.ctx;
}

void CGRectLayoutGrid::set_pixel_col(uint col, int pixel) 
{
    for (uint r = 0; r < _rows; ++r)
    {
        CGRectLayoutLinear& lnr = _hlnrs.at(r);
        _seg& seg = lnr.seg_at(col);
        seg.ispixel = true;
        seg.value.pixel = pixel;
        lnr._changed = true;
    }
}

void CGRectLayoutGrid::set_flex_col(uint col, _flex_t flex) 
{
    for (uint r = 0; r < _rows; ++r)
    {
        CGRectLayoutLinear& lnr = _hlnrs.at(r);
        _seg& seg = lnr.seg_at(col);
        seg.ispixel = false;
        seg.value.flex = flex;
        lnr._changed = true;
    }
}

void CGRectLayoutGrid::set_pixel_row(uint row, int pixel) 
{
    _vlnr._changed = true;
    _seg& seg = _vlnr.seg_at(row);
    seg.ispixel = true;
    seg.value.pixel = pixel;
}

void CGRectLayoutGrid::set_flex_row(uint row, _flex_t flex) 
{
    _vlnr._changed = true;
    _seg& seg = _vlnr.seg_at(row);
    seg.ispixel = false;
    seg.value.flex = flex;
}

NNT_END_CXX
