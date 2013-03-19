//
//  GlobalInfo.h
//  UPOMP
//
//  Created by tokimeki on 11-7-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface UPOMP_GlobalInfo : NSObject {
    
}

//+ (NSString *)ChaosStr:(NSString *)original action:(NSInteger)type;

+ (void)setConfigVersion:(NSString *)version;
+ (NSString *)getConfigVersion;
+ (void)setFrontVersion:(NSString *)version;
+ (NSString *)getFrontVersion;
+ (void)setUpopVersion:(NSString *)version;
+ (NSString *)getUpopVersion;
+ (void)setBindCardAmount:(NSString *)count;
+ (NSString *)getBindCardAmount;
+ (void)setAllowUpdate:(NSString *)enable;
+ (NSString *)getAllowUpdate;
+ (void)setNoTradeTime:(NSString *)time;
+ (NSString *)getNoTradeTime;
+ (void)setServerTimeout:(NSString *)time;
+ (NSString *)getServerTimeout;
+ (void)setPayment:(NSArray *)array;
+ (NSArray *)getPayment;
+ (void)setFrontKey:(NSString *)key;
+ (NSString *)getFrontKey;
+ (void)setUpopKey:(NSString *)key;
+ (NSString *)getUpopKey;

+ (void)setMerchantId:(NSString *)str;
+ (NSString *)getMerchantId;
+ (void)setMerchantOrderId:(NSString *)str;
+ (NSString *)getMerchantOrderId;
+ (void)setMerchantOrderTime:(NSString *)str;
+ (NSString *)getMerchantOrderTime;
+ (void)setSign:(NSString *)str;
+ (NSString *)getSign;
+ (void)setMerchantName:(NSString *)str;
+ (NSString *)getMerchantName;
+ (void)setMerchantOrderAmt:(NSString *)str;
+ (NSString *)getMerchantOrderAmt;
+ (NSString *)getMerchantOrderAmtReq;
+ (void)setMerchantOrderDesc:(NSString *)str;
+ (NSString *)getMerchantOrderDesc;
+ (void)setPluginVersion:(NSString *)str;
+ (NSString *)getPluginVersion;
+ (void)setPluginSerialNo:(NSString *)str;
+ (NSString *)getPluginSerialNo;
+ (void)setSessionId:(NSString *)str;
+ (NSString *)getSessionId;

+ (void)setBaseUrl:(NSString *)str;
+ (NSString *)getBaseUrl;

+ (void)setDeviceNum:(NSString *)str;
+ (NSString *)getDeviceNum;

+ (void)release;
+ (void)reset;

@end