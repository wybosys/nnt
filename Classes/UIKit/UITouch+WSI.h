
# ifndef __WSI_UITOUCH_50288012CC314EF99620CBC13D3C52EF_H_INCLUDED
# define __WSI_UITOUCH_50288012CC314EF99620CBC13D3C52EF_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UITouch (WSI)

- (CGPoint)offset;

@end

WSIDECL_CATEGORY(UITouch, WSI);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class Touch
: public ns::Object<UITouch>
{
    typedef ns::Object<UITouch> super;
    
public:
    
    Touch(UITouch* t)
    : super(t)
    {
        PASS;
    }
    
    Touch(id t)
    : super(t)
    {
        PASS;
    }
    
    template <typename viewT>
    cg::Point location(viewT const& view) const
    {
        wtl::const_pointer<viewT> ptr(view);
        return [this->_self locationInView:*ptr];
    }
    
    cg::Point offset() const
    {
        return [this->_self offset];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif