//
//  MAPolyline.h
//  MAMapKit
//
//  
//  Copyright (c) 2011年 Autonavi Inc. All rights reserved.
//


#import "MAMultiPoint.h"
#import "MAOverlay.h"

/// 此类用于定义一段折线
@interface MAPolyline : MAMultiPoint <MAOverlay>
/**
 *根据指定坐标点生成一段折线
 *@param coords 指定的经纬度坐标点数组
 *@param count 坐标点的个数
 *@return 新生成的折线对象
 */
+ (MAPolyline *)polylineWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end