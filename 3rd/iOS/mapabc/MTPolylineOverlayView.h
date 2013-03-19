//
//  MTPolylineOverlayView.h
//  iMapSDKLib
//
//  Created by Duan Sijiu on 10-12-16.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MTMultiPointOverlayView.h"
/*!
 @header
 @abstract    通过经纬度坐标串，在地图上绘制地理折线的视图类
 */
@interface MTPolylineOverlayView : MTMultiPointOverlayView {
}
/*!
 @method     
 @abstract   构造函数
 */
+(id) polylineView;
@end
