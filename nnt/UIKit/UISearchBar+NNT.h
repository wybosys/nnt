
# ifndef __NNT_UISEARCHBAR_3693D4CD2DE94F74921B6D6EF326CE87_H_INCLUDED
# define __NNT_UISEARCHBAR_3693D4CD2DE94F74921B6D6EF326CE87_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNT_EXTERN signal_t kSignalSearchClicked;
NNT_EXTERN signal_t kSignalBookmarkClicked;
NNT_EXTERN signal_t kSignalCancelClicked;
NNT_EXTERN signal_t kSignalResultsClicked;
NNT_EXTERN signal_t kSignalBeginEditing;
NNT_EXTERN signal_t kSignalEndEditing;

@interface NNTUISearchBar : UISearchBar <UISearchBarDelegate> {
    
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

- (void)visibleCancelButton;
- (void)invisibleCancelButton;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIControl+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class SearchBar
: public Control<SearchBar, NNTUISearchBar>
{
    typedef Control<SearchBar, NNTUISearchBar> super;
    
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif