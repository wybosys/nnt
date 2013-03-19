
# ifndef __NNT_UIKIT_SPREADSHEET_7452B2845C4541B9A1F47218E00EF9E3_H_INCLUDED
# define __NNT_UIKIT_SPREADSHEET_7452B2845C4541B9A1F47218E00EF9E3_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UISpreadSheet);
NNTDECL_EXTERN_CLASS(UISpreadSheetCell);
NNTDECL_EXTERN_CLASS(UISpreadSheetRow);
NNTDECL_EXTERN_CLASS(UISpreadSheetCellMatrix);
NNTDECL_EXTERN_CLASS(NSCellLine);
NNTDECL_EXTERN_CLASS(NgLineStyle);
NNTDECL_EXTERN_CLASS(NgTextStyle);
NNTDECL_EXTERN_CLASS(NgFill);
NNTDECL_EXTERN_CLASS(NgColor);

typedef enum {
    UISpreadSheetCellMatrixTypeCornerLeftTop = 0x01,
    UISpreadSheetCellMatrixTypeCornerRightTop = 0x02,
    UISpreadSheetCellMatrixTypeCornerLeftBottom = 0x03,
    UISpreadSheetCellMatrixTypeCornerRightBottom = 0x04,
    UISpreadSheetCellMatrixTypeCells = 0x10,
    UISpreadSheetCellMatrixTypeHeaderTop = 0x20,
    UISpreadSheetCellMatrixTypeHeaderLeft = 0x21,
    UISpreadSheetCellMatrixTypeHeaderRight = 0x22,
    UISpreadSheetCellMatrixTypeHeaderBottom = 0x23,
} UISpreadSheetCellMatrixType;

typedef enum {
    UISpreadSheetCellMatrixHighlightModeHov = 0x1,
    UISpreadSheetCellMatrixHighlightModeVec = 0x2,
    UISpreadSheetCellMatrixHighlightModeAll = 0x3,
    UISpreadSheetCellMatrixHighlightModeNone = 0x0
} UISpreadSheetCellMatrixHighlightMode;

@protocol UISpreadSheetDataSource <NSObject>

@optional

//! request rows number of sheet.
- (NSUInteger)sheetRowsNumber:(UISpreadSheet*)sheet;

//! request cols number of sheet. 
- (NSUInteger)sheetColsNumber:(UISpreadSheet*)sheet;

//! request header number of sheet for every direction.
- (NSUInteger)sheetHeadersNumber:(UISpreadSheet*)sheet dir:(NgDirection)dir;

@end

@protocol UISpreadSheetDelegate <NSObject>

@optional

//! request row height.
- (real)sheetRowHeight:(UISpreadSheet*)sheet row:(NSUInteger)row;

//! request col width.
- (real)sheetColWidth:(UISpreadSheet*)sheet col:(NSUInteger)col;

//! init cell.
- (void)sheetInit:(UISpreadSheet*)sheet cell:(UISpreadSheetCell*)cell;

//! init row.
- (void)sheetInit:(UISpreadSheet*)sheet row:(UISpreadSheetRow*)row;

//! init sheet.
- (void)sheetInit:(UISpreadSheet*)sheet;

//! request line style for row.
- (NgLineStyle*)sheetRowLineStyle:(UISpreadSheet*)sheet row:(NSUInteger)row;

//! request line style for col.
- (NgLineStyle*)sheetColLineStyle:(UISpreadSheet*)sheet col:(NSUInteger)col;

//! request text-style for every cell.
- (NgTextStyle*)sheetTextStyle:(UISpreadSheet*)sheet row:(NSUInteger)row col:(NSUInteger)col;

//! request string value for every cell.
- (NSString*)sheetTextString:(UISpreadSheet*)sheet row:(NSUInteger)row col:(NSUInteger)col;

//! if current touching cells should be touched.
- (BOOL)sheetShouldTouchs:(UISpreadSheet*)sheet cells:(NSArray*)cells matrix:(UISpreadSheetCellMatrix*)matrix;

//! after cells touched.
- (void)sheetDidTouchs:(UISpreadSheet*)sheet cells:(NSArray*)cells matrix:(UISpreadSheetCellMatrix*)matrix;

//! request fill for every cell.
- (NgFill*)sheetFill:(UISpreadSheet*)sheet row:(NSUInteger)row col:(NSUInteger)col;

//! draw every cell. return YES will draw default cell.
- (void)sheetDrawCell:(UISpreadSheet*)sheet cell:(UISpreadSheetCell*)cell context:(CGContextRef)context;

//! cell.
- (UISpreadSheetCell*)sheetCell:(UISpreadSheet*)sheet row:(NSUInteger)row col:(NSUInteger)col;

//! row.
- (UISpreadSheetRow*)sheetRow:(UISpreadSheet*)sheet row:(NSUInteger)row;

@end

