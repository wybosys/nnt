
# ifndef __NNT_UIKIT_UIBUTTON_CA342FA80851403C9D2E315A470E0823_H_INCLUDED
# define __NNT_UIKIT_UIBUTTON_CA342FA80851403C9D2E315A470E0823_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgFill);
NNTDECL_EXTERN_CLASS(NgColor);
NNTDECL_EXTERN_CLASS(UIStyleSheet);

@interface UIButton (NNT)

+ (UIButton*)buttonCloseRedRound;
+ (UIButton*)buttonCloseGrayRound;

NNTUIVIEW_NOTINHERIT_MUST_DECL;

@end

NNTDECL_CATEGORY(UIButton, NNT);

@interface NNTUIButton : UIButton <NNTUIViewLock> {
    NNTOBJECT_DECL;
    
    //! background gradient. it can be Array, Single.
    id<NSObject> _backgroundGradient;
        
    //! action on button clicked.
    id _target;
    SEL _action;
    id _action_object;
    
    //! is this button is touched.
    BOOL _isTouched;
    
    //! style sheet.
    UIStyleSheet* _styleSheet;
    
    //! text.
    NSString* _text;
    
    //! touched color.
    UIStyleSheet* _touchedStyleSheet;
            
    @private    
    int __lockposition;
}

NNTOBJECT_PROP;

@property (nonatomic, readonly) BOOL isTouched;
@property (nonatomic, retain) id<NSObject> backgroundGradient;
@property (nonatomic, assign) id target;
@property (nonatomic, assign) SEL action;
@property (nonatomic, assign) id action_object;
@property (nonatomic, copy) NSString* text;
@property (nonatomic, retain) UIStyleSheet *styleSheet, *touchedStyleSheet;
@property (nonatomic, retain) NgFill *backgroundFill, *touchedFill;
@property (nonatomic, assign) BOOL enableFeedback;

//! text size.
- (CGSize)textSize;

//! draw button.
- (void)drawButton:(CGContextRef)ctx rect:(CGRect)rect;

//! set textstyle.
- (void)applyTextStyle:(NgTextStyle*)ts;

@end

@interface UIStyledButton : NNTUIButton

@end

@interface UIClearButton : NNTUIButton

+ (id)button;

@end

@interface UISystemButton : UIClearButton {
    UIButton* _button;
}

- (id)initWithButtonType:(UIButtonType)type;

@end

@interface UIBevelButton : NNTUIButton {
    //! inner shadow color.
    NgColor *innerShadowColor;
    
    //! inner shadow length.
    CGFloat innerShadowLength;
    
    //! inner shadow blur.
    CGFloat innerShadowBlur;
}

@property (nonatomic, retain) NgColor *innerShadowColor;
@property (nonatomic, assign) CGFloat innerShadowLength;
@property (nonatomic, assign) CGFloat innerShadowBlur;

+ (id)button;

- (void)drawInnerShadow:(CGContextRef)ctx;
- (void)drawInnerShadow:(CGContextRef)ctx rect:(CGRect)rc;

@end

NNT_EXTERN signal_t kSignalViewClicked;
NNT_EXTERN signal_t kSignalButtonClicked;

//! other buttons.

@interface UIButtonClose : UIClearButton

@property (nonatomic, assign) real radius;

- (id)initWithFrame:(CGRect)frame;

@end

typedef UIButtonClose UICloseButton;

@interface UIBackButton : UIStyledButton

@end

typedef enum {
    UIButtonStateUnchecked = 0,
    UIButtonStateChecked,
    UIButtonStateMixin,
} UIButtonState;

@protocol UIStateButton <NSObject>

@property (nonatomic, assign) UIButtonState state;

- (void)setStateFill:(NgFill*)fill forState:(UIButtonState)state;
- (void)setStateTextStyle:(NgTextStyle*)ts forState:(UIButtonState)state;

@end

@interface UIStateButton : UIClearButton <UIStateButton> {
    UIButtonState _state;
    NgFill *_fillUnchecked, *_fillChecked, *_fillMixin;
    NgTextStyle *_tsUnchecked, *_tsChecked, *_tsMixin;
}

@end

@interface UIButtonGroup : NNTObject {
    NSMutableArray* _buttons;
    
    @protected
    UIButton* _sel;
}

@property (nonatomic, readonly) NSMutableArray* buttons;
@property (nonatomic, retain) UIButton* selected;

//! add button.
- (void)add:(UIButton*)button;

//! clear all.
- (void)clear;

@end

# ifdef NNT_CXX

