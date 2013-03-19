//
//  UPOMP_iPad_ViewCenter.h
//  UPOMP_iPad
//
//  Created by pei xunjun on 11-11-29.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMP_iPad_UI.h"
#import "UPOMP_iPad_View.h"

@interface UPOMP_iPad_ViewCenter : NSObject {

}
-(UPOMP_iPad_UI*)getUIByID:(int)vID view:(UPOMP_iPad_View*)view;
@end
