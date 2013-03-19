/*
 *  MTAsyncSaerchResult.h
 *  iMapSDKLib
 *
 *  Created by yin cai on 11-8-30.
 *  Copyright 2011 AutoNavi. All rights reserved.
 *
 */


@interface MAPOI : NSObject
@property(nonatomic,retain) NSString* address; //POI点地址
@property(nonatomic,retain) NSString* name;    //POI点名称
@property(nonatomic,retain) NSString* type;    //POI点类型
@property(nonatomic,retain) NSString* url;     //POI点相关URL地址
@property(nonatomic,retain) NSString* pguid;    //唯一编号
@property(nonatomic,retain) NSString* tel;      //POI点电话号码
@property(nonatomic,retain) NSString* x;        //经度坐标
@property(nonatomic,retain) NSString* y;        //纬度坐标
@property(nonatomic,retain) NSString* distance; //周边搜索时,距离中心点距离
@property(nonatomic,retain) NSString* driverDistance;//驾车距离
@property(nonatomic,retain) NSString* match;     //匹配度
@property(nonatomic,retain) NSString* code;      //区域代码
@end


@interface MAPoiSearchResult : NSObject
@property(nonatomic,assign) NSInteger count;  //允许返回记录数与用户权限有关系
@property(nonatomic,assign) NSInteger record; //当前返回记录数
@property(nonatomic,assign) NSInteger total;  //总记录数
@property(nonatomic,retain) NSArray*  pois;   //返回的MPOI对象的序列
@end


@interface MARoute : NSObject
@property(nonatomic,retain) NSString* roadName;   //道路名称
@property(nonatomic,retain) NSString* direction;  //方向
@property(nonatomic,retain) NSString* roadLength; //行驶距离
@property(nonatomic,retain) NSString* action;     //辅助动作
@property(nonatomic,retain) NSString* accessorialInfo; //动作
@property(nonatomic,retain) NSString* driveTime;       //行驶时间
@property(nonatomic,retain) NSString* grade;           //道路等级
@property(nonatomic,retain) NSString* form;            //道路描述
@property(nonatomic,retain) NSString* coor;            //行驶路段坐标 格式(x1,y1)
@property(nonatomic,retain) NSString* textInfo;        //本段道路行驶描述
@end

@interface MARouteCity : NSObject
@property(nonatomic,retain) NSString* cityName;       //城市名
@property(nonatomic,retain) NSString* cityEnglishName;//城市英文名
@property(nonatomic,retain) NSString* code;           //地区代码
@property(nonatomic,retain) NSString* telnum;         //电话区号
@end


@interface MARouteSearchResult : NSObject 
@property(nonatomic,assign) NSInteger count;      //导航段数
@property(nonatomic,retain) NSString* bounds;	  //外包矩形范围
@property(nonatomic,retain) NSString* searchtime; //搜索时间
@property(nonatomic,retain) NSString* coors;      //行驶路段坐标串 格式(x1,y1,x2,y2,x3,y3....)
@property(nonatomic,retain) NSArray*  routes;     //MARoute对象数组，存储返回的路段信息
@property(nonatomic,retain) NSString* length;     //导航距离
@property(nonatomic,retain) NSArray* viaCities;   //途经城市 MARouteCity对象数组
@end


@interface MADistanceSearchResult : NSObject
@property(nonatomic,retain) NSString* distance;//距离
@end


@interface MASegment : NSObject
@property(nonatomic,retain) NSString* startName;//起始站名称
@property(nonatomic,retain) NSString* endName;  //终到站名称
@property(nonatomic,retain) NSString* busName;  //公交名称 
@property(nonatomic,retain) NSString* passDepotName;//途经站名称 
@property(nonatomic,retain) NSString* driverLength; //行驶距离
@property(nonatomic,retain) NSString* footLength;   //步行距离
@property(nonatomic,retain) NSString* passDepotCount; //途经站名称
@property(nonatomic,retain) NSString* coordinateList; //途径线路坐标串
@property(nonatomic,retain) NSString* passDepotCoordinate; //途经站点坐标
@end

@interface MABus : NSObject
@property(nonatomic,retain) NSArray* segmentArray; //MASegment对象序列
@property(nonatomic,retain) NSString* footEndLength; //换乘步行长度
@property(nonatomic,retain) NSString* bounds;        //外包矩形范围
@property(nonatomic,retain) NSString* expense;       //费用
@end


