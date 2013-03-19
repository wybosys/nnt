
# ifndef __WSI_UIKIT_UISPREADSHEETCELLMATRIX_74F7DDCDA98A424C85B32DDEA29AA7AE_H_INCLUDED
# define __WSI_UIKIT_UISPREADSHEETCELLMATRIX_74F7DDCDA98A424C85B32DDEA29AA7AE_H_INCLUDED

# import "UIScrollView+WSI.h"
# import "UISpreadSheet.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGLineStyle);
WSIDECL_EXTERN_CLASS(UISpreadSheet);
WSIDECL_EXTERN_CLASS(UISpreadSheetCell);
WSIDECL_EXTERN_CLASS(NSCellLine);

@interface UISpreadSheetRow : NSObject {
    
    //! container of all cells.
    NSMutableArray *cells;

    //! parent sheet.
    UISpreadSheet *parentSheet;
    
    //! first line.
    NSCellLine *lineTop;
    
    //! end line.
    NSCellLine *lineBottom;
    
    //! row height.
    real rowHeight;
}

@property (nonatomic, readonly) NSMutableArray *cells;
@property (nonatomic, assign) NSCellLine *lineTop, *lineBottom;
@property (nonatomic, readonly, getter = getRowHeight) real rowHeight;
@property (nonatomic, assign) UISpreadSheet *parentSheet;

- (id)initWithCapacity:(NSUInteger)sz;

//! add cell.
- (void)addObject:(UISpreadSheetCell*)obj;

//! get cell at index.
- (UISpreadSheetCell*)objectAtIndex:(NSUInteger)idx;

//! cells' count.
- (NSUInteger)count;

//! row height.
- (real)getRowHeight;

//! walk all cells.
- (void)walk:(void (^)(UISpreadSheetCell*))func;

@end

@interface UISpreadSheetCellMatrix : WSIUIScrollView {        
    
    //! range
    NSRange rowRange;
    NSRange colRange;
    
    //! layer draw for cells.
    CALayer *layerCells;
    CALayer *layerAssor;
    
    //! lst selected
    NSArray *selectedCells;
    
    //! type.
    UISpreadSheetCellMatrixType type;
    
    //! pointer to sheet.
    UISpreadSheet *sheet;
    
    //! highlight mode. default is ALL;
    UISpreadSheetCellMatrixHighlightMode highlightMode;
}

@property (nonatomic, assign) NSRange rowRange, colRange;
@property (nonatomic, assign) UISpreadSheet *sheet;
@property (nonatomic, assign) CALayer *layerCells, *layerAssor;
@property (nonatomic, assign) UISpreadSheetCellMatrixType type;
@property (nonatomic, readonly, assign) NSArray *selectedCells;
@property (nonatomic, assign) UISpreadSheetCellMatrixHighlightMode highlightMode;

//! test cell.
- (UISpreadSheetCell*)hitTestForCell:(UITouch*)touch;

//! if contian cell.
- (BOOL)containCell:(UISpreadSheetCell const*)cell;

//! get cell.
- (UISpreadSheetCell*)cellAt:(NSUInteger)row col:(NSUInteger)col;

//! clear selected.
- (void)clearSelected:(BOOL)evt;

//! refresh selected.
- (void)refreshSelected;

//! clear.
- (void)clear;

@end

@interface UISpreadSheetCellMatrix (geometry)

- (real)fullWidth;
- (real)fullHeight;
- (CGSize)fullSize;

@end

@interface UISpreadSheetCellMatrix (interactive)

- (void)transHighlight:(NSArray*)old sel:(NSArray*)sel;
- (void)highlightCell:(UISpreadSheetCell*)cell val:(BOOL)val mode:(UISpreadSheetCellMatrixHighlightMode)mode;
- (void)dehighlight:(UISpreadSheetCell*)cell;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UISpreadSheetCell.h"
# include "UIScrollView+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(sheet)

class Row
: public Object<Row, UISpreadSheetRow>
{
public:
    
    typedef core::pointer_vector<Cell> cells_type;
    
    Row()
    {
        this->_self = [[UISpreadSheetRow alloc] init];
    }
    
    void add_cell(Cell* cell)
    {
        [this->_self addObject:*cell];
        _cells.push_back(cell);
    }
    
    Cell& cell(uint col)
    {
        return *_cells[col];
    }
    
protected:
    cells_type _cells;
};

class Cells
: public ScrollView<Cells, UISpreadSheetCellMatrix>
{
    typedef ScrollView<Cells, UISpreadSheetCellMatrix> super;
    typedef Cells self_type;
    
public:
    
    Cells(UISpreadSheetCellMatrix* r)
    : super(r)
    {
        PASS;
    }
    
    Cells(self_type const& r)
    : super(r._self)
    {
        PASS;
    }
    
    void set_highlight(UISpreadSheetCellMatrixHighlightMode mode)
    {
        this->_self.highlightMode = mode;
    }

};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif