
# ifndef __JUICE_SPIRIT_B509E9128EA64072BF9FF697DA7F7F94_H_INCLUDED
# define __JUICE_SPIRIT_B509E9128EA64072BF9FF697DA7F7F94_H_INCLUDED

# include "../../Math/Math+WSI.h"

JUICE_BEGIN 
WSI_BEGIN_NS(spirit)

template <typename implT, typename typesT>
class Object
{
public:
    
    typedef typename typesT::matrix_type matrix_type;
    
    Object()
    {
        transform.set_identity();   
    }
    
    template <typename unn>
    void next(unn* obj, renderinfo* info)
    {
        jimpl->_next(obj, info, (typename unn::empty_type*)NULL);
    }
    
    //! set time.
    void set_duration(real);
    
    //! set repeat.
    void set_repeat(bool);
    
    //! set reverse.
    void set_reverse(bool);

    //! transform of spirit.
    matrix_type transform;
    
};

template <typename implT, typename typesT>
class Object3d
: public Object<implT, typesT>
{
    
    typedef Object3d<implT, typesT> self_type;
    
public:
    
    Object3d()
    : _timex(0), _timey(0), _timez(0),
    _repeatx(0), _repeaty(0), _repeatz(0),
    _reversex(0), _reversey(0), _reversez(0),
    _x(0), _y(0), _z(0),
    _stepx(0), _stepy(0), _stepz(0),
    _offx(0), _offy(0), _offz(0),
    _ofx(0), _ofy(0), _ofz(0),
    _stpx(0), _stpy(0), _stpz(0)
    {
        PASS;
    }
    
public:
    
    void set(real x, real y, real z)
    {
        _x = x; _y = y; _z = z;
        _stepx = _timex ? (_x / _timex) : 0;
        _stepy = _timey ? (_y / _timey) : 0;
        _stepz = _timez ? (_z / _timez) : 0;
    }
    
    void set_duration(real tm)
    {
        this->_timex = this->_timey = this->_timez = tm;
        if (tm == 0)
            return;
        _stepx = _x / _timex;
        _stepy = _y / _timey;
        _stepz = _z / _timez;
    }
    
    void set_repeat(bool val)
    {
        _repeatx = _repeaty = _repeatz = val;
    }
    
    void set_reverse(bool val)
    {
        _reversex = _reversey = _reversez = val;
    }
    
protected:        
        
    static real _calc_off(real full, bool& repeat, real& offset, bool& reverse, bool& of, bool& stop, real& step, renderinfo* info)
    {
        real off = stop ? 0 : step * info->frame_time;
        
        if (!stop)
        {
            if (of)
            {
                if (reverse)
                {
                    off = -off;
                    
                    if (off + offset >= 0)
                    {
                        offset += off;
                    }
                    else
                    {
                        of = false;
                        off = off + offset;
                        offset = 0;                    
                        
                        if (repeat == false)
                        {
                            stop = true;
                        }
                    }                                        
                }
                else if (repeat)
                {
                    of = false;
                    off = -offset;
                    offset = 0;
                }
                else
                {
                    off = 0;
                    stop = true;
                }
            }
            else
            {
                if (off + offset <= full)
                {
                    offset += off;
                }
                else
                {
                    of = true;
                    off = full - offset;
                    offset = full;
                }
            }
        }

        return off;
    }
    
    real _calc_offx(renderinfo* info)
    {
        return self_type::_calc_off(_x, _repeatx, _offx, _reversex, _ofx, _stpx, _stepx, info);
    }
    
    real _calc_offy(renderinfo* info)
    {
        return self_type::_calc_off(_y, _repeaty, _offy, _reversey, _ofy, _stpy, _stepy, info);
    }
    
    real _calc_offz(renderinfo* info)
    {
        return self_type::_calc_off(_z, _repeatz, _offz, _reversez, _ofz, _stpz, _stepz, info);
    }
    
protected:
    
    //! duration.
    uint _timex, _timey, _timez;
    
    //! if true, from origin.
    bool _repeatx, _repeaty, _repeatz;
    
    //! if true, reverse.
    bool _reversex, _reversey, _reversez;
    
    //! value.
    real _x, _y, _z, _stepx, _stepy, _stepz, _offx, _offy, _offz;
    bool _ofx, _ofy, _ofz;
    bool _stpx, _stpy, _stpz;
};

