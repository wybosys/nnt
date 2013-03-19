
# ifndef __NNT_UITOUCH_50288012CC314EF99620CBC13D3C52EF_H_INCLUDED
# define __NNT_UITOUCH_50288012CC314EF99620CBC13D3C52EF_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UITouch (NNT)

- (CGPoint)offset;

@end

NNTDECL_CATEGORY(UITouch, NNT);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

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
        ntl::const_pointer<viewT> ptr(view);
        return [this->_self locationInView:*ptr];
    }
    
    cg::Point offset() const
    {
        return [this->_self offset];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif