//
//  UPOMP_iPad_LoadingView.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-17.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMP_iPad_View.h"

@interface UPOMP_iPad_LoadingView : UPOMP_iPad_View <UPOMP_iPad_KaNetDelegate>{
	BOOL needReconnect;
    int netMode;
}

@end
