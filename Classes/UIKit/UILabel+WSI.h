
# ifndef __NNT_UIKIT_UILABEL_25522F6AFF374CD9874B033B280994A7_H_INCLUDED
# define __NNT_UIKIT_UILABEL_25522F6AFF374CD9874B033B280994A7_H_INCLUDED

# import "UIControl+NNT.h"

// thanks to FontLabel of Zynga Game Networks.

NNT_BEGIN_HEADER_OBJC

//@class ZFont;
//@class ZAttributedString;

@interface UILabel (NNT)

NNTUIVIEW_NOTINHERIT_MUST_DECL;

//! set textstyle.
- (void)applyTextStyle:(WCGTextStyle*)ts;

@end

@interface NNTUILabel : UILabel {
    NNTOBJECT_DECL;
    
    //! background fill.
    WCGFill *_backgroundFill;
        
    //! works around a bug in UILabel
    void *_reserved;
    
    //! z font.
	//ZFont *zFont;
    
    //! z string.
	//ZAttributedString *zAttributedText;
            
    //! send global event.
    BOOL _sendGlobalEvent;
    
    //! scale to fit. default is NO.
    BOOL _scaleToFit;
    
}

@property (nonatomic, assign) BOOL multiLines;
@property (nonatomic, assign) BOOL scaleToFit;
@property (nonatomic, retain) WCGFill *backgroundFill;
//@property (nonatomic, retain, setter=setZFont:) ZFont *zFont;
//@property (nonatomic, copy) ZAttributedString *zAttributedText;
@property (nonatomic, assign) BOOL sendGlobalEvent;

NNTOBJECT_PROP;

- (id)initWithFrame:(CGRect)frame;

//! copy style.
- (void)copyStyle:(UILabel*)r;

//! text size.
- (CGSize)textSize;

//! text size for string.
- (CGSize)textSize:(NSString*)str;

//! text size.
- (CGSize)directTextSize;

//! text size for multilines.
- (CGSize)textsSize;

//! get the fitable font size.
- (real)fitableFontSize;

@end

NNTDECL_PRIVATE_HEAD(UIMarqueeLabel);

@interface UIMarqueeLabel : NNTUILabel {
    
    //! marquee's step(default is 1) and speed(default is 10ms).
    int _marqueeStep;
    int _marqueeSpeed;
    
    NNTDECL_PRIVATE(UIMarqueeLabel);
}

@property (nonatomic, assign) int marqueeStep, marqueeSpeed;

- (void)start;
- (void)stop;

@end

/*
 
@interface NNTUILabel (FontLabel)

@property (nonatomic, setter=setCGFont:) CGFontRef cgFont __AVAILABILITY_INTERNAL_DEPRECATED;
@property (nonatomic, assign) CGFloat pointSize __AVAILABILITY_INTERNAL_DEPRECATED;

// if attributedText is nil, fall back on using the inherited UILabel properties
// if attributedText is non-nil, the font/text/textColor
// in addition, adjustsFontSizeToFitWidth does not work with attributed text

// -initWithFrame:fontName:pointSize: uses FontManager to look up the font name
- (id)initWithFrame:(CGRect)frame fontName:(NSString *)fontName pointSize:(CGFloat)pointSize;
//- (id)initWithFrame:(CGRect)frame zFont:(ZFont *)font;
- (id)initWithFrame:(CGRect)frame font:(CGFontRef)font pointSize:(CGFloat)pointSize __AVAILABILITY_INTERNAL_DEPRECATED;

@end
 
 */

NNTDECL_CATEGORY(UILabel, NNT);

//! @class UIStyleLabel
//! @code @"<text style=\"font-size:20;font-color:#FF0000;\">RED</text><text style=\"font-size:40;font-color:#0000FF;\">BLUE</text>"
@interface UIStyleLabel : NNTUILabel {
    NSArray* styleStrings;
}

@property (nonatomic, retain) NSArray* styleStrings;

@end

//! emit while marquee running at the end.
NNT_EXTERN signal_t kSignalMarqueeNext;

# ifdef NNT_CXX

_CXXCONTROL_DECL(NNTUILabel);
_CXXCONTROL_DECL(UIMarqueeLabel);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

