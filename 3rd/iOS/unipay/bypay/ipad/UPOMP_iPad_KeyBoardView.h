//
//  UPOMP_iPad_KeyBoardView.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-13.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import "UPOMP_iPad_View.h"
@class UPOMP_iPad;

@protocol UPOMP_iPad_KeyBoardViewDelegate
-(void)okbuttonAction;
-(void)keyAction:(NSString*)text;
@end

@interface UPOMP_iPad_KeyBoardView : UIView{
    UPOMP_iPad *mainView;
    NSMutableArray *numArray;
    NSMutableArray *textArray;
    NSMutableArray *otherArray;
    UIButton *numButton;
    UIButton *textButton;
    UIButton *otherButton;
    UIButton *okButton;
    BOOL isBig;
    int selectMode;
    id <UPOMP_iPad_KeyBoardViewDelegate> delegate;
}
- (id)initWithFrame:(CGRect)frame mainView:(UPOMP_iPad*)view;
- (void)rest;
- (void)setType:(BOOL)b;
- (void)setButtonTitel:(NSString*)titel;
@property (nonatomic, assign) id <UPOMP_iPad_KeyBoardViewDelegate> delegate;
@end
