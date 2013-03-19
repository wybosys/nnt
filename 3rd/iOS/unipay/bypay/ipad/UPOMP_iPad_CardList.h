//
//  UPOMP_iPad_CardList.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-5.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "UPOMP_iPad_UI.h"
#import "UPOMP_iPad_CardInfoView.h"

@interface UPOMP_iPad_CardList :UPOMP_iPad_UI <UPOMP_iPad_KaNetDelegate,UITableViewDataSource,UITableViewDelegate,UIAlertViewDelegate>{
    UIImageView *tipsBG;
	UILabel *tipsTextLabel;
    int netStatus;
    NSArray *cardListArray;
    int maxCount;
    int selectIndex;
    UIButton *reloadButton;
    UIButton *addButton;
    UIImageView *topLine;
    UIImageView *bottomLine;
    UILabel *titelLabel;
    NSMutableArray *headerArray;
    UPOMP_iPad_CardInfoView *cardInfo;
    int netIndex;
    UIAlertView *alert;
}
@end
