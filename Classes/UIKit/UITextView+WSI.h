
# ifndef __WSI_UITEXTVIEW_1F3A3F9EBAC743E6811BE80C7CE54B33_H_INCLUDED
# define __WSI_UITEXTVIEW_1F3A3F9EBAC743E6811BE80C7CE54B33_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WSIUITextView : UITextView {
    
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

//! append one line.
- (void)appendLine:(NSString*)line;

//! apply text style.
- (void)applyTextStyle:(WCGTextStyle*)ts;

//! scroll to end.
- (void)scrollToEnd;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class TextView
: public View<TextView, WSIUITextView>
{
public:
    
    void append(ns::String const& str)
    {
        [this->_self appendLine:str];
    }
    
    void set_editable(bool val = true)
    {
        this->_self.editable = val;
    }
    
    void set_readonly(bool val = true)
    {
        set_editable(!val);
    }
    
    bool editable() const
    {
        return this->_self.editable;
    }
    
    void set_text(ns::String const& str)
    {
        this->_self.text _assign_ str;
    }
    
    ns::String text() const
    {
        return this->_self.text;
    }
    
    void set_textstyle(cg::TextStyle const& ts)
    {
        [this->_self applyTextStyle:ts];
    }
    
    void layout_subviews() {}
    
    void scrollto_end()
    {
        [this->_self scrollToEnd];
    }
    
    void set_font(ui::Font const& font)
    {
        this->_self.font = font;
    }
    
    void set_font(ui::Color const& color)
    {
        this->_self.textColor = color;
    }
    
    void set_alignment(UITextAlignment align)
    {
        this->_self.textAlignment = align;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif