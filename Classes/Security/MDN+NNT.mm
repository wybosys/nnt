
# import "Core.h"
# import "MDN+NNT.h"
# include <CommonCrypto/CommonDigest.h>

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

@implementation MD5

+ (NSString*)StringDigest:(NSString*)string {
    NSData* data = [string dataUsingEncoding:NSUTF8StringEncoding];
    uchar buf[CC_MD5_DIGEST_LENGTH];
    CC_MD5(data.bytes, data.length, buf);
    core::string cs = core::hex_cast(buf, CC_MD5_DIGEST_LENGTH);
    return core::type_cast<ns::String>(cs);
}

@end

NNT_END_OBJC
