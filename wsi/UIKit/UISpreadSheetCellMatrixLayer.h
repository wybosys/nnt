
# ifndef __WSI_UIKIT_UISPREADSHEETCELLMATRIXLAYER_1EF6A1BA6D284BE0807CFBB87C5E6B6B_H_INCLUDED
# define __WSI_UIKIT_UISPREADSHEETCELLMATRIXLAYER_1EF6A1BA6D284BE0807CFBB87C5E6B6B_H_INCLUDED

# import <QuartzCore/QuartzCore.h>

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UISpreadSheetCell);
WSIDECL_EXTERN_CLASS(UISpreadSheetCellMatrix);

@interface UISpreadSheetCellMatrixLayer : CALayer {
    
    UISpreadSheetCellMatrix *cells;
    NSMutableArray *pendingUpdateCells;
    
}

@property (nonatomic, assign) UISpreadSheetCellMatrix *cells;
@property (nonatomic, assign) NSMutableArray *pendingUpdateCells;

- (void)drawAll:(CGContextRef)ctx;
- (void)drawCell:(CGContextRef)ctx cell:(UISpreadSheetCell*)cell;

@end

WSI_END_HEADER_OBJC

# endif