_CXXVIEW_DECL(UIClearButton);
_CXXVIEW_DECL(UISystemButton);
_CXXVIEW_DECL(UIBevelButton);
_CXXVIEW_DECL(UIStateButton);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIControl+NNT.h"
# include "UILabel+NNT.h"
# include "UIImageView+NNT.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

template <typename implT, typename buttonT = NNTUIButton>
class Button
: public Control<implT, buttonT>
{      
    
    typedef Control<implT, buttonT> super;
    
public:
        
    Button()
    : _title(NULL), _image(NULL)
    {
        PASS;
    }
    
    Button(buttonT* btn)
    : super(btn)
    {
        PASS;
    }
    
    ~Button()
    {
        safe_delete(_title);
        safe_delete(_image);
    }
    
    void set_text(ns::String const& str, UIControlState state = UIControlStateNormal)
    {
        [this->_self setTitle:str forState:state];
    }
    
    void set_image(Image const& img, UIControlState state = UIControlStateNormal)
    {
        [this->_self setImage:img forState:state];
    }
    
    void set_background_image(Image const& img, UIControlState state = UIControlStateNormal)
    {
        [this->_self setBackgroundImage:img forState:state];
    }
    
    void set_touched(cg::Fill const& fill)
    {
        this->_self.touchedFill = fill;
    }
    
    UIControlState state() const
    {
        return this->_self.state;
    }
    
    void set_text(Color const& color, UIControlState state = UIControlStateNormal)
    {
        [this->_self setTitleColor:color forState:state];
    }
    
    Label& title()
    {
        if (_title == NULL)
            _title = new Label((NNTUILabel*)this->_self.titleLabel);
        return *_title;
    }
    
    ImageView& image() 
    {
        if (_image == NULL)
            _image = new ImageView((NNTUIImageView*)this->_self.imageView);
        return *_image;
    }
    
    void roundrect()
    {
        CALayer* layer = this->_self.layer;
        layer.borderColor = [[UIColor darkGrayColor] CGColor];
        layer.cornerRadius = 8.0f;
        layer.borderWidth = 1.0f;   
    }
    
    cg::Size textsize() const
    {
        return [this->_self textSize];
    }
    
    void set_feedback(bool b)
    {
        this->_self.enableFeedback = b;
    }
    
protected:
    
    Label* _title;
    ImageView* _image;
    
};

class ClearButton
: public Button<ClearButton, _CXXVIEW(UIClearButton)>
{
    
};

class SystemButton
: public Button<SystemButton, _CXXVIEW(UISystemButton)>
{
    typedef Button<SystemButton, _CXXVIEW(UISystemButton)> super;
    
public:
    
    SystemButton(UIButtonType type)
    : super(nil)
    {
        this->_self = [[objc_type alloc] initWithButtonType:type];
    }
    
};

class BevelButton
: public Button<BevelButton, _CXXVIEW(UIBevelButton)>
{
    
};

class StateButton
: public Button<StateButton, _CXXVIEW(UIStateButton)>
{
public:
    
    void set_unchecked(cg::Fill const& fill)
    {
        [this->_self setStateFill:fill forState:UIButtonStateUnchecked];
    }
    
    void set_checked(cg::Fill const& fill)
    {
        [this->_self setStateFill:fill forState:UIButtonStateChecked];
    }
    
    void set_mixin(cg::Fill const& fill)
    {
        [this->_self setStateFill:fill forState:UIButtonStateMixin];
    }
    
    void set_unchecked(cg::TextStyle const& ts)
    {
        [this->_self setStateTextStyle:ts forState:UIButtonStateUnchecked];
    }
    
    void set_checked(cg::TextStyle const& ts)
    {
        [this->_self setStateTextStyle:ts forState:UIButtonStateChecked];        
    }
    
    void set_mixin(cg::TextStyle const& ts)
    {
        [this->_self setStateTextStyle:ts forState:UIButtonStateMixin];
    }
    
};

class ButtonGroup
: public ns::Object<UIButtonGroup>
{
public:
    
    ButtonGroup()
    {
        PASS;
    }
    
    void clear()
    {
        [this->_self clear];
    }
    
    template <typename btnT>
    void add(btnT const& btn)
    {
        ntl::const_pointer<btnT> ptr(btn);
        [this->_self add:(UIButton*)*ptr];
    }
    
    void* selected() const
    {
        return [this->_self.selected object];
    }
    
    template <typename btnT>
    void set_selected(btnT const& btn)
    {
        this->_self.selected = btn;
    }
    
};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif