
# ifndef __WSI_UIKIT_PAGESWITCHCONTROLLER_B603CBE906A040FBA88BF03B13168EF4_H_INCLUDED
# define __WSI_UIKIT_PAGESWITCHCONTROLLER_B603CBE906A040FBA88BF03B13168EF4_H_INCLUDED

# import "UISwitchController.h"

WSI_BEGIN_HEADER_OBJC

@interface UIPageSwitchController : UISwitchController {
    
    //! class for instance a page. default is nil.
    Class pageClass;
    
    //! number of pages.
    usize numberOfPages;
}

@property (nonatomic, assign) Class pageClass;
@property (nonatomic, assign) usize numberOfPages;

- (void)instanceRootPage;
- (void)clear;

@end

WSI_EXTERN signal_t kSignalPageCreate;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC
_CXXCONTROLLER_DECL(UIPageSwitchController);
WSI_END_HEADER_OBJC

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class PageSwitchController
: public SimpleController<PageSwitchController,
_CXXCONTROLLER(UIPageSwitchController),
WSIUIView
>
{
    typedef SimpleController<PageSwitchController,
    _CXXCONTROLLER(UIPageSwitchController),
    WSIUIView
    > super;
    
public:
    
    void clear()
    {
        [this->_self clear];
    }
    
    template <typename pagesT>
    void add_pages(pagesT const& pages)
    {
        if (pages.size() == 0)
            return;
        
        uint number = this->_self.numberOfPages + pages.size();
        this->_self.numberOfPages = number;
        
        typename pagesT::const_iterator each = pages.begin();
        while (each != pages.end())
        {
            wtl::const_pointer<typename pagesT::value_type> ptr(*each);
            
            // add page.
            [this->_self add_page:*ptr];
            
            ++each;
        }
        
        wtl::const_pointer<typename pagesT::value_type> ptr(pages.front());
        [this->_self set_page:*ptr];
    }
    
    template <typename pagesT>
    void set_pages(pagesT const& pages)
    {
        clear();
        add_pages(pages);
    }
    
    usize count() const
    {
        return this->_self.numberOfPages;
    }
    
    uint current() const
    {
        return [this->_self index_of:this->_self.cur_page];
    }
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif