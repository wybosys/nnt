
# ifndef __WSI_COREANIMATE_OBJECT_04AF009F4A9742F6A4F341DA69F1CE19_H_INCLUDED
# define __WSI_COREANIMATE_OBJECT_04AF009F4A9742F6A4F341DA69F1CE19_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ca)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
