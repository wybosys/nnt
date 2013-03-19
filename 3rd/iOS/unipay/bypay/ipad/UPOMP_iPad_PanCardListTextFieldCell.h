//
//  UPOMP_iPad_PanCardList.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-8.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"
#import "UPOMP_iPad_PoperAsstestationTableViewController.h"

@interface UPOMP_iPad_PanCardListTextFieldCell : UPOMP_iPad_Cell<UITextFieldDelegate,UPOMP_iPad_PoperTabelViewControllerDelegate,UIPopoverControllerDelegate>{
    UITextField *field;
    UIPopoverController *popController;
    UPOMP_iPad_PoperAsstestationTableViewController *tabelViewController;
    UIButton *listButton;
    BOOL poperUP;
}

@end