@interface UISpreadSheet : NNTUIControl <UISpreadSheetDelegate, UISpreadSheetDataSource> {
    
    //! datasource and delegate.
    id <UISpreadSheetDataSource> dataSource;
    id <UISpreadSheetDelegate> delegate;
    
    //! width for col, should overrided by delegate.
    real colWidth;
    
    //! height for row, should overrided by delegate. 
    real rowHeight;
    
    //! line style for col, should override by delegate.
    NgLineStyle *colLineStyle;
    
    //! line style for row, should override by delegate.
    NgLineStyle *rowLineStyle;
    
    //! text style for cell, should override by delegate.
    NgTextStyle *textStyle;
    
    //! fill for cell, should override by delegate.
    NgFill *cellFill;
    
    //! highlight color, when one cell touched, sheet will draw a cross on screen.
    UIColor *selHighlightColor;
    
    //! highlight mode, default is ALL.
    UISpreadSheetCellMatrixHighlightMode highlightMode;
    
    //! last selected cells, store all the select cells in header of cells.
    NSArray *selectedCells;
    
    //! stretch main row or col for fit width.
    BOOL stretchColForFit, stretchRowForFit;
    BOOL stretchColForFitForce, stretchRowForFitForce;
    
    //! reselect on selected cell, default is NO.
    BOOL reselectSelectedCell;
    
    NNTDECL_PRIVATE(UISpreadSheet);
}

@property (nonatomic, assign) id <UISpreadSheetDataSource> dataSource;
@property (nonatomic, assign) id <UISpreadSheetDelegate> delegate;
@property (nonatomic, assign) real colWidth, rowHeight;
@property (nonatomic, retain) NgLineStyle *colLineStyle, *rowLineStyle;
@property (nonatomic, retain) NgTextStyle *textStyle;
@property (nonatomic, retain) NgFill *cellFill;
@property (nonatomic, retain) UIColor *selHighlightColor;
@property (nonatomic, assign) NSArray *selectedCells;
@property (nonatomic, assign) BOOL stretchColForFit, stretchRowForFit, stretchColForFitForce, stretchRowForFitForce;
@property (nonatomic, assign) BOOL reselectSelectedCell;
@property (nonatomic, assign) UISpreadSheetCellMatrixHighlightMode highlightMode;

//! return cols number.
- (NSUInteger)colsNumber;

//! return rows number.
- (NSUInteger)rowsNumber;

//! retrive cell at row and col.
- (UISpreadSheetCell*)cellAt:(NSUInteger)row col:(NSUInteger)col;
- (UISpreadSheetCell*)cellAtMain:(NSUInteger)row col:(NSUInteger)col;

//! retrive row at index.
- (UISpreadSheetRow*)rowAt:(NSUInteger)row;

//! convert cell's frame from cell-martix to sheet.
- (CGRect)convertCellRect:(UISpreadSheetCell*)cell;

//! get cell line.
- (NSCellLine*)colLineAt:(NSUInteger)idx;
- (NSCellLine*)rowLineAt:(NSUInteger)idx;

//! clear.
- (void)clear;

//! clear selected.
- (void)clearSelected;

@end

@interface UISpreadSheet (reload)

//! reload data.
- (void)reloadData;

//! relayout data.
- (void)relayoutData;

//! reload all styles.
- (void)reloadStyles;

//! update geometry.
- (void)updateGeometry;

//! reload all.
- (void)reloadAll;

//! reload line style.
- (void)reloadHovLineStyles;
- (void)reloadVecLineStyles;
- (void)reloadLineStyles;
- (void)reloadLinePos;
- (void)reloadHovLinePos;
- (void)reloadVecLinePos;

@end

@interface UISpreadSheet (wrapper)

- (real)rowHeight:(NSUInteger)row;
- (real)colWidth:(NSUInteger)col;
- (NgLineStyle*)rowLineStyle:(NSUInteger)row;
- (NgLineStyle*)colLineStyle:(NSUInteger)col;
- (NSString*)cellText:(NSUInteger)row col:(NSUInteger)col;
- (NgTextStyle*)cellTextStyle:(NSUInteger)row col:(NSUInteger)col;
- (NgFill*)cellFill:(NSUInteger)row col:(NSUInteger)col;

@end

@interface UISpreadSheet (action)

- (void)highlightCell:(UISpreadSheetCell*)cell val:(BOOL)val;
- (void)highlightRow:(UISpreadSheetCell*)cell val:(BOOL)val;
- (void)highlightCol:(UISpreadSheetCell*)cell val:(BOOL)val;

@end

@interface UISpreadSheet (query)

//! walk all cells
- (void)walkCell:(SEL)sel obj:(NSObject*)obj ctx:(id)ctx;

//! walk all hlines.
- (void)walkLineHov:(SEL)sel obj:(NSObject*)obj ctx:(id)ctx;

