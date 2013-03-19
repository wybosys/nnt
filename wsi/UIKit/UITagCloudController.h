
# ifndef __WSI_UIKIT_TAGCLOUDCONTROLLER_CF4FF5B457B8481A9D25A5431180A58B_H_INCLUDED
# define __WSI_UIKIT_TAGCLOUDCONTROLLER_CF4FF5B457B8481A9D25A5431180A58B_H_INCLUDED

# import "UIViewController+WSI.h"
# import "UITagCloudView.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UITagCloudController);

@protocol UITagCloudDataSource < NSObject >

- (NSUInteger)tagCloudNumberOfTags:(UITagCloudController*)cd;
- (UIView*)tagCloudViewOf:(UITagCloudController*)cd index:(NSUInteger)index;

@end

@interface UITagCloudController : WSIUIViewController <UITagCloudDataSource> {
    id<UITagCloudDataSource> _dataSource;
}

@property (nonatomic, assign) id<UITagCloudDataSource> dataSource;

- (void)clear;
- (void)reloadData;

@end

WSI_EXTERN signal_t kSignalContentClicked;
WSI_EXTERN signal_t kSignalItemClicked;

# ifdef WSI_CXX

_CXXCONTROLLER_DECL(UITagCloudController);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class ITagCloudController
: public IViewController
{
public:
    
    virtual uint count() const = 0;
    virtual id item(uint) const = 0;
    
};

class TagCloudController
: public SimpleController<
TagCloudController,
_CXXCONTROLLER(UITagCloudController),
UITagCloudView,
TagCloud,
ITagCloudController
>
{
public:
    
    TagCloudController()
    {
        PASS;
    }
    
    virtual void view_loaded()
    {
        PASS;
    }
    
    template <typename viewT>
    void add(viewT const& v)
    {
        wtl::const_pointer<viewT> ptr(v);
        _items.add(*ptr);
    }
    
    virtual uint count() const
    {
        return _items.count();
    }
    
    virtual id item(uint idx) const
    {
        return _items.at(idx);
    }
    
    void reload()
    {
        [this->_self reloadData];
    }
    
    void clear()
    {
        [_items removeAllObjects];
        [this->_self clear];
    }
    
protected:
    
    ns::MutableArray _items;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
