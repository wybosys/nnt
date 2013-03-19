//
//  UPOMP_iPad_Page.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "UPOMP_iPad_View.h"

@interface UPOMP_iPad_Page : NSObject {
	NSMutableArray *array;
	UPOMP_iPad_View *cpview;
}
- (void)start;
- (id)initWithView:(UPOMP_iPad_View*)cView;
- (void)restCheckImage;
- (void)stopThread;
- (void)netWork;
- (void)nextCell;
- (NSInteger)numberOfSectionsInTableView;
- (CGFloat)heightForRowAtIndexPath:(NSIndexPath *)indexPath;
- (NSInteger)numberOfRowsInSection:(NSInteger)section;
- (UITableViewCell *)cellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)keyboardWasShown:(NSNotification *)notif;
- (void)keyboardWasHide:(NSNotification *)notif;
- (void)actionWithIndex:(int)Index;
@end
