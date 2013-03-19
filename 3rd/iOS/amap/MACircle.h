//
//  MACircle.h
//  MAMapKit
//
//  
//  Copyright (c) 2011年 Autonavi Inc. All rights reserved.
//

#import "MAShape.h"
#import "MAOverlay.h"
#import "MAGeometry.h"

/// 该类用于定义一个圆
@interface MACircle : MAShape <MAOverlay> {
    @package
    CLLocationCoordinate2D _coordinate;
    CLLocationDistance _radius;
    
    MAMapRect _boundingMapRect;
}

/**
 *根据中心点和半径生成圆
 *@param coord 中心点的经纬度坐标
 *@param radius 半径，单位：米
 *@return 新生成的圆
 */
+ (MACircle *)circleWithCenterCoordinate:(CLLocationCoordinate2D)coord
                                   radius:(CLLocationDistance)radius;


/// 中心点坐标
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/// 半径，单位：米
@property (nonatomic, readonly) CLLocationDistance radius;

/// 该圆的外接矩形
@property (nonatomic, readonly) MAMapRect boundingMapRect; 

@end
