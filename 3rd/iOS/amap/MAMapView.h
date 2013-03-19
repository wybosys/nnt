//
//  MAMapView.h
//  MAMapKit
//
//  
//  Copyright 2011 Autonavi Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MAMapKit.h"
#import "MAUserLocation.h"
@protocol MAMapViewDelegate;

@interface MAMapView : UIView<NSCoding> {
    @private 
    NSArray* _overlays;

}

/// 地图View的Delegate
@property (nonatomic, assign) id<MAMapViewDelegate> delegate;

/// 当前地图类型，可设定为普通模式或合成图模式
@property (nonatomic) MAMapType mapType;

/// 当前地图的经纬度范围，设定的该范围可能会被调整为适合地图窗口显示的范围
@property (nonatomic) MACoordinateRegion region;

/**
 *设定当前地图的显示范围
 *@param region 要设定的地图范围，用经纬度的方式表示
 *@param animated 是否采用动画效果
 */
- (void)setRegion:(MACoordinateRegion)region animated:(BOOL)animated;

/// 当前地图的中心点，改变该值时，地图的比例尺级别不会发生变化
@property (nonatomic) CLLocationCoordinate2D centerCoordinate;

/**
 *设定地图中心点坐标
 *@param coordinate 要设定的地图中心点坐标，用经纬度表示
 *@param animated 是否采用动画效果
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

/**
 *根据当前地图视图frame的大小调整region范围，返回适合当前地图frame的region，调整过程中当前地图的中心点不会改变
 *@param region 要调整的经纬度范围
 *@return 调整后的经纬度范围
 */
- (MACoordinateRegion)regionThatFits:(MACoordinateRegion)region;

