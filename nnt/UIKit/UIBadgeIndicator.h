
# ifndef __NNT_UIKIT_UIBADGEINDICATOR_7057B33900104EFC81B146DD1DCD9081_H_INCLUDED
# define __NNT_UIKIT_UIBADGEINDICATOR_7057B33900104EFC81B146DD1DCD9081_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgMutableTextStyle);
NNTDECL_EXTERN_CLASS(NgLineStyle);

@interface UIBadgeIndicator : NNTUIView {
    
    //! value.
    NSString *_value;
    
    //! style.
    NgMutableTextStyle *_badgeStyle;
    
    //! badge color.
    UIColor *_badgeColor, *_badgeOverlayColor;
    
    //! line style of badge.
    NgMutableLineStyle *_badgeLineStyle;
    
}

@property (nonatomic, copy) NSString *value;
@property (nonatomic, retain) NgTextStyle *badgeStyle;
@property (nonatomic, retain) UIColor *badgeColor, *badgeOverlayColor;
@property (nonatomic, retain) NgLineStyle *badgeLineStyle;

@end

_CXXCONTROL_DECL(UIBadgeIndicator);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class BadgeIndicator
: public Control<BadgeIndicator,
_CXXCONTROL(UIBadgeIndicator)
>
{
    typedef Control<BadgeIndicator,
    _CXXCONTROL(UIBadgeIndicator)
    > super;
    
public:
    
    BadgeIndicator()
    {
        PASS;
    }
    
    virtual ~BadgeIndicator()
    {
        PASS;
    }
    
    void set_value(ns::String const& str)
    {
        this->_self.value = str;
    }
    
    ns::String value() const
    {
        return this->_self.value;
    }
    
    void set_style(cg::MutableTextStyle const& ts)
    {
        this->_self.badgeStyle = ts;
    }
    
    void set_style(cg::MutableLineStyle const& ls)
    {
        this->_self.badgeLineStyle = ls;
    }
    
    void set_style(ui::Color const& cor)
    {
        this->_self.badgeColor = cor;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif