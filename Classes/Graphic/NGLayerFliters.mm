
# import "Core.h"
# import "WCALayerFliters.h"

NNT_BEGIN_OBJC

NNT_USINGCXXNAMESPACE;

@implementation WCALayerFilters

- (void)dealloc {
    [super dealloc];
}

- (void)applyLayer:(CALayer*)layer {
    PASS;
}

@end

@implementation CALayer (WCALayerFilters)

- (void)applyFilter:(id<WCALayerFilters>)filter {
    [filter applyLayer:self];
}

@end

NNTIMPL_CATEGORY(CALayer, WCALayerFilters);

NNTIMPL_OBJCXX_WRAPPER_BEGIN(WCALayerFilters)

- (void)applyLayer:(CALayer *)layer {
    ca::filter::tpl::IFilter* filter = (ca::filter::tpl::IFilter*)self._cxxobj;
    filter->apply(layer);
}

NNTIMPL_OBJCXX_WRAPPER_END

NNT_END_OBJC
