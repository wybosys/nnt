
# import "Core.h"
# import "WCALayerFliters.h"

WSI_BEGIN_OBJC

WSI_USINGCXXNAMESPACE;

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

WSIIMPL_CATEGORY(CALayer, WCALayerFilters);

WSIIMPL_OBJCXX_WRAPPER_BEGIN(WCALayerFilters)

- (void)applyLayer:(CALayer *)layer {
    ca::filter::tpl::IFilter* filter = (ca::filter::tpl::IFilter*)self._cxxobj;
    filter->apply(layer);
}

WSIIMPL_OBJCXX_WRAPPER_END

WSI_END_OBJC
