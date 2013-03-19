//
//  UPOMP_iPad_PayFinish.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-8.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_UI.h"

@interface UPOMP_iPad_PayFinish : UPOMP_iPad_UI{
    BOOL isSuccess;
    UILabel *titelLabel;
    UILabel *merchantOrderIdLable;
    UILabel *merchantOrderTimeLable;
    UILabel *merchantOrderAmtLable;
    UILabel *cupsQidLable;
    UIImageView *line;
    UIImageView *line2;
    UIButton *escButton;
    UIImageView *icon;
    UILabel *errorLable;
}

@end
