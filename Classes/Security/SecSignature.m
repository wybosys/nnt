
# import "Core.h"
# import "SecSignature.h"

WSI_BEGIN_OBJC

NSString* signature_hmac_sha1_name() {
    return @"HMAC-SHA1";
}

NSString* signature_hmac_sha1(NSString* text, NSString* secret) {
    return [text hmac_sha1:secret];
}

NSString* signature_md5_name() {
    return @"MD5";
}

NSString* signature_md5(NSString* text, NSString* secret) {
    return [text md5];
}

WSI_END_OBJC