@property(nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;
@property(nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;
@property(nonatomic, getter = isShowTraffic) BOOL showTraffic;

/// 设定是否显示定位图层
@property (nonatomic) BOOL showsUserLocation;

/// 当前用户位置，返回坐标为经纬度坐标
@property (nonatomic, readonly) MAUserLocation* userLocation;



/**
 *向地图窗口添加标注，需要实现MAMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 *@param annotation 要添加的标注
 */
- (void)addAnnotation:(id <MAAnnotation>)annotation;

/**
 *向地图窗口添加一组标注，需要实现MAMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 *@param annotations 要添加的标注数组
 */
- (void)addAnnotations:(NSArray *)annotations;

/**
 *移除标注
 *@param annotation 要移除的标注
 */
- (void)removeAnnotation:(id <MAAnnotation>)annotation;

/**
 *移除一组标注
 *@param annotation 要移除的标注数组
 */
- (void)removeAnnotations:(NSArray *)annotations;

@property (nonatomic, readonly) NSArray *annotations;
- (MAAnnotationView *)viewForAnnotation:(id <MAAnnotation>)annotation;

@end


@interface MAMapView(OverlaysAPI)
/**
 *向地图窗口添加Overlay，需要实现MAMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的View
 *@param overlay 要添加的overlay
 */
- (void)addOverlay:(id <MAOverlay>)overlay;

/**
 *向地图窗口添加一组Overlay，需要实现BMKMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的View
 *@param overlays 要添加的overlay数组
 */
- (void)addOverlays:(NSArray *)overlays;

/**
 *移除Overlay
 *@param overlay 要移除的overlay
 */
- (void)removeOverlay:(id <MAOverlay>)overlay;

/**
 *移除一组Overlay
 *@param overlays 要移除的overlay数组
 */
- (void)removeOverlays:(NSArray *)overlays;

/**
 *在指定的索引处添加一个Overlay
 *@param overlay 要添加的overlay
 *@param index 指定的索引
 */
- (void)insertOverlay:(id <MAOverlay>)overlay atIndex:(NSUInteger)index;

/**
 *在交换指定索引处的Overlay
 *@param index1 索引1
 *@param index2 索引2
 */
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2;

/**
 *在指定的Overlay之上插入一个overlay
 *@param overlay 带添加的Overlay
 *@param sibling 用于指定相对位置的Overlay
 */
- (void)insertOverlay:(id <MAOverlay>)overlay aboveOverlay:(id <MAOverlay>)sibling;

/**
 *在指定的Overlay之下插入一个overlay
 *@param overlay 带添加的Overlay
 *@param sibling 用于指定相对位置的Overlay
 */
- (void)insertOverlay:(id <MAOverlay>)overlay belowOverlay:(id <MAOverlay>)sibling;

/// 当前mapView中已经添加的Overlay数组
@property (nonatomic, readonly) NSArray *overlays;

/**
 *查找指定overlay对应的View，如果该View尚未创建，返回nil
 *@param overlay 指定的overlay
 *@return 指定overlay对应的View
 */
- (MAOverlayView*)viewForOverlay:(id <MAOverlay>)overlay;
@end

//MapView的Delegate，mapView通过此类来通知用户对应的事件
@protocol MAMapViewDelegate<NSObject>
@optional

/**
 *地图区域即将改变时会调用此接口
 *@param mapview 地图View
 *@param animated 是否动画
 */
- (void)mapView:(MAMapView *)mapView regionWillChangeAnimated:(BOOL)animated;

/**
 *地图区域改变完成后会调用此接口
 *@param mapview 地图View
 *@param animated 是否动画
 */
- (void)mapView:(MAMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

/**
 *根据anntation生成对应的View
 *@param mapView 地图View
 *@param annotation 指定的标注
 *@return 生成的标注View
 */
- (MAAnnotationView*)mapView:(MAMapView *)mapView viewForAnnotation:(id <MAAnnotation>)annotation;

/**
 *当mapView新添加annotation views时，调用此接口
 *@param mapView 地图View
 *@param views 新添加的annotation views
 */
- (void)mapView:(MAMapView *)mapView didAddAnnotationViews:(NSArray *)views;

/**
 *当选中一个annotation views时，调用此接口
 *@param mapView 地图View
 *@param views 选中的annotation views
 */
- (void)mapView:(MAMapView *)mapView didSelectAnnotationView:(MAAnnotationView *)view NS_AVAILABLE(NA, 4_0);

/**
 *当取消选中一个annotation views时，调用此接口
 *@param mapView 地图View
 *@param views 取消选中的annotation views
 */
- (void)mapView:(MAMapView *)mapView didDeselectAnnotationView:(MAAnnotationView *)view NS_AVAILABLE(NA, 4_0);


/**
 *在地图View将要启动定位时，会调用此函数
 *@param mapView 地图View
 */
- (void)mapViewWillStartLocatingUser:(MAMapView *)mapView NS_AVAILABLE(NA, 4_0);

/**
 *在地图View停止定位后，会调用此函数
 *@param mapView 地图View
 */
- (void)mapViewDidStopLocatingUser:(MAMapView *)mapView NS_AVAILABLE(NA, 4_0);

/**
 *用户位置更新后，会调用此函数
 *@param mapView 地图View
 *@param userLocation 新的用户位置
 */
- (void)mapView:(MAMapView *)mapView didUpdateUserLocation:(MAUserLocation *)userLocation NS_AVAILABLE(NA, 4_0);

/**
 *定位失败后，会调用此函数
 *@param mapView 地图View
 *@param error 错误号，参考CLError.h中定义的错误号
 */
- (void)mapView:(MAMapView *)mapView didFailToLocateUserWithError:(NSError *)error NS_AVAILABLE(NA, 4_0);


/**
 *拖动annotation view时view的状态变化，ios3.2以后支持
 *@param mapView 地图View
 *@param view annotation view
 *@param newState 新状态
 *@param oldState 旧状态
 */
- (void)mapView:(MAMapView *)mapView annotationView:(MAAnnotationView *)view didChangeDragState:(MAAnnotationViewDragState)newState 
   fromOldState:(MAAnnotationViewDragState)oldState NS_AVAILABLE(NA, 4_0);


/**
 *根据overlay生成对应的View
 *@param mapView 地图View
 *@param overlay 指定的overlay
 *@return 生成的覆盖物View
 */
- (MAOverlayView *)mapView:(MAMapView *)mapView viewForOverlay:(id <MAOverlay>)overlay NS_AVAILABLE(NA, 4_0);

/**
 *当mapView新添加overlay views时，调用此接口
 *@param mapView 地图View
 *@param overlayViews 新添加的overlay views
 */
- (void)mapView:(MAMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews NS_AVAILABLE(NA, 4_0);








@end