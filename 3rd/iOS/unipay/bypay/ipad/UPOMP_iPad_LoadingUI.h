//
//  UPOMP_iPad_Loading.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-23.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_UI.h"

@interface UPOMP_iPad_LoadingUI : UPOMP_iPad_UI {
	UPOMP_iPad_KaNet *net;
	BOOL isFirst;
	UIImageView *openingImageView;
	UILabel *loadingLable;
	UILabel *companyLable;
	UIActivityIndicatorView *aciv;
    UIView *BGView;
    UIImageView *canelBG;
    UIImageView *noCanelBG;
    UIImageView *logo;
    UIButton *cancelButton;
}
-(void)startNet:(NSString*)titel net:(UPOMP_iPad_KaNet*)cnet;
-(void)overNet;
-(void)cancelNet;
@end
