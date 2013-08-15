
# ifndef __NNT_UKIT_NSVIEWCONTROLLER_56E33B1729B7447094D28C58C88BC1DF_H_INCLUDED
# define __NNT_UKIT_NSVIEWCONTROLLER_56E33B1729B7447094D28C58C88BC1DF_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSViewController (NNT)

- (void)viewDidLoad;
- (void)viewIsLoading;

- (void)viewWillAppear;
- (void)viewDidAppear;

- (void)viewWillDisappear;
- (void)viewDidDisappear;

@end

@interface NNTNSViewController : NSViewController {
    NSView* _view;
    NSString* identity;
}

@property (nonatomic, copy) NSString *identity;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NSView+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class IViewController
: public IObject
{
public:
    
    virtual void view_loaded() = 0;
    virtual NSView* load_view() = 0;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

NNT_BEGIN_HEADER_OBJC

@protocol _cxx_nscontroller_wrapper <NSObject>

@property (nonatomic, assign) ::nnt::ui::IViewController* _cxxobj;

@end

@interface _cxx_nsviewcontroller_wrapper : NNTNSViewController <_cxx_nscontroller_wrapper>
{
    ::nnt::ui::IViewController* _cxxobj;
}

@end

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

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
    
    view_type& view()
    {
        [this->_self view];
        return *_view;
    }
    
    view_type const& view() const
    {
        return *_view;
    }
    
    virtual void* cxxobject() const
    {
        return (implT*)this;
    }
    
    virtual id nsobject() const
    {
        return this->_self;
    }
    
    virtual void drop()
    {
        super::drop();
    }
    
    virtual void destroy()
    {
        this->_self = nil;
        super::destroy();
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif