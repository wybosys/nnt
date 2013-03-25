
# ifndef __NNT_SEC_SIGNATURE_31393C62076047B18EF2D6ECFBD49D54_H_INCLUDED
# define __NNT_SEC_SIGNATURE_31393C62076047B18EF2D6ECFBD49D54_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

typedef struct {
    NSString* (*method_name)();
    NSString* (*method)(NSString* text, NSString* secret);
} sec_signature_func_t;

NNT_EXTERN NSString* signature_hmac_sha1_name();
NNT_EXTERN NSString* signature_hmac_sha1(NSString* text, NSString* secret);

NNT_EXTERN NSString* signature_md5_name();
NNT_EXTERN NSString* signature_md5(NSString* text, NSString* secret);

NNT_END_HEADER_OBJC

# endif
