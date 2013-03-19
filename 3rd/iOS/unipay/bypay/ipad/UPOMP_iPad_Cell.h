//
//  UPOMP_iPad_Cell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad.h"
#import "UPOMP_iPad_CellBGView.h"

@interface UPOMP_iPad_Cell : NSObject {
	NSString *key;
	NSString *titel;
	UILabel *titelLabel;
	UITableViewCell *cell;
	UPOMP_iPad_CellBGView *bg;
}
- (id)init:(UPOMP_iPad_View*)cView;
- (void)restText;
- (void)start;
- (void)setSelect;
- (void)noSelect;
- (void)rest;
- (void)stopThread;
- (NSString*)getValue;
- (UITableViewCell*)getCell;
- (NSString*)checkFinish;
- (NSString*)getCompareText;
- (void)rowAnimating;
- (void)scrollViewDidScroll;
- (void)action:(int)index;
-(void)setPlaceholder:(NSString*)str;
@property BOOL isComplexityCheck;
@property BOOL isDownloadFinish;
@property BOOL isNoCheck;
@property BOOL isAnimating;
@property(nonatomic,retain)NSIndexPath *indexPath;
@property(nonatomic,assign)UPOMP_iPad_Cell *compareCell;
@property(nonatomic,retain)NSString *key;
@property(nonatomic,retain)NSString *titel;
@property(nonatomic,readonly)UPOMP_iPad_View *cpview;
@end
