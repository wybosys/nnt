
# ifndef __WSIUICROSS_CONTROLLER_44D28D9209594644AF768C2966950FF2_H_INCLUDED
# define __WSIUICROSS_CONTROLLER_44D28D9209594644AF768C2966950FF2_H_INCLUDED

# include "UcView.h"

UC_BEGIN_HEADER

class IController
{
public:
    
    virtual void view_loaded() = 0;
    
};

template <typename implT, typename viewT>
class Controller
: public Object<implT>,
public IController
{
public:
    
    typedef viewT view_type;
    
    Controller()
    : _view(NULL)
    {
        PASS;
    }
    
    ~Controller()
    {
        safe_delete(_view);
    }
    
    void create()
    {
        PASS;
    }
    
    void destroy()
    {
        PASS;
    }
    
    view_type& view() const
    {
        if (_view == NULL)
        {
            _view = new view_type;
            core::down_const(this)->view_loaded();
        }
        return *_view;
    }
    
protected:
    
    mutable view_type* _view;
    
};

UC_END_HEADER

# endif
