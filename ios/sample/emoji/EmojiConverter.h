
# ifndef __EMOJICONVERTER_D04599CA31BD4865A1D03E2B5640707C_H_INCLUDED
# define __EMOJICONVERTER_D04599CA31BD4865A1D03E2B5640707C_H_INCLUDED

WSIAPP_BEGIN

class EmojiConverter
{
public:

    EmojiConverter();

    static EmojiConverter& getInstance();

public:

    core::string toemoji(core::string const&) const;
    core::string fromemoji(core::string const&) const;
    uint size() const;
    ns::MutableArray emojis() const;
protected:

    // am <=> emoji
    typedef core::twmap<core::string, core::string> map_type;
    map_type _map;

};

WSIAPP_END

# endif 