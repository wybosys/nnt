//
//  UPOMP_iPad_PhoneNumTextFieldCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-30.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"

@interface UPOMP_iPad_PhoneNumTextFieldCell : UPOMP_iPad_Cell <UITextFieldDelegate> {
	UITextField *field;
	NSString *placeholderPhoneNum;
}
-(void)setPlaceholderPhoneNum:(NSString*)phoneNum;
@end
