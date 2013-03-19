//
//  CPUserInfoData.h
//  ChinaUnionPay
//
//  Created by Anplex on 11-6-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface UPOMP_CPUserInfoData : NSObject {
	NSString *loginName;
	NSString *mobileNumber;
	NSString *email;
	NSString *welcome;
	NSMutableArray *cardArray;
	NSString *secureQuestion;
	int selectedCard;
}
@property int selectedCard;
@property(nonatomic,retain) NSString *loginName;
@property(nonatomic,retain) NSString *mobileNumber;
@property(nonatomic,retain) NSString *email;
@property(nonatomic,retain) NSString *welcome;
@property(nonatomic,retain) NSMutableArray *cardArray;
@property (nonatomic, retain) NSString *secureQuestion;
@end

@interface UPOMP_CPOrderInfoData : NSObject {
	NSString *cupsTraceNum;
	NSString *cupsTraceStatus;
	NSString *cupsSysTime;
	NSString *respCode;
	NSString *respDesc;
	NSString *phoneNum;
	NSString *smsCode;
	NSString *picCode;
	NSString *loginName;
	NSString *password;
	NSString *mobileNumber;
	NSString *welcome;
	NSString *cupsQid;
    NSString *cardPhoneNum;
}
@property(nonatomic,retain)NSString *cupsTraceNum;
@property(nonatomic,retain)NSString *cupsTraceStatus;
@property(nonatomic, retain)NSString *cupsSysTime;
@property(nonatomic,retain)NSString *respCode;
@property(nonatomic,retain)NSString *respDesc;
@property(nonatomic,retain)NSString *password;
@property (nonatomic, retain) NSString *phoneNum;
@property (nonatomic, retain) NSString *smsCode;
@property (nonatomic, retain) NSString *picCode;
@property (nonatomic, retain) NSString *loginName;
@property (nonatomic, retain) NSString *mobileNumber;
@property (nonatomic, retain) NSString *welcome;
@property (nonatomic, retain) NSString *cupsQid;
@property (nonatomic, retain) NSString *cardPhoneNum;
@end

@interface UPOMP_CPBankInfoData : NSObject {
	NSString *panBankId;
	NSString *panBank;
	NSString *panType;
}
@property(nonatomic,retain)NSString *panBankId;
@property(nonatomic,retain)NSString *panBank;
@property(nonatomic,retain)NSString *panType;
@end

@interface UPOMP_CPCardData : NSObject {
	NSString *mobileNumber;
	int isDefault;
	NSString *pan;
	NSString *panBankId;
	NSString *panBank;
	NSString *panType;
	NSString *bindId;
}
@property int isDefault;
@property(nonatomic,retain) NSString *panType;
@property(nonatomic,retain) NSString *panBank;
@property(nonatomic,retain) NSString *pan;
@property(nonatomic,retain) NSString *panBankId;
@property(nonatomic,retain) NSString *bindId;
@property(nonatomic,retain) NSString *mobileNumber;
@end
