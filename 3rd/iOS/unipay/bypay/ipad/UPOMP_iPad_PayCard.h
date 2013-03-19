//
//  UPOMP_iPad_PayCard.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-8.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Page.h"
@interface UPOMP_iPad_PayCard : UPOMP_iPad_Page<UPOMP_iPad_KaNetDelegate>{
    UIButton *payButton;
    UIImageView *line;
    UIImageView *topLine;
    UILabel *titelLabel;
    int netIndex;
}

@end
