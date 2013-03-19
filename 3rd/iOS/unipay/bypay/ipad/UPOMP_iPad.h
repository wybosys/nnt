//
//  UPOMP_iPad.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-16.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMP_iPad_Value.h"
#import "UPOMP_iPad_LoadingView.h"
#import "UPOMP_iPad_KaTBXML.h"
#import "UPOMP_iPad_LoadingUI.h"
#import "UPOMP_iPad_OrderInfoView.h"
#import "UPOMP_iPad_KaTabBar.h"
#import "UPOMP_iPad_KaTabItem.h"
#import "UPOMP_iPad_KaTabBar.h"
#import "UPOMP_iPad_UserView.h"
#import "UPOMP_iPad_PayView.h"
#import "UPOMP_iPad_CardView.h"
#import "UPOMP_iPad_ViewCenter.h"
#import "UPOMP_iPad_AgreementView.h"
#import "UPOMP_iPad_KeyBoardViewController.h"

@protocol UPOMP_iPad_Delegate<NSObject>
@required
-(void)viewClose:(NSData*)data;
@end

@interface UPOMP_iPad : UIViewController <UIAlertViewDelegate,UPOMP_iPad_KaTabBarDelegate>{
	UIAlertView *alert;
	UIAlertView *errorAlert;
	UIAlertView *tirenAlert;
	UIAlertView *qktirenAlert;
	UPOMP_iPad_LoadingView *loadingView;
	UPOMP_iPad_OrderInfoView *orderInfoView;
	UPOMP_iPad_KaTabBar *menuTabBar;
	UPOMP_iPad_UserView *userView;
	UPOMP_iPad_PayView *payView;
	UPOMP_iPad_CardView *cardView;
    UPOMP_iPad_AgreementView *agreementView;
    UILabel *textLabel;
    UIPopoverController *popController;
    UPOMP_iPad_KeyBoardViewController *keyBoardViewController;
	UIView *leftView;
	UIView *rightView;
	UIView *bottomView;
	int selectedIndex;
}
- (void)showTimeOver;
- (void)setXmlData:(NSData*)data;
- (void)closeView:(NSData*)data;
- (void)loadingOver;
- (BOOL)getConfigInfos;
- (void)showESCAlert;
- (NSData*)getXML:(NSString*)myDes;
- (void)tirenAction:(int)num string:(NSString*)str;
- (void)showAgreement:(UPOMP_iPad_View*)view;
- (BOOL)saveXMLbyTag:(NSString*)tag xmlElement:(UPOMP_iPad_TBXMLElement*)root xml:(UPOMP_iPad_KaTBXML*)xml;
- (BOOL)saveXMLbyTag_onLine:(NSString*)tag xmlElement:(UPOMP_iPad_TBXMLElement*)root xml:(UPOMP_iPad_KaTBXML*)xml;
@property BOOL viewClose;
@property BOOL isLogin;
@property BOOL isPayLogin;
@property (nonatomic, assign) id <UPOMP_iPad_Delegate> viewDelegate;
@property (nonatomic,readonly) UPOMP_iPad_ViewCenter*viewCenter;
@property (nonatomic,readonly) UPOMP_iPad_LoadingUI *loadingUI;
@property (nonatomic,readonly) NSArray *t1;
@property (nonatomic,readonly) NSArray *t2;
@property (nonatomic,readonly) NSArray *t3;
@property (nonatomic,readonly) NSArray *t4;
@property (nonatomic,readonly) UPOMP_iPad_Value *defaultValue;
@property (nonatomic,readonly) NSMutableDictionary *upompDictionary;
@property (nonatomic,readonly) UPOMP_iPad_KeyBoardViewController *keyBoardViewController;
@property (nonatomic,readonly) UIPopoverController *popController;
@end
