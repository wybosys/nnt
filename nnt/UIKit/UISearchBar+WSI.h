
# ifndef __WSI_UISEARCHBAR_3693D4CD2DE94F74921B6D6EF326CE87_H_INCLUDED
# define __WSI_UISEARCHBAR_3693D4CD2DE94F74921B6D6EF326CE87_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSI_EXTERN signal_t kSignalSearchClicked;
WSI_EXTERN signal_t kSignalBookmarkClicked;
WSI_EXTERN signal_t kSignalCancelClicked;
WSI_EXTERN signal_t kSignalResultsClicked;
WSI_EXTERN signal_t kSignalBeginEditing;
WSI_EXTERN signal_t kSignalEndEditing;

@interface WSIUISearchBar : UISearchBar <UISearchBarDelegate> {
    
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

- (void)visibleCancelButton;
- (void)invisibleCancelButton;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIControl+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class SearchBar
: public Control<SearchBar, WSIUISearchBar>
{
    typedef Control<SearchBar, WSIUISearchBar> super;
    
public:
    
    SearchBar()
    {
        PASS;
    }
    
    virtual ~SearchBar()
    {
        PASS;
    }
    
    void set_cancel(bool val = true)
    {
        this->_self.showsCancelButton = val == true;
    }
    
    void set_bookmark(bool val = true)
    {
        this->_self.showsBookmarkButton = val == true;
    }
    
    void set_results(bool val = true)
    {
        this->_self.showsSearchResultsButton = val == true;
    }
    
    void set_text(ns::String const& str)
    {
        this->_self.text = str;
    }
    
    void set_tint(ui::Color const& cor)
    {
        this->_self.tintColor = cor;
    }
    
    void set_keyboard(UIKeyboardType kt)
    {
        this->_self.keyboardType = kt;
    }
    
    ns::String text() const
    {
        return this->_self.text;
    }
    
    void set_prompt(ns::String const& str)
    {
        this->_self.prompt = str;
    }
    
    ns::String prompt() const
    {
        return this->_self.prompt;
    }
    
    void set_placeholder(ns::String const& str)
    {
        this->_self.placeholder = str;
    }
    
    ns::String placeholder() const
    {
        return this->_self.placeholder;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif