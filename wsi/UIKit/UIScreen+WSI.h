
# ifndef __WSI_OBJC_UISCREEN_74C522FB215A484BB3ADE2BE2E596F41_H_INCLUDED
# define __WSI_OBJC_UISCREEN_74C522FB215A484BB3ADE2BE2E596F41_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIScreen (WSI)

//! convert current view size to program space.
- (CGSize)currentViewSize;

//! convert current view size to program space.
+ (CGRect)convertCurrentRect:(CGRect)rect;
+ (CGSize)convertCurrentSize:(CGSize)size;
+ (CGPoint)convertCurrentPoint:(CGPoint)pt;
+ (int)convertCurrentOffset:(int)offset;

//! get current orientation.
+ (UIInterfaceOrientation)orientation;

//! convert point of font from designer to device.
+ (real)pointD2D:(real)val;
+ (real)point2Normal:(real)val;
+ (real)point2Retina:(real)val;

//! if is retina.
+ (BOOL)isRetina;

@end

# define PPI_NORMAL_DEVICE 163
# define PPI_RETINA_DEVICE 326

WSIDECL_CATEGORY(UIScreen, WSI);

@interface UIScreenImage : NSObject {
    NSString* _name;
    UIInterfaceOrientation _orientation;
}

@property (nonatomic, copy) NSString* name;
@property (nonatomic, assign) UIInterfaceOrientation orientation;

@end

WSI_END_HEADER_OBJC

# endif