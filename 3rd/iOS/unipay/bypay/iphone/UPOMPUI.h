//
//  CPUI.h
//  ChinaUnionPay
//
//  Created by Anplex on 11-6-17.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "UPOMPView.h"
#import "UPOMPValue.h"
#import "UPOMPNet.h"
#import "UPOMPCell.h"
#import "UPOMPUserInfoData.h"
#import "UPOMP_KaTabBar.h"

typedef enum UPOMP_CPNaBarStyle {
	CP_nabarDefault
//	CP_nabarBack,
//	CP_nabarOrder
} UPOMP_CPNaBarStyle;

@interface UPOMP_CPPage : NSObject{
	NSMutableArray *array;
	UPOMP_CPView *cpview;
}
- (id) initWithView:(UPOMP_CPView*)cView;
- (void)start;
- (NSInteger)numberOfSectionsInTableView;
- (CGFloat)heightForRowAtIndexPath:(NSIndexPath *)indexPath;
- (NSInteger)numberOfRowsInSection:(NSInteger)section;
- (UITableViewCell *)cellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (NSString *)titleForHeaderInSection:(NSInteger)section;
- (void)didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)netWork;
- (void)restCheckUPImage;
- (void)restAllTextField;
- (void)stopThread;
- (BOOL)checkOver:(NSData*)data;
- (void)netComplete;
- (BOOL)isLastAtArray:(int)row;
- (void)nextCell:(int)row;
- (void)prevCell:(int)row;
-(void)UIAction:(int)index;
@end

@interface UPOMP_CPPayCommon : UPOMP_CPPage {
	UIButton *okButton;
	UIButton *escButton;
	UIImageView *bg;
	UILabel *textlabel;
	UILabel *valuelabel;
}
@end

@interface UPOMP_CPPayAttestation : UPOMP_CPPage{
	UPOMP_CPUserInfoData *myUserInfoData;
	UIButton *okButton;
	UIButton *escButton;
	UIImageView *bg;
	UILabel *textlabel;
	UILabel *valuelabel;
}
@end

@interface UPOMP_CPPayCard : UPOMP_CPPage{
	UIButton *okButton;
	UIButton *escButton;
	int netIndex;
	UIImageView *bg;
	UILabel *textlabel;
	UILabel *valuelabel;
}
@end

@interface UPOMP_CPLogin : UPOMP_CPPage{
	UIButton *okButton;
}
@end

@interface UPOMP_CPRegister : UPOMP_CPPage {
	UIButton *okButton;
	UIButton *registInfoButton;
	UIButton *agreement;
	UILabel *mylabel;
	BOOL isRead;
}
@end

@interface UPOMP_CPUI : NSObject {
	UPOMP_CPView *cpview;
	int uiHeight;
	NSIndexPath *selectedCellIndexPath;
	BOOL hasKeyBar;
	UITableView *tableView;
}
- (void)rowToSelectedCell;
- (void)rowToSelectedCellMiddel;
- (void)setSelectedCellIndexPath:(NSIndexPath*)path;
- (void)netCancel;
- (void)netComplete:(NSData*)data;
- (void)netComplete;
- (void)netError:(int)type;
- (void)checkData;
- (void)start;
- (void)addUI;
- (void)removeUI;
- (void)netWork;
- (id) init:(UPOMP_CPView*)cView;
- (void)restUIByIndex:(int)index;
- (void)UIAction:(int)index;
- (void) keyboardWasShown:(NSNotification *) notif;
- (void)restCheckImage;
- (void)stopThread;
- (BOOL)checkOver:(NSData*)data;
- (BOOL)isLastAtArray:(int)row;
- (void)nextCell:(int)row;
- (void)prevCell:(int)row;
- (BOOL)tableUP;
- (void)tableDown;
- (BOOL)NoArray;
@property BOOL hasKeyBar;
@end

@interface UPOMP_CPChangePassword : UPOMP_CPUI<UITableViewDataSource,UITableViewDelegate>{
	UIButton *okButton;
	UIButton *escButton;
	NSMutableArray *array;
	UIImageView *titelBG;
	UILabel *welcomeLable;
	UILabel *welcomeLable1;
	UILabel *welcomeTextLabel;
	UIImageView *iconImage;
	UIImageView *bg;
	UILabel *textlabel;
	UILabel *valuelabel;
}
@end

