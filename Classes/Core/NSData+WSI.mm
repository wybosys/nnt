
# import "Core.h"
# import "NSData+NNT.h"
# import <zlib.h>
# include <CommonCrypto/CommonDigest.h>
# import "coretypes.h"

NNT_BEGIN_OBJC

@implementation NSData (NNT)

- (NSData*)encodeBinaryString {    
    NSUInteger len = [self length];
    char const* each = (char const*)[self bytes];
    NSMutableData *ret = [NSMutableData dataWithLength:(len << 1)];
    char *bytes = (char*)[ret mutableBytes];
    while ( len-- ) {
        bytes[0] = MAP_BINARY_ASCII[b8_h(*each)];
        bytes[1] = MAP_BINARY_ASCII[b8_l(*each)];
        bytes += 2;
        ++each;
    }
    return ret;    
}

- (void)encodeBinaryStringEx:(NSMutableData*)data {
    NSUInteger len = [self length];
    char const* each = (char const*)[self bytes];
    [data initWithLength:(len << 1)];
    char *bytes = (char*)[data mutableBytes];
    while ( len-- ) {
        bytes[0] = MAP_BINARY_ASCII[b8_h(*each)];
        bytes[1] = MAP_BINARY_ASCII[b8_l(*each)];
        bytes += 2;
        ++each;
    }
}

- (NSData*)decodeBinaryString {
    NSUInteger len = [self length];
    len >>= 1;
    
    short_b8 const* each = (short_b8 const*)[self bytes];
    NSMutableData *ret = [NSMutableData dataWithLength:(len)];
    char *bytes = (char*)[ret mutableBytes];
    while ( len-- ) {
        char h = MAP_ASCII_BINARY_MATCH[each->_0];
        char l = MAP_ASCII_BINARY_MATCH[each->_1];
        
        if (h != -1 &&
            l != -1) {
            *bytes++ = b8_make(h, l);
        }
        
        ++each;
    }
    return ret;
}

- (void)decodeBinaryStringEx:(NSMutableData*)data {
    NSUInteger len = [self length];
    len >>= 1;
    
    short_b8 const* each = (short_b8 const*)[self bytes];
    [data initWithLength:(len)];
    char *bytes = (char*)[data mutableBytes];
    while ( len-- ) {
        char h = MAP_ASCII_BINARY_MATCH[each->_0];
        char l = MAP_ASCII_BINARY_MATCH[each->_1];
        
        if (h != -1 &&
            l != -1) {
            *bytes++ = b8_make(h, l);
        }
        
        ++each;
    }
}

- (NSData*)md5 {
    NSMutableData *data = [NSMutableData dataWithLength:CC_MD5_DIGEST_LENGTH];
    CC_MD5((void*)[self bytes], (CC_LONG)[self length], (uchar*)[data mutableBytes]);
    return data;
}

- (void)md5ex:(NSMutableData*)data {
    [data initWithLength:CC_MD5_DIGEST_LENGTH];
    CC_MD5((void*)[self bytes], (CC_LONG)[self length], (uchar*)[data mutableBytes]);
}

- (uint)coreType {
    return CoreTypeData;
}

@end

NNTIMPL_CATEGORY(NSData, NNT);

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ns)

Data null_data;

NNT_END_NS
NNT_END_CXX
