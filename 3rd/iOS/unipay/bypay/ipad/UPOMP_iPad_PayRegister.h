//
//  UPOMP_iPad_PayRegister.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-8.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Page.h"
#import "UPOMP_iPad_UI.h"

@interface UPOMP_iPad_PayRegister : UPOMP_iPad_UI <UITableViewDataSource,UITableViewDelegate,UIScrollViewDelegate,UPOMP_iPad_KaNetDelegate>{
    NSMutableArray *array;
    UIButton *backButton;
    UIButton *registerButton;
	UIButton *agreementButton;
	UIButton *showAgreementButton;
	UILabel *agreementLabel;
    BOOL agreementAgree;
}

@end
