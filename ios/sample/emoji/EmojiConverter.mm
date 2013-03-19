
# include "WSIFoundation.h"
# include "EmojiConverter.h"
# include "EmojiCodec.h"

WSIAPP_BEGIN

EmojiConverter::EmojiConverter()
{
    sys::EmojiConverter& emoji = sys::EmojiConverter::getInstance();

    // make map.
    _map.insert("0", emoji.unicode("\ue410"));
    _map.insert("1", emoji.unicode("\ue407"));
    _map.insert("2", emoji.unicode("\ue106"));
    _map.insert("3", emoji.unicode("\ue408"));
    _map.insert("4", emoji.unicode("\ue402"));
    _map.insert("5", emoji.unicode("\ue411"));
    _map.insert("6", emoji.unicode("\ue40d"));
    _map.insert("7", emoji.unicode("\ue058"));
    _map.insert("8", emoji.unicode("\ue40a"));
    _map.insert("9", emoji.unicode("\ue412"));

    _map.insert("10", emoji.unicode("\ue108"));
    _map.insert("11", emoji.unicode("\ue416"));
    _map.insert("12", emoji.unicode("\ue056"));
    _map.insert("13", emoji.unicode("\ue415"));
    _map.insert("14", emoji.unicode("\ue405"));
    _map.insert("15", emoji.unicode("\ue403"));
    _map.insert("16", emoji.unicode("\ue059"));
    _map.insert("17", emoji.unicode("\ue40c"));
    _map.insert("18", emoji.unicode("\ue107"));
    _map.insert("19", emoji.unicode("\ue40b"));

    _map.insert("20", emoji.unicode("\ue409"));
    _map.insert("21", emoji.unicode("\ue057"));
    _map.insert("22", emoji.unicode("\ue419"));
    _map.insert("23", emoji.unicode("\ue40e"));
    _map.insert("24", emoji.unicode("\ue105"));
    _map.insert("25", emoji.unicode("\ue406"));
    _map.insert("26", emoji.unicode("\ue40f"));
    _map.insert("27", emoji.unicode("\ue401"));
    _map.insert("28", emoji.unicode("\ue404"));
    _map.insert("29", emoji.unicode("\ue51b"));

    _map.insert("30", emoji.unicode("\ue11a"));
    _map.insert("31", emoji.unicode("\ue325"));
    _map.insert("32", emoji.unicode("\ue52f"));
    _map.insert("33", emoji.unicode("\ue22e"));
    _map.insert("34", emoji.unicode("\ue335"));
    _map.insert("35", emoji.unicode("\ue413"));
    _map.insert("36", emoji.unicode("\ue10c"));
    _map.insert("37", emoji.unicode("\ue11c"));
    _map.insert("38", emoji.unicode("\ue116"));
    _map.insert("39", emoji.unicode("\ue41e"));

    _map.insert("40", emoji.unicode("\ue330"));
    _map.insert("41", emoji.unicode("\ue331"));
    _map.insert("42", emoji.unicode("\ue111"));
    _map.insert("43", emoji.unicode("\ue429"));
    _map.insert("44", emoji.unicode("\ue114"));
    _map.insert("45", emoji.unicode("\ue002"));
    _map.insert("46", emoji.unicode("\ue10b"));
    _map.insert("47", emoji.unicode("\ue04f"));
    _map.insert("48", emoji.unicode("\ue052"));
    _map.insert("49", emoji.unicode("\ue428"));

    _map.insert("50", emoji.unicode("\ue12f"));
    _map.insert("51", emoji.unicode("\ue10f"));
    _map.insert("52", emoji.unicode("\ue044"));
    _map.insert("53", emoji.unicode("\ue34b"));
    _map.insert("54", emoji.unicode("\ue443"));
    _map.insert("55", emoji.unicode("\ue311"));
    _map.insert("56", emoji.unicode("\ue043"));
    _map.insert("57", emoji.unicode("\ue42b"));
    _map.insert("58", emoji.unicode("\ue326"));
    _map.insert("59", emoji.unicode("\ue05a"));

    _map.insert("60", emoji.unicode("\ue147"));
    _map.insert("61", emoji.unicode("\ue33e"));
    _map.insert("62", emoji.unicode("\ue30f"));
    _map.insert("63", emoji.unicode("\ue032"));
    _map.insert("64", emoji.unicode("\ue119"));
    _map.insert("65", emoji.unicode("\ue003"));
    _map.insert("66", emoji.unicode("\ue437"));
    _map.insert("67", emoji.unicode("\ue023"));
    _map.insert("68", emoji.unicode("\ue11e"));
    _map.insert("69", emoji.unicode("\ue112"));

    _map.insert("70", emoji.unicode("\ue009"));
    _map.insert("71", emoji.unicode("\ue02d"));
    _map.insert("72", emoji.unicode("\ue103"));
    _map.insert("73", emoji.unicode("\ue12a"));
    _map.insert("74", emoji.unicode("\ue305"));
    _map.insert("75", emoji.unicode("\ue04c"));
    _map.insert("76", emoji.unicode("\ue00e"));
    _map.insert("77", emoji.unicode("\ue421"));
    _map.insert("78", emoji.unicode("\ue41f"));
    _map.insert("79", emoji.unicode("\ue420"));

    _map.insert("80", emoji.unicode("\ue527"));
    _map.insert("81", emoji.unicode("\ue005"));
    _map.insert("82", emoji.unicode("\ue518"));
    _map.insert("83", emoji.unicode("\ue51a"));
    _map.insert("84", emoji.unicode("\ue055"));
    _map.insert("85", emoji.unicode("\ue41c"));
    _map.insert("86", emoji.unicode("\ue11d"));
    _map.insert("87", emoji.unicode("\ue30b"));
    _map.insert("88", emoji.unicode("\ue047"));
    _map.insert("89", emoji.unicode("\ue348"));

    _map.insert("90", emoji.unicode("\ue43c"));
    _map.insert("91", emoji.unicode("\ue44c"));
    _map.insert("92", emoji.unicode("\ue448"));
    _map.insert("93", emoji.unicode("\ue335"));
    _map.insert("94", emoji.unicode("\ue139"));
    _map.insert("95", emoji.unicode("\ue138"));
}

EmojiConverter& EmojiConverter::getInstance()
{
    static EmojiConverter __gs_emoji;
    return __gs_emoji;
}

core::string EmojiConverter::toemoji(core::string const& str) const
{
    map_type::left_map_type::const_iterator found = _map.left_map.find(str);
    if (found == _map.left_map.end())
        return " ";
    return found->second;
}

core::string EmojiConverter::fromemoji(core::string const& str) const
{
    map_type::right_map_type::const_iterator found = _map.right_map.find(str);
    if (found == _map.right_map.end())
        return " ";
    return found->second;
}

uint EmojiConverter::size() const
{
    return _map.left_map.size();
}

ns::MutableArray EmojiConverter::emojis() const
{
    ns::MutableArray emojis;
    for (uint idx = 0; idx < size(); ++idx)
    {
        emojis << ns::String(EmojiConverter::getInstance().toemoji(core::tostr(idx)));
    }
    return emojis;
}

WSIAPP_END