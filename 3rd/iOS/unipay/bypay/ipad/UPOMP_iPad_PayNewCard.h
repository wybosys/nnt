//
//  UPOMP_iPad_PayNewCard.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-9.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_UI.h"
#import "UPOMP_iPad_InfoCell.h"

@interface UPOMP_iPad_PayNewCard : UPOMP_iPad_UI<UPOMP_iPad_KaNetDelegate,UITableViewDataSource,UITableViewDelegate>{
    UIButton *addButton;
    UIButton *backButton;
    UIImageView *titelBg;
    UILabel *titelLabel;
    NSMutableArray *array;
    UPOMP_iPad_InfoCell *userName;
    UIButton *rightButton;
    UIButton *leftButton;
    UILabel *selectLabel;
    UIImageView *onIcon;
    UIImageView *offIcon;
    int cardType;
    UILabel *rightLabel;
    UILabel *leftLabel;
    BOOL willDefault;
    UIButton *defaultButton;
    UILabel *defaultLabel;
    UIAlertView *alert;
}

@end
