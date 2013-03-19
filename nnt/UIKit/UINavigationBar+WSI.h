
# ifndef __WSI_UIKIT_UINAVIGATIONBAR_E3CF1B338F7545949EDC4AF7510C8BF6_H_INCLUDED
# define __WSI_UIKIT_UINAVIGATIONBAR_E3CF1B338F7545949EDC4AF7510C8BF6_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

/* 
@interface UINavigationBar (UIViewRendering)

- (void)drawRect:(CGRect)rect;

@end
 */

@interface UINavigationBar (WSI)

- (void)updateTabBar;

@end

WSIDECL_CATEGORY(UINavigationBar, WSI);

@interface CANavigationBarFillLayer : CALayer

@property (nonatomic, retain) WCGFill* fill;

@end

@interface WSIUINavigationItem : UINavigationItem {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIControl+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class NavigationController;
class NavigationBar;

class NavigationItem
: public Object<NavigationItem, WSIUINavigationItem>
{
    typedef Object<NavigationItem, WSIUINavigationItem> super;
    friend class NavigationBar;
    
public:
    
    NavigationItem()
    {
        PASS;
    }
    
    NavigationItem(objc_type* item)
    : super(item)
    {
        PASS;
    }
    
    ~NavigationItem()
    {
        PASS;
    }
    
    void set_title(ns::String const& str)
    {
        this->_self.title = str;
    }
    
    ns::String title() const
    {
        return this->_self.title;
    }
    
    //! set title view.
    template <typename viewT>
    void set_title(viewT const& v,
                   typename wtl::mixin_type<viewT>::type::view_type const* = NULL)
    {
        wtl::const_pointer<viewT> ptr(v);
        this->_self.titleView = *ptr;
    }
    
};

class NavigationBar
: public Control<NavigationBar, UINavigationBar>
{
    typedef Control<NavigationBar, UINavigationBar> super;
    
public:
    
    NavigationBar(UINavigationBar* bar, NavigationController* ctlr)
    : super(bar)
    {
        _ctlr = ctlr;
        
        super::_release();
        super::_needrelease = false;
    }
    
    ~NavigationBar()
    {
        PASS;
    }
    
    //! set bar's visible.
    void set_visible(bool val = true);
    
    //! set items.
    void set_rightitems(ns::Array const&);
    void set_leftitems(ns::Array const&);
    
    //! set bar image.
    void set_background(cg::Fill const&);
    
    //! set tint.
    void set_tint(ui::Color const& color)
    {
        this->_self.tintColor = color;
    }

    //! set style.
    void set_style(UIBarStyle bs)
    {
        this->_self.barStyle = bs;
    }
    
    UIBarStyle barstyle() const
    {
        return this->_self.barStyle;
    }

    void set_translucent(BOOL val)
    {
        this->_self.translucent = val;
    }
    
    bool is_translucent() const
    {
        return this->_self.translucent;
    }
    
    //! width & height.
    real width() const
    {
        return super::width() * .8f;
    }
    
    real height() const
    {
        return super::height() * .8f;
    }
    
    //! push.
    void push_item(NavigationItem& item, bool animated)
    {
        [this->_self pushNavigationItem:item animated:animated];
    }
    
    //! pop.
    void pop_item(bool animated)
    {
        [this->_self popNavigationItemAnimated:animated];
    }
        
    //! get item.
    NavigationItem& top_item()
    {
        _top._set((WSIUINavigationItem*)this->_self.topItem);
        return _top;
    }
    
    NavigationItem& back_item()
    {
        _back._set((WSIUINavigationItem*)this->_self.backItem);
        return _back;
    }
        
protected:
    
    NavigationController* _ctlr;
    NavigationItem _top;
    NavigationItem _back;
    
};

WSI_BEGIN_NS(tpl)

template <typename viewT>
class NavigationItem
: public ui::NavigationItem
{
public:
    
    NavigationItem()
    {
        _view.set_removable(false);
        set_title(_view);
    }
    
    viewT& title_view()
    {
        return _view;
    }
    
    viewT const& title_view() const
    {
        return _view;
    }
    
protected:
    
    viewT _view;
    
};

WSI_END_NS

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif