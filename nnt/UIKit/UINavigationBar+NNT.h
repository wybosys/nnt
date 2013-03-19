
# ifndef __NNT_UIKIT_UINAVIGATIONBAR_E3CF1B338F7545949EDC4AF7510C8BF6_H_INCLUDED
# define __NNT_UIKIT_UINAVIGATIONBAR_E3CF1B338F7545949EDC4AF7510C8BF6_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

/* 
@interface UINavigationBar (UIViewRendering)

- (void)drawRect:(CGRect)rect;

@end
 */

@interface UINavigationBar (NNT)

- (void)updateTabBar;

@end

NNTDECL_CATEGORY(UINavigationBar, NNT);

@interface CANavigationBarFillLayer : CALayer

@property (nonatomic, retain) NgFill* fill;

@end

@interface NNTUINavigationItem : UINavigationItem {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIControl+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class NavigationController;
class NavigationBar;

class NavigationItem
: public Object<NavigationItem, NNTUINavigationItem>
{
    typedef Object<NavigationItem, NNTUINavigationItem> super;
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
                   typename ntl::mixin_type<viewT>::type::view_type const* = NULL)
    {
        ntl::const_pointer<viewT> ptr(v);
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
        _top._set((NNTUINavigationItem*)this->_self.topItem);
        return _top;
    }
    
    NavigationItem& back_item()
    {
        _back._set((NNTUINavigationItem*)this->_self.backItem);
        return _back;
    }
        
protected:
    
    NavigationController* _ctlr;
    NavigationItem _top;
    NavigationItem _back;
    
};

NNT_BEGIN_NS(tpl)

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

NNT_END_NS

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif