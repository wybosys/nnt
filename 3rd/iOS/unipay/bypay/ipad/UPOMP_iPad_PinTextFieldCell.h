//
//  UPOMP_iPad_PinTextFieldCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-6.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"
#import "UPOMP_iPad_KeyBoardView.h"

@interface UPOMP_iPad_PinTextFieldCell : UPOMP_iPad_Cell <UITextFieldDelegate,UIPopoverControllerDelegate,UPOMP_iPad_KeyBoardViewDelegate>{
    UITextField *field;
	int maxLenght;
	NSString *comparePan;
}
@property int maxLenght;
@property (nonatomic,retain)NSString *comparePan;
@end
