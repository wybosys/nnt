
# ifndef __NNT_Ng_TEXTSTYLE_2BD7713DBD6A41DB956D48C3AC2988A9_H_INCLUDED
# define __NNT_Ng_TEXTSTYLE_2BD7713DBD6A41DB956D48C3AC2988A9_H_INCLUDED

# include "NGColor.h"
# include "NGShadow.h"
# include "NGDefines.h"

NNT_BEGIN_HEADER_OBJC

enum {
    NgFontTypeRegular       = 0,
    NgFontTypeBold          = 1,
    NgFontTypeItalic        = 2,
    NgFontTypeBoldItalic    = 3,
};

typedef uint NgFontType;

@interface NgTextStyle : NSObject <NSCoding, NSCopying, NSMutableCopying> {
    
    //! font name
    NSString *fontName;
    
    //! font size
	CGFloat fontSize;
    
    //! font color
    NgColor *color;
    
    //! text alignment
    NgAlignment alignment;
    
    //! line break
    IOSEXPRESS(UILineBreakMode) MACEXPRESS(NSLineBreakMode) linebreak;
    
    //! font type.
    NgFontType fontType;
    
    //! shadow
    CGShadow *textShadow;
    
    //! auto select font size while drawing. default is NO.
    BOOL scaleToFit;
    real scaleToFitOffset;
    real scaleToFitMax;
    
    //! char rotation, default is 0.
    real charRotation;
}

@property (readonly, copy, nonatomic)     NSString *fontName;
@property (readonly, assign, nonatomic)   CGFloat fontSize; 
@property (readonly, assign, nonatomic)   NgFontType fontType;
@property (readonly, copy, nonatomic)     NgColor *color;
@property (readonly, assign, nonatomic)   NgAlignment alignment;
@property (readonly, assign, nonatomic)   IOSEXPRESS(UILineBreakMode) MACEXPRESS(NSLineBreakMode) linebreak;
@property (readonly, copy, nonatomic)     CGShadow *textShadow;
@property (readonly, assign, nonatomic)   BOOL scaleToFit;
@property (readonly, assign, nonatomic)   real scaleToFitOffset, scaleToFitMax;
@property (readonly, assign, nonatomic)   real charRotation;

/// @name Factory Methods
/// @{
+(id)textStyle;
///	@}

# ifdef NNT_TARGET_IOS
- (UIFont*)uiFont;
# endif

# ifdef NNT_TARGET_MAC
- (NSDictionary*)uiFontAttributes;
# endif

//! calc string size.
- (CGSize)sizeOfString:(NSString*)string;

@end

@interface NgMutableTextStyle : NgTextStyle {
    
}

@property (readwrite, copy, nonatomic)    NSString *fontName;
@property (readwrite, assign, nonatomic)  CGFloat fontSize; 
@property (readwrite, assign, nonatomic)  NgFontType fontType;
@property (readwrite, copy, nonatomic)    NgColor *color;
@property (readwrite, assign, nonatomic)  NgAlignment alignment;
@property (readwrite, assign, nonatomic)  IOSEXPRESS(UILineBreakMode) MACEXPRESS(NSLineBreakMode) linebreak;
@property (readwrite, copy, nonatomic)    CGShadow *textShadow;
@property (readwrite, assign, nonatomic)  BOOL scaleToFit;
@property (readwrite, assign, nonatomic)  real scaleToFitOffset, scaleToFitMax;
@property (readwrite, assign, nonatomic)   real charRotation;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

template <typename styleT>
class _TextStyle
: public ns::Object<styleT>
{
    
    typedef _TextStyle<styleT> self_type;
    typedef ns::Object<styleT> super;

public:
    
    _TextStyle()
    {
        PASS;
    }
    
    _TextStyle(styleT* sty)
    : super(sty)
    {
        PASS;
    }
    
    ns::String fontname() const
    {
        return this->_self.fontName;
    }
    
    real fontsize() const
    {
        return this->_self.fontSize;
    }
    
    NgFontType fonttype() const
    {
        return this->_self.fontType;
    }
    
    Color fontcolor() const
    {
        return Color(this->_self.color);
    }
    
    NgAlignment alignment() const
    {
        return this->_self.alignment;
    }
    
    real charrotation() const
    {
        return this->_self.charRotation;
    }
    
    Shadow shadow() const
    {
        return this->_self.textShadow;
    }
    
# ifdef NNT_TARGET_IOS
    UIFont* uifont() const
    {
        return [this->_self uiFont];
    }
# endif
    
# ifdef NNT_TARGET_MAC
    
    NSDictionary* uifont() const
    {
        return [this->_self uiFontAttributes];
    }
    
# endif
    
};

class MutableTextStyle
: public _TextStyle<NgMutableTextStyle>
{
public:        
    
    MutableTextStyle()
    {
        PASS;
    }
    
    MutableTextStyle(ns::String const& name,
                     real size,
                     Color const& color,
                     NgFontType type = NgFontTypeRegular,
                     NgAlignment align = NgAlignmentCenter)
    {
        set_fontname(name);
        set_fontsize(size);
        set_fontcolor(color);
        set_fonttype(type);
        set_alignment(align);
    }
    
    MutableTextStyle(
                     real size,
                     Color const& color,
                     NgFontType type = NgFontTypeRegular,
                     NgAlignment align = NgAlignmentCenter)
    {
        set_fontsize(size);
        set_fontcolor(color);
        set_fonttype(type);
        set_alignment(align);
    }
    
    void set_fontname(ns::String const& str)
    {
        this->_self.fontName = str;
    }
    
    void set_fontsize(real sz)
    {
        this->_self.fontSize = sz;
    }
    
    void set_fonttype(NgFontType type)
    {
        this->_self.fontType = type;
    }
    
    void set_fontcolor(Color const& color)
    {
        this->_self.color = color;
    }
    
    void set_alignment(NgAlignment align)
    {
        this->_self.alignment = align;
    }

    void set_charrotation(real val)
    {
        this->_self.charRotation = val;
    }
    
    void set_shadow(Shadow const& sd)
    {
        this->_self.textShadow = sd;
    }
    
};

class TextStyle
: public _TextStyle<NgTextStyle>
{
    typedef _TextStyle<NgTextStyle> super;
    
public:
    
    TextStyle()
    {
        PASS;
    }
    
    TextStyle(MutableTextStyle const& r)
    : super(r)
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif