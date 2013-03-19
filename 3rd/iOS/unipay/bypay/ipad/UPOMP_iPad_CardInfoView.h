//
//  UPOMP_iPad_CardInfoView.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-6.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "UPOMP_iPad.h"

@interface UPOMP_iPad_CardInfoView : UIView{
    UPOMP_iPad_View *cpview;
    NSDictionary *dic;
    UIButton *defaultButton;
    UIButton *deleteButton;
    UIButton *balanceButton;
}
- (id)initWithFrame:(CGRect)frame cpview:(UPOMP_iPad_View *)view;
- (void)setDictionary:(NSDictionary*)d;
@end
