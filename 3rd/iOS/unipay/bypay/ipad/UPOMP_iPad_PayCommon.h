//
//  UPOMP_iPad_PayCommon.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-7.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Page.h"

@interface UPOMP_iPad_PayCommon : UPOMP_iPad_Page<UPOMP_iPad_KaNetDelegate>{
    UIButton *payButton;
    UIButton *rightButton;
    UIButton *leftButton;
    UILabel *selectLabel;
    UIImageView *onIcon;
    UIImageView *offIcon;
    int cardType;
    UILabel *rightLabel;
    UILabel *leftLabel;
    UIImageView *line;
    UIImageView *topLine;
    UILabel *titelLabel;
}

@end
