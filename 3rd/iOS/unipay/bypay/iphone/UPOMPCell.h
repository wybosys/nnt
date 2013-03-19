//
//  CPCell.h
//  ChinaUnionPay
//
//  Created by Anplex on 11-6-27.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "UPOMPValue.h"
#import "UPOMPView.h"
#import "UPOMPKeyBoard.h"
#import "UPOMP_KaBGView.h"

@interface UPOMP_CPCell : NSObject {
	UPOMP_CPView *cpview;
	BOOL isOverNet;
	BOOL isNoCheck;
	BOOL isPasswordCheck;
	NSString *titel;
	NSString *message;
	NSString *key;
	NSIndexPath *myIndexPath;
	UPOMP_CPCell *chenckCell;
	UITableViewCell *cell;
	NSString *checkstr;
	BOOL isNumberLock;
	UPOMP_KaBGView *bg;
	UILabel *textLabel;
}
- (void)overCell;
- (void)setText:(NSString*)text;
- (void)start;
- (UITableViewCell* )getCell;
- (NSString*)checkFinish;
- (NSString*)check;
- (void)rest;
- (NSString*)getValue;
- (NSString*)getKey;
- (id)init:(UPOMP_CPView*)cView;
- (id)init:(UPOMP_CPView*)cView check:(UPOMP_CPCell*)checkCPCell;
- (void)didSelectRowAtIndexPath;
- (void)restText;
- (void)stopThread;
- (void)keyBarDown;
- (void)setSelect;
- (void)noSelect;
-(BOOL)tableUP;
-(void)tableDown;
-(void)rowToSelectedCell;
-(void)nextRow;
@property BOOL isKeyBar;
@property BOOL isTableUP;
@property BOOL isOverNet;
@property BOOL isNoCheck;
@property BOOL isPasswordCheck;
@property(nonatomic,retain)NSIndexPath *myIndexPath;
@property(nonatomic,retain)NSString *titel;
@property(nonatomic,retain)NSString *message;
@property(nonatomic,retain)NSString *key;
@property (nonatomic, retain) UPOMP_CPCell *chenckCell;
@property (nonatomic, retain) NSString *checkstr;
@property (nonatomic) BOOL isNumberLock;
@end

@interface UPOMP_UIViewControl : UIView {
}
@end

@interface UPOMP_CPPushSMSCell : UPOMP_CPCell <UITextFieldDelegate> {
	UITextField *field;
	UIButton *button;
	UPOMP_UIViewControl *buttonmask;
	NSMutableData *netData;
	NSMutableURLRequest *request;
	NSURLConnection *conn;
	bool isComplete;
	bool isTimerOver;
	NSString *phoneNum;
	NSString *deskey;
	NSInteger secureInfo;
	NSTimer *timer;
	int freezenum;
	int misc;
	BOOL isCheck;
}
@property (retain, nonatomic) UPOMP_UIViewControl *buttonmask;
@property (retain, nonatomic) NSMutableData *netData;
@property (retain, nonatomic) NSMutableURLRequest *request;
@property (retain, nonatomic) NSURLConnection *conn;
@property bool isComplete;
@property int misc;
@property (nonatomic, retain) NSString *phoneNum;
@property (nonatomic, retain) NSString *deskey;
@property NSInteger secureInfo;
- (void)netWork;
- (void)netWorkOver:(NSData*)data;
- (BOOL)checkOver:(NSData*)data;
@end

@interface UPOMP_CPCVN2Cell : UPOMP_CPCell <UITextFieldDelegate>{
	UITextField *field;
	UPOMPKeyBoard *keyboard;
}
@end

@interface UPOMP_CPWelComeTextFeildCell : UPOMP_CPCell <UITextFieldDelegate>{
	UITextField *field;
}
@end

@interface UPOMP_CPSecureAnswerTextFeildCell : UPOMP_CPCell <UITextFieldDelegate> {
	UITextField *field;
}
@end

