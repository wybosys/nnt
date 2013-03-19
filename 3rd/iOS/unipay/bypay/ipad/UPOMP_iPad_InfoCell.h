//
//  UPOMP_iPad_InfoCell.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-12-3.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UPOMP_iPad.h"

@interface UPOMP_iPad_InfoCell : NSObject{
    UILabel *titelLabel;
	UIImageView *bg;
    UILabel *infoLabel;
    UITableViewCell *cell;
}
- (id)initWithMainView:(UPOMP_iPad*)mainView;
- (UITableViewCell*)getCell;
- (void)setTitelText:(NSString*)str;
- (void)setInfoText:(NSString*)str;
@end
