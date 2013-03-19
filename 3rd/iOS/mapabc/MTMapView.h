//
//  MTMapView.h
//  iMapSDK
//
//  Created by Duan Sijiu on 10-12-11.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MTMapObj.h"
#import "MTUserLocation.h"

@class MTAnnotationView;
@class MTOverlayView;
@class MTLabel;

@protocol MTMapView_Delegate;

/*!
 @header MTMapView
 @abstract 地图视图类，从UIView类继承。是地图sdk的总接口。
 */
@interface MTMapView : UIView <MTMapObj>{

}

/*!
 @function
 @abstract 地图视图对象的构造及初始化
 @param frame 地图尺寸（单位：像素）
 @param delegate 实现MTMapView_Delegate协议的对象id
 */
+(id) mapViewWithFrame:(CGRect)frame Delegate:(id<MTMapView_Delegate>)delegate;

/*!
 @function
 @abstract   设置地图显示的地理区域
 @discussion 通过经纬度矩形框设置地图显示区域
 @param region 地理经纬度坐标矩形
			region.origin :矩形左上角经纬度坐标值
			region.size :经纬度矩形的宽度和高度（均为无符号浮点类型)
 @param animated 动画显示（暂不支持）
*/
- (void)setRegion:(CGRect)region animated:(BOOL)animated;

/*!
 @function
 @abstract   设置地图中心点经纬度
 @param coordinate 地图中心点经纬度
 @param animated 动画显示（暂不支持）
 */
- (void)setCenterCoordinate:(CGPoint)coordinate animated:(BOOL)animated;

/*!
 @function
 @abstract   增加标注
 @param annotation 标注视图类实例
 */
-(void) addAnnotation:(MTAnnotationView*)annotation;

/*!
 @function
 @abstract   删除标注
 @param annotation 需要被删除的标注实例
 */
-(void) removeAnnotation:(MTAnnotationView*)annotation;


/*!
 @function
 @abstract   删除所有标注
 */
-(void) removeAllAnnotation;

/*!
 @function
 @abstract   增加overlay
 @param overlay overlay视图类实例
 */
-(void) addOverlay:(MTOverlayView*)overlay;

/*!
 @function
 @abstract   删除overlay
 @param overlay 需要被删除的overlay实例
 */
-(void) removeOverlay:(MTOverlayView*)overlay;

/*!
 @function
 @abstract   删除所有Overlay
 */
-(void) removeAllOverlay;

/*!
 @function
 @abstract  添加动态交通数据层
 */
-(void) addTMCLayer;

/*!
 @function  
 @abstract  删除动态交通数据层
 */
-(void) removeTMCLayer;

/*!
 @abstract 是否在地图上显示当前位置
 */
@property (nonatomic) BOOL showsUserLocation;
/*!
 @abstract 内建的当前位置管理类事例
 */
@property (nonatomic,retain,readonly) MTUserLocation* userLocation;
/*!
 @abstract 获取当前 Map SDK 的版本
 */
@property (nonatomic,readonly) NSString* version;

@end



/*!
 @header MTMapView_Delegate
 @abstract MTMapView协议类，从NSObject类继承。
 */
@protocol MTMapView_Delegate<NSObject>

/*!
 @function
 @abstract 从实现MTMapView_Delegate的对象获取鉴权key
 */
-(NSString*)userKeyForMTMapView;

/*!
 @function
 @abstract 向实现MTMapView_Delegate的类返回鉴权结果
 @param result 鉴权结果
 */
-(void)mapViewAuthResult:(BOOL)result;
@end



