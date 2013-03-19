//
//  MAPolygon.h
//  MAMapKit
//
//  
//  Copyright (c) 2011年 Autonavi Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MAMultiPoint.h"
#import "MAOverlay.h"

/// 此类用于定义一个多边形区域
@interface MAPolygon : MAMultiPoint <MAOverlay> {
    @package
    CLLocationCoordinate2D _centroid;
    BOOL _isDefinitelyConvex;
}


/**
 *根据多个点生成多边形
 *@param coords 经纬度坐标点数组，这些点将被拷贝到生成的多边形对象中
 *@param count 点的个数
 *@return 新生成的多边形对象
 */
+ (MAPolygon*)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;
@end