template <typename implT, typename typesT>
class Rotate
: public Object3d<implT, typesT>
{
    JUICE_SUPER(Object3d<implT MCOMMA typesT>);
    JUICE_FRIEND(Object<implT MCOMMA typesT>);

public:    
    
    typedef typename typesT::matrix_type matrix_type;
    
    Rotate()
    {
        PASS;
    }
    
protected:
    
    template <typename entityT>
    void _next(entityT* entity, renderinfo* info, empty_renderentity_type* empty_renderentity, 
               typename matrix_type::empty_type* empty_matrix = NULL)
    {        
        this->__next(entity, info, empty_renderentity, empty_matrix);
    }
    
    template <typename entityT>
    void __next(entityT* entity, renderinfo* info, 
                empty_renderentity_type*, 
                empty_axises3d_type*)
    {
        real off_x = super::_calc_offx(info);
        real off_y = super::_calc_offy(info);
        real off_z = super::_calc_offz(info);
        
        this->transform.set_rotate(off_x, 1, 0, 0);
        this->transform.set_rotate(off_y, 0, 1, 0);
        this->transform.set_rotate(off_z, 0, 0, 1);
        
        _ref_transform(entity) *= this->transform; 
    }
    
    template <typename entityT>
    void __next(entityT* entity, renderinfo* info, 
                empty_renderentity_type*, 
                empty_axises2d_type*)
    {
        real off_z = super::_calc_offz(info);        
        this->transform.set_rotate(off_z);
        
        _ref_transform(entity) *= this->transform; 
    }
        
};

template <typename implT, typename typesT>
class Translate
: public Object3d<implT, typesT>
{
    JUICE_SUPER(Object3d<implT MCOMMA typesT>);
    JUICE_FRIEND(Object<implT MCOMMA typesT>);
    
public:
    
    typedef typename typesT::matrix_type matrix_type;    
    
    Translate()
    {
        PASS;
    }
    
protected:
    
    template <typename entityT>
    void _next(entityT* entity, renderinfo* info, empty_renderentity_type*)
    {        
        real off_x = super::_calc_offx(info);
        real off_y = super::_calc_offy(info);
        real off_z = super::_calc_offz(info);
        
        this->transform.set_translate(off_x, off_y, off_z);                        
        
        _ref_transform(entity) *= this->transform;
    }
    
};

template <typename implT, typename typesT>
class Scale
: public Object3d<implT, typesT>
{
    JUICE_SUPER(Object3d<implT MCOMMA typesT>);
    JUICE_FRIEND(Object<implT MCOMMA typesT>);
    
public:
    
    typedef typename typesT::matrix_type matrix_type;    
    
    Scale()
    {
        PASS;
    }
    
protected:
    
    template <typename entityT>
    void _next(entityT* entity, renderinfo* info, empty_renderentity_type*)
    {        
        real off_x = super::_calc_offx(info);
        real off_y = super::_calc_offy(info);
        real off_z = super::_calc_offz(info);
        
        this->transform.set_scale(1 + off_x, 1 + off_y, 1 + off_z);                        
        
        _ref_transform(entity) *= this->transform;
    }
    
};

template <typename implT, typename typesT>
class AddScale
: public Object3d<implT, typesT>
{
    JUICE_SUPER(Object3d<implT MCOMMA typesT>);
    JUICE_FRIEND(Object<implT MCOMMA typesT>);
    
public:
    
    typedef typename typesT::matrix_type matrix_type;    
    
    AddScale()
    {
        PASS;
    }
    
protected:
    
    template <typename entityT>
    void _next(entityT* entity, renderinfo* info, empty_renderentity_type*)
    {        
        real off_x = super::_calc_offx(info);
        real off_y = super::_calc_offy(info);
        real off_z = super::_calc_offz(info);
        
        this->transform.set_addscale(off_x, off_y, off_z);
                
        _ref_transform(entity) *= this->transform;
    }
    
};

template <typename implT, typename typesT>
class Value
: public Object3d<implT, typesT>
{
    JUICE_SUPER(Object3d<implT MCOMMA typesT>);
    JUICE_FRIEND(Object<implT MCOMMA typesT>);
    
public:
    
    typedef typename typesT::matrix_type matrix_type;    
    
    Value()
    : cur_x(0), cur_y(0), cur_z(0)
    {
        PASS;
    }
    
    void next(renderinfo* info)
    {        
        real off_x = super::_calc_offx(info);
        real off_y = super::_calc_offy(info);
        real off_z = super::_calc_offz(info);
        
        cur_x += off_x;
        cur_y += off_y;
        cur_z += off_z;        
    }
    
    real cur_x, cur_y, cur_z;
};

WSI_END_NS 
JUICE_END

# endif