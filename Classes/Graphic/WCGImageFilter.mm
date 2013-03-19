
# import "Core.h"
# import "WCGImageFilter.h"
# import "JuiceCocoa++.hpp"

WSI_BEGIN_OBJC

WSI_USINGCXXNAMESPACE;

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

WSIIMPL_OBJCXX_WRAPPER_BEGIN(WCGImageFilter)

- (WCGImage*)apply:(WCGImage *)image {
    cg::IImageFilter* filter = (cg::IImageFilter*)self._cxxobj;
    cg::Image ret = filter->apply(image);
    return ret.consign();
}

WSIIMPL_OBJCXX_WRAPPER_END

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(cg)

WSI_BEGIN_NS(filter)

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

WSI_END_NS

WSI_END_NS
WSI_END_CXX
