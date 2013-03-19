//
//  UPOMP_iPad_RestPassword.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-2.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad.h"
#import "UPOMP_iPad_Page.h"
#import "UPOMP_iPad_GetSecureQuestionPage.h"
#import "UPOMP_iPad_RestPasswordPage.h"

@interface UPOMP_iPad_RestPassword : UPOMP_iPad_UI <UITableViewDataSource,UITableViewDelegate>{
    NSArray *pageArray;
    UPOMP_iPad_Page *page;
    int pageIndex;
    NSString *loginName;
    NSString *secureQuestion;
}
    
@end
