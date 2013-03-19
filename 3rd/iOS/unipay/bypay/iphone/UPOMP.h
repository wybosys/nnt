//
//  ChinaPayMainView.h
//  ChinaUnionPay
//
//  Created by Anplex on 11-6-17.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMPUserInfoData.h"
#import "UPOMPView.h"
#import "UPOMP_AgreementView.h"
#import "UPOMPUI.h"
@protocol UPOMPDelegate;
@interface UPOMP : UIViewController <UIAlertViewDelegate>{
	id <UPOMPDelegate>	viewDelegate;
	UPOMP_CPPayView *payView;
	UPOMP_CPUserView *userView;
	UPOMP_CPCardView *cardView;
	int selectedItemIndex;
	int appType;
	UPOMP_CPUserInfoData *userInfoData;
	UPOMP_CPLoading *loadingUI;
	bool isLogin;
	bool hasLoadCardList;
	UIAlertView *alert;
	UIAlertView *errorAlert;
	UIAlertView *tirenAlert;
	UIAlertView *qktirenAlert;
	UPOMP_CPLoadingView *loadingView;
	UPOMP_CPOrderInfoData *orderInfoData;
	NSString *backApp;
	NSMutableArray *cardPayUI;
	NSMutableArray *userCardList;
	UPOMP_CPTabBar *tabBar;
	int paySelecetCardIndex;
	int defaultCard;
	NSMutableArray *cardsList;
	int selecedCardsIndex;
	NSString *selecedCardsStr;
	int secureQuestionSelectIndex;
	NSMutableArray *secureQuestionArray;
	NSString *smspushInfo;
	NSString *smspushSecInfo;
	bool viewClose;
	NSMutableArray *PayCommonUI;
	NSString *attPayName;
	SystemSoundID pmph;
	NSArray *t1;
	NSArray *t2;
	NSArray *t3;
	NSArray *t4;
	UPOMP_AgreementView *agView;
	int selectedPayType;
    BOOL isCardListReLoad;
}
- (void)showAgreementView;
- (void)playSound;
- (void)startRegiestUIs;
- (void)releaseRegiestUIs;
- (void)logOut;
- (void)setSelectIndex:(int)index;
- (void)setSelectView:(int)index;
- (void)setXmlData:(NSData*)data;//入口函数
- (void)closeView:(NSData*)data;//关闭接口
- (void)keyboardWasShown:(NSNotification *) notif;
- (void)checkOK;
- (void)EscAction;
- (void)ErrorAction;
- (void)parseConfig:(NSData *)data;
- (void)tirenAction:(int)num string:(NSString*)str;
@property int appType;
@property int defaultCard;
@property bool isLogin;
@property bool hasLoadCardList;
@property bool viewClose;
@property(nonatomic,retain) NSMutableArray *userCardList;
@property(nonatomic,retain) UPOMP_CPLoading *loadingUI;
@property(nonatomic,retain) UPOMP_CPUserInfoData *userInfoData;
@property(nonatomic,retain) UPOMP_CPOrderInfoData *orderInfoData;
@property(nonatomic,retain) NSMutableArray *secureQuestionArray;
@property int secureQuestionSelectIndex;
@property(nonatomic,retain) NSMutableArray *cardsList;
@property int selecedCardsIndex;
@property int paySelecetCardIndex;
@property int selectedPayType;
@property BOOL isCardListReLoad;
@property(nonatomic,retain) NSString *selecedCardsStr;
@property(nonatomic,retain) NSMutableArray *cardPayUI;
@property (nonatomic, assign) id <UPOMPDelegate> viewDelegate;
@property (nonatomic, retain) NSString *smspushInfo;
@property (nonatomic, retain) NSString *smspushSecInfo;
@property (nonatomic, retain) NSString *backApp;
@property (nonatomic,retain) UPOMP_CPCardView *cardView;
@property (nonatomic,retain) NSMutableArray *PayCommonUI;
@property (nonatomic,retain) NSString *transTimeout;
@property (nonatomic,retain) NSString *merchantPublicCert;
@property (nonatomic,retain) NSString *backEndUrl;
@property (nonatomic,readonly) NSArray *t1;
@property (nonatomic,readonly) NSArray *t2;
@property (nonatomic,readonly) NSArray *t3;
@property (nonatomic,readonly) NSArray *t4;
@property (nonatomic,retain) NSString *attPayName;
@end
//支付插件回掉接口函数 传递nsdata 报文数据 xml 当支付插件关闭时自动调用并传递参数
@protocol UPOMPDelegate<NSObject>
@required
-(void)viewClose:(NSData*)data;
@end
