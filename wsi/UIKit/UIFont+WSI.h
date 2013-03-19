
# ifndef __WSI_UIKIT_FONT_E058459450D74DD7BCBCA0A6E5AAC585_H_INCLUDED
# define __WSI_UIKIT_FONT_E058459450D74DD7BCBCA0A6E5AAC585_H_INCLUDED

WSI_BEGIN_HEADER_OBJC


WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class Font
: public ns::Object<UIFont>
{
    typedef ns::Object<UIFont> super;
    
public:
        
    Font(ns::String const& name, real size)
    : super(nil)
    {
        this->_self = [[UIFont fontWithName:name size:size] retain];
    }
    
    Font(Font const& r)
    : super(r._self)
    {
        PASS;
    }
    
    Font(UIFont* r)
    : super(r)
    {
        PASS;
    }
    
    static Font System(real size)
    {
        return Font([UIFont systemFontOfSize:size]);
    }
    
    static Font BoldSystem(real size)
    {
        return Font([UIFont boldSystemFontOfSize:size]);
    }
    
    static Font ItalicSystem(real size)
    {
        return Font([UIFont italicSystemFontOfSize:size]);
    }
    
    ns::String family_name() const
    {
        return this->_self.familyName;
    }
    
    ns::String font_name() const
    {
        return this->_self.fontName;
    }
    
    real point_size() const
    {
        return this->_self.pointSize;
    }
    
    real ascender() const
    {
        return this->_self.ascender;
    }
    
    real descender() const
    {
        return this->_self.descender;
    }
    
    real cap_height() const
    {
        return this->_self.capHeight;
    }
    
    real x_height() const
    {
        return this->_self.xHeight;
    }
    
    real line_height() const
    {
        return this->_self.lineHeight;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
