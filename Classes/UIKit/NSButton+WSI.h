
# ifndef __WSINS_BUTTON_D1922D19F6B84EE69C7B90467B1A2187_H_INCLUDED
# define __WSINS_BUTTON_D1922D19F6B84EE69C7B90467B1A2187_H_INCLUDED

# include "NSControl+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface WSINSButton : NSButton {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "NSControl+WSI.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)

template <uint typeID>
struct nsbutton_type_traits
{};

template <>
struct nsbutton_type_traits<NSMomentaryPushInButton>
{
    enum 
    {
        IMAGEPOSITION = NSNoImage,
        BEZELSTYLE = NSRoundedBezelStyle
    };
};

template <usize typeID, typename buttonT = WSINSButton >
class Button
: public Control< Button<typeID, buttonT>, buttonT >
{
public:
    
    Button()
    {        
        PASS;
    }    
    
    void init()
    {
        this->_self = [[buttonT alloc] initWithZero];
        [this->_self setButtonType:typeID];   
        [this->_self setImagePosition:nsbutton_type_traits<typeID>::IMAGEPOSITION];
        [this->_self setBezelStyle:nsbutton_type_traits<typeID>::BEZELSTYLE];
    }
    
    inline void set_text(::NSString* str)
    {
        [this->_self setTitle:str];
    }
    
protected:
    
    void set_buttontype(NSButtonType type)
    {
        [this->_self setButtonType:type];
    }
};

typedef Button<NSMomentaryPushInButton> PushButton;

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif