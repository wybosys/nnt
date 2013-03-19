
# import "Core.h"
# import "UISpreadSheet.h"
# import "UISpreadSheetCell.h"
# import "UISpreadSheetCellMatrix.h"
# import "UISpreadSheetHeader.h"
# import "UISpreadSheetCorner.h"
# import "Graphic+NNT.h"
# import "UIColor+NNT.h"

NNT_BEGIN_OBJC

signal_t kSignalSheetTouchs = @"::nnt::ui::sheet::touches";

@interface UISpreadSheetPrivate : NSObject <UIScrollViewDelegate> {
    UISpreadSheet *d_owner;
    
    UISpreadSheetHeaderVec *header_left;
    UISpreadSheetHeaderVec *header_right;
    UISpreadSheetHeaderHov *header_top;
    UISpreadSheetHeaderHov *header_bottom;
    UISpreadSheetCorner *corner_lt;
    UISpreadSheetCorner *corner_rt;
    UISpreadSheetCorner *corner_lb;
    UISpreadSheetCorner *corner_rb;
    UISpreadSheetCellMatrix *cells;
    
    CGPoint ptTouch;
    NSMutableArray *rows;
    
    NSMutableArray *hlines;
    NSMutableArray *vlines;
}

@property (nonatomic, assign) UISpreadSheet *d_owner;
@property (nonatomic, retain) UISpreadSheetHeaderVec *header_left, *header_right;
@property (nonatomic, retain) UISpreadSheetHeaderHov *header_top, *header_bottom;
@property (nonatomic, retain) UISpreadSheetCorner *corner_lt, *corner_rt, *corner_lb, *corner_rb;
@property (nonatomic, retain) UISpreadSheetCellMatrix *cells;

@property (nonatomic, assign) CGPoint ptTouch;
@property (nonatomic, retain) NSMutableArray *rows;
@property (nonatomic, retain) NSMutableArray *hlines, *vlines;

- (void)syncOffset:(UIScrollView*)view animated:(BOOL)animated;
- (void)clear;

@end

@implementation UISpreadSheetPrivate

@synthesize d_owner;
@synthesize header_left, header_right, header_top, header_bottom;
@synthesize corner_lt, corner_rt, corner_lb, corner_rb;
@synthesize cells;
@synthesize ptTouch;
@synthesize rows;
@synthesize hlines, vlines;

- (id)init {
    self = [super init];
    
    d_owner.delegate = d_owner;
    d_owner.dataSource = d_owner;
    
    rows = [[NSMutableArray alloc] init];
    hlines = [[NSMutableArray alloc] init];
    vlines = [[NSMutableArray alloc] init];
        
    cells = [[UISpreadSheetCellMatrix alloc] initWithZero];
    [d_owner addSubview:cells];
    cells.sheet = d_owner;
    cells.delegate = self;
    cells.type = UISpreadSheetCellMatrixTypeCells;
    
    header_left = [[UISpreadSheetHeaderVec alloc] initWithZero];
    [d_owner addSubview:header_left];
    header_left.sheet = d_owner;
    header_left.delegate = self;
    header_left.type = UISpreadSheetCellMatrixTypeHeaderLeft;
    
    header_right = [[UISpreadSheetHeaderVec alloc] initWithZero];
    [d_owner addSubview:header_right];
    header_right.sheet = d_owner;
    header_right.delegate = self;
    header_right.type = UISpreadSheetCellMatrixTypeHeaderRight;
    
    header_top = [[UISpreadSheetHeaderHov alloc] initWithZero];
    [d_owner addSubview:header_top];
    header_top.sheet = d_owner;
    header_top.delegate = self;
    header_top.type = UISpreadSheetCellMatrixTypeHeaderTop;
    
    header_bottom = [[UISpreadSheetHeaderHov alloc] initWithZero];
    [d_owner addSubview:header_bottom];
    header_bottom.sheet = d_owner;
    header_bottom.delegate = self;
    header_bottom.type = UISpreadSheetCellMatrixTypeHeaderBottom;
    
    corner_lt = [[UISpreadSheetCorner alloc] initWithZero];
    [d_owner addSubview:corner_lt];
    corner_lt.sheet = d_owner;
    corner_lt.delegate = self;
    corner_lt.type = UISpreadSheetCellMatrixTypeCornerLeftTop;
    
    corner_lb = [[UISpreadSheetCorner alloc] initWithZero];
    [d_owner addSubview:corner_lb];
    corner_lb.sheet = d_owner;
    corner_lb.delegate = self;
    corner_lb.type = UISpreadSheetCellMatrixTypeCornerLeftBottom;
    
    corner_rt = [[UISpreadSheetCorner alloc] initWithZero];
    [d_owner addSubview:corner_rt];
    corner_rt.sheet = d_owner;
    corner_rt.delegate = self;
    corner_rt.type = UISpreadSheetCellMatrixTypeCornerRightTop;
    
    corner_rb = [[UISpreadSheetCorner alloc] initWithZero];
    [d_owner addSubview:corner_rb];
    corner_rb.sheet = d_owner;
    corner_rb.delegate = self;
    corner_rb.type = UISpreadSheetCellMatrixTypeCornerRightBottom;
    
    return self;
}

- (void)dealloc {
    zero_release(header_left);
    zero_release(header_right);
    zero_release(header_top);
    zero_release(header_bottom);
    zero_release(corner_lt);
    zero_release(corner_rt);
    zero_release(corner_lb);
    zero_release(corner_rb);
    zero_release(cells);
    zero_release(rows);
    zero_release(hlines);
    zero_release(vlines);
    
    [super dealloc];
}

- (void)syncOffset:(UIScrollView *)scrollView animated:(BOOL)animated {
    if (scrollView == cells) {
        [header_top setContentOffset:CGPointSetX(header_top.contentOffset, scrollView.contentOffset.x) animated:animated];
        [header_bottom setContentOffset:CGPointSetX(header_bottom.contentOffset, scrollView.contentOffset.x) animated:animated];
        [header_left setContentOffset:CGPointSetY(header_left.contentOffset, scrollView.contentOffset.y) animated:animated];
        [header_right setContentOffset:CGPointSetY(header_right.contentOffset, scrollView.contentOffset.y) animated:animated];
    } else if (scrollView == header_top) {
        [cells setContentOffset:CGPointSetX(cells.contentOffset, scrollView.contentOffset.x) animated:animated];
        [header_bottom setContentOffset:CGPointSetX(header_bottom.contentOffset, scrollView.contentOffset.x) animated:animated];
    } else if (scrollView == header_bottom) {
        [cells setContentOffset:CGPointSetX(cells.contentOffset, scrollView.contentOffset.x) animated:animated];
        [header_top setContentOffset:CGPointSetX(header_top.contentOffset, scrollView.contentOffset.x) animated:animated];
    } else if (scrollView == header_left) {
        [cells setContentOffset:CGPointSetY(cells.contentOffset, scrollView.contentOffset.y) animated:animated];
        [header_right setContentOffset:CGPointSetY(header_right.contentOffset, scrollView.contentOffset.y) animated:animated];
    } else if (scrollView == header_right) {
        [cells setContentOffset:CGPointSetY(cells.contentOffset, scrollView.contentOffset.y) animated:animated];
        [header_left setContentOffset:CGPointSetY(header_left.contentOffset, scrollView.contentOffset.y) animated:animated];
    }
}

- (void)clear {
    [rows removeAllObjects];
    [hlines removeAllObjects];
    [vlines removeAllObjects];
    
    [header_left clear];
    [header_right clear];
    [header_top clear];
    [header_bottom clear];
    
    [corner_lt clear];
    [corner_lb clear];
    [corner_rt clear];
    [corner_rb clear];
    
    [cells clear];
}

# pragma mark scrollview

- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate {
    [self syncOffset:scrollView animated:YES];
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    [self syncOffset:scrollView animated:YES];
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    [self syncOffset:scrollView animated:NO];
}

@end

@implementation UISpreadSheet

@synthesize dataSource, delegate;
@synthesize colLineStyle, rowLineStyle, textStyle, cellFill;
@synthesize selHighlightColor, highlightMode;
@synthesize selectedCells;
@synthesize stretchColForFit, stretchRowForFit, stretchColForFitForce, stretchRowForFitForce;
@synthesize reselectSelectedCell;
@synthesize rowHeight, colWidth;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self == nil)
        return self;

    NNTDECL_PRIVATE_INIT(UISpreadSheet);
    
    self.backgroundColor = [UIColor whiteColor];
                
    colLineStyle = [[NgMutableLineStyle alloc] init];
    rowLineStyle = [[NgMutableLineStyle alloc] init];
    
    textStyle = [[NgMutableTextStyle alloc] init];
    ((NgMutableTextStyle*)textStyle).alignment = NgAlignmentCenter;
    
    self.selHighlightColor = [UIColor colorWithARGB:0x33000000];
    
    cellFill = nil;
    rowHeight = 25;
    colWidth = 100;
        
    stretchColForFit = NO;
    stretchRowForFit = NO;
    stretchColForFitForce = NO;
    stretchRowForFitForce = NO;
        
    reselectSelectedCell = NO;
    
    self.highlightMode = UISpreadSheetCellMatrixHighlightModeAll;

    return self;
}

- (void)dealloc {
    zero_release(colLineStyle);
    zero_release(rowLineStyle);
    zero_release(textStyle);
    zero_release(cellFill);
    zero_release(selHighlightColor);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalSheetTouchs);
NNTEVENT_END

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
}

/*
- (void)didMoveToWindow {
    [super didMoveToWindow];
    
    [self reloadData];
    [self relayoutData];
}
 */

- (void)setFrame:(CGRect)frame {
    CGRect rc = self.bounds;
    
    [super setFrame:frame];
    
    if (CGRectEqualToRect(rc, self.bounds) == NO)    
        [self relayoutData];
}

/*
- (void)layoutSubviews {
    [super layoutSubviews];
    
    [self relayoutData];
}
 */

- (void)setDelegate:(id<UISpreadSheetDelegate>)__delegate {
    delegate = __delegate;
}

- (void)setDataSource:(id<UISpreadSheetDataSource>)__dataSource {
    dataSource = __dataSource;
}

- (UISpreadSheetCell*)cellAt:(NSUInteger)row col:(NSUInteger)col {
    UISpreadSheetRow *tgt_row = [d_ptr.rows objectAtIndex:row];
    return [tgt_row objectAtIndex:col];
}

- (UISpreadSheetCell*)cellAtMain:(NSUInteger)row col:(NSUInteger)col {
    return [d_ptr.cells cellAt:row col:col];   
}

- (UISpreadSheetRow*)rowAt:(NSUInteger)row {
    return [d_ptr.rows objectAtIndex:row];
}

- (CGRect)convertCellRect:(UISpreadSheetCell *)cell {
    CGRect ret = CGRectZero;
    CGPoint offset = CGPointZero;
    CGPoint origin = CGPointZero;
    UISpreadSheetCellMatrix *mats[] = {
        d_ptr.header_bottom, d_ptr.header_left, d_ptr.header_right, d_ptr.header_top,
        d_ptr.corner_lb, d_ptr.corner_lt, d_ptr.corner_rb, d_ptr.corner_rt,
        d_ptr.cells
    };
    for (uint i = 0; i < 9; ++i) {
        UISpreadSheetCellMatrix *mat = mats[i];
        if ([mat containCell:cell]) {
            offset = mat.contentOffset;
            origin = mat.frame.origin;
            break;
        }
    }
    ret.origin.x = cell.frame.origin.x - offset.x + origin.x;
    ret.origin.y = cell.frame.origin.y - offset.y + origin.y;
    ret.size = cell.frame.size;
    return ret;
}

- (NSCellLine*)colLineAt:(NSUInteger)idx {
    return [d_ptr.vlines objectAtIndex:idx null:nil];
}

- (NSCellLine*)rowLineAt:(NSUInteger)idx {
    return [d_ptr.hlines objectAtIndex:idx null:nil];
}

- (void)clear {
    // clear selected.
    [self clearSelected];
    
    // clear objects.
    [d_ptr clear];    
    
    // relayout.
    [self reloadStyles];
}

- (void)clearSelected {
    [d_ptr.header_top clearSelected:YES];
    [d_ptr.header_bottom clearSelected:YES];
    [d_ptr.header_left clearSelected:YES];
    [d_ptr.header_right clearSelected:YES];
    [d_ptr.cells clearSelected:YES];
}

- (void)setHighlightMode:(UISpreadSheetCellMatrixHighlightMode)mode {
    highlightMode = mode;
    
    d_ptr.header_top.highlightMode = mode;
    d_ptr.header_bottom.highlightMode = mode;
    d_ptr.header_left.highlightMode = mode;
    d_ptr.header_right.highlightMode = mode;
    d_ptr.cells.highlightMode = mode;
}

- (NSUInteger)rowsNumber {
    NSUInteger ret = 0;
    if ([dataSource respondsToSelector:@selector(sheetRowsNumber:)])
        ret = [dataSource sheetRowsNumber:self];
    return ret;
}

- (NSUInteger)colsNumber {
    NSUInteger ret = 0;
    if ([dataSource respondsToSelector:@selector(sheetColsNumber:)])
        ret = [dataSource sheetColsNumber:self];
    return ret;
}

@end

@interface UISpreadSheet (hidden)

- (void)refreshSelected;

@end

@implementation UISpreadSheet (hidden)

- (void)refreshSelected {
    [d_ptr.cells refreshSelected];
}

@end

@implementation UISpreadSheet (wrapper)

- (NSUInteger)headerTopNumber {
    NSUInteger ret = 0;
    if ([dataSource respondsToSelector:@selector(sheetHeadersNumber:dir:)])
        ret = [dataSource sheetHeadersNumber:self dir:NgDirectionTop];
    return ret;
}

