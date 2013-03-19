
# import "Core.h"
# import "NSString+NNT.h"
# import "NSData+NNT.h"
# import <CommonCrypto/CommonHMAC.h>

NNT_BEGIN_HEADER_OBJC

# import "RegexKitLite.h"

NNT_END_HEADER_OBJC

# ifdef NNT_USE_BASE64
#   import <Google/GTMBase64.h>
# endif

# import "coretypes.h"

NNT_BEGIN_OBJC

NSStringEncoding NSGB18030Encoding = 0x80000632;
NSStringEncoding NSGB2312Encoding = 0x80000630;
NSStringEncoding NSGBKEncoding = 0x80000631;
NSStringEncoding NSGig5Encoding = 0x80000A03;

//CFStringConvertEncodingToNSStringEncoding kCFStringEncodingGB_18030_2000

NSString* GetStringEncodingName(NSStringEncoding encoding)
{
    if (encoding == NSUTF8StringEncoding)
        return @"utf-8";
    else if (encoding == NSGB18030Encoding)
        return @"gb18030";
    else if (encoding == NSGB2312Encoding)
        return @"gb2312";
    else if (encoding == NSGBKEncoding)
        return @"gbk";
    else if (encoding == NSGig5Encoding)
        return @"big5";
    return @"utf-8";
}

@implementation NSString (NNT)

- (NSString*)encodeBinaryString:(NSStringEncoding)encoding {
    NSMutableData* data = [NSMutableData alloc];
    [[self dataUsingEncoding:encoding] encodeBinaryStringEx:data];
    NSString *str = [[NSString alloc] initWithData:data encoding:encoding];
    [data release];
    return [str autorelease];
}

- (NSString*)decodeBinaryString:(NSStringEncoding)encoding {
    NSMutableData *data = [NSMutableData alloc];
    [[self dataUsingEncoding:encoding] decodeBinaryStringEx:data];
    NSString *str = [[NSString alloc] initWithData:data encoding:encoding];
    [data release];
    return [str autorelease];
}

- (NSString*)toUnicodeString {    
    // to data.
    NSData* tmp = [self dataUsingEncoding:NSUTF16BigEndianStringEncoding];
    
    // encode to binary with insert '\u'
    NSUInteger len = [tmp length];
    char const* each = (char const*)[tmp bytes];
    
    NSMutableData* data = [[NSMutableData alloc] initWithLength:((len << 1) + (len >> 1))];
    char *bytes = (char*)[data mutableBytes];
    while ( len &&
           *each ) {
        
        bytes[0] = '\\';
        bytes[1] = 'u';
                
        bytes[2] = MAP_BINARY_ASCII[b8_h(*each)];
        bytes[3] = MAP_BINARY_ASCII[b8_l(*each)];
        
        ++each;
        
        bytes[4] = MAP_BINARY_ASCII[b8_h(*each)];
        bytes[5] = MAP_BINARY_ASCII[b8_l(*each)];
                
        ++each;
        
        bytes += 6;
        len -= 2;
    }

    // to string.
    NSString *str = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
    [data release];
    return [str autorelease];
}

- (NSString*)fromUnicodeString {
    NSMutableData *data = [NSMutableData alloc];
    // decode binary.
    [[self dataUsingEncoding:NSASCIIStringEncoding] decodeBinaryStringEx:data];
    // to string.
    NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF16StringEncoding];
    [data release];
    return [str autorelease];   
}

+ (NSString*)uuidString {
    CFUUIDRef uuid = CFUUIDCreate(kCFAllocatorDefault);
    NSString *uuidString = (NSString *)CFUUIDCreateString(kCFAllocatorDefault, uuid);
    [uuidString autorelease];
    CFRelease(uuid);    
    return uuidString;
}

- (NSString*)md5 {
    NSMutableData *data = [NSMutableData alloc];
    [[self dataUsingEncoding:NSUTF8StringEncoding] md5ex:data];
    NSMutableData *data_str = [NSMutableData alloc];
    [data encodeBinaryStringEx:data_str];
    NSString *str = [[NSString alloc] initWithData:data_str encoding:NSASCIIStringEncoding];
    [data release];
    [data_str release];
    return [str autorelease];
}

