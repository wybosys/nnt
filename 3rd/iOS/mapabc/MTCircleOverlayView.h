//
//  MTCircleOverlayView.h
//  iMapSDKLib
//
//  Created by Duan Sijiu on 10-12-17.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MTOverlayView.h"

/*!
 @header
 @abstract    通过经纬度坐标串，在地图上绘制地理圆的视图类
 */
@interface MTCircleOverlayView : MTOverlayView {
}

/*!
 @abstract   圆的中心点经纬度坐标
 */
@property (nonatomic, assign) CGPoint centerLngLatXY;
/*!
 @abstract   圆的半径（单位：米）
 */
@property (nonatomic, assign) CGFloat radius; 

/*!
 @method     
 @abstract   构造函数
 */
+(id)circleOverlayView;

@end
