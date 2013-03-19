//
//  UPOMP_iPad_TitelBar.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class UPOMP_iPad;
@interface UPOMP_iPad_TitelBar : UIView {
	UILabel *label;
	NSString *imageName;
	UPOMP_iPad *mainView;
}
- (id)initWithFrame:(CGRect)frame name:(NSString*)name mainView:(UPOMP_iPad*)view;
- (void)setTitel:(NSString*)text;
@property BOOL hasLogo;
@end