- (NSString*)hmac_sha1:(NSString *)secret {
    NSData *secretData = [secret dataUsingEncoding:NSUTF8StringEncoding];
    NSData *clearTextData = [self dataUsingEncoding:NSUTF8StringEncoding];
    unsigned char result[20];
	CCHmac(kCCHmacAlgSHA1, [secretData bytes], [secretData length], [clearTextData bytes], [clearTextData length], result);    
    NSData* code = [NNTObject base64_encode:[NSData dataWithBytes:result length:20]];
    NSString* ret_str = [[NSString alloc] initWithData:code encoding:NSUTF8StringEncoding];
    return [ret_str autorelease];
}

- (NSString*)uniqueIdentify {
    return [self md5];
}

- (NSString*)unescape {
    usize const len = [self length];
    if (len == 0)
        return @"";
    usize const buf_len = [self length] << 1 + 1;
    unichar *buf = (unichar*)malloc(buf_len);
    uindex j = 0;
    for (uindex i = 0; i < len; ++i) {
        unichar c = [self characterAtIndex:i];
        buf[j++] = c;
        if (c == '%') {
            buf[j++] = '%';
        }
    }
    buf[j] = 0;
    NSString* str = [NSString stringWithCharacters:buf length:j];
    free(buf);
    return str;
}

- (real)realValue {
# if REAL_IS_FLOAT == 1
    return [self floatValue];
# else
    return [self doubleValue];
# endif
}

- (id)json_decode {
    return [NNTObject json_decode:self];
}

- (NSArray*)getCharactersArray {
    return [self getCharactersArray:NO];
}

- (NSArray*)getCharactersArray:(BOOL)reverse {
    NSMutableArray *arr = [NSMutableArray arrayWithCapacity:[self length]];
    if (reverse) {
        for (uindex i = [self length]; i != 0; --i) {
            unichar c = [self characterAtIndex:i];
            [arr addObject:[NSString stringWithCharacters:&c length:1]];
        }
    } else {
        for (uindex i = 0; i < [self length]; ++i) {
            unichar c = [self characterAtIndex:i];
            [arr addObject:[NSString stringWithCharacters:&c length:1]];
        }
    }
    return arr;
}

- (BOOL)notEmpty {
    if ([self isEqualToString:@""])
        return NO;
    if ([self matchedByRegex:@"\\s+"])
        return NO;
    return YES;
}

- (uint)coreType {
    return CoreTypeString;
}

- (NNTValueType)valueType {
    return NNTValueTypeString;
}

- (NSString*)urlencode {
    NSString *result = (NSString *)CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault,
                                                                           (CFStringRef)self,
                                                                           NULL,
																		   CFSTR("!*'();:@&=+$,/?%#[]"),
                                                                           kCFStringEncodingUTF8);
    [result autorelease];
	return result;
}

- (NSString*)urldecode {
	NSString *result = (NSString *)CFURLCreateStringByReplacingPercentEscapesUsingEncoding(kCFAllocatorDefault,
																						   (CFStringRef)self,
																						   CFSTR(""),
																						   kCFStringEncodingUTF8);
    [result autorelease];
	return result;
}

@end

NNTIMPL_CATEGORY(NSString, NNT);
NNTIMPL_CATEGORY(NSString, Regex);

// thanks to RegexKitLite.

enum {
    RKLSplitOp                         = 1UL,
    RKLReplaceOp                       = 2UL,
    RKLRangeOp                         = 3UL,
    RKLArrayOfStringsOp                = 4UL,
    RKLArrayOfCapturesOp               = 5UL,
    RKLCapturesArrayOp                 = 6UL,
    RKLDictionaryOfCapturesOp          = 7UL,
    RKLArrayOfDictionariesOfCapturesOp = 8UL,
    RKLMaskOp                          = 0xFUL,
    RKLReplaceMutable                  = 1UL << 4,
    RKLSubcapturesArray                = 1UL << 5,
};
typedef NSUInteger RKLRegexOp;
#define NSNotFoundRange       ((NSRange){.location=(NSUInteger)NSNotFound, .length=              0UL})
#define NSMaxiumRange         ((NSRange){.location=                   0UL, .length=    NSUIntegerMax})

