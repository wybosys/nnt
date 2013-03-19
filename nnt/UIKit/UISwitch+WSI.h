
# ifndef __WSI_UIKIT_UISWITCH_BBE43FBCCAC0429CA27ED80D2D429FA5_H_INCLUDED
# define __WSI_UIKIT_UISWITCH_BBE43FBCCAC0429CA27ED80D2D429FA5_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface WSIUISwitch : UISwitch {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

@interface UIImageSwitch : WSIUIView {
    
    //! image for false.
    UIImage *imageFalse;
    
    //! image for true.
    UIImage *image;
    
    //! over color when image false is not set. default is gray.
    UIColor* colorFalse;
    
    //! status. default is no.
    int value;
    
    //! show close btn. default is NO.
    BOOL showClose;
    
    //! close button.
    WSIUIButton* buttonClose;
}

@property (nonatomic, retain) UIImage *imageFalse, *image;
@property (nonatomic, retain) UIColor *colorFalse;
@property (nonatomic, assign) int value;
@property (nonatomic, assign) BOOL showClose;
@property (nonatomic, retain) WSIUIButton *buttonClose;

- (void)close;

@end

WSI_EXTERN signal_t kSignalValueChanged;
WSI_EXTERN signal_t kSignalButtonCloseClicked;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class SwitchButton
: public ui::Control<SwitchButton, WSIUISwitch>
{
public:
    
    SwitchButton()
    {
        PASS;
    }
    
    void set_on(bool val = true, bool ani = true)
    {
        [this->_self setOn:val animated:ani];
    }
    
    bool is_on() const
    {
        return this->_self.on;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif