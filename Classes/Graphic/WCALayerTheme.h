
# ifndef __NNT_WCA_LAYERTHEME_79319518F18549639241FC25F0FA9F71_H_INCLUDED
# define __NNT_WCA_LAYERTHEME_79319518F18549639241FC25F0FA9F71_H_INCLUDED

# import "WCALayer.h"

NNT_BEGIN_HEADER_OBJC

@protocol WCALayerTheme <NSObject>

//! set in layer.
- (void)setInLayer:(CALayer*)layer;

# ifdef NNT_TARGET_IOS

//! create a image by layer.
- (UIImage*)createImage:(CGSize)size;

# endif

@end

@interface WCALayerTheme : NNTObject <WCALayerTheme> 
{
    
    CGColorRef background;
    
}

@property (nonatomic) CGColorRef background;

@end

NNT_END_HEADER_OBJC

# endif