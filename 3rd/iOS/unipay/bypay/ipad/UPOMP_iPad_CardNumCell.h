//
//  UPOMP_iPad_CardNumCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-6.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_Cell.h"

@interface UPOMP_iPad_CardNumCell : UPOMP_iPad_Cell<UITextViewDelegate>{
    UILabel *label;
	UITextView *myTextView;
	UIView *bgView;
	NSMutableString *tempNo;
}

@end
