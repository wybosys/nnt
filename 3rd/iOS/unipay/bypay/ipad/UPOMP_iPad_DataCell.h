//
//  UPOMP_iPad_DataCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-6.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"
#import "UPOMP_iPad_DataViewController.h"


@interface UPOMP_iPad_DataCell : UPOMP_iPad_Cell <UIPopoverControllerDelegate>{
    UIButton *rightButton;
    UIButton *leftButton;
    UIImageView *rightIcon;
    UIImageView *leftIcon;
    UILabel *rightLabel;
    UILabel *leftLabel;
    UILabel *rightTextLabel;
    UILabel *leftTextLabel;
    UIPopoverController *popController;
    UPOMP_iPad_DataViewController *dataViewController;
    BOOL poperUP;
}
@end
