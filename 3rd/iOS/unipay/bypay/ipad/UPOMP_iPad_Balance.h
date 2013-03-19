//
//  UPOMP_iPad_Balance.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-7.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_UI.h"
#import "UPOMP_iPad_InfoCell.h"
#import "UPOMP_iPad_PinTextFieldCell.h"

@interface UPOMP_iPad_Balance : UPOMP_iPad_UI<UPOMP_iPad_KaNetDelegate,UITableViewDataSource,UITableViewDelegate>{
    UIImageView *titelBg;
    UILabel *titelLabel;
    UPOMP_iPad_InfoCell *cardName;
    NSDictionary *dic;
    UPOMP_iPad_PinTextFieldCell *pin;
    BOOL hasNet;
    UIButton *balanceButton;
    UIButton *backButton;
    UIImageView *line1;
    UIImageView *line2;
    UIImageView *icon;
    UILabel *balanceTitel;
    UILabel *balanceText;
}

@end
