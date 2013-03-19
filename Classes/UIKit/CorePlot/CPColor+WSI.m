
# import "Core.h"
# import "CorePlot+NNT.h"

NNT_BEGIN

@implementation CPColor (NNT)

+ (CPColor*)colorWithARGB:(int)__value {
    return [CPColor colorWithComponentRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(ARGB_ALPHA(__value))];
}

+ (CPColor*)colorWithRGBA:(int)__value {
    return [CPColor colorWithComponentRed:AS_C32P(RGBA_RED(__value)) green:AS_C32P(RGBA_GREEN(__value)) blue:AS_C32P(RGBA_BLUE(__value)) alpha:AS_C32P(RGBA_ALPHA(__value))];
}

+ (CPColor*)colorWithRGB:(int)__value {
    return [CPColor colorWithComponentRed:AS_C32P(ARGB_RED(__value)) green:AS_C32P(ARGB_GREEN(__value)) blue:AS_C32P(ARGB_BLUE(__value)) alpha:AS_C32P(0xFF)]; 
}

+ (CPColor*)multiWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b {
    return [CPColor multiWith:color r:__r g:__g b:__b a:1.f];
}

+ (CPColor*)multiWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    float const* _comps = CGColorGetComponents(color.cgColor);
    float comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] *= __r;
    comps[1] *= __g;
    comps[2] *= __b;
    comps[3] *= __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(color.cgColor), comps);
    CPColor *ret = [safe_alloc(CPColor) initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];
}

+ (CPColor*)addWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b {
    return [CPColor addWith:color r:__r g:__g b:__b a:0.f];
}

+ (CPColor*)addWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a {
    float const* _comps = CGColorGetComponents(color.cgColor);
    float comps[4] = { _comps[0], _comps[1], _comps[2], _comps[3] };
    comps[0] += __r;
    comps[1] += __g;
    comps[2] += __b;
    comps[3] += __a;
    CGColorRef ref = CGColorCreate(CGColorGetColorSpace(color.cgColor), comps);
    CPColor *ret = [safe_alloc(CPColor) initWithCGColor:ref];
    CGColorRelease(ref);
    return [ret autorelease];
}

@end

NNTIMPL_CATEGORY(CPColor, NNT);

NNT_END