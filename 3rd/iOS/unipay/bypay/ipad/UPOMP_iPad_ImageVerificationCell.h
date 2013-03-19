//
//  UPOMP_iPad_ImageVerificationCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-29.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"
#import "UPOMP_iPad_KaNet.h"

@interface UPOMP_iPad_ImageVerificationCell : UPOMP_iPad_Cell <UITextFieldDelegate,UPOMP_iPad_KaNetDelegate> {
	UITextField *field;
	UIView *buttonBG;
	UIButton *imageButton;
	UIButton *restButton;
	UIActivityIndicatorView *aciv;
	UPOMP_iPad_KaNet *net;
	int netIndex;
	NSString *validateCodeUrl;
	BOOL canReLoad;
}
@end