- (NSUInteger)headerBottomNumber {
    NSUInteger ret = 0;
    if ([dataSource respondsToSelector:@selector(sheetHeadersNumber:dir:)])
        ret = [dataSource sheetHeadersNumber:self dir:NgDirectionBottom];
    return ret;
}

- (NSUInteger)headerLeftNumber {
    NSUInteger ret = 0;
    if ([dataSource respondsToSelector:@selector(sheetHeadersNumber:dir:)])
        ret = [dataSource sheetHeadersNumber:self dir:NgDirectionLeft];
    return ret;
}

- (NSUInteger)headerRightNumber {
    NSUInteger ret = 0;
    if ([dataSource respondsToSelector:@selector(sheetHeadersNumber:dir:)])
        ret = [dataSource sheetHeadersNumber:self dir:NgDirectionRight];
    return ret;
}

- (real)rowHeight:(NSUInteger)row {
    real ret = self.rowHeight;
    if ([delegate respondsToSelector:@selector(sheetRowHeight:row:)])
        ret = [delegate sheetRowHeight:self row:row];
    return ret;
}

- (real)colWidth:(NSUInteger)col {
    real ret = self.colWidth;
    if ([delegate respondsToSelector:@selector(sheetColWidth:col:)])
        ret = [delegate sheetColWidth:self col:col];
    return ret;
}

- (NgLineStyle*)rowLineStyle:(NSUInteger)row {
    NgLineStyle *ret = self.rowLineStyle;
    if ([delegate respondsToSelector:@selector(sheetRowLineStyle:row:)])
        ret = [delegate sheetRowLineStyle:self row:row];
    return ret;
}

- (NgLineStyle*)colLineStyle:(NSUInteger)col {
    NgLineStyle *ret = self.colLineStyle;
    if ([delegate respondsToSelector:@selector(sheetColLineStyle:col:)])
        ret = [delegate sheetColLineStyle:self col:col];
    return ret;
}

- (NSString*)cellText:(NSUInteger)row col:(NSUInteger)col {
    NSString *ret = nil;
    if ([delegate respondsToSelector:@selector(sheetTextString:row:col:)])
        ret = [delegate sheetTextString:self row:row col:col];
    return ret;
}

- (NgTextStyle*)cellTextStyle:(NSUInteger)row col:(NSUInteger)col {
    NgTextStyle *ret = self.textStyle;
    if ([delegate respondsToSelector:@selector(sheetTextStyle:row:col:)])
        ret = [delegate sheetTextStyle:self row:row col:col];
    return ret;
}

- (NgFill*)cellFill:(NSUInteger)row col:(NSUInteger)col {
    NgFill *ret = self.cellFill;
    if ([delegate respondsToSelector:@selector(sheetFill:row:col:)])
        ret = [delegate sheetFill:self row:row col:col];
    return ret;
}

@end

@implementation UISpreadSheet (reload)

- (void)reloadAll {
    [self reloadData];
    [self relayoutData];
}

