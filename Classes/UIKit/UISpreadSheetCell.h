
# ifndef __NNT_UIKIT_UISPREADSHEETCELL_5F679FE7960B4DF09F88A747CE74822F_H_INCLUDED
# define __NNT_UIKIT_UISPREADSHEETCELL_5F679FE7960B4DF09F88A747CE74822F_H_INCLUDED

# import "UICell.h"

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(sheet)

class Cell;

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UISpreadSheetRow);
NNTDECL_EXTERN_CLASS(UISpreadSheetCellMatrixLayer);

@interface UISpreadSheetCell : NSCell {
    
    WCGFill *cellFill;
    CGRect frame;
    UISpreadSheetCellMatrixLayer *layer;
    UISpreadSheetRow *parentRow;
    
}

@property (nonatomic, retain) WCGFill *cellFill;
@property (nonatomic, assign) CGRect frame;
@property (nonatomic, readonly) CGRect bounds;
@property (nonatomic, assign) UISpreadSheetCellMatrixLayer *layer;
@property (nonatomic, assign) UISpreadSheetRow *parentRow;

- (void)drawInContext:(CGContextRef)ctx;
- (void)setNeedsDisplay;
- (void)setNeedsDisplaySelf;

- (void)highlightRow;
- (void)highlightCol;
- (void)dehighlight;

@end

# ifdef NNT_CXX

@interface _cxx_sheetcell : UISpreadSheetCell {
@public
    ::wsi::ui::sheet::Cell* cell;
}

@end

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(sheet)

class Cell
: public ui::Object<Cell, _cxx_sheetcell>
{
    typedef ui::Object<Cell, _cxx_sheetcell> super;
    typedef Cell self_type;
    
public:
    
    Cell()
    {
        this->_self = [[_cxx_sheetcell alloc] init];
        this->_self->cell = this;
    }
    
    Cell(self_type const& r)
    : super(r._self)
    {
        PASS;
    }
    
    Cell(_cxx_sheetcell* cell)
    : super(cell)
    {
        PASS;
    }
    
    virtual ~Cell()
    {
        PASS;
    }
    
    self_type& operator = (self_type const& r)
    {
        this->_set(r);
        return *this;
    }
    
    virtual void draw(CGContextRef)
    {
        PASS;
    }
    
    CGRect bounds() const
    {
        return this->_self.bounds;
    }
    
    CGRect frame() const
    {
        return this->_self.frame;
    }
    
    void set_background(cg::Fill const& fill)
    {
        this->_self.cellFill = fill;
    }
    
    void set_text(ns::String const& str)
    {
        this->_self.text = str;
    }
    
    void set_style(cg::TextStyle const& ts)
    {
        this->_self.textStyle = ts;
    }
    
    uint row() const
    {
        return this->_self.row;
    }
    
    uint col() const
    {
        return this->_self.col;
    }
    
    void dehighlight()
    {
        [this->_self dehighlight];
    }
    
    void highlight_row()
    {
        [this->_self highlightRow];
    }
    
    void highlight_col()
    {
        [this->_self highlightCol];
    }
    
    virtual ns::String text() const;
        
};

class CellArray
: public ns::Array
{
    typedef ns::Array super;
    
public:
    
    CellArray(NSArray* arr)
    : super(arr)
    {
        PASS;
    }
    
    Cell& operator [] (uint idx)
    {
        Cell* cell = (Cell*)[at(idx) object];
        return *cell;
    }
    
    Cell& operator [] (int idx)
    {
        Cell* cell = (Cell*)[at(idx) object];
        return *cell;
    }

};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif