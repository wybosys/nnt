//
//  MTAnnotation.h
//  iMapSDK
//
//  Created by Duan Sijiu on 10-12-13.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>

/*!
    @header
    @abstract    地图标注的接口类
*/

@protocol MTAnnotation
@required
/*!
 @abstract    标注的经纬度坐标
 */
@property (nonatomic) CGPoint coordinate;
/*!
 @abstract    标注的锚点像素坐标
 */
@property (nonatomic) CGPoint hotXY;
@end
