//
//  UPOMP_iPad_UserInfo.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-4.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_UI.h"
#import "UPOMP_iPad_HeaderView.h"
#import "UPOMP_iPad_UserInfoView.h"
#import "UPOMP_iPad_InfoCell.h"

@interface UPOMP_iPad_UserInfo : UPOMP_iPad_UI<UPOMP_iPad_KaNetDelegate,UITableViewDataSource,UITableViewDelegate>{
    NSMutableArray *headerArray;
    int selectedIndex;
    UPOMP_iPad_UserInfoView *userInfo;
    NSMutableArray *changePasswordArray;
    NSMutableArray *changePhoneArray;
    UIButton *changPasswordButton;
    UIButton *changPhoneButton;
    UIImageView *line;
    UIImageView *tipsBG;
	UILabel *tipsTextLabel;
    BOOL isUP;
}

@end