@interface UPOMP_CPChangeInfo : UPOMP_CPUI<UITableViewDataSource,UITableViewDelegate>{
	UIButton *okButton;
	UIButton *escButton;
	NSMutableArray *array;
	UIImageView *titelBG;
	UILabel *welcomeLable;
	UILabel *welcomeLable1;
	UILabel *welcomeTextLabel;
	UIImageView *iconImage;
	
	UIImageView *bg;
	UILabel *textlabel;
	UILabel *valuelabel;
	UIImageView *bg2;
	UILabel *textlabel2;
	UILabel *valuelabel2;
}
@end

@interface UPOMP_CPPayDetail : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate>{
	UIButton *okButton;
	UIButton *escButton;
}
@end

@interface UPOMP_CPCommonDetail : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate,UPOMP_KaTabBarDelegate>{
	UIButton *okButton;
	UIButton *escButton;
	UIButton *leftButton;
	UIButton *rightButton;
	UIImageView *leftImage;
	UIImageView *rightImage;
	UILabel *leftLabel;
	UILabel *rightLabel;
	int panType;
	UIImageView *bg2;
	UILabel *textlabel2;
	UIImageView *titelBG;
	UILabel *welcomeLable;
	UILabel *welcomeLable1;
	UILabel *welcomeTextLabel;
	UIImageView *iconImage;
	UIImageView *bg;
	UILabel *textlabel;
	UILabel *valuelabel;
	UIImageView *imageView;
	UPOMP_KaTabBar *tabbar;
	UPOMP_KaTabItem *commItem;
	UPOMP_KaTabItem *attestationItem;
	UPOMP_KaTabItem *cardItem;
	NSMutableArray *array;
}
@end

@interface UPOMP_CPPayCardList : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate,UPOMP_KaTabBarDelegate> {
	UIButton *okButton;
	UIButton *escButton;
	NSString *cardMobileNum;
	UIButton *moreButton;
	int netIndex;
	UIImageView *bg;
	UILabel *textlabel;
	UILabel *valuelabel;
	UIImageView *bg2;
	UILabel *textlabel2;
	UILabel *valuelabel2;
	UIImageView *bg3;
	UILabel *textlabel3;
	UILabel *valuelabel3;
	
	UIImageView *titelBG;
	UILabel *welcomeLable;
	UILabel *welcomeLable1;
	UILabel *welcomeTextLabel;
	UIImageView *iconImage;
	UPOMP_CPPushSMSCell *sms;
	int type;
	
	UIImageView *imageView;
	UPOMP_KaTabBar *tabbar;
	UPOMP_KaTabItem *commItem;
	UPOMP_KaTabItem *attestationItem;
	UPOMP_KaTabItem *cardItem;
}
@end

@interface UPOMP_CPUserPayCardList : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate> {
	UIImageView *titelImage;
    UIImageView *titelBotImage;
	UILabel *titelLabel;
	UIButton *okButton;
	UIButton *escButton;
    UIButton *restButton;
    int type;
}
-(void)setSelectIndex:(int)index;
@end

@interface UPOMP_MyPayButton : UIButton{
	int index;
	UPOMP_CPUserPayCardList *list;
}
@property int index;
-(void)setCPCardList:(UPOMP_CPUserPayCardList*)cardlist;
@end

@interface UPOMP_CPPayFinish : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate> {
	UIButton *okButton;
	int cellHeight;
}
@end

@interface UPOMP_CPPayMode : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate,UPOMP_KaTabBarDelegate>{
	UIImageView *imageView;
	UPOMP_KaTabBar *tabbar;
	NSArray *array;
	UPOMP_CPPage *page;
	UPOMP_CPPayCommon *payCommon;
	UPOMP_CPPayCard *payCard;
	UPOMP_CPPayAttestation *payAttestation;
	UPOMP_KaTabItem *commItem;
	UPOMP_KaTabItem *attestationItem;
	UPOMP_KaTabItem *cardItem;
}
@end

@interface UPOMP_CPUserMain : UPOMP_CPUI <UPOMP_KaTabBarDelegate,UITableViewDataSource,UITableViewDelegate>{
	UPOMP_KaTabBar *tabbar;
	NSArray *array;
	UPOMP_CPPage *page;
	UPOMP_CPLogin *login;
	UPOMP_CPRegister *registe;
	UIImageView *imageView;
	UPOMP_KaTabItem *loginItem;
	UPOMP_KaTabItem *registeItem;
}
@end

@interface UPOMP_CPForgetPassword : UPOMP_CPUI<UITableViewDataSource,UITableViewDelegate>{
	UIButton *okButton;
	UIButton *escButton;
	NSMutableArray *array;
}
@end

@interface UPOMP_CPRestPassword : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate>{
	NSMutableArray *array;
	UIButton *okButton;
	UIButton *escButton;
	UIImageView *bg;
	UILabel *textlabel;
	UILabel *valuelabel;
}
@end

@interface UPOMP_CPUserInfo : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate> {
	UIImageView *titelBG;
	UILabel *welcomeLable;
	UILabel *welcomeLable1;
	UILabel *welcomeTextLabel;
	UIImageView *iconImage;
	UIButton *passButton;
	UIButton *phoneButton;
}
@end

@interface UPOMP_MyNavigationBar : UINavigationBar{
	
}
@end

@interface UPOMP_CPNavigationBar : UPOMP_CPUI {
	UPOMP_MyNavigationBar *myNaBar;
	UILabel *label;
}
-(void)setLabelText:(NSString*)str;
-(void)back;
-(void)back:(int)num;
-(void)setBarItemByStyle:(int)style title:(NSString*)str;
-(void)popItem;
@end

@interface UPOMP_CPLoading : UPOMP_CPUI {
	UIImageView *uView;
	UIImageView *uViews;
	UIView *bgView;
	UIView *bgView2;
	UIActivityIndicatorView *aciv;
	UILabel *label;
	UIButton *overButton;
	UPOMP_CPNet *net;
	BOOL isFirst;
	UIImageView *opening;
	UILabel *openingLabel;
	UILabel *openlabelText;
	UIActivityIndicatorView *openingaciv;
	UIImageView *logo;
}
-(void)startNet:(NSString*)titel cpNet:(UPOMP_CPNet*)cnet;
-(void)overNet;
-(void)setView:(UPOMP_CPView*)sView;
@end

@interface UPOMP_CPTabBar : UIView {
	UPOMP *mainView;
	UIImageView* defaultImageView1;
	UIImageView* defaultImageView2;
	UIImageView* defaultImageView3;
	UIImageView* defaultImageView4;
	UIImageView* onImageView1;
	UIImageView* onImageView2;
	UIImageView* onImageView3;
	UIButton *button1;
	UIButton *button2;
	UIButton *button3;
	UIButton *button4;
	int selectedIndex;
}
-(void)setSelecetView;
- (id)initWithFrame:(CGRect)frame mainView:(UPOMP*)mView;
@property int selectedIndex;
@end


@interface UPOMP_CPCardList : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate>{
	UIImageView *textImage;
	UIImageView *textImageBG;
	UIImageView *textImageBot;
	UIImageView *titelImage;
    UIImageView *titelBotImage;
	UILabel *titelLabel;
	UILabel *textLabel;
	UIButton *okButton;
	UIButton *restButton;
	int type;
}
-(void)setSelectIndex:(int)index;
@end

@interface UPOMP_MyButton : UIButton{
	int index;
	UPOMP_CPCardList *list;
}
@property int index;
-(void)setCPCardList:(UPOMP_CPCardList*)cardlist;
@end

@interface UPOMP_CPNewCard : UPOMP_CPUI <UIAlertViewDelegate,UITableViewDataSource,UITableViewDelegate>{
	int panType;
	UIButton *okButton;
	UIAlertView *alert;
	UIButton *leftButton;
	UIButton *rightButton;
	UIImageView *leftImage;
	UIImageView *rightImage;
	UILabel *leftLabel;
	UILabel *rightLabel;
	UIButton *escButton;
	UIImageView *bg;
	UILabel *textlabel;
	UILabel *valuelabel;
	UIImageView *bg2;
	UILabel *textlabel2;
	NSMutableArray *myArray;
	UIButton *agreement;
	UILabel *mylabel;
	BOOL isRead;
}
@end

@interface UPOMP_CPCardBalance : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate>{
	NSString *addAmt;
	NSString *des;
	UIButton *okButton;
	UIButton *escButton;
	BOOL canOK;
	UPOMP_CPPasswordTextFieldCell *passCell;
	BOOL selected;
}
@end
