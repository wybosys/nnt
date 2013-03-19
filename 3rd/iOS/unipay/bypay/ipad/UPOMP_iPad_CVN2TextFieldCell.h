//
//  UPOMP_iPad_CVN2TextFieldCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-6.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"
#import "UPOMP_iPad_KeyBoardView.h"

@interface UPOMP_iPad_CVN2TextFieldCell : UPOMP_iPad_Cell <UITextFieldDelegate,UIPopoverControllerDelegate,UPOMP_iPad_KeyBoardViewDelegate>{
    UITextField *field;
}

@end
