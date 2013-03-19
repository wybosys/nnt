//
//  UPOMP_iPad_PayMode.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_UI.h"
#import "UPOMP_iPad.h"
#import "UPOMP_iPad_Page.h"
#import "UPOMP_iPad_Cell.h"
#import "UPOMP_iPad_PayAttestationNext.h"

@interface UPOMP_iPad_PayMode : UPOMP_iPad_UI <UPOMP_iPad_KaTabBarDelegate,UITableViewDataSource,UITableViewDelegate>{
	UPOMP_iPad_KaTabBar *menuTabBar;
    UPOMP_iPad_Page *page;
    NSArray *pageArray;
    UIImageView *tipsBG;
	UILabel *tipsTextLabel;
    int selectIndex;
    UPOMP_iPad_PayAttestationNext *attestationNext;
}

@end
