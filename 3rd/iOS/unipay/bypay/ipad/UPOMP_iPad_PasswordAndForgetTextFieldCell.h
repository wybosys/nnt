//
//  UPOMP_iPad_PasswordAndForgetTextFieldCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-29.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"
#import "UPOMP_iPad_KeyBoardView.h"

@interface UPOMP_iPad_PasswordAndForgetTextFieldCell : UPOMP_iPad_Cell <UITextFieldDelegate,UIPopoverControllerDelegate,UPOMP_iPad_KeyBoardViewDelegate>{
	UITextField *field;
	UIButton *forgetbutton;
}

@end
