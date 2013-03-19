
# ifndef __WSI_CGSHAPE_2F56484DE8A74F2791022B61CEB4BAB2_H_INCLUDED
# define __WSI_CGSHAPE_2F56484DE8A74F2791022B61CEB4BAB2_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WCGShape : NSObject {
    CGContextRef _ctx;
}

@property (nonatomic, assign) CGContextRef context;

- (void)openPath:(CGRect)rect;
- (void)closePath:(CGRect)rect;

- (void)addTopEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource;
- (void)addRightEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource;
- (void)addBottomEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource;
- (void)addLeftEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource;

- (void)addToPath:(CGRect)rect;

- (void)addInverseToPath:(CGRect)rect;

- (UIEdgeInsets)insetsForSize:(CGSize)size;

@end

WSI_END_HEADER_OBJC

# endif