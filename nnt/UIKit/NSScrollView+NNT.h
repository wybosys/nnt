
# ifndef __NNTNS_SCROLLVIEW_D736FE461F454250997050D89A2B9335_H_INCLUDED
# define __NNTNS_SCROLLVIEW_D736FE461F454250997050D89A2B9335_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTNSScrollView : NSScrollView

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NSControl+NNT.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

template <typename implT, 
typename scrollT = NNTNSScrollView
>
class ScrollView
: public View <implT, scrollT>
{
    typedef View <implT, scrollT> super;
    
public:    
        
    ScrollView()
    {        
        PASS;
    }
    
    void init()
    {
        this->_self = [[scrollT alloc] initWithZero];
    }
    
    template <typename viewT>
    void set_document(viewT const& view)
    {
        ntl::const_pointer<viewT> ptr(view);
        [this->_self setDocumentView:*ptr];
    }
    
};

class Scroll
: public ScrollView<Scroll, NNTNSScrollView>
{
    
};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif