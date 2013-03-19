
# ifndef __WSI_UIKIT_PAGEROLLER_25B4484BE0B44D6E98E16CC7E4AEF1BF_H_INCLUDED
# define __WSI_UIKIT_PAGEROLLER_25B4484BE0B44D6E98E16CC7E4AEF1BF_H_INCLUDED

# include "UIControl+WSI.h"
# include "UIPageRollerPage.h"
# include "UIPageControl+WSI.h"
# include "UIItemView.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UIPageRoller);

@protocol UIPageRollerDataSource <NSObject>

- (NSInteger)pageRollerNumberOfPages:(UIPageRoller*)roller;
- (UIRollerPage*)pageRollerCreatePage:(UIPageRoller*)roller index:(NSInteger)idx;

@optional

- (CGFloat)pageRollerHeightOfPageControl:(UIPageRoller*)roller;

@end

@protocol UIPageRollerDelegate <NSObject>

@end

WSIDECL_PRIVATE_HEAD(UIPageRoller);

@interface UIPageRoller : WSIUIControl <UIPageRollerDataSource, UIPageRollerDelegate> {
    
    //! delegate.
    id<UIPageRollerDataSource> _dataSource;
    id<UIPageRollerDelegate> _delegate;
    
    //! value.
    NSInteger _numberOfCurrentPage;
    
    //! current page.
    UIRollerPage *_currentPage;
    
    //! the pointer to page control.
    WSIUIPageControl* _pageControl;
    
    //! pages container.
    UIItemsContainer* _pages;
    
    WSIDECL_PRIVATE(UIPageRoller);
}

@property (nonatomic, assign) id<UIPageRollerDataSource> dataSource;
@property (nonatomic, assign) id<UIPageRollerDelegate> delegate;
@property (nonatomic, assign) NSInteger numberOfCurrentPage;
@property (nonatomic, assign) UIRollerPage* currentPage;
@property (nonatomic, retain) UIItemsContainer *pages;
@property (nonatomic, readonly) WSIUIPageControl* pageControl;

- (void)clear;
- (void)reloadData;

@end

_CXXVIEW_DECL(UIPageRoller);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class IPageRoller
: public IControl
{
public:
    
    virtual usize count() const = 0;
    virtual id page(uint idx) const = 0;
    
};

class PageRoller
: public Control<PageRoller, _CXXVIEW(UIPageRoller), IPageRoller>
{
public:
    
    PageRoller()
    {
        PASS;
    }
    
    template <typename pageT>
    void add(pageT const& obj)
    {
        wtl::const_pointer<pageT> ptr(obj);
        _pages.add(*ptr);
    }
    
    virtual id page(uint idx) const
    {
        return _pages[idx];
    }
    
    virtual usize count() const
    {
        return _pages.count();
    }
    
    void clear()
    {
        [this->_self clear];
        _pages.clear();
    }
    
    void reload()
    {
        [this->_self reloadData];
    }
    
protected:
    
    ns::MutableArray _pages;

};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif