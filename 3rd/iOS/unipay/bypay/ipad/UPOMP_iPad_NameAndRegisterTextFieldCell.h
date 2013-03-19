//
//  UPOMP_iPad_NameAndRegisterTextFieldCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-8.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"

@interface UPOMP_iPad_NameAndRegisterTextFieldCell : UPOMP_iPad_Cell <UITextFieldDelegate>{
    UITextField *field;
    UIButton *registerButton;
}

@end
