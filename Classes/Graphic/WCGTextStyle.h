
# ifndef __WSI_WCG_TEXTSTYLE_2BD7713DBD6A41DB956D48C3AC2988A9_H_INCLUDED
# define __WSI_WCG_TEXTSTYLE_2BD7713DBD6A41DB956D48C3AC2988A9_H_INCLUDED

# include "WCGColor.h"
# include "CGShadow.h"
# include "WCGDefines.h"

WSI_BEGIN_HEADER_OBJC

enum {
    WCGFontTypeRegular       = 0,
    WCGFontTypeBold          = 1,
    WCGFontTypeItalic        = 2,
    WCGFontTypeBoldItalic    = 3,
};

typedef uint WCGFontType;

@interface WCGTextStyle : NSObject <NSCoding, NSCopying, NSMutableCopying> {
    
    //! font name
    NSString *fontName;
    
    //! font size
	CGFloat fontSize;
    
    //! font color
    WCGColor *color;
    
    //! text alignment
    WCGAlignment alignment;
    
    //! line break
    IOSEXPRESS(UILineBreakMode) MACEXPRESS(NSLineBreakMode) linebreak;
    
    //! font type.
    WCGFontType fontType;
    
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
@property (readonly, assign, nonatomic)   WCGFontType fontType;
@property (readonly, copy, nonatomic)     WCGColor *color;
@property (readonly, assign, nonatomic)   WCGAlignment alignment;
@property (readonly, assign, nonatomic)   IOSEXPRESS(UILineBreakMode) MACEXPRESS(NSLineBreakMode) linebreak;
@property (readonly, copy, nonatomic)     CGShadow *textShadow;
@property (readonly, assign, nonatomic)   BOOL scaleToFit;
@property (readonly, assign, nonatomic)   real scaleToFitOffset, scaleToFitMax;
@property (readonly, assign, nonatomic)   real charRotation;

/// @name Factory Methods
/// @{
+(id)textStyle;
///	@}

# ifdef WSI_TARGET_IOS
- (UIFont*)uiFont;
# endif

# ifdef WSI_TARGET_MAC
- (NSDictionary*)uiFontAttributes;
# endif

//! calc string size.
- (CGSize)sizeOfString:(NSString*)string;

@end

@interface WCGMutableTextStyle : WCGTextStyle {
    
}

@property (readwrite, copy, nonatomic)    NSString *fontName;
@property (readwrite, assign, nonatomic)  CGFloat fontSize; 
@property (readwrite, assign, nonatomic)  WCGFontType fontType;
@property (readwrite, copy, nonatomic)    WCGColor *color;
@property (readwrite, assign, nonatomic)  WCGAlignment alignment;
@property (readwrite, assign, nonatomic)  IOSEXPRESS(UILineBreakMode) MACEXPRESS(NSLineBreakMode) linebreak;
@property (readwrite, copy, nonatomic)    CGShadow *textShadow;
@property (readwrite, assign, nonatomic)  BOOL scaleToFit;
@property (readwrite, assign, nonatomic)  real scaleToFitOffset, scaleToFitMax;
@property (readwrite, assign, nonatomic)   real charRotation;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cg)

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
    
    WCGFontType fonttype() const
    {
        return this->_self.fontType;
    }
    
    Color fontcolor() const
    {
        return Color(this->_self.color);
    }
    
    WCGAlignment alignment() const
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
    
# ifdef WSI_TARGET_IOS
    UIFont* uifont() const
    {
        return [this->_self uiFont];
    }
# endif
    
# ifdef WSI_TARGET_MAC
    
    NSDictionary* uifont() const
    {
        return [this->_self uiFontAttributes];
    }
    
# endif
    
};

class MutableTextStyle
: public _TextStyle<WCGMutableTextStyle>
{
public:        
    
    MutableTextStyle()
    {
        PASS;
    }
    
    MutableTextStyle(ns::String const& name,
                     real size,
                     Color const& color,
                     WCGFontType type = WCGFontTypeRegular,
                     WCGAlignment align = WCGAlignmentCenter)
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
                     WCGFontType type = WCGFontTypeRegular,
                     WCGAlignment align = WCGAlignmentCenter)
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
    
    void set_fonttype(WCGFontType type)
    {
        this->_self.fontType = type;
    }
    
    void set_fontcolor(Color const& color)
    {
        this->_self.color = color;
    }
    
    void set_alignment(WCGAlignment align)
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
: public _TextStyle<WCGTextStyle>
{
    typedef _TextStyle<WCGTextStyle> super;
    
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif