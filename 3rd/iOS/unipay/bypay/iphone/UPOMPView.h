//
//  CPView.h
//  ChinaUnionPay
//
//  Created by Anplex on 11-6-17.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "UPOMPValue.h"
//#import "UPOMP.h"

@class UPOMP_CPCell;
@class UPOMP_CPNet;
@class UPOMP_CPNavigationBar;
@class UPOMP;
@class UPOMP_CPUI;
@class UPOMP_CPLoading;

typedef enum UPOMP_CPViewID {
	CP_UserForget,
	CP_UserMain,
	CP_UserInfoMain,
	CP_PayDetail,
	CP_PayFinish,
	CP_PayMode,
	CP_CardList,
	CP_NewCard,
	CP_NewCard_Pay,
	CP_LoadingCheckIn,
	CP_PayCardList,
	CP_CardBalance,
	CP_RestPassword,
	CP_CommonDetail,
	CP_UserPayCardList,
	CP_UserChangePhone,
	CP_UserChangPassword,
	CP_CardInfo,
	CP_PayRegister
} CPViewID;

@class UPOMP_KaTextFieldToolBar;
@interface UPOMP_CPView : UIView {
	UPOMP_KaTextFieldToolBar *toolBar;
	UPOMP *mainView;
	UPOMP_CPNavigationBar *navBar;
	UPOMP_CPUI *myUI;
	UIAlertView *alert;
	NSMutableArray *viewIDs;
	int myUIID;
	UPOMP_CPNet *net;
	UPOMP_CPCell *cell;
	int oldID;
}
- (void)netWorkStart:(NSString*)titel;
- (void)removeLoading;
- (void)netWork;
- (void)netCancel;
- (void)netWorkOver:(NSData*)data;
- (bool)checkOver:(NSData*)data;
- (void)netComplete;
- (void)netComplete:(NSData*)data;
- (void)netError:(int)type;
//- (void)UIAction:(int)index;
- (void)start;
- (void)back;
- (void)back:(int)num;
- (id)initWithFrame:(CGRect)frame MainView:(UPOMP*)view;
- (void)changeView:(int)vID;
- (void)keyboardWasShown:(NSNotification *) notif;
- (void)setAlertTitel:(NSString*)tString info:(NSString*)iString;
- (void)restViewIDs;
- (void)restCheckImage;
- (void)stopThread; //可能不用
- (void)toolBarUP;
- (void)toolBarDown;
- (void)addToolBar;
- (void)removeToolBar;
- (void)setToolBarFrame:(CGRect)rect;
- (CGPoint)getToolBarHight;
@property int myUIID;
@property(nonatomic,retain) UPOMP_CPNet *net;
@property(nonatomic,retain) UPOMP_CPCell *cell;
@property(nonatomic,readonly) UPOMP_CPNavigationBar *navBar;
@property(nonatomic,readonly) UPOMP_CPUI *myUI;
@property(nonatomic,readonly) UPOMP *mainView;
@end

@interface UPOMP_CPPayView : UPOMP_CPView {
}
@end

@interface UPOMP_CPUserView : UPOMP_CPView {
}
@end

@interface UPOMP_CPCardView : UPOMP_CPView {
}
@end

@interface UPOMP_CPLoadingView : UPOMP_CPView <UIAlertViewDelegate>{
	int netMode;
	BOOL needReconnect;
}
@end
