//
//  CPValue.h
//  ChinaUnionPay
//
//  Created by Anplex on 11-6-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

typedef enum UPOMP_CPPayModeCellID {
	CP_PayModeCell_Phone,
	CP_PayModeCell_SMSCheck,
	CP_PayModeCell_CardType,
	CP_PayModeCell_BankName,
	CP_PayModeCell_CardNum,
	CP_PayModeCell_CardPass,
	CP_PayModeCell_CardData,
	CP_PayModeCell_CardCVN2,
	CP_PayModeCell_DynamicNum,
	CP_PayModeCell_UserName,
	CP_PayModeCell_UserPass,
	CP_PayModeCell_SaveCardNum,
	CP_PayModeCell_SaveCardPass
} UPOMP_CPPayModeCellID;

typedef enum UPOMP_CPAppType {
	CP_UpPay,
	CP_UpLogin,
	CP_UpRegister,
	CP_UpAccountManager,
	CP_UpPanManager
} UPOMP_CPAppType;

typedef enum UPOMP_CPNetError {
	CP_NoBody,
	CP_ConnError,
	CP_CheckError,
	CP_Cancel
} UPOMP_CPNetError;

#define MYBUNDLE_NAME @ "UPOMPImage.bundle"
#define MYBUNDLE_PATH [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent: MYBUNDLE_NAME]
#define MYBUNDLE [NSBundle bundleWithPath: MYBUNDLE_PATH]

@interface UPOMP_CPValue : NSObject {

}
+(void)animateEaseInEaseOut:(CALayer*)laye delegate:(id)del;
+(void)animation_FadeIN_OUT_DOWN:(UIView *)theView delegate:(id)d;
+(void)animation_FadeIN_OUT_UP:(UIView *)theView delegate:(id)d;
+(NSString*)getMyBundlePath:(NSString*)filename;
+(BOOL)checkIsChinese:(NSString*)str;
+(BOOL)amtchString:(NSString*)str checkString:(NSString*)checkStr;
+(void)animation_FadeIN_OUT_FromRight:(UIView *)theView;
+(void)animation_FadeIN_OUT_FromLeft:(UIView *)theView;
+(UIButton*)getEnterButtonByTitel:(NSString*)titel drawX:(int)x drawY:(int)y;
+(UIButton*)getEscButtonByTitel:(NSString*)titel drawX:(int)x drawY:(int)y;
+(UIButton*)getButtonByTitel:(NSString*)titel frame:(CGRect)rect;
+(UITextField*)getTextFieldByFrame:(CGRect)rect textDelegate:(id)tDelegate returnKeyType:(UIReturnKeyType)type;
@end
