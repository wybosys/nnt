//
//  MTUserLocation.h
//  iMapSDKLib
//
//  Created by Duan Sijiu on 10-12-20.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "MTMapObj.h"
#import "MTCircleOverlayView.h"

/*!
 @header
 @abstract    在地图上绘制用户所在位置的视图类
 */
@interface MTUserLocation : MTCircleOverlayView 
<MTMapObj, CLLocationManagerDelegate>{
}

/*!
    @method     
    @abstract   设置定位中心点图标资源
	@param image 图标资源
*/
-(void)setCenterImage:(UIImage *)image;

/*!
    @method     
    @abstract   启动实时定位
	@param time 实时定位间隔时间（单位：秒）
*/
-(void)startLocatingWithCycleTime:(CGFloat)time;
/*!
 @method     
 @abstract   停止实时定位
 */
-(void)stopLocating;

/*!
 @method     
 @abstract   获得最近一次定位到的用户经纬度坐标
 @result 经纬度坐标
 */
-(CGPoint) getUserLocation;

@end