- (void)reloadData {    
    NSUInteger const sz_rows_full = self.rowsNumber;
    NSUInteger const sz_cols_full = self.colsNumber;
    NSUInteger sz_header_left = self.headerLeftNumber, sz_header_right = self.headerRightNumber, sz_header_top = self.headerTopNumber, sz_header_bottom = self.headerBottomNumber;
    NSUInteger const sz_rows = sz_rows_full - sz_header_top - sz_header_bottom;
    NSUInteger const sz_cols = sz_cols_full - sz_header_left - sz_header_right;
        
    NSCellLine *hline_prev = [[NSCellLine alloc] init];
    [d_ptr.hlines addObject:hline_prev];
    [hline_prev release];
    NSCellLine *vline_prev = [[NSCellLine alloc] init];
    [d_ptr.vlines addObject:vline_prev];
    [vline_prev release];
    
    for (uint c = 0; c < sz_cols_full; ++c) {
        NSCellLine *vline = [[NSCellLine alloc] init];
        vline_prev.nextLine = vline;
        vline.prevLine = vline_prev;
        vline.npos = vline.prevLine.npos + 1;
        vline.pos = [self colWidth:c];
        
        [d_ptr.vlines addObject:vline];
        [vline release];
        vline_prev = vline;
    }
    
    for (uint r = 0; r < sz_rows_full; ++r) {        
        // create a row.
        UISpreadSheetRow *row = nil;
        if ([delegate respondsToSelector:@selector(sheetRow:row:)])
            row = [[delegate sheetRow:self row:r] retain];
        if (row == nil)
            row = [[UISpreadSheetRow alloc] initWithCapacity:sz_cols_full];
        
        // set row.
        row.parentSheet = self;
        
        NSCellLine *hline = [[NSCellLine alloc] init];                        
        hline_prev.nextLine = hline;
        hline.prevLine = hline_prev;
        hline.npos = hline_prev.npos + 1;
        hline.pos = [self rowHeight:r];
        hline.style = [self rowLineStyle:r];
        
        row.lineTop = hline_prev;
        row.lineBottom = hline_prev.nextLine;
        
        for (uint c = 0; c < sz_cols_full; ++c) {
            // create a cell.
            UISpreadSheetCell *cell = nil;            
            if ([delegate respondsToSelector:@selector(sheetCell:row:col:)])
                cell = [[delegate sheetCell:self row:r col:c] retain];
            if (cell == nil)
                cell = [[UISpreadSheetCell alloc] init];
            
            // set cell.
            if (cell.text == nil)
                cell.text = [self cellText:r col:c];
            if (cell.textStyle == nil)
                cell.textStyle = [self cellTextStyle:r col:c];
            if (cell.cellFill == nil)
                cell.cellFill = [self cellFill:r col:c];
            
            cell.lineTop = hline_prev;
            cell.lineBottom = cell.lineTop.nextLine;
            cell.lineLeft = [d_ptr.vlines objectAtIndex:c];
            cell.lineRight = cell.lineLeft.nextLine;
            
            if ([delegate respondsToSelector:@selector(sheetInit:cell:)])
                [delegate sheetInit:self cell:cell];
            
            [row addObject:cell];
            
            [cell release];
        }
        
        if ([delegate respondsToSelector:@selector(sheetInit:row:)])
            [delegate sheetInit:self row:row];
        
        [d_ptr.rows addObject:row];
        [d_ptr.hlines addObject:hline];
        [row release];
        [hline release];
        hline_prev = hline;
    }
        
    UISpreadSheetCellMatrix *cells = d_ptr.cells;
    cells.rowRange = NSMakeRange(sz_header_top, sz_rows);
    cells.colRange = NSMakeRange(sz_header_left, sz_cols);
    
    UISpreadSheetHeaderVec *header_left = d_ptr.header_left;
    header_left.rowRange = NSMakeRange(sz_header_top, sz_rows);
    header_left.colRange = NSMakeRange(0, sz_header_left);
    
    UISpreadSheetHeaderVec *header_right = d_ptr.header_right;
    header_right.rowRange = NSMakeRange(sz_header_top, sz_rows);
    header_right.colRange = NSMakeRange(sz_header_left + sz_cols, sz_header_right);
    
    UISpreadSheetHeaderHov *header_top = d_ptr.header_top;
    header_top.rowRange = NSMakeRange(0, sz_header_top);
    header_top.colRange = NSMakeRange(sz_header_left, sz_cols);
    
    UISpreadSheetHeaderHov *header_bottom = d_ptr.header_bottom;
    header_bottom.rowRange = NSMakeRange(sz_header_top + sz_rows, sz_header_bottom);
    header_bottom.colRange = NSMakeRange(sz_header_left, sz_cols);
    
    UISpreadSheetCorner *corner_lt = d_ptr.corner_lt;
    corner_lt.rowRange = NSMakeRange(0, sz_header_top);
    corner_lt.colRange = NSMakeRange(0, sz_header_left);
    
    UISpreadSheetCorner *corner_rt = d_ptr.corner_rt;
    corner_rt.rowRange = NSMakeRange(0, sz_header_top);
    corner_rt.colRange = NSMakeRange(sz_header_left + sz_cols, sz_header_right);
    
    UISpreadSheetCorner *corner_lb = d_ptr.corner_lb;
    corner_lb.rowRange = NSMakeRange(sz_header_top + sz_rows, sz_header_bottom);
    corner_lb.colRange = NSMakeRange(0, sz_header_left);
    
    UISpreadSheetCorner *corner_rb = d_ptr.corner_rb;
    corner_rb.rowRange = NSMakeRange(sz_header_top + sz_rows, sz_header_bottom);
    corner_rb.colRange = NSMakeRange(sz_header_left + sz_cols, sz_header_right);
    
    if ([delegate respondsToSelector:@selector(sheetInit:)])
        [delegate sheetInit:self];
}

