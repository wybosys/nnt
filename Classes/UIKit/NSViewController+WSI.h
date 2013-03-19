
# ifndef __WSI_UKIT_NSVIEWCONTROLLER_56E33B1729B7447094D28C58C88BC1DF_H_INCLUDED
# define __WSI_UKIT_NSVIEWCONTROLLER_56E33B1729B7447094D28C58C88BC1DF_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface NSViewController (WSI)

- (void)viewDidLoad;
- (void)viewIsLoading;

- (void)viewWillAppear;
- (void)viewDidAppear;

- (void)viewWillDisappear;
- (void)viewDidDisappear;

@end

@interface WSINSViewController : NSViewController {
    NSView* _view;
    NSString* identity;
}

@property (nonatomic, copy) NSString *identity;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "NSView+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class IViewController
: public IObject
{
public:
    
    virtual void view_loaded() = 0;
    virtual NSView* load_view() = 0;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

WSI_BEGIN_HEADER_OBJC

@protocol _cxx_nscontroller_wrapper <NSObject>

@property (nonatomic, assign) ::wsi::ui::IViewController* _cxxobj;

@end

@interface _cxx_nsviewcontroller_wrapper : WSINSViewController <_cxx_nscontroller_wrapper>
{
    ::wsi::ui::IViewController* _cxxobj;
}

@end

WSI_END_HEADER_OBJC

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

template <typename implT, typename viewT,
typename ctlrT = _cxx_nsviewcontroller_wrapper,
typename interT = IViewController
>
class Controller
: public Object<implT, ctlrT>,
public interT
{
    typedef Controller<implT, ctlrT, interT> self_type;
    typedef Object<implT, ctlrT> super;
    
public:
    
    typedef viewT view_type;
    
    Controller()
    : _view(NULL)
    {
        this->impl()->init();
        
        _iswrapper = [this->_self conformsToProtocol:@protocol(_cxx_nscontroller_wrapper)];
        
        if (_iswrapper)
        {
            id<_cxx_nscontroller_wrapper> obj = (id<_cxx_nscontroller_wrapper>)this->_self;            
            obj._cxxobj = (implT*)this;
        }
    }
    
    ~Controller()
    {
        if (_iswrapper && this->_self)
        {
            id<_cxx_nscontroller_wrapper> obj = (id<_cxx_nscontroller_wrapper>)this->_self;
            obj._cxxobj = NULL;
        }
        
        safe_delete(_view);
    }
    
    void init()
    {
        this->_self = [[ctlrT alloc] init];
    }
    
    virtual NSView* load_view()
    {
        _view = new view_type;        
        return **_view;
    }
    
    inline view_type& view()
    {
        [this->_self view];
        return *_view;
    }
    
    inline view_type const& view() const
    {
        return *_view;
    }
    
    virtual void Release()
    {
        if (this->_reference_count() == 1)
        {
            this->Destroy();
        }
        else
        {
            super::Release();
        }
    }
    
    virtual void Destroy()
    {
        this->_self = nil;
        super::Destroy();
    }
    
    virtual void* cxxobject() const
    {
        return (implT*)this;
    }
    
    virtual id nsobject() const
    {
        return this->_self;
    }
    
    
protected:
    
    void _cxxwrapper_Destroy()
    {        
        // because controller is release, so must set zero to _self.
        this->_self = nil;
        
        // super.
        super::Destroy();
    }
    
protected:
    
    viewT* _view;
    bool _iswrapper;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif