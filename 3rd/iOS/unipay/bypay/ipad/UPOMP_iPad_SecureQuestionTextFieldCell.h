//
//  UPOMP_iPad_SecureQuestionTextFieldCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-30.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"
#import "UPOMP_iPad_PoperTabelViewController.h"

@interface UPOMP_iPad_SecureQuestionTextFieldCell : UPOMP_iPad_Cell <UITextFieldDelegate,UPOMP_iPad_PoperTabelViewControllerDelegate,UIPopoverControllerDelegate> {
	UITextField *field;
    UIButton *listButton;
    UIPopoverController *popController;
    UPOMP_iPad_PoperTabelViewController *tabelViewController;
    BOOL poperUP;
}

@end
