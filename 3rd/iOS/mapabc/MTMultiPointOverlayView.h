//
//  MTMultiPointOverlayView.h
//  iMapSDKLib
//
//  Created by Duan Sijiu on 10-12-17.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MTOverlayView.h"

/*!
 @header
 @abstract    通过经纬度坐标串，绘制“地图上图形”的视图类基类
 */
@interface MTMultiPointOverlayView : MTOverlayView {
	struct _lnglatXY{
		_lnglatXY* pre;
		CGPoint lnglatXY;
		_lnglatXY* next;
	} *mutiPointRef;
}
/*!
    @method     
    @abstract   删除所有经纬度坐标点
*/
- (void) removeAllPoints;

/*!
 @method     
 @abstract   添加一对经纬度坐标点
 */
- (void) addPointWithLongitude:(float)lng Latitude:(float)lat;
@end