NNT_BEGIN_HEADER_OBJC

extern id rkl_performRegexOp(id self, SEL _cmd, RKLRegexOp regexOp, NSString *regexString, RKLRegexOptions options, NSInteger capture, id matchString, NSRange *matchRange, NSString *replacementString, NSError **error, void *result, NSUInteger captureKeysCount, id captureKeys[captureKeysCount], const int captureKeyIndexes[captureKeysCount]);

NNT_END_HEADER_OBJC

@implementation NSString (Regex)

- (BOOL)matchedByRegex:(NSString *)regex {
    return [self matchedByRegex:regex full:YES];
}

- (BOOL)matchedByRegex:(NSString *)regex full:(BOOL)full {
    //return [self isMatchedByRegex:regex];    
    NSRange result = NSNotFoundRange, range = NSMaxiumRange;
    rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLRangeOp, regex, RKLNoOptions, 0L, self, &range, NULL, NULL,  &result, 0UL, NULL, NULL);
    BOOL found = ((result.location == (NSUInteger)NSNotFound) ? NO : YES);
    if (found && full)
        return result.length == [self length];
    return found;
}

- (BOOL)matchedByRegex:(NSString *)regex inRange:(NSRange)range {
    //return [self isMatchedByRegex:regex inRange:range];
    NSRange result = NSNotFoundRange;
    rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLRangeOp, regex, RKLNoOptions, 0L, self, &range, NULL, NULL,  &result, 0UL, NULL, NULL);
    return((result.location == (NSUInteger)NSNotFound) ? NO : YES);
}

- (BOOL)matchedByRegex:(NSString *)regex options:(StringRegexOptions)options inRange:(NSRange)range error:(NSError **)error {
    //return [self isMatchedByRegex:regex options:(RKLRegexOptions)options inRange:range error:error];
    NSRange result = NSNotFoundRange;
    rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLRangeOp, regex, options,      0L, self, &range, NULL, error, &result, 0UL, NULL, NULL);
    return((result.location == (NSUInteger)NSNotFound) ? NO : YES);
}

- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regex withString:(NSString *)replacement {
    NSRange searchRange = NSMaxiumRange;
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLReplaceOp, regex, RKLNoOptions, 0L, self, &searchRange, replacement, NULL,  NULL, 0UL, NULL, NULL));    
}

- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regex withString:(NSString *)replacement range:(NSRange)searchRange {
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLReplaceOp, regex, RKLNoOptions, 0L, self, &searchRange, replacement, NULL,  NULL, 0UL, NULL, NULL));
}

- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regex withString:(NSString *)replacement options:(StringRegexOptions)options range:(NSRange)searchRange error:(NSError **)error {
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLReplaceOp, regex, options,      0L, self, &searchRange, replacement, error, NULL, 0UL, NULL, NULL));
}

- (NSArray *)componentsMatchedByRegex:(NSString *)regex {
    NSRange searchRange = NSMaxiumRange;
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLArrayOfStringsOp, regex, RKLNoOptions, 0L,      self, &searchRange, NULL, NULL,  NULL, 0UL, NULL, NULL));
}

- (NSArray *)componentsMatchedByRegex:(NSString *)regex capture:(NSInteger)capture {
    NSRange searchRange = NSMaxiumRange;
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLArrayOfStringsOp, regex, RKLNoOptions, capture, self, &searchRange, NULL, NULL,  NULL, 0UL, NULL, NULL));
}

- (NSArray *)componentsMatchedByRegex:(NSString *)regex range:(NSRange)range {
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLArrayOfStringsOp, regex, RKLNoOptions, 0L,      self, &range,       NULL, NULL,  NULL, 0UL, NULL, NULL));
}

- (NSArray *)componentsMatchedByRegex:(NSString *)regex options:(StringRegexOptions)options range:(NSRange)range capture:(NSInteger)capture error:(NSError **)error {
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLArrayOfStringsOp, regex, options,      capture, self, &range,       NULL, error, NULL, 0UL, NULL, NULL));
}

- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regex {
    NSRange searchRange = NSMaxiumRange;
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLCapturesArrayOp, regex, RKLNoOptions, 0L, self, &searchRange, NULL, NULL,  NULL, 0UL, NULL, NULL));
}

- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regex range:(NSRange)range {
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLCapturesArrayOp, regex, RKLNoOptions, 0L, self, &range,       NULL, NULL,  NULL, 0UL, NULL, NULL));
}

- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regex options:(StringRegexOptions)options range:(NSRange)range error:(NSError **)error {
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)RKLCapturesArrayOp, regex, options,      0L, self, &range,       NULL, error, NULL, 0UL, NULL, NULL));
}

- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regex {
    NSRange searchRange = NSMaxiumRange;
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)(RKLArrayOfCapturesOp | RKLSubcapturesArray), regex, RKLNoOptions, 0L, self, &searchRange, NULL, NULL,  NULL, 0UL, NULL, NULL));
}

- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regex range:(NSRange)range {
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)(RKLArrayOfCapturesOp | RKLSubcapturesArray), regex, RKLNoOptions, 0L, self, &range,       NULL, NULL,  NULL, 0UL, NULL, NULL));
}

- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regex options:(StringRegexOptions)options range:(NSRange)range error:(NSError **)error {
    return(rkl_performRegexOp(self, _cmd, (RKLRegexOp)(RKLArrayOfCapturesOp | RKLSubcapturesArray), regex, options,      0L, self, &range,       NULL, error, NULL, 0UL, NULL, NULL));
}

@end

id kNSStringUUID() {
    return [NSString uuidString];
}

id kNSStringTimestamp() {
    return [NSString stringWithFormat:@"%d", (int)time(NULL)];
}

id kNSStringNonce() {
    CFUUIDRef theUUID = CFUUIDCreate(NULL);
    CFStringRef string = CFUUIDCreateString(NULL, theUUID);
    //NSMakeCollectable(theUUID);
    CFRelease(theUUID);
    return (NSString*)NSMakeCollectable(string);
    //return (NSString*)string;
}

id kNSStringNonceSimple() {
    return [NSString stringWithFormat:@"%u", arc4random() % (9999999 - 123400) + 123400];
}

NSString *kNSStringYES = @"YES", *kNSStringNO = @"NO";

NNT_END_OBJC

NNT_BEGIN_CXX

NSString* tostr(NSURL* url)
{
    return url.relativePath;
}

NSString* tostr(bool val)
{
    return val ? kNSStringYES : kNSStringNO;
}

NSString* tostr(int val) {
    return [[::NSNumber numberWithInt:val] stringValue];
}

NSString* tostr(uint val) {
    return [[::NSNumber numberWithUnsignedInt:val] stringValue];
}

NSString* tostr(float val) {
    return [[::NSNumber numberWithFloat:val] stringValue];
}

NSString* tostr(double val) {
    return [[::NSNumber numberWithDouble:val] stringValue];
}

NSString* tostr(long val) {
    return [[::NSNumber numberWithLong:val] stringValue];
}

NSString* tostr(ulong val) {
    return [[::NSNumber numberWithUnsignedLong:val] stringValue];
}

NSString* tostr(longlong val) {
    return [[::NSNumber numberWithLongLong:val] stringValue];
}

NSString* tostr(ulonglong val) {
    return [[::NSNumber numberWithUnsignedLongLong:val] stringValue];
}

NSString* tostr(NSString* val) {
    return val;
}

NSString* tostr(char const* val) {
    return [NSString stringWithCString:val encoding:NSUTF8StringEncoding];
}

NSString* tostr(core::string const& val) {
    return tostr(val.c_str());
}

NSString* tostr(::NSData* val) {
    return [[[NSString alloc] initWithData:val encoding:NSUTF8StringEncoding] autorelease];
}

NNT_BEGIN_NS(ns)

String null_string = @"";

NNT_END_NS

NNT_END_CXX