@interface UPOMP_CPSecureQuestionCell : UPOMP_CPCell<UIPickerViewDelegate,UIPickerViewDataSource,UITextFieldDelegate>{
	UIButton *button;
	UIPickerView *pickerView;
	UITextField *field;
	int tempRow;
}
@end

@interface UPOMP_CPEmailTextFieldCell : UPOMP_CPCell <UITextFieldDelegate>{
	UITextField *field;
}
@end

@interface UPOMP_CPRegisterNameCell : UPOMP_CPCell <UITextFieldDelegate> {
	UITextField *field;
	//UIButton *checkButton;
	//UIActivityIndicatorView *aciv;
	//UIView *bgView;
	//NSMutableData *netData;
	//NSMutableURLRequest *request;
	//NSURLConnection *conn;
	//bool isComplete;
	//NSString *deskey;
}
@end

@interface UPOMP_CPPasswordAndForgetTextFieldCell : UPOMP_CPCell <UITextFieldDelegate>{
	UITextField *field;
	UIButton *forgetbutton;
	UPOMPKeyBoard *keyboard;
}
@end

@interface UPOMP_CPNameAndRegisterButtonCell : UPOMP_CPCell <UITextFieldDelegate> {
	UITextField *field;
	UIButton *button;
}
@end

@interface UPOMP_CPNameTextFieldCell : UPOMP_CPCell <UITextFieldDelegate>{
	UITextField *field;
}
@end

@interface UPOMP_CPPasswordTextFieldCell : UPOMP_CPCell<UITextFieldDelegate> {
	UITextField *field;
	UPOMPKeyBoard *keyboard;
	NSString *pinCheckStr;
	NSString *placeholderText;
	bool isNoBG;
}
-(void)setNoBGStyle;
-(void)setTitel:(NSString *)str;
-(void)setplaceholderText:(NSString*)str;
@property (nonatomic,retain) NSString *pinCheckStr;
@end

@interface UPOMP_CPRePasswordCell : UPOMP_CPCell<UITextFieldDelegate> {
	UITextField *field;
	UPOMPKeyBoard *keyboard;
	BOOL isLast;
}
@property BOOL isLast;
@end

@interface UPOMP_CPCheckUPTextFieldCell : UPOMP_CPCell <UITextFieldDelegate>{
	UITextField *field;
	UIButton *imageView;
	UIButton *restButton;
	UIActivityIndicatorView *aciv;
	NSString *url;
	NSMutableData *netData;
	NSMutableURLRequest *request;
	NSURLConnection *conn;
	bool isComplete;
	int netIndex;
	UIView *myView;
	NSString *deskey;
}
@end

@interface UPOMP_CPPhoneTextFieldCell : UPOMP_CPCell <UITextFieldDelegate> {
	UITextField *field;
	NSString *placeholderText;
	BOOL isStar;
	NSString *value;
}
-(void)setplaceholderText:(NSString*)str;
@property BOOL isStar;
@end

@interface UPOMP_CPCommonPhoneCell : UPOMP_CPCell <UITextFieldDelegate> {
	UITextField *field;
	BOOL isStar;
//	UIButton *infoButton;
}
@end

@interface UPOMP_CPCardNumTextFieldCell : UPOMP_CPCell <UITextViewDelegate,UIScrollViewDelegate> {
	//UITextField *field;
	UILabel *label;
	UITextView *view;
	UIView *bgView;
	NSMutableString *tempNo;
}
@end

@interface UPOMP_CPPanDataCell : UPOMP_CPCell <UIPickerViewDelegate,UIPickerViewDataSource>{
	UIView *bgview;
	UIButton *yybutton;
	UILabel *yylabel;
	UIButton *mmbutton;
	UILabel *mmlabel;
	UIPickerView *yyPickerView;
	NSMutableArray *yyArray;
	NSMutableArray *mmArray;
	UILabel *yyPickerLable;
	UILabel *mmPickerLable;
	int yyText;
	int mmText;
	int year;
}
@end
