//
//  UPOMP_iPad_HeaderView.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-4.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMP_iPad.h"

@interface UPOMP_iPad_HeaderView : UIView{
    UPOMP_iPad_View *cpview;
    int index;
    BOOL isSelected;
    BOOL isFirst;
    NSString *titel;
   // UIImageView *arrow;
}
- (id)initWithFrame:(CGRect)frame view:(UPOMP_iPad_View*)view index:(int)i titel:(NSString*)str;
- (void)setSelected:(BOOL)bo;
- (void)setFirst:(BOOL)bo;
@property BOOL isSelected; 
@end
