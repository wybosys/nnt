
# ifndef __WSI_UIKIT_UILAYOUTGRIDVIEW_7D0273304D4A4FE99A4F68A2A06598EA_H_INCLUDED
# define __WSI_UIKIT_UILAYOUTGRIDVIEW_7D0273304D4A4FE99A4F68A2A06598EA_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGLineStyle);
WSIDECL_EXTERN_CLASS(WSIUILabel);

WSIDECL_PRIVATE_HEAD(UILayoutGridView);

@interface UILayoutGridView : WSIUIView {
    
    //! row.
    NSUInteger _rows, _cols;
    
    //! padding.
    CGPadding _padding;
    
    //! margin
    CGMargin _margin;
    
    //! line style.
    WCGLineStyle *_rowLineStyle;
    WCGLineStyle *_colLineStyle;
    
    //! reuse label.
    WSIUILabel *_reuseLabel;
    
@private
    
    NSMutableArray *_rowlines, *_collines;
    
    WSIDECL_PRIVATE(UILayoutGridView);
}

@property (nonatomic, assign) NSUInteger rows, cols;
@property (nonatomic, assign) CGPadding padding;
@property (nonatomic, assign) CGMargin margin;
@property (nonatomic, retain) WCGLineStyle *rowLineStyle, *colLineStyle;
@property (nonatomic, retain) WSIUILabel *reuseLabel;

//! init
- (id)initWithFrame:(CGRect)frame;
- (id)initWithGrid:(NSUInteger)rows cols:(NSUInteger)cols;

//! add subview
- (void)addSubview:(UIView *)view row:(NSUInteger)row col:(NSUInteger)col;
- (void)addSubview:(UIView *)view;

//! clear items.
- (void)clear;

//! begin & end.
- (void)beginAdd;
- (void)endAdd;

//! set label.
- (WSIUILabel*)addLabel:(NSString *)label row:(NSUInteger)row col:(NSUInteger)col;
- (WSIUILabel*)addLabel:(NSString *)label;

//! set subview, for merge cells.
- (void)setSubview:(UIView *)view row:(NSUInteger)row col:(NSUInteger)col;

//! get subview at
- (UIView*)viewAt:(NSUInteger)row col:(NSUInteger)col;
- (UILabel*)labelAt:(NSUInteger)row col:(NSUInteger)col;
- (id)objectAt:(NSUInteger)row col:(NSUInteger)col;
- (id)objectAt:(NSUInteger)index;

//! get row line.
- (UIView*)getRowLine:(NSUInteger)row;

//! set layout.
- (void)setLayoutCol:(NSUInteger)col pixel:(int)pixel;
- (void)setLayoutCol:(NSUInteger)col flex:(real)flex;
- (void)setLayoutRow:(NSUInteger)row pixel:(int)pixel;
- (void)setLayoutRow:(NSUInteger)row flex:(real)flex;

//! relayout.
- (void)updateLayout;

@end

_CXXVIEW_DECL(UILayoutGridView);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UILabel+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class LayoutGrid
: public View<LayoutGrid, _CXXVIEW(UILayoutGridView)>
{
    
    typedef View<LayoutGrid, _CXXVIEW(UILayoutGridView)> super;
    
public:
    
    LayoutGrid()
    {
        PASS;
    }
        
    virtual void layout_subviews()
    {
        PASS;
    }
    
    void set_rows(uint val)
    {
        this->_self.rows = val;
    }
    
    uint rows() const
    {
        return this->_self.rows;
    }
    
    void set_cols(uint val)
    {
        this->_self.cols = val;
    }
    
    uint cols() const
    {
        return this->_self.cols;
    }
    
    void set_padding(CGPadding const& pd)
    {
        this->_self.padding = pd;
    }
    
    CGPadding padding() const
    {
        return this->_self.padding;
    }
    
    void set_margin(CGMargin const& mg)
    {
        this->_self.margin = mg;
    }
    
    CGMargin margin() const
    {
        return this->_self.margin;
    }
    
    void set_rowline(cg::LineStyle const& ls)
    {
        this->_self.rowLineStyle = ls;
    }
    
    void set_colline(cg::LineStyle const& ls)
    {
        this->_self.colLineStyle = ls;
    }
    
    void clear()
    {
        [this->_self clear];
    }
    
    void begin_add()
    {
        [this->_self beginAdd];
    }
    
    void commit_add()
    {
        [this->_self endAdd];
    }
    
    WSIUILabel* add(ns::String const& text, uint row, uint col)
    {
        return [this->_self addLabel:text row:row col:col];
    }
    
    WSIUILabel* add(ns::String const& text)
    {
        return [this->_self addLabel:text];
    }
    
    template <typename viewT>
    void add(viewT const& view, uint row, uint col, typename wtl::is_same<viewT, ns::String>::differ* = NULL)
    {
        wtl::const_pointer<viewT> ptr(view);
        [this->_self addSubview:*ptr row:row col:col];
    }
    
    template <typename viewT>
    void add(viewT const& view, typename wtl::is_same<viewT, ns::String>::differ* = NULL)
    {
        wtl::const_pointer<viewT> ptr(view);
        [this->_self addSubview:*ptr];
    }
    
    UIView* view_at(uint row, uint col)
    {
        return [this->_self viewAt:row col:col];
    }
    
    WSIUILabel* label_at(uint row, uint col)
    {
        return (WSIUILabel*)[this->_self labelAt:row col:col];
    }
    
    id object_at(uint row, uint col)
    {
        return [this->_self objectAt:row col:col];
    }
    
    id object_at(uint idx)
    {
        return [this->_self objectAt:idx];
    }
    
    void update()
    {
        [this->_self updateLayout];
    }
    
    void set_layout_col(uint col, _pixel const& pixel)
    {
        [this->_self setLayoutCol:col pixel:pixel.val];
    }
    
    void set_layout_col(uint col, _flex const& flex)
    {
        [this->_self setLayoutCol:col flex:flex.val];
    }
    
    void set_layout_row(uint row, _pixel const& pixel)
    {
        [this->_self setLayoutRow:row pixel:pixel.val];
    }
    
    void set_layout_row(uint row, _flex const& flex)
    {
        [this->_self setLayoutRow:row flex:flex.val];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
