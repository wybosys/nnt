
# import "Core.h"
# import "UIColor+WSI.h"

WSI_BEGIN

@implementation UIColor (WSI)

- (id)initWithRGBA:(int)__value {
    self = [self initWithRed:AS_C32P(RGBA_RED(__value)) green:AS_C32P(RGBA_GREEN(__value)) blue:AS_C32P(RGBA_BLUE(__value)) alpha:AS_C32P(RGBA_ALPHA(__value))];
    return self;
}

- (id)initWithARGB:(int)__value {
    self = [self initWithRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(ARGB_ALPHA(__value))];
    return self;
}

- (id)initWithRGB:(int)__value {
    self = [self initWithRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(0xFF)];
    return self;
}

+ (UIColor*)colorWithRGBA:(int)__value {
    return [UIColor colorWithRed:AS_C32P(RGBA_RED(__value)) green:AS_C32P(RGBA_GREEN(__value)) blue:AS_C32P(RGBA_BLUE(__value)) alpha:AS_C32P(RGBA_ALPHA(__value))];
}

+ (UIColor*)colorWithARGB:(int)__value {
    return [UIColor colorWithRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(ARGB_ALPHA(__value))];
}

+ (UIColor*)colorWithRGB:(int)__value {
    return [UIColor colorWithRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(0xFF)];
}

+ (UIColor*)multiWith:(UIColor*)color r:(float)__r g:(float)__g b:(float)__b {
    return [UIColor multiWith:color r:__r g:__g b:__b a:1.f];
}

+ (UIColor*)multiWith:(UIColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    float const* _comps = CGColorGetComponents(color.CGColor);
    float comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] *= __r;
    comps[1] *= __g;
    comps[2] *= __b;
    comps[3] *= __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(color.CGColor), comps);
    UIColor *ret = [[UIColor alloc] initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];
}

+ (UIColor*)addWith:(UIColor*)color r:(float)__r g:(float)__g b:(float)__b {
    return [UIColor addWith:color r:__r g:__g b:__b a:0.f];
}

+ (UIColor*)addWith:(UIColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    float const* _comps = CGColorGetComponents(color.CGColor);
    float comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] += __r;
    comps[1] += __g;
    comps[2] += __b;
    comps[3] += __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(color.CGColor), comps); 
    UIColor *ret = [[UIColor alloc] initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];
}

- (uint)valueRGBA {
    float const* _comps = CGColorGetComponents(self.CGColor);
    return RGBA(_comps[0] * 255, _comps[1] * 255, _comps[2] * 255, _comps[3] * 255);
}

- (uint)valueRGB {
    float const* _comps = CGColorGetComponents(self.CGColor);
    return RGB(_comps[0] * 255, _comps[1] * 255, _comps[2] * 255);
}

- (uint)valueARGB {
    float const* _comps = CGColorGetComponents(self.CGColor);
    return ARGB(_comps[0] * 255, _comps[1] * 255, _comps[2] * 255, _comps[3] * 255);   
}

- (UIColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b {
    UIColor *color = [UIColor colorWithRGB:[self valueRGB]];
    return [UIColor multiWith:color r:__r g:__g b:__b];
}

- (UIColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    UIColor *color = [UIColor colorWithRGBA:[self valueRGBA]];
    return [UIColor multiWith:color r:__r g:__g b:__b a:__a];
}

@end

WSIIMPL_CATEGORY(UIColor, WSI);

WSI_END