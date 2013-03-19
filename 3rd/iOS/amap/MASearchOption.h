/*
 *  MTAsyncSearchOption.h
 *  iMapSDKLib
 *
 *  Created by yin cai on 11-8-30.
 *  Copyright 2011 AutoNavi. All rights reserved.
 *
 */

//poi查询选项
@interface MAPoiSearchOption : NSObject
@property(nonatomic,retain) NSString* config; //查询服务名 (必填) 关键字查询:BESN 中心点关键字查询周边:BELSBN 中心点坐标查询周边L:BELSBXY
@property(nonatomic,retain) NSString* authKey;//查询密钥(必填)  从code.mapabc.com注册获取
@property(nonatomic,retain) NSString* encode; //字符编码 默认为GBK 目前支持GBK 和 UTF-8
@property(nonatomic,retain) NSString* searchName; //搜索关键字 必填选项
@property(nonatomic,retain) NSString* cityCode; //城市编号(默认为total)，定义查询城市的参数。在全国范围内进行查询时赋值为“total”即可。
										        //城市编号与电话区号十分相似，但并不完全相同，其区别是：在多个城市使用同一个电话区号时，在城市编码中会进行区分。
@property(nonatomic,retain) NSString* cenName; //中心点关键字。周边查询中，通过本参数指定中心点关键字(config = BELSBN时为必填选项)。
@property(nonatomic,retain) NSString* cenX;    //经度，用于以坐标为中心点坐标周边查询(config = BELSBXY时为必填选项)
@property(nonatomic,retain) NSString* cenY;    //纬度，用于以坐标为中心点坐标周边查询(config = BELSBXY时为必填选项)
@property(nonatomic,retain) NSString* range;  //周边查询范围 默认值为3000


@property(nonatomic,retain) NSString* searchType; //查询类型,可不填
@property(nonatomic,retain) NSString* srcType;  // 数据源类型 (默认值为POI)  英文库 mpoi、基础库 POI、 企业地标 DIBIAO、公交站台 BUS、通用编辑器 USERPOI、
										 // 上述数据源可以混合查询，例如公交数据+基础库数据查询BUS:1000%2bPOI,代表前1000条数据为公交数据，后面为基础库数据
@property(nonatomic,retain) NSString* sr;       // sr=0代表按照关键字排序 sr=1代表按照距离排序 默认值为0
@property(nonatomic,retain) NSString* naviflag; //默认为0，不按照导航距离排序，如果为1将按照导航距离排序，但性能比直线距离排序差
@property(nonatomic,retain) NSString* number; //每页显示结果数量 默认值为20
@property(nonatomic,retain) NSString* batch;  //分页号（显示第几页）默认值为1
@end




//网络导航查询选项
@interface MARouteSearchOption : NSObject
@property(nonatomic,retain) NSString* config; //查询服务名 (必填) 网络导航:R
@property(nonatomic,retain) NSString* authKey;//查询密钥(必填)  从code.mapabc.com注册获取
@property(nonatomic,retain) NSString* encode; //字符编码 默认为GBK 目前支持GBK 和 UTF-8
@property(nonatomic,retain) NSString* x1;     //起点经度(必填)
@property(nonatomic,retain) NSString* y1;     //起点纬度(必填)
@property(nonatomic,retain) NSString* x2;     //终点经度(必填)
@property(nonatomic,retain) NSString* y2;     //终点纬度(必填)
@property(nonatomic,retain) NSString* xs;     //途经点经度集合,限制10个以内
@property(nonatomic,retain) NSString* ys;     //途经点纬度集合,限制10个以内
@property(nonatomic,retain) NSString* per;    //抽稀参数，控制返回坐标数量(默认值为50)
@property(nonatomic,retain) NSString* routeType; //导航规则：(默认值为0)
												 //routeType=0速度优先（时间）
												 //routeType=1费用优先（不走收费路段最快道路）
												 //routeType=2距离优先
												 //routeType=3不走快速路（不走快速路，不包含高速路）
												 //routeType=9多策略（同时使用速度优先、费用优先、距离优先三个策略计算路径）
												 //routeType=10国道优先
@property(nonatomic,retain) NSString* avoidanceType; //避让规则
													 //1为区域避让
													 //2为名称避让
													 //3为区域避让加名称避让
													 //当 region和 name有一个不为空时候， avoidanceType就不能为空，否则查询无结果。
@property(nonatomic,retain) NSString* region; //区域避让 格式如下用“:”符号区分避让区域，用“;”符号区分坐标对。
											  //表示避让的区域，区域由(x，y)坐标点组成，如果是四边形则有四个坐标点，如果是五边形则有五个坐标点。
                                              //避让的区域最多有32个，每个区域中最多有16个顶点
@property(nonatomic,retain) NSString* name;   //名称避让 例如避让一条道路
@property(nonatomic,retain) NSString* ext;    //返回途经城市 0表示不返回途经城市，默认为0,1表示返回途经城市列表，城市做排重处理 2表示返回途经城市列表，城市不做排重
@end

@interface MADistanceSearchOption : NSObject
@property(nonatomic,retain) NSString* config; //查询服务名 (必填) 网络测距:R
@property(nonatomic,retain) NSString* authKey;//查询密钥(必填)  从code.mapabc.com注册获取
@property(nonatomic,retain) NSString* encode; //字符编码 默认为GBK 目前支持GBK 和 UTF-8
@property(nonatomic,retain) NSString* x1;     //起点经度(必填)
@property(nonatomic,retain) NSString* y1;     //起点纬度(必填)
@property(nonatomic,retain) NSString* x2;     //终点经度(必填)
@property(nonatomic,retain) NSString* y2;     //终点纬度(必填)
@property(nonatomic,retain) NSString* routeType; //测距规则：(默认值为0)
												 //routeType=0速度优先（时间）
												 //routeType=1费用优先（不走收费路段最快道路）
												 //routeType=2距离优先
												 //routeType=3不走快速路（不走快速路，不包含高速路）
												 //routeType=9多策略（同时使用速度优先、费用优先、距离优先三个策略计算路径）
												 //routeType=10国道优先
