
# ifndef __WSI_UIKIT_ITEMVIEW_2A4718702D1840D6A77E281025FF17E5_H_INCLUDED
# define __WSI_UIKIT_ITEMVIEW_2A4718702D1840D6A77E281025FF17E5_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UIItemView : WSIUIView {
    UIView* _contentView;
}

@property (nonatomic, retain) UIView* contentView;

@end

_CXXVIEW_DECL(UIItemView);

@protocol UIItemsDatasource <NSObject>

@optional

- (NSUInteger)numberOfItems:(id)obj;
- (id)itemAtIndex:(NSUInteger)idx;

@end

@interface UIItemsContainer : WSIObject {
    NSMutableArray* _items;
    id<UIItemsDatasource> _dataSource;
}

@property (nonatomic, retain) NSMutableArray* items;
@property (nonatomic, assign) id<UIItemsDatasource> dataSource;

- (NSUInteger)count;
- (id)objectAtIndex:(NSUInteger)idx;
- (UIItemView*)addView:(UIView*)view;
- (void)addItem:(UIItemView*)item;

+ (UIItemView*)View:(UIView*)view;

@end

WSI_EXTERN signal_t kSignalContentClicked;
WSI_EXTERN signal_t kSignalItemClicked;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(tpl)

template <typename implT, typename contentT>
class ItemView
: public View<implT, _CXXVIEW(UIItemView)>
{
public:
    
    ItemView()
    {
        this->_self.contentView = this->content;
        this->content.set_removable(ui::hold);
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
    contentT* operator -> ()
    {
        return &content;
    }
    
    contentT content;
    
};

template <typename implT>
class ItemsDatasource
{
public:
    
    virtual usize count() const
    {
        return [_impl() count];
    }
    
    virtual id item(uint idx) const
    {
        return [_impl() objectAtIndex:idx];
    }
    
    template <typename itemT>
    void add(itemT const& item)
    {
        wtl::const_pointer<itemT> ptr(item);
        UIItemsContainer* con = _impl();
        [con.items addObject:*ptr];
    }
    
protected:
    
    UIItemsContainer* _impl() const
    {
        return (UIItemsContainer*)*(implT*)this;
    }
    
};

WSI_END_NS

template <typename contentT>
class Itemlize
: public tpl::ItemView<Itemlize<contentT>, contentT>
{
public:
    
    Itemlize()
    {
        PASS;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