- (void)relayoutData {     
    //uint sz_vlines = [d_ptr.vlines count];
    //uint sz_hlines = [d_ptr.hlines count];
    //if (!sz_vlines || !sz_hlines)
    //    return;
    
    CGRect const rc = self.bounds;        
    
    CGRect rc_corner_lt = CGRectMakePt(rc.origin);
    rc_corner_lt.size.width = [d_ptr.corner_lt fullWidth];
    rc_corner_lt.size.height = [d_ptr.corner_lt fullHeight];
    d_ptr.corner_lt.frame = rc_corner_lt;
    
    CGRect rc_corner_rt = CGRectMakeSz(CGSizeMake([d_ptr.corner_rt fullWidth], [d_ptr.corner_rt fullHeight]));
    rc_corner_rt.origin.x = rc.origin.x + rc.size.width - rc_corner_rt.size.width;
    rc_corner_rt.origin.y = rc.origin.y;
    d_ptr.corner_rt.frame = rc_corner_rt;
    
    CGRect rc_corner_lb = CGRectMakeSz(CGSizeMake([d_ptr.corner_lb fullWidth], [d_ptr.corner_lb fullHeight]));
    rc_corner_lb.origin.x = rc.origin.x;
    rc_corner_lb.origin.y = rc.origin.y + rc.size.height - rc_corner_lb.size.height;
    d_ptr.corner_lb.frame = rc_corner_lb;
    
    CGRect rc_corner_rb = CGRectMakeSz(CGSizeMake([d_ptr.corner_rb fullWidth], [d_ptr.corner_rb fullHeight]));
    rc_corner_rb.origin.x = rc.origin.x + rc.size.width - rc_corner_rb.size.width;
    rc_corner_rb.origin.y = rc.origin.y + rc.size.height - rc_corner_rb.size.height;
    d_ptr.corner_rb.frame = rc_corner_rb;
    
    CGRect rc_header_left = CGRectMakePt(CGRectLeftBottom(&rc_corner_lt));
    rc_header_left.size.width = rc_corner_lt.size.width;
    rc_header_left.size.height = rc_corner_lb.origin.y - rc_header_left.origin.y;
    d_ptr.header_left.frame = rc_header_left;
    
    CGRect rc_header_top = CGRectMakePt(CGRectRightTop(&rc_corner_lt));
    rc_header_top.size.width = rc_corner_rt.origin.x - rc_header_top.origin.x;
    rc_header_top.size.height = rc_corner_lt.size.height;
    d_ptr.header_top.frame = rc_header_top;
    
    CGRect rc_header_right = CGRectMakePt(CGRectLeftBottom(&rc_corner_rt));
    rc_header_right.size.width = rc_corner_rt.size.width;
    rc_header_right.size.height = rc_corner_rb.origin.y - rc_header_right.origin.y;
    d_ptr.header_right.frame = rc_header_right;
    
    CGRect rc_header_bottom = CGRectMakePt(CGRectRightTop(&rc_corner_lb));
    rc_header_bottom.size.width = rc_corner_rb.origin.x - rc_header_bottom.origin.x;
    rc_header_bottom.size.height = rc_corner_rb.size.height;
    d_ptr.header_bottom.frame = rc_header_bottom;
    
    CGRect rc_cells = CGRectMakePt(CGRectRightBottom(&rc_corner_lt));
    rc_cells.size.width = rc_corner_rt.origin.x - rc_corner_lt.origin.x - rc_corner_lt.size.width;
    rc_cells.size.height = rc_corner_lb.origin.y - rc_corner_lt.origin.y - rc_corner_lt.size.height;
    d_ptr.cells.frame = rc_cells;
        
    BOOL stretchCol = (stretchColForFit && d_ptr.cells.colRange.length) || stretchColForFitForce;
    BOOL stretchRow = (stretchRowForFit && d_ptr.cells.rowRange.length) || stretchRowForFitForce;
    if (stretchCol || stretchRow) {
        CGSize const sz_old = [d_ptr.cells fullSize];
        if (stretchCol) {            
            if (sz_old.width < d_ptr.cells.frame.size.width || stretchColForFitForce) {
                NSCellLine *beginCol = [self colLineAt:d_ptr.cells.colRange.location + 1];
                NSCellLine *endCol = [self colLineAt:d_ptr.cells.colRange.location + d_ptr.cells.colRange.length + 1];
                for (NSCellLine *line = beginCol; line != endCol; line = line.nextLine) {
                    line.pos = line.pos / sz_old.width * d_ptr.cells.frame.size.width;
                }
            }
        }
        if (stretchRow ) {
            if (sz_old.height < d_ptr.cells.frame.size.height || stretchRowForFitForce) {
                NSCellLine *beginRow = [self rowLineAt:d_ptr.cells.rowRange.location + 1];
                NSCellLine *endRow = [self rowLineAt:d_ptr.cells.rowRange.location + d_ptr.cells.rowRange.length + 1];
                for (NSCellLine *line = beginRow; line != endRow; line = line.nextLine) {
                    line.pos = line.pos / sz_old.height * d_ptr.cells.frame.size.height;
                }
            }
        }
    }
    
    d_ptr.header_top.contentSize = [d_ptr.header_top fullSize];
    d_ptr.header_bottom.contentSize = [d_ptr.header_bottom fullSize];
    d_ptr.header_left.contentSize = [d_ptr.header_left fullSize];
    d_ptr.header_right.contentSize = [d_ptr.header_right fullSize];
    d_ptr.cells.contentSize = [d_ptr.cells fullSize];
    d_ptr.corner_lb.contentSize = [d_ptr.corner_lb fullSize];
    d_ptr.corner_lt.contentSize = [d_ptr.corner_lt fullSize];
    d_ptr.corner_rb.contentSize = [d_ptr.corner_rb fullSize];
    d_ptr.corner_rt.contentSize = [d_ptr.corner_rt fullSize];    
    
    // update selected.
    [self refreshSelected];
}

