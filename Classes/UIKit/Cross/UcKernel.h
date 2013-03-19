
# ifndef __NNTUICROSS_KERNEL_B2952CCCF68043738FC97C6749B08E0F_H_INCLUDED
# define __NNTUICROSS_KERNEL_B2952CCCF68043738FC97C6749B08E0F_H_INCLUDED

# include "../../Math/LeRect.h"

# define UC_BEGIN_HEADER \
NNT_BEGIN_HEADER_CXX \
NNT_BEGIN_NS(ui) \
NNT_BEGIN_NS(uc)

# define UC_END_HEADER \
NNT_END_NS \
NNT_END_NS \
NNT_END_HEADER_CXX

# define UC_BEGIN \
NNT_BEGIN_CXX \
NNT_BEGIN_NS(ui) \
NNT_BEGIN_NS(uc)

# define UC_END \
NNT_END_NS \
NNT_END_NS \
NNT_END_CXX

UC_BEGIN_HEADER

typedef int Value;
typedef ::nnt::Point<Value, 2> Point;
typedef ::nnt::Size<Value, 2> Size;
typedef ::nnt::Rect<Value, 2, Point, Size> Rect;

# define UC_OBJECT \
void create(); \
void destroy();

template <typename implT>
class Object
: public cxx::Object<>
{

	typedef implT self_type;

protected:

	typedef self_type _class;

public:
    
    Object()
    : _obj(NULL)
    {
        _impl()->create();
    }
    
    ~Object()
    {
        _impl()->destroy();
    }
    
    void create()
    {
        PASS;
    }
    
    void destroy()
    {
        PASS;
    }
    
    inline void* object() const
    {
        return (void*)_obj;
    }
    
    inline void set_object(void* obj)
    {
        this->destroy();
        this->_obj = obj;
    }

	static implT* New()
	{
		return new implT;
	}

protected:
    
    template <typename tyT>
    inline tyT* _as() const
    {
        return (tyT*)_obj;
    }
    
    inline implT* _impl() const
    {
        return (implT*)this;
    }
    
    template <typename tyT>
    inline void _create()
    {
        _obj = new tyT();
    }

    template <typename tyT>
    inline void _destroy()
    {
        if (_obj)
        {
            delete (tyT*) _obj;
            _obj = NULL;
        }
    }
    
    void* _obj;
    
};

UC_END_HEADER

# endif
