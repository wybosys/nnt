//
//  UPOMP_iPad_PoperAsstestationTableViewController.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-12.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMP_iPad_PoperTabelViewController.h"
#import "UPOMP_iPad.h"

@interface UPOMP_iPad_PoperAsstestationTableViewController : UITableViewController{
    id <UPOMP_iPad_PoperTabelViewControllerDelegate> delegate;
    UPOMP_iPad *mainView;
}
-(void)setMainView:(UPOMP_iPad*)view;
@property (nonatomic, assign) id <UPOMP_iPad_PoperTabelViewControllerDelegate> delegate;
@property (nonatomic, assign) NSArray *infos;
@property BOOL hasAdd;
@property int selectIndex;
@end
