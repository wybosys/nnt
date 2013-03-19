//
//  MTAsyncSearch.h
//  iMapSDKLib
//
//  Created by caiyin on 11-7-21.
//  Copyright 2011 Autonavi. All rights reserved.
//


#import "MASearchOption.h"
#import "MASearchResult.h"


@protocol MASearchDelegate;

/*!
 @header MASearch
 @abstract 异步查询类，从NSObject类继承。是一套异步查询的接口,基于Protocol Buffers实现。
 */
@interface MASearch : NSObject{

}

/*!
 @abstract 实现了MASearchDelegate协议的类指针
 */
@property(nonatomic,assign) id<MASearchDelegate> delegate;

/*!
 @function
 @abstract MASearch类对象的初始化函数
 @param delegate 实现MASearchDelegate协议的对象id
 @result MASearch类对象id
 */
+(id)maSearchWithDelegate:(id<MASearchDelegate>)delegate;


/*!
 @function
 @abstract POI查询接口函数
 @param searchOption POI查询选项(具体属性字段参考MASearchOption类中的@interface定义)
 */
-(void)poiSearchWithOption:(MAPoiSearchOption*)searchOption;

/*!
 @function
 @abstract 导航路径查询接口函数
 @param searchOption 导航路径查询选项(具体属性字段参考MASearchOption类中的@interface定义)
 */
-(void)routeSearchWithOption:(MARouteSearchOption*)searchOption;

/*!
 @function
 @abstract 公交导航查询接口函数
 @param searchOption 公交导航查询选项(具体属性字段参考MASearchOption类中的@interface定义)
 */
-(void)busRouteSearchWithOption:(MABusRouteSearchOption*)searchOption;

/*!
 @function
 @abstract 公交线路查询接口函数
 @param searchOption 公交线路查询选项(具体属性字段参考MASearchOption类中的@interface定义)
 */
-(void)busLineSearchWithOption:(MABusLineSearchOption*)searchOption;

/*!
 @function
 @abstract 两点之间距离查询函数
 @param searchOption 两点之间距离查询选项(具体属性字段参考MASearchOption类中的@interface定义)
 */
-(void)distanceSearchWithOption:(MADistanceSearchOption*)searchOption;

/*!
 @function
 @abstract GPS坐标偏移查询接口函数
 @param searchOption GPS坐标偏移查询查询选项(具体属性字段参考MASearchOption类中的@interface定义)
 */
-(void)gpsOffsetSearchWithOption:(MARGCSearchOption*)searchOption;

/*!
 @function
 @abstract 地理编码查询接口函数
 @param searchOption 地理编码查询选项(具体属性字段参考MTAsyncSearchOption类中的@interface定义)
 */
-(void)geoCodingSearchWithOption:(MAGeoCodingSearchOption*)searchOption;

/*!
 @function
 @abstract 逆地理编码查询接口函数
 @param searchOption 逆编码查询选项(具体属性字段参考MASearchOption类中的@interface定义)
 */
-(void)reverseGeocodingSearchWithOption:(MAReverseGeocodingSearchOption*)searchOption;

@end



/*!
 @header MASearchDelegate
 @abstract MASearchDelegate协议类，从NSObject类继承。
 */
@protocol MASearchDelegate<NSObject>
@optional

/*!
 @function
 @abstract 通知查询成功或失败的回调函数
 @param searchOption 发起查询的查询选项
 @param errCode 错误码
 错误码对应列表
 000000  操作成功
 000001  无查询结果
 000002  调用服务发生异常
 010001  非法坐标格式
 010002  字符集编码错误
 010003  Apikey为空
 020000  产品未授权
 020001  Apikey不正确
 020002  Api账号不存在
 020003  没有服务访问权限
 020004  IP验证失败
 020005  城市验证失败
 020006  基础模型验证失败
 020007  网卡地址不匹配
 020008  license配置错误
 020009  城市号不匹配
 020010  头文件不匹配
 020011  请求数超出最大范围
 030001  缓存服务器异常
 040001  查询服务连接异常
 040002  查询服务返回格式解析异常
 050001  当前请求数据格式不支持
 */
-(void)search:(id)searchOption Error:(NSString*)errCode;

/*!
 @function
 @abstract POI查询回调函数
 @param searchOption 发起POI查询的查询选项(具体字段参考MTAsyncSearchOption类中的@interface定义)
 @param result 查询结果(具体字段参考MTAsyncSearchResult类中的@interface定义)
）
 */
-(void)poiSearch:(MAPoiSearchOption*)poiSearchOption Result:(MAPoiSearchResult*)result;

/*!
 @function
 @abstract 导航路径查询回调函数
 @param searchOption 发起导航路径查询的查询选项(具体字段参考MASearchOption类中的@interface定义)
 @param result 查询结果(具体字段参考MASearchResult类中的@interface定义)
 ）
 */
-(void)routeSearch:(MARouteSearchOption*)routeSearchOption Result:(MARouteSearchResult*)result;

/*!
 @function
 @abstract 公交导航查询回调函数
 @param searchOption 发起公交导航查询的查询选项(具体字段参考MASearchOption类中的@interface定义)
 @param result 查询结果(具体字段参考MAsyncSearchResult类中的@interface定义)
 ）
 */
-(void)busRouteSearch:(MABusRouteSearchOption*)busRouteSearchOption Result:(MABusRouteSearchResult*)result;

/*!
 @function
 @abstract 两点之间距离查询回调函数
 @param searchOption 发起公两点之间距离查询的查询选项(具体字段参考MASearchOption类中的@interface定义)
 @param result 查询结果(具体字段参考MASearchResult类中的@interface定义)
 ）
 */
-(void)distanceSearch:(MADistanceSearchOption*)distanceSearchOption Result:(MADistanceSearchResult*)result;

/*!
 @function
 @abstract 公交线路查询回调函数
 @param searchOption 发起公交线路查询的查询选项(具体字段参考MASearchOption类中的@interface定义)
 @param result 查询结果(具体字段参考MASearchResult类中的@interface定义)
 ）
 */
-(void)busLineSearch:(MABusLineSearchOption*)busLineSearchOption Result:(MABusLineSearchResult*)result;

/*!
 @function
 @abstract GPS坐标偏移查询回调函数
 @param searchOption 发起GPS坐标偏移查询的查询选项(具体字段参考MASearchOption类中的@interface定义)
 @param result 查询结果(具体字段参考MASearchResult类中的@interface定义)
 ）
 */
-(void)gpsOffsetSearch:(MARGCSearchOption*)gpsOffSearchOption Result:(MARGCSearchResult*)result;

/*!
 @function
 @abstract 地理编码查询回调函数
 @param searchOption 发起地理编码查询的查询选项(具体字段参考MASearchOption类中的@interface定义)
 @param result 查询结果(具体字段参考MASearchResult类中的@interface定义)
 ）
 */
-(void)geoCodingSearch:(MAGeoCodingSearchOption*)geoCodingSearchOption Result:(MAGeoCodingSearchResult*)result;

/*!
 @function
 @abstract 逆地理编码查询回调函数
 @param searchOption 发起逆地理编码查询的查询选项(具体字段参考MASearchOption类中的@interface定义)
 @param result 查询结果(具体字段参考MASearchResult类中的@interface定义)
 ）
 */
-(void)reverseGeocodingSearch:(MAReverseGeocodingSearchOption*)geoCodingSearchOption Result:(MAReverseGeocodingSearchResult*)result;
@end

