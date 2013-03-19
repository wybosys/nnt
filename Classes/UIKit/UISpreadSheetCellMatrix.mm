
# import "Core.h"
# import "UISpreadSheetCellMatrix.h"
# import "UISpreadSheet.h"
# import "UISpreadSheetCell.h"
# import "UISpreadSheetCellMatrixLayer.h"
# import <QuartzCore/QuartzCore.h>
# import "Graphic+NNT.h"

NNT_BEGIN_OBJC

@implementation UISpreadSheetRow

@synthesize cells;
@synthesize lineTop, lineBottom;
@dynamic rowHeight;
@synthesize parentSheet;

- (id)initWithCapacity:(NSUInteger)sz {
    self = [super init];
    cells = [[NSMutableArray alloc] initWithCapacity:sz];
    return self;
}

- (id)init {
    self = [super init];
    cells = [[NSMutableArray alloc] init];
    return self;
}

- (void)dealloc {
    zero_release(cells);
    
    [super dealloc];
}

- (void)addObject:(UISpreadSheetCell*)obj {
    [cells addObject:obj];
    obj.parentRow = self;
}

- (UISpreadSheetCell*)objectAtIndex:(NSUInteger)idx {
    return [cells objectAtIndex:idx];
}

- (NSUInteger)count {
    return [cells count];
}

- (real)getRowHeight {
    return [lineBottom distancePrev:lineTop];
}

- (void)walk:(void (^)(UISpreadSheetCell *))func {
    for (UISpreadSheetCell *cell in cells) {
        func(cell);
    }
}

@end

@interface UISpreadSheetCellMatrixAssorLayer : CALayer {
    
}

@end

@implementation UISpreadSheetCellMatrixAssorLayer

- (void)drawInContext:(CGContextRef)ctx {
    PASS;
}

@end

@interface UISpreadSheetCellMatrix (hidden)

- (void)setSelected:(NSArray*)arr evt:(BOOL)evt;

@end

@implementation UISpreadSheetCellMatrix

@synthesize rowRange, colRange;
@synthesize sheet;
@synthesize layerCells, layerAssor;
@synthesize type;
@synthesize selectedCells;
@synthesize highlightMode;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.bounces = NO;
    self.bouncesZoom = NO;
    self.userInteractionEnabled = YES;
        
    rowRange = NSMakeRange(0, 0);
    colRange = NSMakeRange(0, 0);
    
    layerCells = [[UISpreadSheetCellMatrixLayer alloc] initWithLayer:self.layer];
    ((UISpreadSheetCellMatrixLayer*)layerCells).cells = self;
    [self.layer addSublayer:layerCells];
    
    layerAssor = [[UISpreadSheetCellMatrixAssorLayer alloc] initWithLayer:self.layer];
    [self.layer addSublayer:layerAssor];
    
    highlightMode = UISpreadSheetCellMatrixHighlightModeAll;
    
    return self;
}

- (void)dealloc {
    zero_release(selectedCells);
    zero_release(layerCells);
    zero_release(layerAssor);
    
    [super dealloc];
}

- (void)setContentSize:(CGSize)contentSize {
    [super setContentSize:contentSize];
    
    layerCells.frame = CGRectMakeSz(contentSize);
    [layerCells setNeedsDisplay];
    
    layerAssor.frame = CGRectMakeSz(contentSize);
}

- (UISpreadSheetCell*)hitTestForCell:(UITouch*)touch {
    UISpreadSheetCell *ret = nil;
    CGPoint pt = [touch locationInView:self];
    real height = 0;
    for (uint r = 0; r < rowRange.length; ++r) {
        UISpreadSheetRow const* tgt_row = [sheet rowAt:r + rowRange.location];
        height += tgt_row.rowHeight;
        if (height > pt.y) {
            real width = 0;
            for (uint c = 0; c < colRange.length; ++c) {
                UISpreadSheetCell *cell = [tgt_row objectAtIndex:c + colRange.location];
                width += cell.width;
                if (width > pt.x) {
                    ret = cell;
                    break;
                }
            }
            break;
        }
    }
    return ret;
}

- (UISpreadSheetCell*)cellAt:(NSUInteger)row col:(NSUInteger)col {
    UISpreadSheetRow *tgt_row = [sheet rowAt:row + rowRange.location];
    UISpreadSheetCell *tgt_cell = [tgt_row objectAtIndex:col + colRange.location];
    return tgt_cell;
}

- (BOOL)containCell:(const UISpreadSheetCell *)cell {
    return NSLocationInRange(cell.row, self.rowRange) && NSLocationInRange(cell.col, self.colRange);
}

- (void)clearSelected:(BOOL)evt {
    NSArray *arr = [NSArray new];
    [self setSelected:arr evt:evt];
    [arr release];
}

- (void)refreshSelected {
    if ([self.selectedCells count] == 0)
        return;
    
    id sheet_selected = [sheet.selectedCells retain];
    NSArray *arr = [self.selectedCells retain];
    [self clearSelected:NO];
    [self setSelected:arr evt:NO];
    [arr release];
    sheet.selectedCells = sheet_selected;
    [sheet_selected release];
}

- (void)clear {
    rowRange = NSMakeRange(0, 0);
    colRange = NSMakeRange(0, 0);
}

@end

@implementation UISpreadSheetCellMatrix (geometry)

- (real)fullWidth {
    NSCellLine const* begin = [sheet colLineAt:colRange.location];
    NSCellLine const* end = [sheet colLineAt:colRange.location + colRange.length];
    return [end distancePrev:begin];
}

