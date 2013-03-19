//
//  UPOMP_iPad_RePasswordTextFieldCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-30.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"
#import "UPOMP_iPad_KeyBoardView.h"

@interface UPOMP_iPad_RePasswordTextFieldCell : UPOMP_iPad_Cell <UITextFieldDelegate,UIPopoverControllerDelegate,UPOMP_iPad_KeyBoardViewDelegate> {
	UITextField *field;
}

@end
