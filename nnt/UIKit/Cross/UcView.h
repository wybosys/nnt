
# ifndef __NNTUICROSS_VIEW_A6D9968FFF564FEBAF77B4E585BA79F5_H_INCLUDED
# define __NNTUICROSS_VIEW_A6D9968FFF564FEBAF77B4E585BA79F5_H_INCLUDED

UC_BEGIN_HEADER

class IView
{
public:
    
    virtual void resize(Size const&) = 0;
    virtual void show() = 0;
    
};

NNT_BEGIN_NS(impl)

NNTCLASS(View);

class View
{
public:
    
    static void Resize(void*, Size const&);
    static void Show(void*);
    static void* Create();
    static void Destroy(void*&);
    
};

NNT_END_NS

template <typename implT>
class View
: public Object<implT>,
public IView
{
public:
  
    View()
    {
        PASS;
    }
    
    ~View()
    {
        PASS;
    }
    
    void create()
    {
        this->_obj = impl::View::Create();
    }
    
    void destroy()
    {
        impl::View::Destroy(this->_obj);
    }
    
    virtual void resize(Size const& sz)
    {
        impl::View::Resize(this->_obj, sz);
    }
    
    virtual void show()
    {
        impl::View::Show(this->_obj);
    }
        
};

UC_END_HEADER

# endif
