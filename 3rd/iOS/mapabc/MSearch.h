//
//  MSearch.h
//  iMapSDKLib
//
//  Created by yin cai on 10-12-16.
//  Copyright 2010 Autonavi. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "sa_types.h"
#include "ut_types.h"

typedef id SEARCH_THREAD_ID;

@protocol MSearchDelegate;
@protocol GPSToOffsetByPoint_Delegate;

/*!
 @header MSearch
 @abstract 搜索类，从NSObject类继承。
 */
@interface MSearch : NSObject
{
	
}

/*!
 @function
 @abstract 搜索对象的构造及初始化
 @param key 搜索服务器鉴权要用到的key
 @param delegate 接收搜索结果的对象的id,需要遵守MSearchDelegate协议
 */
+(id)MSearchWithKey:(NSString*)key delegate:(id<MSearchDelegate>) delegate;


/*!
 @function
 @abstract 获取鉴权结果
 // *返回值*
 //  -2 网络未连接
 //  -1 key不存在(非法的key) 	                                     
 //  0 成功  
 //  1 已经到达最大激活数 
 //  2 key被注销 
 //  3 key被加入黑名单 
 //  4 key被管理员锁定
 //  8 key的某个访问ip被加入黑名单 
 //  11 终端被加入黑名单 
 //  12 终端被锁定 
 //  13 终端被注销 
 //  14 SDK api验证系统异常
 //  15 必需的参数key或者终端号为空
 */
-(NSInteger)ResultOfAuth;

/*!
 @function
 @abstract 根据关键字进行POI搜索
 @param keywords 要搜索的关键字
 @param city 当前城市编码 可以输入汉字如:"北京" 也可以输入电话区号如:"010"
 @param options POI搜索配置选项 
 */
- (SEARCH_THREAD_ID)PoiSearchByKeywords:(NSString*)keywords City:(NSString*)city Options:(MPOISEARCHOPTIONS)options;


/*!
 @function
 @abstract 根据中心点经纬度和关键字进行POI搜索
 @param centerPoiXY 中心点经纬度
 @param keywords 要搜索的关键字
 @param city 当前城市编码 可以输入汉字如:"北京" 也可以输入电话区号如:"010"
 @param options POI搜索配置选项 
 */
- (SEARCH_THREAD_ID)PoiSearchByCenPoi:(MLONLAT)centerPoiXY KeyWords:(NSString*)keywords City:(NSString*)city Options:(MPOISEARCHOPTIONS)options;


/*!
 @function
 @abstract 根据中心点关键字和搜索关键字进行POI搜索
 @param centerKeywords 中心点关键字
 @param keywords 要搜索的关键字
 @param city 当前城市编码 可以输入汉字如:"北京" 也可以输入电话区号如:"010"
 @param options POI搜索配置选项 
 */
- (SEARCH_THREAD_ID)PoiSearchByCenKeywords:(NSString*)centerKeywords SearchKeyWords:(NSString*)keywords City:(NSString*)city Options:(MPOISEARCHOPTIONS)options;

/*!
 @function
 @abstract 根据起始点经纬度坐标搜索路径引导信息
 @param startPoiXY 起始点经纬度坐标
 @param endPoiXY 终点经纬度坐标
 @param options 路径引导信息搜索配置选项 
 */
- (SEARCH_THREAD_ID)RouteSearchByStartPoi:(MLONLAT)startPoiXY EndPoi:(MLONLAT)endPoiXY Options:(MAUTONAVISEARCHOPTIONS)options;

/*!
 @function
 @abstract 根据两个点的经纬度计算两点间的距离
 @param Xs X点经纬度坐标
 @param Ys Y点经纬度坐标
 @param options 距离搜索配置选项 
 */
- (SEARCH_THREAD_ID)CalculaNaviDistanceByXPoint:(NSString*)Xs YPoint:(NSString*)Ys Options:(MAUTODISSEARCHOPTIONS)options;


/*!
 @function
 @abstract 根据起始点经纬度坐标搜索公交引导信息
 @param startPoiXY 起始点经纬度坐标
 @param endPoiXY 终点经纬度坐标
 @param city 当前城市编码 可以输入汉字如:"北京" 也可以输入电话区号如:"010"
 @param options 公交引导信息搜索配置选项 
 */
- (SEARCH_THREAD_ID)BusSearchByStartPoi:(MLONLAT)startPoiXY EndPoi:(MLONLAT)endPoiXY City:(NSString*)city Options:(MBUSNAVISEARCHOPTIONS)options;

/*!
 @function
 @abstract 根据公交ID搜索公交引导信息
 @param busId 公交ID
 @param city 当前城市编码 可以输入汉字如:"北京" 也可以输入电话区号如:"010"
 @param options 公交引导信息搜索配置选项 
 */
