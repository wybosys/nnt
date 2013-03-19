//
//  CPCardInfo.h
//  UPOMP
//
//  Created by pei xunjun on 11-9-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMPUI.h"

@interface UPOMP_CPCardInfo : UPOMP_CPUI <UITableViewDataSource,UITableViewDelegate> {
	UIButton *buttonDefault;
	UIButton *buttonBack;
	UIButton *buttonBalance;
	UIButton *buttonDelete;
	int netIndex;
	UIAlertView *checkAlert;
}

@end
