
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
virtual void init(); \
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
    
    virtual ~Object()
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
    
    virtual void init() = 0;

    void* object() const
    {
        return (void*)_obj;
    }
    
    void set_object(void* obj)
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
    tyT* _as() const
    {
        return (tyT*)_obj;
    }
    
    implT* _impl() const
    {
        return (implT*)this;
    }
    
    template <typename tyT>
    void _new()
    {
        _obj = new tyT();
    }

    template <typename tyT>
    void _delete()
    {
        if (_obj)
        {
            delete (tyT*) _obj;
            _obj = NULL;
        }
    }
    
    void* _obj;
    
};

# ifdef NNT_MSVC

NNT_BEGIN_NS(msvc)

NNTCLASS(BackgroundWindow);

class BackgroundWindow
{
public:

    BackgroundWindow();
    ~BackgroundWindow();

    int main();

    LPSTR cmd;
    HINSTANCE hprevious, hcurrent;
    int ws;

    int (*entry)(int, char**);

};

NNT_END_NS

# endif

UC_END_HEADER

# endif
