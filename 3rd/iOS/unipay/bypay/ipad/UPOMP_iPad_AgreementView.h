//
//  UPOMP_iPad_AgreementView.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-8.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class UPOMP_iPad;
@interface UPOMP_iPad_AgreementView : UIView{
    UIButton *backButton;
    UITextView *textview;
    UILabel *lable;
    UPOMP_iPad *mainView;
    UIView *bg;
}
- (id)initWithFrame:(CGRect)frame mainView:(UPOMP_iPad*)view;
@end
