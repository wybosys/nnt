//
//  UPOMP_iPad_SMSTextFieldCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-30.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"

@interface UPOMP_iPad_SMSTextFieldCell : UPOMP_iPad_Cell <UITextFieldDelegate,UPOMP_iPad_KaNetDelegate> {
	UITextField *field;
	UIButton *smsButton;
	UILabel *countLabel;
	UPOMP_iPad_KaNet *net;
	BOOL isGetSMS;
	NSString *smsPhone;
    NSTimer *timer;
    BOOL canReLoad;
    int countDownIndex;
    NSString *backSecureInfo;
	NSString *secureInfo;
	NSString *misc;
	NSString *phoneValue;
}
@property(nonatomic,retain)NSString *secureInfo;
@property(nonatomic,retain)NSString *misc;
@property(nonatomic,retain)NSString *phoneValue;
@end
