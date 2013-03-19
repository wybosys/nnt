
# ifndef __WSI_CORE_NSVALUE_91989D8246224E48A7F1DAEBA5C6E752_H_INCLUDED
# define __WSI_CORE_NSVALUE_91989D8246224E48A7F1DAEBA5C6E752_H_INCLUDED

# import "../Graphic/WCGBase.h"

WSI_BEGIN_HEADER_OBJC


WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class Value
: public ns::Object<NSValue>
{
    typedef ns::Object<NSValue> super;
    
public:
    
    Value()
    {
        PASS;
    }
    
    ~Value()
    {
        PASS;
    }
    
    Value(CATransform3D const& mat)
    : super(nil)
    {
        this->_self = [[NSValue valueWithCATransform3D:mat] retain];
    }
    
    operator CATransform3D () const
    {
        return [this->_self CATransform3DValue];
    }
    
    Value(CGAffineTransform const& mat)
    : super(nil)
    {
        this->_self = [[NSValue valueWithCGAffineTransform:mat] retain];
    }
    
    operator CGAffineTransform () const
    {
        return [this->_self CGAffineTransformValue];
    }
    
    Value(CGPoint const& pt)
    : super(nil)
    {
        this->_self = [[NSValue valueWithCGPoint:pt] retain];
    }
    
    operator CGPoint () const
    {
        return [this->_self CGPointValue];
    }
    
    Value(CGSize const& sz)
    : super(nil)
    {
        this->_self = [[NSValue valueWithCGSize:sz] retain];
    }
    
    operator CGSize () const
    {
        return [this->_self CGSizeValue];
    }
    
    Value(CGRect const& rc)
    : super(nil)
    {
        this->_self = [[NSValue valueWithCGRect:rc] retain];
    }
    
    operator CGRect () const
    {
        return [this->_self CGRectValue];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
