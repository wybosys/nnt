
# ifndef __NNT_CORE_NSVALUE_91989D8246224E48A7F1DAEBA5C6E752_H_INCLUDED
# define __NNT_CORE_NSVALUE_91989D8246224E48A7F1DAEBA5C6E752_H_INCLUDED

# import "../Graphic/NGBase.h"

NNT_BEGIN_HEADER_OBJC


NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
