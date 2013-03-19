//
//  MTMapObj.h
//  iMapSDK
//
//  Created by Duan Sijiu on 10-12-10.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>

@class MMapCoordinate;

/*!
    @header MTMapObj
    @abstract   所有地图对象的接口类
*/
@protocol MTMapObj <NSObject>
@required
/*!
 @abstract 地图坐标系统对象
 */
@property (nonatomic,retain) MMapCoordinate* mapCoordinate;

/*!
    @function
    @abstract   地图状态更新的回调函数
    @param      dt 与上次地图更新的时间间隔（单位：毫秒）。
*/
-(void) update:(CGFloat) dt;
@end
