//
//  UPOMP_iPad_OrderInfoView.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class UPOMP_iPad;
@interface UPOMP_iPad_OrderInfoView : UIView {
	UPOMP_iPad *mainView;
	int desMode;
}
- (id)initWithFrame:(CGRect)frame mainView:(UPOMP_iPad*)view;
@end
