
# ifndef __NNT_UIKIT_DRAWERVIEW_30C52D9E76B340F59DF84A92E5CF066A_H_INCLUDED
# define __NNT_UIKIT_DRAWERVIEW_30C52D9E76B340F59DF84A92E5CF066A_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UIDrawerView : NNTUIView {
    
    CGRectPositionType _positionType;
    CGFloat _length;
    bool _opened;
    
    UIView* _beyondView;
}

@property (nonatomic, assign) CGRectPositionType positionType;
@property (nonatomic, assign) CGFloat length;

- (void)openBeyondView:(UIView*)view animated:(BOOL)animated;
- (void)close:(BOOL)animated;

@end

_CXXVIEW_DECL(UIDrawerView);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class Drawer
: public ui::View<Drawer, _CXXVIEW(UIDrawerView)>
{
public:
    
    Drawer()
    {
        PASS;
    }
    
    void open(UIView* view, bool animated = ui::animate)
    {
        [this->_self openBeyondView:view animated:animated];
    }
    
    void close(bool animated = ui::animate)
    {
        [this->_self close:animated];
    }
    
    void set_position(CGRectPositionType pt)
    {
        this->_self.positionType = pt;
    }
    
    CGRectPositionType position() const
    {
        return this->_self.positionType;
    }
    
    void set_length(real val)
    {
        this->_self.length = val;
    }
    
    real length() const
    {
        return this->_self.length;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
