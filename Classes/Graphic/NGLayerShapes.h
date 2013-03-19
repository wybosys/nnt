
# ifndef __NNT_CA_LAYERSHAPES_01A4FA101FF041548EE37C59A4EA8AC6_H_INCLUDED
# define __NNT_CA_LAYERSHAPES_01A4FA101FF041548EE37C59A4EA8AC6_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@protocol NgShapeLayer <NSObject>

@end

@interface NgShapeLayer : CAShapeLayer < NgShapeLayer >

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include NGPath.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ca)
NNT_BEGIN_NS(shape)

NNT_BEGIN_NS(tpl)

template <typename implT,
typename objcT = NgShapeLayer>
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

NNT_END_NS

class Shape
: public tpl::Shape<Shape>
{
    
};

NNT_END_NS
NNT_END_NS
NNT_END_CXX

# endif

# endif