@interface MABusRouteSearchResult : NSObject
@property(nonatomic,assign) NSInteger count;      //导航段数
@property(nonatomic,retain) NSString* searchtime; //查询时间
@property(nonatomic,retain) NSArray*  routes;//MABus数组,用来存储MABus对象序列
@end


@interface MABusLine : NSObject
@property(nonatomic,retain) NSString* length; //路线长度(单位:公里)
@property(nonatomic,retain) NSString* name; //线路名称
@property(nonatomic,retain) NSString* type; //线路类型 比如：普通公交、地铁等
@property(nonatomic,retain) NSString* status; //线路状态  0：停止，1：普通
@property(nonatomic,retain) NSString* line_id; //线路唯一id标识
@property(nonatomic,retain) NSString* key_name; //路线名称的关键部分
@property(nonatomic,retain) NSString* front_name; //始发站名称
@property(nonatomic,retain) NSString* terminal_name;//终点站名称
@property(nonatomic,retain) NSString* start_time; //首班发车时间 格式初定为”HHMM”,时间为24小时制(0000--2359)
@property(nonatomic,retain) NSString* end_time;   //末班发车时间 格式初定为”HHMM”,时间为24小时制(0000--2359)
@property(nonatomic,retain) NSString* company;    //公交公司名称
@property(nonatomic,retain) NSString* basic_price; //基本价格
@property(nonatomic,retain) NSString* total_price; //总价格 当为单一票价的时候，总价格=基本价格
@property(nonatomic,retain) NSString* commutation_ticket; //是否可以使用月票，0：无，1：有
@property(nonatomic,retain) NSString* auto_ticket; //是否自动（无人）售票，0：否，1：是
@property(nonatomic,retain) NSString* ic_card;     //是否使用电子售票/交通卡，0：否，1：是
@property(nonatomic,retain) NSString* loop;        //是否环线，没有起点，没有终点，周而复始，比如地铁环线。0：否，1：是
@property(nonatomic,retain) NSString* double_deck; //是否双层，0：否，1：是
@property(nonatomic,retain) NSString* data_source; //数据来源，1：自行采集，0：其他
@property(nonatomic,retain) NSString* air;         //是否有空调，0：无，1：有
@property(nonatomic,retain) NSString* description; //线路备注信息
@property(nonatomic,retain) NSString* speed;       //线路的平均行驶速度，（目前是以采集到的速度为准）,单位为 km/h
@property(nonatomic,retain) NSString* front_spell; //始发站名称拼音
@property(nonatomic,retain) NSString* terminal_spell;//终点站名称拼音
@property(nonatomic,retain) NSString* service_period;//服务时间周期描述，例如：夏季线路、周末线路、夜班车等
@property(nonatomic,retain) NSString* time_interval1;//发车间隔1
@property(nonatomic,retain) NSString* interval1; //发车间隔1适用的时间段，起始时间（HHMM）空格截至时间（HHMM）
@property(nonatomic,retain) NSString* time_interval2;//发车间隔2
@property(nonatomic,retain) NSString* interval2;//发车间隔2适用的时间段，起始时间（HHMM）空格截至时间（HHMM）
@property(nonatomic,retain) NSString* time_interval3;//发车间隔3
@property(nonatomic,retain) NSString* interval3; //发车间隔3适用的时间段，起始时间（HHMM）空格截至时间（HHMM）
@property(nonatomic,retain) NSString* time_interval4;//发车间隔4
@property(nonatomic,retain) NSString* interval4; //发车间隔4适用的时间段，起始时间（HHMM）空格截至时间（HHMM）
@property(nonatomic,retain) NSString* time_interval5;//发车间隔5
@property(nonatomic,retain) NSString* interval5; //发车间隔5适用的时间段，起始时间（HHMM）空格截至时间（HHMM）
@property(nonatomic,retain) NSString* time_interval6;//发车间隔6
@property(nonatomic,retain) NSString* interval6; //发车间隔6适用的时间段，起始时间（HHMM）空格截至时间（HHMM）
@property(nonatomic,retain) NSString* time_interval7;//发车间隔7
@property(nonatomic,retain) NSString* interval7; //发车间隔7适用的时间段，起始时间（HHMM）空格截至时间（HHMM）
@property(nonatomic,retain) NSString* time_interval8;//发车间隔8
@property(nonatomic,retain) NSString* interval8; //发车间隔8适用的时间段，起始时间（HHMM）空格截至时间（HHMM）
@property(nonatomic,retain) NSString* time_desc; //发车信息 用文字来描述无特定发车规则（即发车无规律）的发车信息
@property(nonatomic,retain) NSString* express_way;//公共交通线是否路经高速道路，0:否，1：是
@property(nonatomic,retain) NSString* stationDesc;//途经站点信息描述
@property(nonatomic,retain) NSString* coorDesc; //线路坐标描述信息
@end