- (void)reloadHovLineStyles {
    uint sz_hlines = [d_ptr.hlines count];
    if (!sz_hlines)
        return;
    
    for (uint h = 0; h < sz_hlines; ++h) {
        NSCellLine *line = [d_ptr.hlines objectAtIndex:h];
        line.pos = [self rowHeight:h];
        line.style = [self rowLineStyle:h];
    }
}

- (void)reloadVecLineStyles {
    uint sz_vlines = [d_ptr.vlines count];
    if (!sz_vlines)
        return;
    
    for (uint v = 0; v < sz_vlines; ++v) {
        NSCellLine *line = [d_ptr.vlines objectAtIndex:v];
        line.pos = [self colWidth:v];
        line.style = [self colLineStyle:v];
    }
}

- (void)reloadLineStyles {
    [self reloadHovLineStyles];
    [self reloadVecLineStyles];
}

- (void)reloadHovLinePos {
    uint sz_hlines = [d_ptr.hlines count];
    if (!sz_hlines)
        return;
    
    for (uint h = 0; h < sz_hlines; ++h) {
        NSCellLine *line = [d_ptr.hlines objectAtIndex:h];
        line.pos = [self rowHeight:h];
    }
}

- (void)reloadVecLinePos {
    uint sz_vlines = [d_ptr.vlines count];
    if (!sz_vlines)
        return;
    
    for (uint v = 0; v < sz_vlines; ++v) {
        NSCellLine *line = [d_ptr.vlines objectAtIndex:v];
        line.pos = [self colWidth:v];
    }
}

- (void)reloadLinePos {
    [self reloadHovLinePos];
    [self reloadVecLinePos];
}

- (void)reloadStyles {        
    uint const sz_cols_full = [d_ptr.vlines count];
    uint const sz_rows_full = [d_ptr.hlines count];
    for (uint c = 1; c < sz_cols_full; ++c) {
        NSCellLine *vline = [d_ptr.vlines objectAtIndex:c];
        uint cid = c - 1;
        vline.pos = [self colWidth:cid];
        vline.style = [self colLineStyle:cid];
    }
    
    for (uint r = 1; r < sz_rows_full; ++r) {
        uint rid = r - 1;
        NSCellLine *hline = [d_ptr.hlines objectAtIndex:r];
        hline.pos = [self rowHeight:rid];
        hline.style = [self rowLineStyle:rid];
                
        UISpreadSheetRow *row = [d_ptr.rows objectAtIndex:rid];
        
        for (uint c = 0; c < sz_cols_full - 1; ++c) {
            UISpreadSheetCell *cell = [row.cells objectAtIndex:c];
            
            //cell.text = [self cellText:rid col:c];
            cell.textStyle = [self cellTextStyle:rid col:c];
            cell.cellFill = [self cellFill:rid col:c];
        }
    }
        
    [self relayoutData];
}

- (void)updateGeometry {        
    uint const sz_cols_full = [d_ptr.vlines count];
    uint const sz_rows_full = [d_ptr.hlines count];
    for (uint c = 1; c < sz_cols_full; ++c) {
        NSCellLine *vline = [d_ptr.vlines objectAtIndex:c];
        vline.pos = [self colWidth:c - 1];
    }
    
    for (uint r = 1; r < sz_rows_full; ++r) {
        uint rid = r - 1;
        NSCellLine *hline = [d_ptr.hlines objectAtIndex:r];
        hline.pos = [self rowHeight:rid];
    }
    
    [self relayoutData];
}

@end

@interface UISpreadSheet (event)

@end

@implementation UISpreadSheet (event)

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    d_ptr.ptTouch = [[touches anyObject] locationInView:self];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [[touches anyObject] locationInView:self];        
    d_ptr.ptTouch = pt;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    PASS;
}

@end

@implementation UISpreadSheet (action)

