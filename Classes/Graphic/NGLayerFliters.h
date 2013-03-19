
# ifndef __NNT_CA_LAYERFILTERS_F060F8544EE1433888F7FFD13A7D4FF7_H_INCLUDED
# define __NNT_CA_LAYERFILTERS_F060F8544EE1433888F7FFD13A7D4FF7_H_INCLUDED

# import "NGLayer.h"

NNT_BEGIN_HEADER_OBJC

@protocol NgLayerFilters <NSObject>

- (void)applyLayer:(CALayer*)layer;

@end

@interface NgLayerFilters : NNTObject < NgLayerFilters >

@end

@interface CALayer (NgLayerFilters)

- (void)applyFilter:(id<WCALayerFilters>)filter;

@end

NNTDECL_CATEGORY(CALayer, NgLayerFilters);

NNTDECL_OBJCXX_WRAPPER(NgLayerFilters);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NGPath.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ca)
NNT_BEGIN_NS(filter)

NNT_BEGIN_NS(tpl)

class IFilter
: public ns::cxx::IObject
{
public:
    
    virtual void apply(CALayer*) const = 0;
    
};

template <typename implT,
typename filterT = NNT_OBJCXX_WRAPPER(NgLayerFilters),
typename interT = IFilter
>
class Filter
: public ns::cxx::Object<filterT, interT>
{
public:
    
    Filter()
    {
        PASS;
    }
    
    virtual ~Filter()
    {
        PASS;
    }
    
    virtual void apply(CALayer*) const
    {
        PASS;
    }
    
};

NNT_END_NS

class Shadow
: public tpl::Filter<Shadow>
{
public:
    
    Shadow()
    : opacity(0), offset(0, 0), radius(3)
    {
        PASS;
    }
    
    virtual void apply(CALayer* layer) const
    {
        layer.shadowColor = color;
        layer.shadowOpacity = opacity;
        layer.shadowRadius = radius;
        layer.shadowOffset = offset;
        layer.shadowPath = path;
    }
    
    cg::Color color;
    cg::Size offset;
    real opacity;
    real radius;
    cg::Path path;
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
