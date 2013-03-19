//
//  CPPayRegister.h
//  UPOMP
//
//  Created by pei xunjun on 11-9-30.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMPUI.h"

@interface UPOMP_CPPayRegister : UPOMP_CPUI<UITableViewDataSource,UITableViewDelegate>{
	UIButton *okButton;
	UIButton *escButton;
	UIButton *registInfoButton;
	UIButton *agreement;
	UILabel *mylabel;
	BOOL isRead;
	NSMutableArray *array;
}

@end