@end




//公交导航查询选项
@interface MABusRouteSearchOption : NSObject
@property(nonatomic,retain) NSString* config; //查询服务名 (必填) 公交导航:BR
@property(nonatomic,retain) NSString* authKey;//查询密钥(必填)  从code.mapabc.com注册获取
@property(nonatomic,retain) NSString* encode; //字符编码 默认为GBK 目前支持GBK 和 UTF-8
@property(nonatomic,retain) NSString* x1;     //起点经度(必填)
@property(nonatomic,retain) NSString* y1;     //起点纬度(必填)
@property(nonatomic,retain) NSString* x2;     //终点经度(必填)
@property(nonatomic,retain) NSString* y2;     //终点纬度(必填)
@property(nonatomic,retain) NSString* per;    //抽稀参数，控制返回坐标数量(默认值为50)
@property(nonatomic,retain) NSString* routeType; //导航规则：(默认值为0)
												 //routeType=0速度优先（时间）
												 //routeType=1费用优先（不走收费路段最快道路）
												 //routeType=2距离优先
												 //routeType=3不走快速路（不走快速路，不包含高速路）
												 //routeType=9多策略（同时使用速度优先、费用优先、距离优先三个策略计算路径）
												 //routeType=10国道优先
@property(nonatomic,retain) NSString* cityCode; //城市编码(必填) 以电话区号为准
@end

//公交线路导航查询选项
@interface MABusLineSearchOption : NSObject
@property(nonatomic,retain) NSString* config; //查询服务名 (必填) 公交线路查询:BusLine
@property(nonatomic,retain) NSString* authKey;//查询密钥(必填)  从code.mapabc.com注册获取
@property(nonatomic,retain) NSString* encode; //字符编码 默认为GBK 目前支持GBK 和 UTF-8
@property(nonatomic,retain) NSString* cityCode; //城市编码(必填) 以电话区号为准
@property(nonatomic,retain) NSString* ids;    //公交线路id集合,如果有多个id中间用","分割.根据线路id查询的时候此参数必填
@property(nonatomic,retain) NSString* busName;//公交名称 根据公交名称查询此参数必填
@property(nonatomic,retain) NSString* stationName; //公交站点名称 根据公交站点查询此参数必填
@property(nonatomic,retain) NSString* number; //每页显示结果数量 默认值为20
@property(nonatomic,retain) NSString* batch;  //分页号（显示第几页）默认值为1
@property(nonatomic,retain) NSString* resData; //返回线路坐标:按照公交名称或者公交线路查询时此参数起作用
											   //0 不返回线路坐标，默认为0
                                               //1 返回线路坐标

@end


//坐标偏移查询选项
@interface MARGCSearchOption : NSObject
@property(nonatomic,retain) NSString* config; //查询服务名 (必填) 坐标偏移:RGC
@property(nonatomic,retain) NSString* authKey;	  //查询密钥(必填)  从code.mapabc.com注册获取
@property(nonatomic,retain) NSString* encode; //字符编码 默认为GBK 目前支持GBK 和 UTF-8
@property(nonatomic,retain) NSString* coors;  //原始坐标的经纬度字符串 格式(x1,y1;x2,y2;x3,y3...)
@end


//地理编码查询选项
@interface MAGeoCodingSearchOption : NSObject
@property(nonatomic,retain) NSString* config; //查询服务名 (必填) 坐标偏移:GOC
@property(nonatomic,retain) NSString* authKey;//查询密钥(必填)  从code.mapabc.com注册获取
@property(nonatomic,retain) NSString* encode; //字符编码 默认为GBK 目前支持GBK 和 UTF-8
@property(nonatomic,retain) NSString* address; //查询地址
@property(nonatomic,retain) NSString* poiNumber; //POI返回数量 默认值为10
@end


@interface MAReverseGeocodingSearchOption : NSObject
@property(nonatomic,retain) NSString* config; //查询服务名 (必填) 坐标偏移:SPAS
@property(nonatomic,retain) NSString* authKey;//查询密钥(必填)  从code.mapabc.com注册获取
@property(nonatomic,retain) NSString* encode; //字符编码 默认为GBK 目前支持GBK 和 UTF-8
@property(nonatomic,retain) NSString* multiPoint;//单点查询或多点查询 单点查询:0 多点查询:1 默认为0
@property(nonatomic,retain) NSString* x;//单点查询 x坐标
@property(nonatomic,retain) NSString* y;//单点查询 y坐标
@property(nonatomic,retain) NSString* xCoors;//多点查询 x坐标集合 (格式:x1,x2,x3,.....)
@property(nonatomic,retain) NSString* yCoors;//多点查询 y坐标集合 (格式:y1,y2,y3,.....)
@property(nonatomic,retain) NSString* poiNumber;//返回周边POI点数量 默认值:10
@property(nonatomic,retain) NSString* roadNumber;//返回周边道路数量  默认值:10
@property(nonatomic,retain) NSString* crossNumber;//返回周边交叉路口数量 默认值:10
@property(nonatomic,retain) NSString* range;//限定周边热点POI和道路的距离范围 单位:(米) 默认值：300
@property(nonatomic,retain) NSString* pattern;//返回数据的模式，0为返回地标性POI，1为返回全部POI，默认值:0
											  //如果要查询的点在繁华地区设置为0效果较好，如果在偏远地区设置1更好
@end



