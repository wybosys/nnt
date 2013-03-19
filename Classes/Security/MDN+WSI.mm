
# import "Core.h"
# import "MDN+WSI.h"
# include <CommonCrypto/CommonDigest.h>

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

@implementation MD5

+ (NSString*)StringDigest:(NSString*)string {
    NSData* data = [string dataUsingEncoding:NSUTF8StringEncoding];
    uchar buf[CC_MD5_DIGEST_LENGTH];
    CC_MD5(data.bytes, data.length, buf);
    core::string cs = core::hex_cast(buf, CC_MD5_DIGEST_LENGTH);
    return core::type_cast<ns::String>(cs);
}

@end

WSI_END_OBJC
