
# include "Core.h"
# include "String+WSI.h"
# include <CommonCrypto/CommonDigest.h>

WSI_BEGIN_C

uchar crd(char c) {
    for (int i = 0; i < 10; ++i) {
        if (MAP_BINARY_ASCII_LOWER[i] == c)
            return i;
    }
    for (int i = 10; i < 16; ++i) {
        if (MAP_BINARY_ASCII_LOWER[i] == c)
            return i;
        else if (MAP_BINARY_ASCII[i] == c)
            return i;
    }
    return 0;
}

int str_indexof_char(char const* __str, char c, int len, int offset) {
    char const* str = __str + offset;
    len = (len == -1) ? (int)strlen(str) : len;
    int bound = len - offset;
    for (int i = 0; i < bound; ++i) {
        if (*str++ == c) {
            return i;
        }
    }
    return -1;
}

WSI_END_C

WSI_BEGIN_OBJC

@implementation WSIString

- (NSString*)uniqueIdentify {
    return [[NSNumber numberWithUnsignedInteger:[self hash]] stringValue];
}

@end

CFStringEncoding CFStringEncodingFromWindowsLocaleCode(udword lang) {
    CFStringEncoding ret = kCFStringEncodingUTF8;
    switch (lang) {
        case 1095: ret = kCFStringEncodingMacGujarati; break;
        case 1099: ret = kCFStringEncodingMacKannada; break;
        case 1097: ret = kCFStringEncodingMacTamil; break;
        case 1079: ret = kCFStringEncodingMacGeorgian; break;
        case 1067: ret = kCFStringEncodingMacArmenian; break;
        case 1098: ret = kCFStringEncodingMacTelugu; break;
        case 1054: ret = kCFStringEncodingMacThai; break;
        case 1041: ret = kCFStringEncodingMacJapanese; break;
        case 4100: ret = kCFStringEncodingMacChineseSimp; break;
        case 2052: ret = kCFStringEncodingGB_18030_2000; break;
        case 1042: ret = kCFStringEncodingMacKorean; break;
        case 1028: ret = kCFStringEncodingMacChineseTrad; break;
        case 5124: ret = kCFStringEncodingGB_18030_2000; break;
        case 3076: ret = kCFStringEncodingGB_18030_2000; break;
        case 1048: ret = kCFStringEncodingMacRomanian; break;
    }
    return ret;
}

WSI_END_OBJC

WSI_BEGIN_CXX 
WSI_BEGIN_NS(wtl)

core::string tostr(NSString* str) {
    char const* pstr = [str UTF8String];
    if (pstr == NULL)
        return core::null_string;
    return pstr;
}

bool tobool(NSString* str) {
    if ([str isEqualToString:@"0"])
        return false;
    return ![str isEqualToString:kNSStringNO];
}

int toint(NSString* str) {
    return [str intValue];
}

uint touint(NSString* str) {
    return [str intValue];
}

short toshort(NSString* str) {
    return [str intValue];
}

ushort toushort(NSString* str) {
    return [str intValue];
}

long tolong(NSString* str) {
    return [str intValue];
}

ulong toulong(NSString* str) {
    return [str intValue];
}

float tofloat(NSString* str) {
    return [str floatValue];
}

double todouble(NSString* str) {
    return [str doubleValue];
}

real toreal(NSString* str) {
# ifdef REAL_IS_DOUBLE
    return [str doubleValue];
# else
    return [str floatValue];
# endif
}

WSI_END_NS 
WSI_END_CXX
