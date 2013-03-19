
# ifndef __WSI_UIKIT_UIBADGEINDICATOR_7057B33900104EFC81B146DD1DCD9081_H_INCLUDED
# define __WSI_UIKIT_UIBADGEINDICATOR_7057B33900104EFC81B146DD1DCD9081_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGMutableTextStyle);
WSIDECL_EXTERN_CLASS(WCGLineStyle);

@interface UIBadgeIndicator : WSIUIView {
    
    //! value.
    NSString *_value;
    
    //! style.
    WCGMutableTextStyle *_badgeStyle;
    
    //! badge color.
    UIColor *_badgeColor, *_badgeOverlayColor;
    
    //! line style of badge.
    WCGMutableLineStyle *_badgeLineStyle;
    
}

@property (nonatomic, copy) NSString *value;
@property (nonatomic, retain) WCGTextStyle *badgeStyle;
@property (nonatomic, retain) UIColor *badgeColor, *badgeOverlayColor;
@property (nonatomic, retain) WCGLineStyle *badgeLineStyle;

@end

_CXXCONTROL_DECL(UIBadgeIndicator);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif