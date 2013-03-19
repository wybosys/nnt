
# ifndef __WSI_UKIT_NSVIEW_D1542BE15AA14C9B80FE5F06E7F47276_H_INCLUDED
# define __WSI_UKIT_NSVIEW_D1542BE15AA14C9B80FE5F06E7F47276_H_INCLUDED

# import "WSIUIObject.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface NSView (WSI)

- (id)initWithZero;

- (void)moveToCenter:(NSPoint)pt;
- (void)moveTo:(NSPoint)pos;

@end

WSIDECL_EXTERN_CLASS(WCGFill);

@interface WSINSView : NSView {
    
    //! background fill.
    WCGFill* backgroundFill;
    
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@property (nonatomic, retain) WCGFill* backgroundFill;

- (void)layoutSubviews;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)

class IView;

WSI_END_NS
WSI_END_HEADER_CXX

WSI_BEGIN_HEADER_OBJC

@protocol _cxx_nsview_wrapper <NSObject>

@property (nonatomic, assign) ::wsi::ui::IView* _cxxobj;

@end

@interface _cxx_nsview_wrapper : WSINSView <_cxx_nsview_wrapper>
{
    ::wsi::ui::IView* _cxxobj;    
}

@end

WSI_END_HEADER_OBJC

# include "WSIUIObject.h"
# include "../Graphic/WCGFill.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)

class IView
: public IObject
{
public:
    
    virtual void layout_subviews() = 0;
    virtual void draw(CGContextRef, NSRect const&) {}
    
};

template <typename implT, 
typename viewT = _cxx_nsview_wrapper,
typename interT = IView
>
class View
: public Object<implT, viewT>,
public interT
{
    typedef View<implT, viewT, interT> self_type;
    typedef Object<implT, viewT> super;
    
public:    
    
    typedef viewT view_type;
    typedef empty_view_type empty_type;
    
    View()
    : _needremove(true)
    {
        this->impl()->init();
        this->_updateself();
    }
    
    ~View()
    {
        if (this->_self)
        {
            if (_iswrapper)
                ((id<_cxx_nsview_wrapper>)this->_self)._cxxobj = NULL;      
            
            if (_needremove && this->_self.superview)
                [this->_self removeFromSuperview];
        }
    }
    
    void init()
    {
        this->_self = [[viewT alloc] initWithZero];
    }
    
    void set_frame(CGRect const& rc)
    {
        [this->_self setFrame:rc];
    }
    
    CGRect frame() const
    {
        return this->_self.frame;
    }
    
    CGRect bounds() const
    {
        return this->_self.bounds;
    }

    template <typename subviewT>
    inline void add_subview(subviewT const& view,
                            typename wtl::mixin_type<subviewT>::type::view_type const* = NULL)
    {
        wtl::const_pointer<subviewT> ptr(view);
        [this->_self addSubview:*ptr];
    }
    
    template <typename subviewT>
    inline void remove_subview(subviewT const& view,
                               typename wtl::mixin_type<subviewT>::type::view_type const* = NULL)
    {
        wtl::const_pointer<subviewT> ptr(view);
        [*ptr removeFromSuperview];
    }
    
    inline void add_subview(NSView* view)
    {
        [this->_self addSubview:view];
    }
    
    inline void remove_subview(NSView* view)
    {
        [view removeFromSuperview];
    }
    
    void set_background(cg::Fill const& fill)
    {
        this->_self.backgroundFill = fill;
    }
    
    //! add sub controller or sub view smart.
    template <typename elementT>
    inline void add_sub(elementT const& elemT,
                        typename wtl::mixin_type<elementT>::type::empty_type* empty = NULL)
    {
        this->_add_sub(elemT, empty);
    }
    
    virtual void Destroy()
    {
        this->_self = nil;
        super::Destroy();
    }
    
    virtual void Release()
    {
        super::Release();
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
    
    void _updateself()
    {
        _iswrapper = [this->_self conformsToProtocol:@protocol(_cxx_nsview_wrapper)];
        if (_iswrapper)
        {
            id<_cxx_nsview_wrapper> obj = (id<_cxx_nsview_wrapper>)this->_self;
            obj._cxxobj = (interT*)this;
        }
    }
    
    template <typename elementT>
    inline void _add_sub(elementT const& elemT,
                         empty_view_type* = NULL)
    {
        this->impl()->add_subview(elemT);
    }
    
    template <typename elementT>
    inline void _add_sub(elementT const& elemT,
                         empty_controller_type* = NULL)
    {
        this->impl()->add_subcontroller(elemT);
    }
    
private:        
    
    bool _iswrapper;
    bool _needremove;
    
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif

# endif