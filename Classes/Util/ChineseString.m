
# import "Core.h"
# import "ChineseString.h"
# import "Char+NNT.h"

NNT_BEGIN_OBJC

@implementation ChineseString

+ (NSString*)CharacterToPinYin:(NSString *)str {
    NSData* data = [str dataUsingEncoding:NSGB18030Encoding];
    NSArray* arr = chinese2pinyin_stream([data bytes], [data length]);
    return [arr componentsJoinedByString:@""];
}

+ (NSString*)CharacterToPinYin:(NSString *)str separator:(NSString *)separator {
    NSData* data = [str dataUsingEncoding:NSGB18030Encoding];
    NSArray* arr = chinese2pinyin_stream([data bytes], [data length]);
    return [arr componentsJoinedByString:separator];
}

+ (NSString*)CharacterToPinYin:(NSString*)str encoding:(NSStringEncoding)encoding {
    NSData* data = [str dataUsingEncoding:encoding];
    NSArray* arr = chinese2pinyin_stream([data bytes], [data length]);
    return [arr componentsJoinedByString:@""];
}

+ (NSString*)CharacterToPinYin:(NSString*)str separator:(NSString*)separator encoding:(NSStringEncoding)encoding {
    NSData* data = [str dataUsingEncoding:encoding];
    NSArray* arr = chinese2pinyin_stream([data bytes], [data length]);
    return [arr componentsJoinedByString:separator];
}

@end

NNT_END_OBJC