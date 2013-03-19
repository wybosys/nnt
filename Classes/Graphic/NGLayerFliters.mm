
# import "Core.h"
# import "NGLayerFliters.h"

NNT_BEGIN_OBJC

NNT_USINGCXXNAMESPACE;

@implementation NgLayerFilters

- (void)dealloc {
    [super dealloc];
}

- (void)applyLayer:(CALayer*)layer {
    PASS;
}

@end

@implementation CALayer (NgLayerFilters)

- (void)applyFilter:(id<NgLayerFilters>)filter {
    [filter applyLayer:self];
}

@end

NNTIMPL_CATEGORY(CALayer, NgLayerFilters);

NNTIMPL_OBJCXX_WRAPPER_BEGIN(NgLayerFilters)

- (void)applyLayer:(CALayer *)layer {
    ca::filter::tpl::IFilter* filter = (ca::filter::tpl::IFilter*)self._cxxobj;
    filter->apply(layer);
}

NNTIMPL_OBJCXX_WRAPPER_END

NNT_END_OBJC
