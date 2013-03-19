
# ifndef __NNT_UIKIT_UIGRIDVIEW_337D008AA0DE423CB0C397021B0EEC88_H_INCLUDED
# define __NNT_UIKIT_UIGRIDVIEW_337D008AA0DE423CB0C397021B0EEC88_H_INCLUDED

# import "UIGridViewItem.h"
# import "UIScrollView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(WCALayer);

NNTDECL_PRIVATE_HEAD(UIGridView);

@interface UIGridView : NNTUIScrollView {
    
    //! rows and cols.
    NSUInteger _rows, _cols;
    
    //! preferred rows and cols.
    real _preferredRows, _preferredCols;
    
    //! padding of items.
    CGPadding _padding;
    
    //! margin of items.
    CGMargin _margin;
    
    //! if enableFillIndex is YES, when remove item from grid, the next item will move ahead.
    BOOL _enableFillIndex;
    
    //! children
    NSArray *_children;
    
    //! item's default background fill.
    WCGFill *_itemBackgroundFill;
    
    //! item scaleToFit. default is NO.
    BOOL _itemScaleToFit;
    
    //! item's high light fill.
    WCGFill *_itemHighlight;
    
    //! item size.
    CGSize _preferredItemSize;
    
    //! item shadow.
    CGShadow *_itemShadow;
    
    //! item border.
    WCGLineStyle *_itemBorder;
    
    //! class for instance item, default is UIGridViewItem.
    Class _classItem;
    
    //! split line style. default is nil.
    WCGLineStyle *_rowLineStyle, *_colLineStyle;
    
    //! enable animated, default is YES.
    BOOL _enableAnimated;
    
    NNTDECL_PRIVATE(UIGridView);
}

@property (nonatomic) NSUInteger rows, cols;
@property (nonatomic) real preferredRows, preferredCols;
@property (nonatomic) CGPadding padding;
@property (nonatomic) CGMargin margin;
@property (nonatomic) BOOL enableFillIndex;
@property (nonatomic, readonly) NSArray *children;
@property (nonatomic, retain) WCGFill *itemBackgroundFill;
@property (nonatomic, assign) BOOL itemScaleToFit;
@property (nonatomic, retain) CGShadow *itemShadow;
@property (nonatomic, assign) CGSize preferredItemSize;
@property (nonatomic, retain) WCGLineStyle *itemBorder;
@property (nonatomic, assign) BOOL enableAnimated;
@property (nonatomic, assign) Class classItem;
@property (nonatomic, retain) WCGFill *itemHighlight;
@property (nonatomic, retain) WCGLineStyle *rowLineStyle, *colLineStyle;

- (id)initWithFrame:(CGRect)frame;
- (id)initWithFrame:(CGRect)frame rows:(NSUInteger)rows cols:(NSUInteger)cols;

//! add child
- (UIGridViewItem*)addChildView:(UIView*)child;
- (UIGridViewItem*)addChildView:(UIView*)child item:(UIGridViewItem*)item;
- (UIGridViewItem*)addChild:(UIGridViewItem*)child;

//! get item.
- (UIGridViewItem*)itemAt:(NSUInteger)row col:(NSUInteger)col;

//! index of item.
- (CGPoint)indexOfItem:(UIGridViewItem*)item;

//! remove item
- (void)removeItem:(UIGridViewItem*)item;

//! clear.
- (void)clearItems;

//! hittest
- (UIGridViewItem*)hitTestForItem:(CGPoint*)pt;

//! relayoutItem.
- (void)relayoutItems:(BOOL)animated;

//! calc single item's size.
- (CGSize)calcItemSize;

//! calc content's size.
- (CGSize)calcContentSize;

@end

_CXXVIEW_DECL(UIGridView);

NNT_EXTERN signal_t kSignalContentClicked;
NNT_EXTERN signal_t kSignalItemClicked;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIScrollView+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

template <typename implT, 
typename gridT = _CXXVIEW(UIGridView)
>
class GridView
: public ScrollView<implT, gridT>
{
    typedef ScrollView<implT, gridT> super;
    
public:
    
    typedef GridItem<> item_type;
    
    GridView()
    {
        PASS;
    }
    
    explicit GridView(gridT* grid)
    : super(grid)
    {
        PASS;
    }
    
    void set_itemscaletofit(bool val)
    {
        this->_self.itemScaleToFit = val;
    }
    
    void set_padding(CGPadding const& pad)
    {
        this->_self.padding = pad;
    }
    
    void set_margin(CGMargin const& mag)
    {
        this->_self.margin = mag;
    }
    
    void set_rows(uint rows)
    {
        this->_self.rows = rows;
    }
    
    uint rows() const
    {
        return this->_self.rows;
    }
    
    void set_cols(uint cols)
    {
        this->_self.cols = cols;
    }
    
    uint cols() const
    {
        return this->_self.cols;
    }

    void set_preferred_rows(uint rows)
    {
        this->_self.preferredRows = rows;
    }
    
    uint preferred_rows() const
    {
        return this->_self.preferredRows;
    }
    
    void set_preferred_cols(uint cols)
    {
        this->_self.preferredCols = cols;
    }
    
    uint preferred_cols() const
    {
        return this->_self.preferredCols;
    }
    
    void set_preferred_size(cg::Size const& sz)
    {
        this->_self.preferredItemSize = sz;
    }
    
    cg::Size preferred_size() const
    {
        return this->_self.preferredItemSize;
    }
    
    item_type add_item(UIView* item)
    {
        item_type::objc_type* ret = (item_type::objc_type*)[this->_self addChildView:item];
        return ret;
    }
    
    void add(UIGridViewItem* item)
    {
        [this->_self addChild:item];
    }
    
    template <typename objT>
    void add(objT const& item)
    {
        wtl::const_pointer<objT> ptr(item);
        id obj = *ptr;
        if ([obj isKindOfClass:[UIGridViewItem class]])
            add((UIGridViewItem*)obj);
        else
            add_item((UIView*)obj);
    }
    
    item_type item_at(uint row, uint col) const
    {
        item_type::objc_type* ret = (item_type::objc_type*)[this->_self itemAt:row col:col];
        return ret;
    }
    
    void relayout_items(bool ani = true)
    {
        [this->_self relayoutItems:ani];
    }
    
    void clear()
    {
        [this->_self clearItems];
    }
    
    void set_row(cg::LineStyle const& ls)
    {
        this->_self.rowLineStyle = ls;
    }
    
    void set_col(cg::LineStyle const& ls)
    {
        this->_self.colLineStyle = ls;
    }
    
};

class Grid
: public GridView<Grid, _CXXVIEW(UIGridView)>
{
    typedef GridView<Grid, _CXXVIEW(UIGridView)> super;
    
public:
    
    Grid()
    {
        PASS;
    }
    
    Grid(UIGridView* view)
    : super((objc_type*)view)
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
