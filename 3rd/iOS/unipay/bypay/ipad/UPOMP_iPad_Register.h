//
//  UPOMP_iPad_Register.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Page.h"

@interface UPOMP_iPad_Register : UPOMP_iPad_Page <UPOMP_iPad_KaNetDelegate>{
	UIButton *registerButton;
	UIButton *agreementButton;
	UIButton *showAgreementButton;
	UILabel *agreementLabel;
    BOOL agreementAgree;
}

@end
