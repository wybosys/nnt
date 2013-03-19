//
//  KaTextFieldToolBar.h
//  UPOMP
//
//  Created by pei xunjun on 11-9-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMPView.h"

@interface UPOMP_KaTextFieldToolBar : UIToolbar {
	UPOMP_CPView *cpview;
	UIBarButtonItem *prevButtonItem;
	UIBarButtonItem *nextButtonItem;
	UIBarButtonItem *hiddenButtonItem;
	UIBarButtonItem *spaceButtonItem;
	BOOL canButton;
}
- (id)initWithFrame:(CGRect)frame cpView:(UPOMP_CPView*)view;
- (void)setprevButtonEnabled:(BOOL)b;
- (void)setnextButtonEnabled:(BOOL)b;
@end
