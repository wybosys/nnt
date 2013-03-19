
# ifndef __WSI_UIKIT_UITEXTFIELD_87EDC93DA1DF4CAE925EA33DD7C12EF6_H_INCLUDED
# define __WSI_UIKIT_UITEXTFIELD_87EDC93DA1DF4CAE925EA33DD7C12EF6_H_INCLUDED

# import "UIControl+WSI.h"
# import "UITableViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(WSIUITextField);

typedef enum
{
    UIReturnKeyEnableAutomatically,
    UIReturnKeyEnableManual,
} UIReturnKeyEnableType;

@interface UITextField (WSI)

- (void)applyTextStyle:(WCGTextStyle*)ts;

@end

WSIDECL_CATEGORY(UITextField, WSI);

@interface WSIUITextField : UITextField {
    
    //! restrict string for input, regex format.
    NSString *_inputRestrict;
    
    //! check string for input, regex format.
    NSString *_validRestrict;
    
    //! invalid color.
    UIColor *_invalidFontColor, *_invalidBackgroundColor;
    
    //! padding.
    CGPadding _padding;
    
    WSIOBJECT_DECL;
    WSIDECL_PRIVATE(WSIUITextField);
}

WSIOBJECT_PROP;

@property (nonatomic, copy) NSString *inputRestrict;
@property (nonatomic, copy) NSString *validRestrict;
@property (nonatomic, retain) UIColor *invalidFontColor, *invalidBackgroundColor;
@property (nonatomic, retain) WCGFill *backgroundFill;
@property (nonatomic, assign) CGPadding padding;
@property (nonatomic, readonly) BOOL isValid;

- (BOOL)changeText:(NSString*)text;

@end

@interface UISuggestTextField : WSIUITextField < UIItemProvider > {
    
    //! data source.
    NSObject < UIItemProvider > *_dataSource;
    
    //! size for suggest list.
    CGSize _sizeSuggestList;
    
    //! datas.
    NSArray* _datas;
    
    @private
    WSIUITableViewController* _items;
    
}

@property (nonatomic, assign) NSObject < UIItemProvider > *dataSource;
@property (nonatomic, assign) CGSize sizeSuggestList;
@property (nonatomic, retain) NSArray* datas;

@end

@interface UIHistoryTextField : UISuggestTextField  < UIItemSerial >
{
    //! identity for store history.
    NSString* _identity;
 
    //! delegate.
    NSObject < UIItemSerial > *_serialDelegate;
    
    //! limit. default is NSInfinite.
    NSUInteger _limitCount;
    
}

@property (nonatomic, copy) NSString* identity;
@property (nonatomic, assign) NSObject < UIItemSerial > *serialDelegate;
@property (nonatomic, assign) NSUInteger limitCount;

@end

//! signal, emit while value changed.
WSI_EXTERN signal_t kSignalValueChanged;

//! signal, emit while begin editing.
WSI_EXTERN signal_t kSignalBeginEditing;

//! signal, emit while end editing.
WSI_EXTERN signal_t kSignalEndEditing;

//! signal, emit while text's valid status is changed.
WSI_EXTERN signal_t kSignalValidChanged;

//! clear.
WSI_EXTERN signal_t kSignalEditingClear;

//! return.
WSI_EXTERN signal_t kSignalEditingReturn;

# ifdef WSI_CXX

# include "UIControl+WSI.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(tpl)

template <typename implT>
class Keyboard
: public implT
{
    typedef Keyboard<implT> keyboard_type;
    
public:
    
    keyboard_type& keyboard()
    {
        return *this;
    }

    keyboard_type const& keyboard() const
    {
        return *this;
    }
    
    void set_type(UIKeyboardType kt)
    {
        this->_self.keyboardType = kt;
    }
    
    UIKeyboardType type() const
    {
        return this->_self.keyboardType;
    }
    
    void set_appearance(UIKeyboardAppearance ka)
    {
        this->_self.keyboardAppearance = ka;
    }
    
    UIKeyboardAppearance appearance() const
    {
        return this->_self.keyboardAppearance;
    }

    void set_returnkey(UIReturnKeyType kt)
    {
        this->_self.returnKeyType = kt;
    }
    
    UIReturnKeyType returnkey() const
    {
        return this->_self.returnKeyType;
    }
    
    void set_autoreturn(UIReturnKeyEnableType rket)
    {
        if (rket == UIReturnKeyEnableAutomatically)
            this->_self.enablesReturnKeyAutomatically = YES;
        else
            this->_self.enablesReturnKeyAutomatically = NO;
    }
    
    UIReturnKeyEnableType autoreturn() const
    {
        if (this->_self.enablesReturnKeyAutomatically)
            return UIReturnKeyEnableAutomatically;
        return UIReturnKeyEnableManual;
    }
    
};

