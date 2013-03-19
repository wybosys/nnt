//
//  MAMultiPoint.h
//  MAMapKit
//
//  
//  Copyright (c) 2011年 Autonavi Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "MAShape.h"
#import "MAGeometry.h"
#import "MATypes.h"

/// 该类用于定义多个坐标点
@interface MAMultiPoint : MAShape {
    @package
    MAMapPoint *_points;
    NSUInteger _pointCount;
    MAMapRect _boundingRect;
}

/// 坐标点数组
@property (nonatomic, readonly) MAMapPoint *points;

/// 坐标点的个数
@property (nonatomic, readonly) NSUInteger pointCount;

/**
 *将经纬度坐标数据转换为直角坐标点数据，并拷贝到指定的数组中
 *@param coords 经纬度坐标数组，转换后的坐标将存储到该数组中，该数组长度必须大于等于要拷贝的坐标点的个数（range.length）
 *@param range 指定要拷贝的数据段 
 */
- (void)getCoordinates:(CLLocationCoordinate2D *)coords range:(NSRange)range;

@end