- (SEARCH_THREAD_ID)BusSearchByBusId:(NSString*)busId City:(NSString*)city Options:(MBUSINFOSEARCHOPTIONS)options;

/*!
 @function
 @abstract 根据公交站点名称搜索公交引导信息
 @param stationName 公交站点名称
 @param city 当前城市编码 可以输入汉字如:"北京" 也可以输入电话区号如:"010"
 @param options 公交引导信息搜索配置选项 
 */
- (SEARCH_THREAD_ID)BusSearchByBusStation:(NSString*)stationName City:(NSString*)city Options:(MBUSINFOSEARCHOPTIONS)options;

/*!
 @function
 @abstract 根据公交名称搜索公交引导信息
 @param busName 公交名称
 @param city 当前城市编码 可以输入汉字如:"北京" 也可以输入电话区号如:"010"
 @param options 公交引导信息搜索配置选项 
 */
- (SEARCH_THREAD_ID)BusSearchByBusName:(NSString*)busName City:(NSString*)city Options:(MBUSINFOSEARCHOPTIONS)options;


/*!
 @function
 @abstract 查询偏移后的坐标
 @param delegate 接收查询结果的对象的id，需要遵守GPSToOffsetByPoint_Delegate协议
 */
- (SEARCH_THREAD_ID)GPSToOffSetByPoint:(id<GPSToOffsetByPoint_Delegate>)delegate;


/*!
 @function
 @abstract 根据点坐标返回此点的空间位置描述信息,包括该点所在省市区,周边的POI和道路
 @param poiXY 点坐标
 @param options 查询配置选项 
 */
- (SEARCH_THREAD_ID)PoiToAddressByPoi:(MLONLAT)poiXY Options:(MREGEOCODESEARCHOPTIONS)options;

/*!
 @function
 @abstract 地址匹配查询(根据地址信息，查询该地址所对应的点坐标)
 @param address 地址信息
 */
- (SEARCH_THREAD_ID)AddressToPoiByAddress:(NSString*)address;


/*!
 @function
 @abstract 终止查询线程，目前只对GPSToOffSetByPoint查询起作用
 @param threadID 线程ID
 */
-(void)stopSearchThread:(id)threadID;
@end


/*!
 @header GPSToOffsetByPoint_Delegate
 @abstract 偏移坐标查询协议类，从NSObject类继承。
 */
@protocol GPSToOffsetByPoint_Delegate<NSObject>

/*!
 @abstract 偏移前的点经纬度
 */
@property(nonatomic,assign) MLONLAT poiXY;

/*!
 @abstract 偏移查询配置选项
 */
@property(nonatomic,assign) MCOORDINATESEARCHOPTIONS options;

/*!
 @function
 @abstract 返回查询后的偏移坐标
 @param lonlat 查询结果
 */
-(void) GPSToOffsetResponse:(MLONLAT)lonlat;
@end


/*!
 @header MSearchDelegate
 @abstract MSearch协议类，从NSObject类继承。
 */
@protocol MSearchDelegate <NSObject>

/*!
 @function
 @abstract 返回查询模块初始化结果
 @param res 初始化结果
 */
//-(void) InitWithKeyResponse:(BOOL)res;

/*!
 @function
 @abstract 返回POI查询结果
 @param info POI查询结果
 */
-(void) PoiSearchResponse:(MPOISEARCHRESULT*)info;

/*!
 @function
 @abstract 返回路径引导信息查询结果
 @param info 路径引导信息查询结果
 */
-(void) RouteSearchResponse:(MAUTONAVISEARCHRESULT*)info;

/*!
 @function
 @abstract 返回距离计算查询结果
 @param info 距离计算查询结果
 */
-(void) CalculaNaviDistanceResponse:(MAUTODISSEARCHRESULT*)info;

/*!
 @function
 @abstract 返回公交导航结果
 @param info 公交导航结果
 */
-(void) BusNaviSearchByResponse:(MBUSNAVISEARCHRESULT*)info;

/*!
 @function
 @abstract 返回公交查询结果
 @param info 公交查询结果
 */
-(void) BusSearchResponse:(MBUSINFOSEARCHRESULT*)info;

/*!
 @function
 @abstract 返回空间位置信息查询结果
 @param info 空间位置信息查询结果
 */
-(void) PoiToAddressResponse:(MREGEOCODESEARCHRESULT*)info;

/*!
 @function
 @abstract 返回地址匹配查询结果
 @param info 地址匹配查询结果
 */
-(void) AddressToPoiResponse:(MADDRESSMATHINGRESULT*)info;
@end



