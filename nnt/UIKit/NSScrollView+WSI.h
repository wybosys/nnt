
# ifndef __WSINS_SCROLLVIEW_D736FE461F454250997050D89A2B9335_H_INCLUDED
# define __WSINS_SCROLLVIEW_D736FE461F454250997050D89A2B9335_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WSINSScrollView : NSScrollView

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "NSControl+WSI.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)

template <typename implT, 
typename scrollT = WSINSScrollView
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
        wtl::const_pointer<viewT> ptr(view);
        [this->_self setDocumentView:*ptr];
    }
    
};

class Scroll
: public ScrollView<Scroll, WSINSScrollView>
{
    
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif