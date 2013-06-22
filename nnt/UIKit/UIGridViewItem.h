
# ifndef __NNT_UIKIT_UIGRIDVIEWITEM_F84BFC3E90BE49F2B0EE203B41B6BABB_H_INCLUDED
# define __NNT_UIKIT_UIGRIDVIEWITEM_F84BFC3E90BE49F2B0EE203B41B6BABB_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UIGridView);
NNTDECL_EXTERN_CLASS(UIGridViewItem);

@protocol UIGridViewItemDelegate <NSObject>
@optional

- (void)gridviewItem:(UIGridViewItem*)item draw:(CGContextRef)contex rect:(CGRect)rect;

@end

@interface UIGridViewItem : NNTUIView {
    
    //! scale view to fill item, default is NO
    BOOL _scaleToFill;
    
    //! content
    UIView *_content;
    
    //! grid
    UIGridView *_gridView;
    
    //! margin
    CGMargin _margin;
    BOOL _selfMargin;
    
    //! high light.
    NgFill* _highlightFill;
    
    //! delegate & source.
    id <UIGridViewItemDelegate> _delegate;
    
}

@property (nonatomic, assign) BOOL scaleToFill;
@property (nonatomic, retain) UIView *content;
@property (nonatomic, assign) UIGridView *gridView;
@property (nonatomic, assign) CGMargin margin;
@property (nonatomic, assign) BOOL selfMargin;
@property (nonatomic, assign) id <UIGridViewItemDelegate> delegate;
@property (nonatomic, retain) NgFill* highlightFill;

@end

NNTDECL_EXTERN_CLASS(UIGridViewItemWithClose);

@protocol UIGridViewItemWithCloseDelegate <UIGridViewItemDelegate>

- (void)griditemClose:(UIGridViewItemWithClose*)item;

@end

@interface UIGridViewItemWithClose : UIGridViewItem {
    CGRectPositionType closePosition;
    UIButton *closeButton;
}

@property (nonatomic, assign) CGRectPositionType closePosition;
@property (nonatomic, readonly) UIButton *closeButton;

@end

@interface UIGridViewItemWithLabel : UIGridViewItem {
    UILabel *label;
    NSUInteger height;
}

@property (nonatomic, retain) UILabel *label;
@property (nonatomic, assign) NSUInteger height;

@end

# ifdef NNT_CXX

_CXXVIEW_DECL(UIGridViewItem);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

NNT_BEGIN_NS(tpl)

template <typename implT,
typename itemT
>
class GridItem
: public View<implT, itemT>
{
    typedef View<implT, itemT> super;
    typedef implT impl_type;
    
public:
    
    GridItem()
    {
        PASS;
    }
    
    GridItem(impl_type const& r)
    : super(r._self)
    {
        PASS;
    }
    
    GridItem(itemT* item)
    : super(item)
    {
        PASS;
    }
    
    UIView* content() const
    {
        return this->_self.content;
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
};

NNT_END_NS

template <typename itemT = _CXXVIEW(UIGridViewItem) >
class GridItem
: public tpl::GridItem<
GridItem<itemT>,
itemT>
{
    typedef tpl::GridItem<
    GridItem<itemT>,
    itemT> super;
    
    typedef GridItem<itemT> impl_type;
    
public:
    
    GridItem()
    {
        PASS;
    }
    
    GridItem(impl_type const& r)
    : super(r)
    {
        PASS;
    }
    
    GridItem(itemT* item)
    : super(item)
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
