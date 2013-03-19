
# import "Core.h"
# import "UISpreadSheetCell.h"
# import "UISpreadSheetCellMatrixLayer.h"
# import "Graphic+NNT.h"

NNT_BEGIN_OBJC

@implementation UISpreadSheetCell

@synthesize cellFill;
@synthesize frame, bounds;
@synthesize layer;
@synthesize parentRow;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(cellFill);
    
    [super dealloc];
}

- (void)setFrame:(CGRect)rc {
    frame = rc;
    bounds = CGRectMakeSz(frame.size);
}

- (void)drawInContext:(CGContextRef)ctx {    
    // draw base.
    NgFill *theFill = self.cellFill;
    
    if (theFill) {
        [theFill fillRect:self.frame inContext:ctx];
    }
    
    NSString *theText = self.text;
    if (text) {
        NgTextStyle *theTs = self.textStyle;
        if (theTs) {                    
            CGContextAddTextInRect(ctx, self.frame, theText, theTs);
        }
    }
    
    // draw by delegate.
    id<UISpreadSheetDelegate> delegate = parentRow.parentSheet.delegate;
    if ([delegate respondsToSelector:@selector(sheetDrawCell:cell:context:)]) {
        [delegate sheetDrawCell:parentRow.parentSheet
                           cell:self
                        context:ctx];;
    }
}

- (void)setNeedsDisplay {
    [layer setNeedsDisplayInRect:self.frame];
}

- (void)setNeedsDisplaySelf {
    [layer.pendingUpdateCells addObject:self];
    [layer setNeedsDisplayInRect:self.frame];
}

- (void)highlightRow {
    [self.parentRow.parentSheet highlightRow:self val:YES];
}

- (void)highlightCol {
    [self.parentRow.parentSheet highlightCol:self val:YES];
}

- (void)dehighlight {
    [self.parentRow.parentSheet highlightRow:self val:NO];
    [self.parentRow.parentSheet highlightCol:self val:NO];
}

@end

@implementation _cxx_sheetcell

- (void)drawInContext:(CGContextRef)ctx {
    [super drawInContext:ctx];
    
    CGContextSaveGState(ctx);
    CGContextTranslateCTM(ctx, frame.origin.x, frame.origin.y);
    cell->draw(ctx);
    CGContextRestoreGState(ctx);        
}

- (NSString*)text {
    return cell->text().consign();
}

- (void*)object {
    return cell;
}

@end

NNT_END_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(sheet)

ns::String Cell::text() const
{
    return [this->_self getText];
}

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX
