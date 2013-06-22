
# ifndef __NNT_UTIL_CHINESESTRING_0DF8A61BC1C04347AD8782A469B4333A_H_INCLUDED
# define __NNT_UTIL_CHINESESTRING_0DF8A61BC1C04347AD8782A469B4333A_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface ChineseString : NNTObject

+ (NSString*)CharacterToPinYin:(NSString*)str;
+ (NSString*)CharacterToPinYin:(NSString*)str separator:(NSString*)separator;

+ (NSString*)CharacterToPinYin:(NSString*)str encoding:(NSStringEncoding)encoding;
+ (NSString*)CharacterToPinYin:(NSString*)str separator:(NSString*)separator encoding:(NSStringEncoding)encoding;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(util)
NNT_BEGIN_NS(lang)

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

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif