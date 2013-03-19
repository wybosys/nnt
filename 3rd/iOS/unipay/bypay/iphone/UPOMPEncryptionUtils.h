//
//  EncryptionUtils.h
//  UPOMP
//
//  Created by tokimeki on 11-7-23.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonCryptor.h>


@interface UPOMP_EncryptionUtils : NSObject {
}

+ (NSData *)encryptionWithBase64:(NSString *)str withData:(NSData *)strdata;
+ (NSData *)decryptionWithBase64:(NSString *)str;
+ (NSData *)encryptionWithMD5:(NSString *)str;
+ (NSString *)encryptionWithMD5ReturnString:(NSString *)str;
+ (NSString *)encryptionWith3DesWithBase64:(NSString *)plainText operation:(CCOperation)encryptOrDecrypt key:(NSString *)publickey;
+ (NSData *)encryptionWithRSA:(NSString *)plainText withKeyData:(NSData *)keydata;
+ (Byte*)pin2PinBlock:(NSString*)aPin;
+ (Byte*)formatPan:(NSString*)aPan;
+ (NSData*)encryptedPinWithPin:(NSString*)pin pan:(NSString*)pan;
+ (NSString*)decodeWithRSA3Des:(NSString*)str;
+ (NSData *)encryptRSAByData:(NSData *)strData usingKey:(SecKeyRef)key error:(NSError **)err;
+ (void)releaseItem;
@end
