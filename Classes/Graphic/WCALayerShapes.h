
# ifndef __WSI_CA_LAYERSHAPES_01A4FA101FF041548EE37C59A4EA8AC6_H_INCLUDED
# define __WSI_CA_LAYERSHAPES_01A4FA101FF041548EE37C59A4EA8AC6_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@protocol WCAShapeLayer <NSObject>

@end

@interface WCAShapeLayer : CAShapeLayer < WCAShapeLayer >

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "WCGPath.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ca)
WSI_BEGIN_NS(shape)

WSI_BEGIN_NS(tpl)

template <typename implT,
typename objcT = WCAShapeLayer>
class Shape
: public ns::Object<objcT>
{
public:
    
    Shape()
    {
        this->_self.path = path;
    }
    
    ~Shape()
    {
        PASS;
    }
    
    cg::MutablePath path;
    
};

WSI_END_NS

class Shape
: public tpl::Shape<Shape>
{
    
};

WSI_END_NS
WSI_END_NS
WSI_END_CXX

# endif

# endif
