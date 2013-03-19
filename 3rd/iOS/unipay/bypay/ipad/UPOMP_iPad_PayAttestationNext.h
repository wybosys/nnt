//
//  UPOMP_iPad_PayAttestationNext.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-9.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Page.h"
#import "UPOMP_iPad.h"
#import "UPOMP_iPad_SMSTextFieldCell.h"
#import "UPOMP_iPad_InfoCell.h"
#import "UPOMP_iPad_PoperAsstestationTableViewController.h"
@interface UPOMP_iPad_AttestationWelcomeView: UIView{
    UPOMP_iPad *mainView;
    
}
- (id)initWithFrame:(CGRect)frame mainView:(UPOMP_iPad *)view;
@property BOOL canDraw;
@end
@interface UPOMP_iPad_PayAttestationNext : UPOMP_iPad_Page<UPOMP_iPad_KaNetDelegate,UPOMP_iPad_PoperTabelViewControllerDelegate,UIPopoverControllerDelegate>{
    UIButton *okButton;
    UIButton *backButton;
    UIImageView *line;
    UIImageView *topLine;
    UIImageView *line2;
    BOOL netOver;
    int netIndex;
    NSArray *cardListArray;
    int defaultIndex;
    int netOverType;
    UPOMP_iPad_AttestationWelcomeView *welcome;
    UPOMP_iPad_SMSTextFieldCell *smsCell;
    UPOMP_iPad_InfoCell *cardNumCell;
    UPOMP_iPad_InfoCell *phoneNumCell;
    NSDictionary *dic;
    UILabel *infoStr;
    UIButton *moreButton;
    int maxCount;
    UIPopoverController *popController;
    UPOMP_iPad_PoperAsstestationTableViewController *tabelViewController;
    NSMutableArray *cardNameArray;
    int selectIndex;
}

@end
