//
//  KaBGView.h
//  UPOMP
//
//  Created by pei xunjun on 11-9-23.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class UPOMP_CPCell;
@interface UPOMP_KaBGView : UIView {
	BOOL isSelect;
	UPOMP_CPCell *myCell;
}
-(void)setCell:(UPOMP_CPCell*)cell;
-(void)setSelect:(BOOL)b;
-(BOOL)getSelect;
@end
