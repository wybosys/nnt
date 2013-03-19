//
//  MAPolylineView.h
//  MAMapKit
//
//  
//  Copyright (c) 2011年 Autonavi Inc. All rights reserved.
//


#import <UIKit/UIKit.h>

#import "MAPolyline.h"
#import "MAOverlayPathView.h"

/// 此类用于定义一个折线View
@interface MAPolylineView : MAOverlayPathView

/**
 *根据指定的折线生成一个折线View
 *@param polyline 指定的折线数据对象
 *@return 新生成的折线View
 */
- (id)initWithPolyline:(MAPolyline *)polyline;

/// 该View对应的折线数据对象
@property (nonatomic, readonly) MAPolyline *polyline;

@end
