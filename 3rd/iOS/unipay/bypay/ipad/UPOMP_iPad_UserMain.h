//
//  UPOMP_iPad_UserMain.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_UI.h"
#import "UPOMP_iPad.h"
#import "UPOMP_iPad_Login.h"
#import "UPOMP_iPad_Register.h"

@interface UPOMP_iPad_UserMain : UPOMP_iPad_UI <UPOMP_iPad_KaTabBarDelegate,UITableViewDataSource,UITableViewDelegate,UIScrollViewDelegate>{
	UPOMP_iPad_KaTabBar *menuTabBar;
	UPOMP_iPad_Page *page;
	NSArray *pageArray;
	UIImageView *tipsBG;
	UILabel *tipsTextLabel;
}

@end
