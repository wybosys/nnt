
# import "Core.h"
# import "NGImageFilter.h"
# import "JuiceCocoa++.hpp"

NNT_BEGIN_OBJC

NNT_USINGCXXNAMESPACE;

@implementation NgImageFilter

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (NgImage*)apply:(NgImage*)image {
    return nil;
}

@end

@interface NgImageFilter (impl)

@end

@implementation NgImageFilter (impl)

@end

NNTIMPL_OBJCXX_WRAPPER_BEGIN(NgImageFilter)

- (NgImage*)apply:(NgImage *)image {
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
