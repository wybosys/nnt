//
//  UPOMP_iPad_Value.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-17.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "UPOMP_iPad_KaBase64.h"
#import "UPOMP_iPad_Ka3Des.h"
#import "UPOMP_iPad_KaRSA.h"
#import "UPOMP_iPad_KaMD5.h"
#import "UPOMP_iPad_KaPinBlock.h"

typedef enum UPOMP_iPad_AppType {
	UPOMP_iPad_CP_UpPay,
	UPOMP_iPad_CP_UpLogin,
	UPOMP_iPad_CP_UpRegister,
	UPOMP_iPad_CP_UpAccountManager,
	UPOMP_iPad_CP_UpPanManager
} UPOMP_iPad_AppType;

typedef enum UPOMP_iPad_ViewID {
    UPOMP_iPad_CP_PayMode,
    UPOMP_iPad_CP_UserMain,
    UPOMP_iPad_CP_RestPassword,
    UPOMP_iPad_CP_UserInfo,
    UPOMP_iPad_CP_CardList,
    UPOMP_iPad_CP_NewCard,
    UPOMP_iPad_CP_CardBalance,
    UPOMP_iPad_CP_PayFinish,
    UPOMP_iPad_CP_PayRegister,
    UPOMP_iPad_CP_PayNewCard,
    UPOMP_iPad_CP_LoadingCheckIn
} UPOMP_iPad_ViewID;

@interface UPOMP_iPad_Value : NSObject {
	
}
- (UITextField*)textFieldStyleByFrame:(CGRect)rect textDelegate:(id)delegate returnKeyType:(UIReturnKeyType)returnKeyType keyboardType:(UIKeyboardType)keyboardType;
- (UIButton*)buttonStyleWithPoint:(CGPoint)point Titel:(NSString*)titel imageURL:(NSString*)url;
- (UIButton*)textFieldButtonStyleWithPoint:(CGPoint)point Titel:(NSString*)titel imageURL:(NSString*)url;
- (UILabel*)tipsTextLabelStyleWithText:(NSString*)text;
- (NSString*)getMyBundlePath:(NSString*)filename;
- (NSString*)decodeWithRSA3Des:(NSString*)str;
- (NSString*)formatAmt:(NSString*)str;
- (NSString*)formatTime:(NSString*)str;
- (NSString*)formatPhoneNum:(NSString *)str;
- (NSString*)formatCardNum:(NSString *)str;
- (BOOL)checkIsChinese:(NSString*)str;
- (BOOL)amtchString:(NSString*)str checkString:(NSString*)checkStr;
- (void)animateEaseInEaseOut:(CALayer*)laye delegate:(id)del;
- (void)animation_FadeIN_OUT_FromRight:(UIView *)theView delegate:(id)d;
- (void)animation_FadeIN_OUT_FromLeft:(UIView *)theView delegate:(id)d;
- (void)animation_FadeIN_OUT_UP:(UIView *)theView delegate:(id)d;
- (void)animation_FadeIN_OUT_DOWN:(UIView *)theView delegate:(id)d;
@property (nonatomic,readonly)UPOMP_iPad_KaBase64 *base64;
@property (nonatomic,readonly)UPOMP_iPad_Ka3Des *_3Des;
@property (nonatomic,readonly)UPOMP_iPad_KaRSA *rsa;
@property (nonatomic,readonly)UPOMP_iPad_KaMD5 *md5;
@property (nonatomic,readonly)UPOMP_iPad_KaPinBlock *pinBlock;
@end