template <typename implT>
class TextInput
: public Keyboard<implT>
{
public:
    
    TextInput()
    {
        PASS;
    }
    
};

template <typename uiT = WSIUITextField >
class TextField
: public TextInput< Control< TextField<uiT>, uiT > >
{        
public:
    
    TextField()
    {
        PASS;
    }
    
    void set_placeholder(ns::String const& str)
    {
        this->_self.placeholder = str;
    }
    
    NSString* placeholder() const
    {
        return this->_self.placeholder;
    }
    
    void set_text(ns::String const& str)
    {
        this->_self.text = str;
    }
    
    void change_text(ns::String const& str)
    {
        [this->_self changeText:str];
    }
    
    ns::String text() const
    {
        return this->_self.text;
    }
    
    void set_padding(CGPadding const& padding)
    {
        this->_self.padding = padding;
    }

    void set_text(ui::Color const& cor)
    {
        this->_self.textColor = cor;
    }
    
    UIColor* text_color() const
    {
        return this->_self.textColor;
    }
    
    void set_font(ui::Font const& ft)
    {
        this->_self.font = ft;
    }
    
    UIFont* font() const
    {
        return this->_self.font;
    }
    
    void set_textalignment(UITextAlignment align)
    {
        this->_self.textAlignment = align;
    }
    
    UITextAlignment textalignment() const
    {
        return this->_self.textAlignment;
    }

    void set_borderstyle(UITextBorderStyle bs)
    {
        this->_self.borderStyle = bs;
    }
    
    UITextBorderStyle borderstyle() const
    {
        return this->_self.borderStyle;
    }
    
    void set_clearbegin(bool b)
    {
        this->_self.clearsOnBeginEditing = b;
    }
    
    bool is_clearbegin() const
    {
        return this->_self.clearsOnBeginEditing;
    }

    bool set_fitwidth(bool b)
    {
        this->_self.adjustsFontSizeToFitWidth = b;
    }
    
    void is_fitwidth() const
    {
        return this->_self.adjustsFontSizeToFitWidth;
    }
    
    void set_textstyle(cg::TextStyle const& ts)
    {
        [this->_self applyTextStyle:ts];
    }
    
    void set_validrestrict(ns::String const& str)
    {
        this->_self.validRestrict = str;
    }
    
    void set_invalidcolor(ui::Color const& color)
    {
        this->_self.invalidFontColor = color;
    }
    
    void set_invalidback(ui::Color const& color)
    {
        this->_self.invalidBackgroundColor = color;
    }

    bool is_valid() const
    {
        return this->_self.isValid;
    }
};

WSI_END_NS

typedef tpl::TextField<> TextField;

class SecureTextField
: public TextField
{
public:
    
    SecureTextField()
    {
        [this->_self setSecureTextEntry:YES];
    }
    
};

WSI_BEGIN_NS(tpl)

template <typename uiT = UISuggestTextField >
class SuggestTextField
: public TextField< uiT >
{
public:
    
    void reload()
    {
        if (items.count() == 0)
        {
            this->_self.datas = nil;
            return;
        }
        
        ns::MutableArray arr(items.count());
        for (uint i = 0; i < items.count(); ++i)
            arr.add(items[i]);
        this->_self.datas = arr;
    }
    
    core::vector<ns::String> items;
};

WSI_END_NS

typedef tpl::SuggestTextField<> SuggestTextField;

class HistoryTextField
: public tpl::SuggestTextField< UIHistoryTextField >
{
    
public:
    
    void set_identity(ns::String const& str)
    {
        this->_self.identity = str;
    }
    
    ns::String identity() const
    {
        return this->_self.identity;
    }
    
    void set_limit(uint cnt)
    {
        this->_self.limitCount = cnt;
    }
    
    uint limit() const
    {
        return this->_self.limitCount;
    }
    
protected:
    
    void reload();
    
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

WSI_END_HEADER_OBJC

# endif