NNT_BEGIN_NS(tpl)

template <typename implT, typename labelT>
class Label
: public Control<implT, labelT>
{
    typedef Control<implT, labelT> super;
    typedef implT self_type;
    
public:
    
    Label()
    {
        PASS;
    }
    
    Label(id lbl)
    : super((labelT*)lbl, false)
    {
        PASS;
    }
    
    Label(ns::String const& name)
    {
        this->_self.text _assign_ name;
    }
    
    virtual ~Label()
    {
        PASS;
    }
    
    self_type& operator = (self_type const& r)
    {
        this->_set(r);
        return *this;
    }
        
    void set_text(ns::String const& str)
    {
        this->_self.text _assign_ str;
    }
    
    void set_textstyle(cg::TextStyle const& ts)
    {
        uint align;
        switch (ts.alignment())
        {
            case WCGAlignmentLeft: align = TextAlignment<Left>(); break;
            case WCGAlignmentRight: align = TextAlignment<Right>(); break;
            default: align = TextAlignment<Center>(); break;
        }
        this->_self.textAlignment = (UITextAlignment)align;
        this->_self.textColor _assign_ ui::Color(ts.fontcolor());
        this->_self.shadowColor _assign_ ui::Color(ts.shadow().color());
        this->_self.font = ts.uifont();
    }
    
    void set_alignment(UITextAlignment align)
    {
        this->_self.textAlignment = align;
    }
    
    void set_font(cg::TextStyle const& ts)
    {
        this->_self.font = ts.uifont();
    }
    
    void set_fontcolor(Color const& color)
    {
        this->_self.textColor = color;
    }
    
    void set_font(UIFont* font)
    {
        this->_self.font = font;
    }
    
    ns::String text()
    {
        return this->_self.text;
    }
         
    UITextAlignment alignment() const
    {
        return this->_self.textAlignment;
    }
    
    void set_linebreak(UILineBreakMode mode)
    {
        this->_self.lineBreakMode = mode;
    }
    
    UILineBreakMode linebreak() const
    {
        return this->_self.lineBreakMode;
    }
    
    void set_multilines(bool val = core::enable)
    {
        this->_self.multiLines = val;
    }
    
    bool is_multilines() const
    {
        return this->_self.multiLines;
    }
    
    cg::Size textsize() const
    {
        return [this->_self textSize];
    }
    
    cg::Size textsize(ns::String const& str) const
    {
        return [this->_self textSize:str];
    }
    
};
    
NNT_END_NS
    
class Label
: public tpl::Label<Label, _CXXCONTROL(NNTUILabel)>
{
    
    typedef tpl::Label<Label, _CXXCONTROL(NNTUILabel)> super;
  
public:
    
    Label()
    {
        PASS;
    }
    
    Label(NNTUILabel* lbl)
    : super(lbl)
    {
        PASS;
    }
    
    Label(ns::String const& name)
    : super(name)
    {
        PASS;
    }
    
};
    
class MarqueeLabel
: public tpl::Label<MarqueeLabel, _CXXCONTROL(UIMarqueeLabel)>
{
    
    typedef tpl::Label<MarqueeLabel, _CXXCONTROL(UIMarqueeLabel)> super;
        
public:
    
    MarqueeLabel()
    {
        PASS;
    }
    
    MarqueeLabel(NNTUILabel* lbl)
    : super(lbl)
    {
        PASS;
    }
    
    MarqueeLabel(ns::String const& name)
    : super(name)
    {
        PASS;
    }
    
    void start()
    {
        [this->_self start];
    }
    
    void stop()
    {
        [this->_self stop];
    }
        
    void set_step(int val)
    {
        this->_self.marqueeStep = val;
    }
    
    void set_speed(int val)
    {
        this->_self.marqueeSpeed = val;
    }
    
    void set_textstyle(cg::TextStyle const& ts)
    {
        cg::MutableTextStyle style = ts.clone<cg::MutableTextStyle>();
        style.set_alignment(WCGAlignmentLeft);
        super::set_textstyle(style);
    }
    
protected:
    
    void set_alignment(UITextAlignment align);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif