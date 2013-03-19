
# ifndef __WSI_CODEC_EMOJI_59E7BA8B0A184B6AB1A1E694035EAB00_H_INCLUDED
# define __WSI_CODEC_EMOJI_59E7BA8B0A184B6AB1A1E694035EAB00_H_INCLUDED

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(sys)

class EmojiConverter
{
public:
    
    EmojiConverter();
    
public:
    
    static EmojiConverter& getInstance();
    
    //! from softbank to unicode if needed.
    core::string const& unicode(core::string const&) const;
    
    //! read.
    bool read_emoji(core::string::const_iterator&, core::string&);
    
protected:
    
    typedef core::twmap<core::string, core::string> map_type;
    map_type _map; // from softbank to unicode.
    
};

class EmojiVersion
{
public:
    
    EmojiVersion();
    
    static bool VERSION_SOFTBANK;
    static char CHAR_IDR;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif
