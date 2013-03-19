
# ifndef __WSI_CA_LAYERFILTERS_F060F8544EE1433888F7FFD13A7D4FF7_H_INCLUDED
# define __WSI_CA_LAYERFILTERS_F060F8544EE1433888F7FFD13A7D4FF7_H_INCLUDED

# import "WCALayer.h"

WSI_BEGIN_HEADER_OBJC

@protocol WCALayerFilters <NSObject>

- (void)applyLayer:(CALayer*)layer;

@end

@interface WCALayerFilters : WSIObject < WCALayerFilters >

@end

@interface CALayer (WCALayerFilters)

- (void)applyFilter:(id<WCALayerFilters>)filter;

@end

WSIDECL_CATEGORY(CALayer, WCALayerFilters);

WSIDECL_OBJCXX_WRAPPER(WCALayerFilters);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "WCGPath.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ca)
WSI_BEGIN_NS(filter)

WSI_BEGIN_NS(tpl)

class IFilter
: public ns::cxx::IObject
{
public:
    
    virtual void apply(CALayer*) const = 0;
    
};

template <typename implT,
typename filterT = WSI_OBJCXX_WRAPPER(WCALayerFilters),
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

WSI_END_NS

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

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
