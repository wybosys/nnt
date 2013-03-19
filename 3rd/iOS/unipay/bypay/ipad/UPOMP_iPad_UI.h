//
//  UPOMP_iPad_UI.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-23.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_View.h"

@interface UPOMP_iPad_UI : NSObject {
	UPOMP_iPad_View *cpview;
	int uiHeight;
	NSIndexPath *selectedCellIndexPath;
	UITableView *tableView;
}
- (id)init:(UPOMP_iPad_View*)cView;
- (void)start;
- (void)willVisual;
- (void)willRelease;
- (void)keyboardWasShown:(NSNotification *)notif;
- (void)keyboardWasHide:(NSNotification *)notif;
- (void)restCheckImage;
- (void)netWork;
- (void)nextCell;
- (void)tableUP;
- (void)tableDown;
- (void)rowToSelectedCell;
- (void)UIAction:(int)index;
- (void)setText:(NSString*)str index:(int)index;
- (NSString*)getTextWithIndex:(int)index;
- (void)stopThread;
@property BOOL hasKeyBar;
@end
