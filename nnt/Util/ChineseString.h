
# ifndef __WSI_UTIL_CHINESESTRING_0DF8A61BC1C04347AD8782A469B4333A_H_INCLUDED
# define __WSI_UTIL_CHINESESTRING_0DF8A61BC1C04347AD8782A469B4333A_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface ChineseString : WSIObject

+ (NSString*)CharacterToPinYin:(NSString*)str;
+ (NSString*)CharacterToPinYin:(NSString*)str separator:(NSString*)separator;

+ (NSString*)CharacterToPinYin:(NSString*)str encoding:(NSStringEncoding)encoding;
+ (NSString*)CharacterToPinYin:(NSString*)str separator:(NSString*)separator encoding:(NSStringEncoding)encoding;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(util)
WSI_BEGIN_NS(lang)

class Chinese
{
public:
    
    static ns::String Pinyinize(ns::String const& str, NSStringEncoding encoding = NSUTF8StringEncoding)
    {
        return [ChineseString CharacterToPinYin:str encoding:encoding];
    }
    
    static ns::String Pinyinize(ns::String const& str, ns::String const& separ, NSStringEncoding encoding = NSUTF8StringEncoding)
    {
        return [ChineseString CharacterToPinYin:str separator:separ encoding:encoding];
    }
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif