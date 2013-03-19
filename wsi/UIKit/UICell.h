
# ifndef __WSI_UIKIT_UICELL_A79090DA408F434BB2C7302B2D501B27_H_INCLUDED
# define __WSI_UIKIT_UICELL_A79090DA408F434BB2C7302B2D501B27_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGLineStyle);
WSIDECL_EXTERN_CLASS(WCGTextStyle);
WSIDECL_EXTERN_CLASS(WCGFill);

@protocol NSCell <NSObject>

@end

@protocol NSCellLine <NSObject>

@end

@interface NSCellLine : WSIObject <NSCellLine> {
    
    NSCellLine *nextLine;
    NSCellLine *prevLine;
    
    NSUInteger npos; //! index of lines.
    real pos; //! position(offset from pre line) of self.
    real absolutePos; //! position from first line.
    
    WCGLineStyle *style;
}

@property (nonatomic, assign) NSCellLine *nextLine, *prevLine;
@property (nonatomic, assign) NSUInteger npos;
@property (nonatomic, assign) real pos;
@property (nonatomic, retain) WCGLineStyle *style;
@property (nonatomic, readonly, getter = getAbsolutePos) real absolutePos;

- (real)getAbsolutePos;
- (BOOL)distancePrev:(NSCellLine const*)line val:(real*)val;
- (real)distancePrev:(NSCellLine const*)line;
- (BOOL)distanceNext:(NSCellLine const*)line val:(real*)val;
- (real)distanceNext:(NSCellLine const*)line;

@end

@interface NSCell : WSIObject <NSCell> {
    
    NSString *text;
    WCGTextStyle *textStyle;
        
    NSCellLine *lineLeft, *lineRight, *lineTop, *lineBottom;
    
    real width, height;
    
    NSUInteger row, col;
}

@property (nonatomic, copy) NSString *text;
@property (nonatomic, retain) WCGTextStyle *textStyle;
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
    WCGFill *cellFill;
    
}

@property (nonatomic, readonly) NSCell *cell;
@property (nonatomic, retain) WCGFill *cellFill;

@end

WSI_END_HEADER_OBJC

# endif