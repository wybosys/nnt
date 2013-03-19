//
//  UPOMP_iPad_DataViewController.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-6.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UPOMP_iPad_DataViewController : UIViewController<UIPickerViewDelegate,UIPickerViewDataSource>{
    UIPickerView *pickerView;
    NSMutableArray *yyArray;
    NSMutableArray *mmArray;
    int year;
    UILabel *yyPickerLable;
    UILabel *mmPickerLable;
    int yyText;
    int mmText;
}
- (NSString*)getYYMM;
- (void)rest;
@end
