
# ifndef __NNT_UITEXTVIEW_1F3A3F9EBAC743E6811BE80C7CE54B33_H_INCLUDED
# define __NNT_UITEXTVIEW_1F3A3F9EBAC743E6811BE80C7CE54B33_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTUITextView : UITextView {
    
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

//! append one line.
- (void)appendLine:(NSString*)line;

//! apply text style.
- (void)applyTextStyle:(NgTextStyle*)ts;

//! scroll to end.
- (void)scrollToEnd;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class TextView
: public View<TextView, NNTUITextView>
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
    
    void set_alignment(uint align)
    {
        this->_self.textAlignment = (NSTextAlignment)align;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif