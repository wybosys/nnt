
# import "Core.h"
# import "UISpreadSheetHeader.h"
# import "UISpreadSheetCell.h"

NNT_BEGIN_OBJC

@implementation UISpreadSheetHeader

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)transHighlight:(NSArray *)old sel:(NSArray *)sel {
    PASS;
}

@end

@implementation UISpreadSheetHeaderHov

- (void)highlightCell:(UISpreadSheetCell *)cell val:(BOOL)val mode:(UISpreadSheetCellMatrixHighlightMode)mode {
    if (self.rowRange.length == 0)
        return;
    if (!NSLocationInRange(cell.lineLeft.npos, self.colRange))
        return;
    
    UISpreadSheetCell *localcell = [self.sheet cellAt:self.rowRange.location col:cell.lineLeft.npos];
    [super highlightCell:localcell val:val mode:UISpreadSheetCellMatrixHighlightModeVec];
}

@end

@implementation UISpreadSheetHeaderVec

- (void)highlightCell:(UISpreadSheetCell *)cell val:(BOOL)val mode:(UISpreadSheetCellMatrixHighlightMode)mode {
    if (self.colRange.length == 0)
        return;
    if (!NSLocationInRange(cell.lineTop.npos, self.rowRange))
        return;
    
    UISpreadSheetCell *localcell = [self.sheet cellAt:cell.lineTop.npos col:self.colRange.location];
    [super highlightCell:localcell val:val mode:UISpreadSheetCellMatrixHighlightModeHov];
}

@end

NNT_END_OBJC