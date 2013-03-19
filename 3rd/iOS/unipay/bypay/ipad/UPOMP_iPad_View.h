//
//  UPOMP_iPad_View.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-17.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMP_iPad_KaNet.h"
#import "UPOMP_iPad_TitelBar.h"

@class UPOMP_iPad;
@class UPOMP_iPad_UI;
@class UPOMP_iPad_Cell;

@interface UPOMP_iPad_View : UIView {
	UPOMP_iPad_TitelBar *titelBar;
	UPOMP_iPad *mainView;
	UIAlertView *alert;
	NSMutableArray *viewIDs;
	int myUIID;
	UPOMP_iPad_Cell *cell;
	int oldID;
	
}
- (void)start;
- (id)initWithFrame:(CGRect)frame MainView:(UPOMP_iPad*)view;
- (void)setAlertTitel:(NSString*)tString info:(NSString*)iString;
- (void)netWorkStart:(NSString*)titel;
- (void)netWork;
- (void)titelBarHasLogo:(BOOL)bo;
- (void)titelBarAddView:(UIView*)view;
- (void)titelBarSetTitel:(NSString*)text;
- (void)changeView:(int)vID;
- (void)back;
- (NSData*)setPostDataByAppName:(NSString*)appName keys:(NSArray*)keys values:(NSArray*)values anotherInfo:(NSString *)anotherStr;
- (void) keyboardWasShown:(NSNotification *)notif;
- (void) keyboardWasHide:(NSNotification *)notif;
@property(nonatomic,readonly) UPOMP_iPad *mainView;
@property(nonatomic,readonly) UPOMP_iPad_UI *myUI; 
@property(nonatomic,readonly) UPOMP_iPad_KaNet *net;
@property(nonatomic,retain) UPOMP_iPad_Cell *cell;
@end
