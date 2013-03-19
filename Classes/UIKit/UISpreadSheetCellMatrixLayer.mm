
# import "Core.h"
# import "UISpreadSheetCellMatrixLayer.h"
# import "UISpreadSheetCellMatrix.h"
# import "UISpreadSheetCell.h"
# import "CoreGraphic+WSI.h"

WSI_BEGIN_OBJC

@implementation UISpreadSheetCellMatrixLayer

@synthesize cells;
@synthesize pendingUpdateCells;

- (id)initWithLayer:(id)layer {
    self = [super initWithLayer:layer];
    
    pendingUpdateCells = [NSMutableArray new];
    
    return self;
}

- (void)dealloc {
    zero_release(pendingUpdateCells);
    
    [super dealloc];
}

- (void)drawInContext:(CGContextRef)ctx {
    [super drawInContext:ctx];
    
    CGContextRef context = ctx;
    CGContextSaveGState(context);
    
    if ([pendingUpdateCells count]) {
        for (UISpreadSheetCell *cell in pendingUpdateCells) {
            [self drawCell:ctx cell:cell];
        }
        [pendingUpdateCells release];
    } else {
        [self drawAll:ctx];
    }
       
    CGContextRestoreGState(context);
}

- (void)drawAll:(CGContextRef)ctx {
    NSRange rowRange = cells.rowRange;
    NSRange colRange = cells.colRange;
    NSCellLine const* beginRow = [cells.sheet rowLineAt:rowRange.location];
    NSCellLine const* beginCol = [cells.sheet colLineAt:colRange.location];
    
    CGRect rect = self.bounds;        
    
    // draw text
    for (NSUInteger r = 0; r < rowRange.length; ++r) {
        NSUInteger row = rowRange.location + r;
        UISpreadSheetRow *tgt_row = [cells.sheet rowAt:row];
        for (NSUInteger c = 0; c < colRange.length; ++c) {
            NSUInteger col = colRange.location + c;                        
            UISpreadSheetCell* cell = [tgt_row objectAtIndex:col];
            
            if ([cell isKindOfClass:[UISpreadSheetCell class]]) {
                real x = [cell.lineLeft distancePrev:beginCol];
                real y = [cell.lineTop distancePrev:beginRow];
                cell.frame = CGRectMake(x, y, cell.width, cell.height);
                [cell drawInContext:ctx];
                cell.layer = self;               
            }
        }
    }
    
    // draw row line
    for (NSUInteger i = 0; i <= rowRange.length; ++i) {
        NSUInteger row = rowRange.location + i;
        NSCellLine *line = [cells.sheet rowLineAt:row];
        
        real pos = [line distancePrev:beginRow];
        
        if (line.style) {
            [line.style setLineStyleInContext:ctx];
            CGContextMoveToPoint(ctx, rect.origin.x, pos);
            CGContextAddLineToPoint(ctx, rect.origin.x + rect.size.width, pos);
            CGContextStrokePath(ctx);
        }
    }
    
    // draw col line
    for (NSUInteger i = 0; i <= colRange.length; ++i) {
        NSUInteger col = colRange.location + i;
        NSCellLine *line = [cells.sheet colLineAt:col];
        
        real pos = [line distancePrev:beginCol];
        
        if (line.style) {
            [line.style setLineStyleInContext:ctx];
            CGContextMoveToPoint(ctx, pos, rect.origin.y);
            CGContextAddLineToPoint(ctx, pos, rect.origin.y + rect.size.height);
            CGContextStrokePath(ctx);
        }
    }
}

- (void)drawCell:(CGContextRef)ctx cell:(UISpreadSheetCell *)cell {    
    // draw text
    real x = cell.frame.origin.x;
    real y = cell.frame.origin.y;
    real width = cell.frame.size.width;
    real height = cell.frame.size.height;

    [cell drawInContext:ctx];
    
    // draw line
    [cell.lineTop.style setLineStyleInContext:ctx];
    CGContextMoveToPoint(ctx, x, y);
    CGContextAddLineToPoint(ctx, x + width, y);
    CGContextStrokePath(ctx);
    
    [cell.lineBottom.style setLineStyleInContext:ctx];
    CGContextMoveToPoint(ctx, x, y + height);
    CGContextAddLineToPoint(ctx, x + width, y + height);
    CGContextStrokePath(ctx);
    
    [cell.lineLeft.style setLineStyleInContext:ctx];
    CGContextMoveToPoint(ctx, x, y);
    CGContextAddLineToPoint(ctx, x, y + height);
    CGContextStrokePath(ctx);
    
    [cell.lineRight.style setLineStyleInContext:ctx];
    CGContextMoveToPoint(ctx, x + width, y);
    CGContextAddLineToPoint(ctx, x + width, y + height);
    CGContextStrokePath(ctx);
}

@end


WSI_END_OBJC