//! walk all vlines.
- (void)walkLineVec:(SEL)sel obj:(NSObject*)obj ctx:(id)ctx;

@end

NNTDECL_EXTERN_CLASS(UISpreadSheetHeaderVec);
NNTDECL_EXTERN_CLASS(UISpreadSheetHeaderHov);
NNTDECL_EXTERN_CLASS(UISpreadSheetCorner);

@interface UISpreadSheet (children)

- (UISpreadSheetHeaderVec*)headerCellsLeft;
- (UISpreadSheetHeaderVec*)headerCellsRight;
- (UISpreadSheetHeaderHov*)headerCellsTop;
- (UISpreadSheetHeaderHov*)headerCellsBottom;
- (UISpreadSheetCorner*)cornerCellsLeftTop;
- (UISpreadSheetCorner*)cornerCellsRightTop;
- (UISpreadSheetCorner*)cornerCellsLeftBottom;
- (UISpreadSheetCorner*)cornerCellsRightBottom;
- (UISpreadSheetCellMatrix*)Cells;

@end

NNT_EXTERN signal_t kSignalSheetTouchs;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIControl+NNT.h"
# import "UISpreadSheetCell.h"
# import "UISpreadSheetCellMatrix.h"
# import "UISpreadSheetHeader.h"
# import "UISpreadSheetCorner.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class SpreadSheet;

NNT_END_NS
NNT_END_HEADER_CXX

NNT_BEGIN_HEADER_OBJC

class _cxxwrapper_spreadsheet
{
public:
    ::nnt::ui::SpreadSheet* sheet;
    
    ::nnt::ui::SpreadSheet* operator -> ()
    {
        return sheet;
    }
    
};

@interface _cxx_spreadsheet : UISpreadSheet {
    @public
    _cxxwrapper_spreadsheet _sheet;
}

@end

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class SpreadSheet
: public Control<SpreadSheet, 
_cxx_spreadsheet
>
{
    typedef Control<SpreadSheet, 
    _cxx_spreadsheet
    > super;
    
    friend class ::_cxxwrapper_spreadsheet;
    
public:
    
    typedef core::pointer_vector<sheet::Row> rows_type;
    
    SpreadSheet()
    {
        _init();
        
        this->_self->_sheet.sheet = this;
    }
    
    sheet::Row& row(uint row)
    {
        return *_rows[row];
    }
    
    void reload()
    {
        [this->_self reloadAll];
    }
    
    void set_highlight(UISpreadSheetCellMatrixHighlightMode mode)
    {
        this->_self.highlightMode = mode;
    }
    
    sheet::Cells topheader() const
    {
        return [this->_self headerCellsTop];
    }
    
    sheet::Cells bottomheader() const
    {
        return [this->_self headerCellsBottom];
    }
    
    sheet::Cells leftheader() const
    {
        return [this->_self headerCellsLeft];
    }
    
    sheet::Cells rightheader() const
    {
        return [this->_self headerCellsRight];
    }
    
    sheet::Cells cells() const
    {
        return [this->_self Cells];
    }
    
    sheet::Cells ltcorner() const
    {
        return [this->_self cornerCellsLeftTop];
    }
    
    sheet::Cells rtcorner() const
    {
        return [this->_self cornerCellsRightTop];
    }
    
    sheet::Cells lbcorner() const
    {
        return [this->_self cornerCellsLeftBottom];
    }
    
    sheet::Cells rbcorner() const
    {
        return [this->_self cornerCellsRightBottom];
    }
    
    void set_highlight(Color const& color)
    {
        this->_self.selHighlightColor = color;
    }
    
    void clear()
    {
        [this->_self clear];
    }
    
    void clear_selected()
    {
        [this->_self clearSelected];
    }
    
    void set_reselectable(bool val)
    {
        this->_self.reselectSelectedCell = val;
    }
    
    void set_textstyle(cg::TextStyle const& ts)
    {
        this->_self.textStyle = ts;
    }
    
public:
    
    uint fixheader_left, fixheader_right, fixheader_top, fixheader_bottom;    
    uint rows, cols;
    uint col_width, row_height;
    cg::LineStyle linestyle_row, linestyle_col;

    void _clear()
    {
        // clear.
        _rows.clear();
        
        // resize rows.
        _rows.resize(rows);
        
        // resize cols.
        for (uint i = 0; i < rows; ++i)
        {
            for (uint j = 0; j < cols; ++j)
            {
                sheet::Cell* cell = _cell(i, j);
                _rows[i]->add_cell(cell);
            }
        }
    }
    
protected:
    
    virtual sheet::Cell* _cell(uint r, uint c) const
    {
        return new sheet::Cell;
    }
    
    void _init()
    {
        fixheader_top = fixheader_bottom = fixheader_left = fixheader_right = 0;
        rows = cols = 0;
        col_width = row_height = 50;
    }    
    
    rows_type _rows;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif