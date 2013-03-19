//
//  SecureQuestionTabelViewController.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-1.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol UPOMP_iPad_PoperTabelViewControllerDelegate
// Sent when the user selects a row in the recent searches list.
- (void)didSelectRow:(int)row;
@end

@interface UPOMP_iPad_PoperTabelViewController : UITableViewController{
    id <UPOMP_iPad_PoperTabelViewControllerDelegate> delegate;
}
@property (nonatomic, assign) id <UPOMP_iPad_PoperTabelViewControllerDelegate> delegate;
@property (nonatomic, assign) NSArray *infos;
@end
