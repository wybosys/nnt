//
//  UPOMP_iPad_RestPasswordPage.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-2.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Page.h"
#import "UPOMP_iPad_InfoCell.h"

@interface UPOMP_iPad_RestPasswordPage : UPOMP_iPad_Page <UPOMP_iPad_KaNetDelegate>{
    UIButton *backButton;
    UIButton *restButton;
    UPOMP_iPad_InfoCell *secureQuestionCell;
}
@end
