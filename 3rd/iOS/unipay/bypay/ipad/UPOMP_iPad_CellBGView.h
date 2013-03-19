//
//  UPOMP_iPad_CellBGView.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class UPOMP_iPad_Cell;
@interface UPOMP_iPad_CellBGView : UIView {
	BOOL isSelect;
	UPOMP_iPad_Cell *myCell;
}
-(void)setCell:(UPOMP_iPad_Cell*)cell;
-(void)setSelect:(BOOL)b;
-(BOOL)getSelect;
@end
