
# ifndef __NNT_COCOS_VIEW_BEB37E16560E4BE9B90051113618AADC_H_INCLUDED
# define __NNT_COCOS_VIEW_BEB37E16560E4BE9B90051113618AADC_H_INCLUDED

# ifdef NNT_OBJC

# include "../../UIKit/UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC
NNTDECL_EXTERN_CLASS(EAGLView);
NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cocos)

class View
: public ui::View<View>
{
public:
    
    View();
    ~View();
    
    void layout_subviews();
    
protected:
    
    EAGLView* _gl;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
