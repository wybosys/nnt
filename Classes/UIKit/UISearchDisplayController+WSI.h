
# ifndef __NNT_UIKIT_SEARCHDISPLAYCONTROLLER_80E3B4DAC6BC4777BA9605218EBE420C_H_INCLUDED
# define __NNT_UIKIT_SEARCHDISPLAYCONTROLLER_80E3B4DAC6BC4777BA9605218EBE420C_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface NNTUISearchDisplayController : UISearchDisplayController <UISearchDisplayDelegate> {
    NNTOBJECT_DECL;
    
    UIView* _accordingView;
}

@property (nonatomic, assign) UIView* accordingView;

NNTOBJECT_PROP;

@end

# ifdef NNT_CXX

_CXXCONTROLLER_DECL(NNTUISearchDisplayController);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UISearchBar+NNT.h"
# include "UITableViewController+NNT.h"
# include "UINavigationController+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(tpl)

class ISearchDisplayController
: public IViewController
{
public:
    
    virtual bool searchByString(ns::String const&) = 0;
    virtual bool searchByScope(uint) = 0;
    
};

template <typename implT, typename tabT, typename barT = ui::SearchBar >
class SearchDisplayController
: public SimpleController<
implT,
_CXXCONTROLLER(NNTUISearchDisplayController),
UIView,
_NullView<UIView>,
ISearchDisplayController
>
{
    
    typedef SimpleController<
    implT,
    _CXXCONTROLLER(NNTUISearchDisplayController),
    UIView,
    _NullView<UIView>,
    ISearchDisplayController
    > super;
    
public:
    
    typedef typename super::objc_type objc_type;
    
    SearchDisplayController()
    {
        PASS;
    }
    
    virtual ~SearchDisplayController()
    {
        safe_delete(_bar);
        safe_delete(_tab);
        safe_delete(_navi);
    }
    
    void init()
    {
        _bar = new barT;
        _tab = new tabT;
        _navi = new NavigationController;
        
        // set default navi to tab.
        _tab->set_navigation(*_navi);
        
        id ctlr = *_tab;
        if ([ctlr isKindOfClass:[UINavigationController class]])
        {
            UINavigationController* navi = (UINavigationController*)ctlr;
            ctlr = navi.topViewController;
            navi.navigationBarHidden = YES;
        }
        
        this->_self = [[objc_type alloc] initWithSearchBar:*_bar contentsController:ctlr];
        this->_self.searchResultsDataSource = ctlr;
        this->_self.searchResultsDelegate = ctlr;
        
        // bar under self control.
        _bar->set_removable(false);
    }
    
    barT& searchbar()
    {
        return *_bar;
    }
    
    barT const& searchbar() const
    {
        return *_bar;
    }
    
    tabT& table()
    {
        return *_tab;
    }
    
    tabT const& table() const
    {
        return *_tab;
    }
    
    void set_active(bool active, bool animated = true)
    {
        if (animated)
            [this->_self setActive:active animated:animated];
        else
            this->_self.active = active;
    }
    
    bool active() const
    {
        return this->_self.active;
    }
    
    template <typename CxxUIObject>
    static implT* From(CxxUIObject* uiobj)
    {
        objc_type* ctlr = (objc_type*)((UIViewController*)uiobj->nsobject()).searchDisplayController;
        return dynamic_cast<implT*>(ctlr._cxxobj);
    }
    
    template <typename viewT>
    void set_according(viewT const& obj)
    {
        wtl::const_pointer<viewT> ptr(obj);
        this->_self.accordingView = *ptr;
    }
    
public:
    
    virtual bool searchByString(ns::String const&)
    {
        return false;
    }
    
    virtual bool searchByScope(uint)
    {
        return false;
    }
    
protected:
    
    barT* _bar;
    tabT* _tab;
    NavigationController* _navi;
    
};

NNT_END_NS

NNT_BEGIN_NS(impl)

class SearchDisplayController
: public tpl::SearchDisplayController<SearchDisplayController, ui::impl::TableController>
{
    
};

NNT_END_NS

template <typename tabT, typename barT = ui::SearchBar>
class SearchDisplayController
: public tpl::SearchDisplayController<
SearchDisplayController<tabT, barT>,
tabT
>
{
public:
    
    SearchDisplayController()
    {
        PASS;
    }
    
    virtual ~SearchDisplayController()
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
