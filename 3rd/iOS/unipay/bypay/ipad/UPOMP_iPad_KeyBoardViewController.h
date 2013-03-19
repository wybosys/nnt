//
//  UPOMP_iPad_KeyBoardViewController.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-13.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMP_iPad_KeyBoardView.h"
@class UPOMP_iPad;

@interface UPOMP_iPad_KeyBoardViewController : UIViewController{
    UPOMP_iPad_KeyBoardView *keyboardView;
    UPOMP_iPad *mainView;
}
- (id)initWithMainView:(UPOMP_iPad*)mainView;
- (void)restKeyBoard;
- (void)setKeyBoardType:(BOOL)isOnlyNum;
- (void)setKeyBoardButtonTitel:(NSString*)titel;
- (void)setDelegate:(id)del;
@end
