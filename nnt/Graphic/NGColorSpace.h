
# ifndef __NNT_Ng_NgCOLORSPACE_E13B52F1A0194D56850347A77D13BB6B_H_INCLUDED
# define __NNT_Ng_NgCOLORSPACE_E13B52F1A0194D56850347A77D13BB6B_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NgColorSpace : NSObject {
    
@private
    CGColorSpaceRef cgColorSpace;
    
}

@property (nonatomic, readonly, assign) CGColorSpaceRef cgColorSpace;

+ (NgColorSpace *)genericRGBSpace;

- (id)initWithCGColorSpace:(CGColorSpaceRef)colorSpace;

@end


NNT_END_HEADER_OBJC

# endif