- (real)fullHeight {
    NSCellLine const* begin = [sheet rowLineAt:rowRange.location];
    NSCellLine const* end = [sheet rowLineAt:rowRange.location + rowRange.length];
    return [end distancePrev:begin];
}

- (CGSize)fullSize {
    return CGSizeMake([self fullWidth], [self fullHeight]);
}

@end

@implementation UISpreadSheetCellMatrix (interactive)

- (void)transHighlight:(NSArray *)old sel:(NSArray *)sel {
    if (highlightMode == UISpreadSheetCellMatrixHighlightModeNone)
        return;
    
    // turn off
    for (id each in old) {
        if (![sel containsObject:each]) {
            [self highlightCell:each val:NO mode:UISpreadSheetCellMatrixHighlightModeAll];
            [sheet highlightCell:each val:NO];
        }
    }
    // turn on
    for (id each in sel) {
        if (![old containsObject:each]) {
            [self highlightCell:each val:YES mode:UISpreadSheetCellMatrixHighlightModeAll];
            [sheet highlightCell:each val:YES];
        }
    }
}

- (void)highlightCell:(UISpreadSheetCell *)cell val:(BOOL)val mode:(UISpreadSheetCellMatrixHighlightMode)mode {
    UIColor* highlightColor = sheet.selHighlightColor;
    if (highlightColor == nil)
        return;
    
    if (val) {        
        NSCellLine const* beginRow = [sheet rowLineAt:rowRange.location];
        NSCellLine const* beginCol = [sheet colLineAt:colRange.location];        
        real x = [cell.lineLeft distancePrev:beginCol];
        real y = [cell.lineTop distancePrev:beginRow];
        CGRect frame = CGRectMake(x, y, cell.width, cell.height);
        
        if (MASK_CHECK(UISpreadSheetCellMatrixHighlightModeVec, mode)) {
            CALayer *barh = [[CALayer alloc] initWithLayer:self.layer];
            barh.backgroundColor = highlightColor.CGColor;
            barh.frame = CGRectMake(frame.origin.x, 0, frame.size.width, self.layerAssor.bounds.size.height);
            [self.layerAssor addSublayer:barh];
            [barh release];
            [cell attachPush:@"::base::highlight::barh" obj:barh];
        }
        
        if (MASK_CHECK(UISpreadSheetCellMatrixHighlightModeHov, mode)) {
            CALayer *barv = [[CALayer alloc] initWithLayer:self.layer];
            barv.backgroundColor = highlightColor.CGColor;
            barv.frame = CGRectMake(0, frame.origin.y, self.layerAssor.bounds.size.width, frame.size.height);
            [self.layerAssor addSublayer:barv];
            [barv release];
            [cell attachPush:@"::base::highlight::barv" obj:barv];
        }
    } else {
        CALayer *barh = (CALayer*)[cell._attach pop:@"::base::highlight::barh"];
        CALayer *barv = (CALayer*)[cell._attach pop:@"::base::highlight::barv"];        
        [barh removeFromSuperlayer];
        [barv removeFromSuperlayer];
    }
}

- (void)dehighlight:(UISpreadSheetCell*)cell {
    CALayer *barh = (CALayer*)[cell._attach pop:@"::base::highlight::barh"];
    CALayer *barv = (CALayer*)[cell._attach pop:@"::base::highlight::barv"];        
    [barh removeFromSuperlayer];
    [barv removeFromSuperlayer];
}

@end

@implementation UISpreadSheetCellMatrix (hidden)

- (void)setSelected:(NSArray*)arr evt:(BOOL)evt {
    id <UISpreadSheetDelegate> delegate = sheet.delegate;
    
    // set trans.
    [self transHighlight:selectedCells sel:arr];
    
    // replace.
    [arr retain];
    [selectedCells release];
    selectedCells = arr;
    
    // set selected.
    sheet.selectedCells = selectedCells;
    
    // event.
    if (evt && [arr count]) {
        
        [self.sheet emit:kSignalSheetTouchs result:arr];
        
        if ([delegate respondsToSelector:@selector(sheetDidTouchs:cells:matrix:)]) {
            [delegate sheetDidTouchs:sheet cells:arr matrix:self];            
        }
    }
}

@end

@interface UISpreadSheetCellMatrix (event)

@end

@implementation UISpreadSheetCellMatrix (event)

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    id <UISpreadSheetDelegate> delegate = sheet.delegate;
    NSMutableArray *arr = [[NSMutableArray alloc] init];
    
    // find cell.
    for (UITouch *touch in touches) {
        UISpreadSheetCell *cell = [self hitTestForCell:touch];
        if (cell)
            [arr addObject:cell];
    }
    
    // will touch.
    if ([arr count]) {        
        if (sheet.reselectSelectedCell == NO) {            
            BOOL same = YES;
            for (id each in arr)
            {
                if (![selectedCells containsObject:each])
                    same = NO;
            }
            
            if (same) {
                [arr release];
                return;
            }
        }
        
        if ([delegate respondsToSelector:@selector(sheetShouldTouchs:cells:matrix:)]) {
            if (![delegate sheetShouldTouchs:sheet cells:arr matrix:self]) {
                [arr release];
                return;
            }
        }        
    }    
    
    // set selected.
    [self setSelected:arr evt:YES];
    
    // free.
    [arr release];
}

@end

NNT_END_OBJC