@interface MABusLineSearchResult : NSObject
@property(nonatomic,retain) NSArray* busLineArray;//MABusline对象的序列
@property(nonatomic,assign) NSInteger count;      //允许返回记录数 
@property(nonatomic,retain) NSString* searchtime; //查询时间
@property(nonatomic,assign) NSInteger record;     //当前返回记录数
@property(nonatomic,assign) NSInteger total;      //总记录数
@end


@interface MARGCItem : NSObject
@property(nonatomic,retain) NSString* x; //偏移后的经度坐标
@property(nonatomic,retain) NSString* y; //偏移后的纬度坐标
@end

@interface MARGCSearchResult : NSObject
@property(nonatomic,retain) NSArray* rgcItemArray;//返回的MARGCItem对象的序列
@end

@interface MAGeoPOI : NSObject
@property(nonatomic,retain) NSString* name; //名称
@property(nonatomic,retain) NSString* level; //等级
@property(nonatomic,retain) NSString* x;     //经度坐标
@property(nonatomic,retain) NSString* y;     //纬度坐标
@property(nonatomic,retain) NSString* address; //地址
@property(nonatomic,retain) NSString* province; //省份
@property(nonatomic,retain) NSString* city;     //城市
@property(nonatomic,retain) NSString* district; //区域
@property(nonatomic,retain) NSString* range;    //范围
@property(nonatomic,retain) NSString* ename;    //英文名称
@property(nonatomic,retain) NSString* eprovince; //英文省份
@property(nonatomic,retain) NSString* ecity;     //英文城市
@property(nonatomic,retain) NSString* edistrict; //英文区域
@property(nonatomic,retain) NSString* eaddress;  //英文地址
@end


@interface MAGeoCodingSearchResult : NSObject
@property(nonatomic,assign) NSInteger count; //返回的记录条数
@property(nonatomic,retain) NSArray* geoCodingArray; //返回的地理兴趣点(MAGeoPOI对象)队列
@end


@interface MAProvince : NSObject
@property(nonatomic,retain) NSString* name;//省份名称
@property(nonatomic,retain) NSString* code;//省份编码
@end

@interface MACity : NSObject 
@property(nonatomic,retain) NSString* name;//城市名称
@property(nonatomic,retain) NSString* code;//城市编码
@property(nonatomic,retain) NSString* tel;//电话区号
@end

@interface MADistrict : NSObject 
@property(nonatomic,retain) NSString* name;//区域名称
@property(nonatomic,retain) NSString* code;//区域编码
@property(nonatomic,retain) NSString* x;//区域中心点经度
@property(nonatomic,retain) NSString* y;//区域中心点纬度
@property(nonatomic,retain) NSString* bounds;//区域矩形范围
@end

@interface MARoad : NSObject
@property(nonatomic,retain) NSString* Id; //道路id
@property(nonatomic,retain) NSString* name;//道路名称
@property(nonatomic,retain) NSString* ename;//道路英文名称
@property(nonatomic,retain) NSString* width;//道路宽度
@property(nonatomic,retain) NSString* level;//道路等级
@property(nonatomic,retain) NSString* direction;//道路方向
@property(nonatomic,retain) NSString* distance;//距离参数点距离
@end


@interface MACross : NSObject
@property(nonatomic,retain) NSString* name;//交叉口名称
@property(nonatomic,retain) NSString* x; //交叉口经度
@property(nonatomic,retain) NSString* y; //交叉口纬度
@end


@interface MAReverseGeocodingInfo : NSObject
@property(nonatomic,retain) MAProvince* province;//省份信息
@property(nonatomic,retain) MACity* city;//城市信息
@property(nonatomic,retain) MADistrict* district;//区信息
@property(nonatomic,retain) NSArray* roads;//道路信息 MARoad对象队列
@property(nonatomic,retain) NSArray* pois;//poi信息 MAPOI对象队列
@property(nonatomic,retain) NSArray* crosses;//道路交叉口信息
@end


@interface MAReverseGeocodingSearchResult : NSObject
@property(nonatomic,retain) NSArray* resultArray; //返回的MAReverseGeocodingResult对象序列
@end






