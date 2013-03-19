
# import "Core.h"
# import "WCGImageFilter.h"
# import "JuiceCocoa++.hpp"

NNT_BEGIN_OBJC

NNT_USINGCXXNAMESPACE;

@implementation WCGImageFilter

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (WCGImage*)apply:(WCGImage*)image {
    return nil;
}

@end

@interface WCGImageFilter (impl)

@end

@implementation WCGImageFilter (impl)

@end

NNTIMPL_OBJCXX_WRAPPER_BEGIN(WCGImageFilter)

- (WCGImage*)apply:(WCGImage *)image {
    cg::IImageFilter* filter = (cg::IImageFilter*)self._cxxobj;
    cg::Image ret = filter->apply(image);
    return ret.consign();
}

NNTIMPL_OBJCXX_WRAPPER_END

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(cg)

NNT_BEGIN_NS(filter)

cg::Image SetColor::apply(cg::Image const& img) const
{
    ::juice::cocoa::Graphics gra;
    if (gra.create_rgba(img.size()) == false)
        return cg::Image::Null();
    ::juice::cocoa::Image image(img);
    image.fill(gra, gra.bounds());
    gra.set_blend(kCGBlendModeSourceIn);
    ::juice::cocoa::Brush br(color);
    br.fill(gra, gra.bounds());
    return gra.to_image();
}

cg::Image OverColor::apply(cg::Image const& img) const
{
    ::juice::cocoa::Graphics gra;
    if (gra.create_rgba(img.size()) == false)
        return cg::Image::Null();
    ::juice::cocoa::Image image(img);
    image.fill(gra, gra.bounds());
    gra.set_blend(kCGBlendModeColor);
    ::juice::cocoa::Brush br(color);
    br.fill(gra, gra.bounds());
    gra.set_blend(kCGBlendModeDestinationIn);
    image.fill(gra, gra.bounds());
    return gra.to_image();
}

NNT_END_NS

NNT_END_NS
NNT_END_CXX
