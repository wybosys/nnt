//
//  MAPointAnnotation.h
//  MAMapKit
//
//  Created by yin cai on 12-2-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import "MAShape.h"

@interface MAPointAnnotation : MAShape {
    @package
    CLLocationCoordinate2D _coordinate;
}

@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end
