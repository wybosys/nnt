
# ifndef __NNT_UIKIT_UICELL_A79090DA408F434BB2C7302B2D501B27_H_INCLUDED
# define __NNT_UIKIT_UICELL_A79090DA408F434BB2C7302B2D501B27_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgLineStyle);
NNTDECL_EXTERN_CLASS(NgTextStyle);
NNTDECL_EXTERN_CLASS(NgFill);

@protocol NSCell <NSObject>

@end

@protocol NSCellLine <NSObject>

@end

@interface NSCellLine : NNTObject <NSCellLine> {
    
    NSCellLine *nextLine;
    NSCellLine *prevLine;
    
    NSUInteger npos; //! index of lines.
    real pos; //! position(offset from pre line) of self.
    real absolutePos; //! position from first line.
    
    NgLineStyle *style;
}

@property (nonatomic, assign) NSCellLine *nextLine, *prevLine;
@property (nonatomic, assign) NSUInteger npos;
@property (nonatomic, assign) real pos;
@property (nonatomic, retain) NgLineStyle *style;
@property (nonatomic, readonly, getter = getAbsolutePos) real absolutePos;

- (real)getAbsolutePos;
- (BOOL)distancePrev:(NSCellLine const*)line val:(real*)val;
- (real)distancePrev:(NSCellLine const*)line;
- (BOOL)distanceNext:(NSCellLine const*)line val:(real*)val;
- (real)distanceNext:(NSCellLine const*)line;

@end

@interface NSCell : NNTObject <NSCell> {
    
    NSString *text;
    NgTextStyle *textStyle;
        
    NSCellLine *lineLeft, *lineRight, *lineTop, *lineBottom;
    
    real width, height;
    
    NSUInteger row, col;
}

@property (nonatomic, copy) NSString *text;
@property (nonatomic, retain) NgTextStyle *textStyle;
@property (nonatomic, assign) NSCellLine *lineLeft, *lineRight, *lineTop, *lineBottom;
@property (nonatomic, readonly, getter = getWidth) real width;
@property (nonatomic, readonly, getter = getHeight) real height;
@property (nonatomic, readonly, getter = getRow) NSUInteger row;
@property (nonatomic, readonly, getter = getCol) NSUInteger col;

- (real)getWidth;
- (real)getHeight;
- (NSUInteger)getRow;
- (NSUInteger)getCol;
- (NSString*)getText;

@end

@interface UICell : UIView {
    
    NSCell *cell;
    NgFill *cellFill;
    
}

@property (nonatomic, readonly) NSCell *cell;
@property (nonatomic, retain) NgFill *cellFill;

@end

NNT_END_HEADER_OBJC

# endif