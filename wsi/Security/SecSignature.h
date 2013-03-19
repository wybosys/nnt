
# ifndef __WSI_SEC_SIGNATURE_31393C62076047B18EF2D6ECFBD49D54_H_INCLUDED
# define __WSI_SEC_SIGNATURE_31393C62076047B18EF2D6ECFBD49D54_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

typedef struct {
    NSString* (*method_name)();
    NSString* (*method)(NSString* text, NSString* secret);
} sec_signature_func_t;

WSI_EXTERN NSString* signature_hmac_sha1_name();
WSI_EXTERN NSString* signature_hmac_sha1(NSString* text, NSString* secret);

WSI_EXTERN NSString* signature_md5_name();
WSI_EXTERN NSString* signature_md5(NSString* text, NSString* secret);

WSI_END_HEADER_OBJC

# endif