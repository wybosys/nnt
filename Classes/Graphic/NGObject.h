
# ifndef __NNT_COREANIMATE_OBJECT_04AF009F4A9742F6A4F341DA69F1CE19_H_INCLUDED
# define __NNT_COREANIMATE_OBJECT_04AF009F4A9742F6A4F341DA69F1CE19_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ca)

template <typename objcT>
class Object
: public ns::Object<objcT>
{
    typedef ns::Object<objcT> super;
    
public:
    
    Object()
    {
        PASS;
    }
    
    Object(objcT* r)
    : super(r)
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