- (void)highlightCell:(UISpreadSheetCell *)cell val:(BOOL)val {
    [d_ptr.header_top highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeNone];
    [d_ptr.header_bottom highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeNone];
    [d_ptr.header_left highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeNone];
    [d_ptr.header_right highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeNone];
}

- (void)highlightRow:(UISpreadSheetCell*)cell val:(BOOL)val {
    [d_ptr.header_left highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeNone];
    [d_ptr.header_right highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeNone];  
    [d_ptr.cells highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeHov];
}

- (void)highlightCol:(UISpreadSheetCell*)cell val:(BOOL)val {
    [d_ptr.header_top highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeNone];
    [d_ptr.header_bottom highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeNone];
    [d_ptr.cells highlightCell:cell val:val mode:UISpreadSheetCellMatrixHighlightModeVec];
}

@end

@implementation UISpreadSheet (query)

- (void)walkCell:(SEL)sel obj:(NSObject*)obj ctx:(id)ctx {
    for (UISpreadSheetRow *row in d_ptr.rows) {
        for (UISpreadSheetCell *cell in row.cells) {
            if (![obj performSelector:sel withObject:cell withObject:ctx])
                break;
        }
    }
}

- (void)walkLineHov:(SEL)sel obj:(NSObject*)obj ctx:(id)ctx {
    uint const count = [d_ptr.hlines count];
    for (uint i = 1; i < count; ++i) {
        NSCellLine *line = [d_ptr.hlines objectAtIndex:i];
        if (![obj performSelector:sel withObject:line withObject:ctx])
            break;
    }
}

- (void)walkLineVec:(SEL)sel obj:(NSObject*)obj ctx:(id)ctx {
    uint const count = [d_ptr.vlines count];
    for (uint i = 1; i < count; ++i) {
        NSCellLine *line = [d_ptr.vlines objectAtIndex:i];
        if (![obj performSelector:sel withObject:line withObject:ctx])
            break;
    }
}

@end

@implementation UISpreadSheet (children)

- (UISpreadSheetHeaderVec*)headerCellsLeft {
    return d_ptr.header_left;
}

- (UISpreadSheetHeaderVec*)headerCellsRight {
    return d_ptr.header_right;
}

- (UISpreadSheetHeaderHov*)headerCellsTop {
    return d_ptr.header_top;
}

- (UISpreadSheetHeaderHov*)headerCellsBottom {
    return d_ptr.header_bottom;
}

- (UISpreadSheetCorner*)cornerCellsLeftTop {
    return d_ptr.corner_lt;
}

- (UISpreadSheetCorner*)cornerCellsRightTop {
    return d_ptr.corner_rt;
}

- (UISpreadSheetCorner*)cornerCellsLeftBottom {
    return d_ptr.corner_lb;
}

- (UISpreadSheetCorner*)cornerCellsRightBottom {
    return d_ptr.corner_rb;
}

- (UISpreadSheetCellMatrix*)Cells {
    return d_ptr.cells;
}

@end

@implementation _cxx_spreadsheet

- (NSUInteger)sheetHeadersNumber:(UISpreadSheet*)sheet dir:(NgDirection)dir {
    NSUInteger ret = 0;
    switch (dir)
    {
        case NgDirectionLeft: ret = _sheet->fixheader_left; break;
        case NgDirectionRight: ret = _sheet->fixheader_right; break;
        case NgDirectionTop: ret = _sheet->fixheader_top; break;
        case NgDirectionBottom: ret = _sheet->fixheader_bottom; break;
    }
    return ret;
}

- (NSUInteger)sheetRowsNumber:(UISpreadSheet*)sheet {
    return _sheet->rows;
}

- (NSUInteger)sheetColsNumber:(UISpreadSheet*)sheet {
    return _sheet->cols;
}

- (real)sheetRowHeight:(UISpreadSheet*)sheet row:(NSUInteger)row {
    return _sheet->row_height;
}

- (real)sheetColWidth:(UISpreadSheet*)sheet col:(NSUInteger)col {
    return _sheet->col_width;
}

- (UISpreadSheetCell*)sheetCell:(UISpreadSheet*)sheet row:(NSUInteger)row col:(NSUInteger)col {
    return _sheet->row(row).cell(col);
}

- (UISpreadSheetRow*)sheetRow:(UISpreadSheet*)sheet row:(NSUInteger)row {
    return _sheet->row(row);
}

- (void)clear {
    [super clear];
    _sheet->_clear();
}

- (NgLineStyle*)sheetRowLineStyle:(UISpreadSheet*)sheet row:(NSUInteger)row {
    return _sheet->linestyle_row;
}

- (NgLineStyle*)sheetColLineStyle:(UISpreadSheet*)sheet col:(NSUInteger)col {
    return _sheet->linestyle_col;
}

@end

NNT_END_OBJC