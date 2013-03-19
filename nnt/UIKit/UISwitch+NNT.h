
# ifndef __NNT_UIKIT_UISWITCH_BBE43FBCCAC0429CA27ED80D2D429FA5_H_INCLUDED
# define __NNT_UIKIT_UISWITCH_BBE43FBCCAC0429CA27ED80D2D429FA5_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface NNTUISwitch : UISwitch {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface UIImageSwitch : NNTUIView {
    
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
    NNTUIButton* buttonClose;
}

@property (nonatomic, retain) UIImage *imageFalse, *image;
@property (nonatomic, retain) UIColor *colorFalse;
@property (nonatomic, assign) int value;
@property (nonatomic, assign) BOOL showClose;
@property (nonatomic, retain) NNTUIButton *buttonClose;

- (void)close;

@end

NNT_EXTERN signal_t kSignalValueChanged;
NNT_EXTERN signal_t kSignalButtonCloseClicked;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class SwitchButton
: public ui::Control<SwitchButton, NNTUISwitch>
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif