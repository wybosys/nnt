
# ifndef __NNT_WCG_WCGCOLORSPACE_E13B52F1A0194D56850347A77D13BB6B_H_INCLUDED
# define __NNT_WCG_WCGCOLORSPACE_E13B52F1A0194D56850347A77D13BB6B_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface WCGColorSpace : NSObject {
    
@private
    CGColorSpaceRef cgColorSpace;
    
}

@property (nonatomic, readonly, assign) CGColorSpaceRef cgColorSpace;

+ (WCGColorSpace *)genericRGBSpace;

- (id)initWithCGColorSpace:(CGColorSpaceRef)colorSpace;

@end


NNT_END_HEADER_OBJC

# endif