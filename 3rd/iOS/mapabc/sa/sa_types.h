
//_________________________________Copyright (c) 2009,Mapabc Co.,Ltd_____________________________
//                                       All rights reserved.
// 
//   文件名称：sa_types.h
//   文件标识：见配置管理计划书
//   描    述：地理信息服务类型定义
// 
//   当前版本：1.0
//   作    者：张小刚
//   完成日期：2010.01.31
//_______________________________________________________________________________________________

#ifndef	__SA_TYPES__H  
#define __SA_TYPES__H 

#include <string.h>
#include "ut_types.h"
#include "htl.h"

/////////////////////////////////POI查询/////////////////////////////////

struct MPOISEARCHOPTIONS // POI查询参数
{
	MPOISEARCHOPTIONS()
	{
		lRecordsPerPage = 10;    // 默认为10
		lPageNum        = 1;     // 默认为1
		lRange          = 3000;  // 默认为3000
		memset(cSearchType, 0, sizeof(cSearchType));
		strcpy(cSrcType, "POI"); // 默认为POI
		cSr             = 0;     // 默认按照关键字排序
		cLanguage       = 0;     // 默认为中文 // 中英文
	};

	long lRecordsPerPage; // 每页记录数
	long lPageNum;        // 分页号(显示第几页)
	long lRange;          // 周边查询范围,单位米
	char cSearchType[64]; // 查询类型,可不填 具体参考用户手册
	char cSrcType[32];    // 数据源类型 英文库 mpoi、基础库 POI、 企业地标 DIBIAO、公交站台 BUS、通用编辑器 USERPOI、
	                      // 上述数据源可以混合查询，例如公交数据+基础库数据查询BUS:1000%2bPOI,代表前1000条数据为公交数据，后面为基础库数据
	char cSr;             // cSr=0代表按照关键字排序 cSr=1代表按照距离排序
	char cLanguage;       // 查询语种 0中文 1英文 // 中英文
};

struct MPLATFORM // 站台信息
{
	MLONLAT Coor; // 站台坐标
};

struct MPOI // POI(兴趣点)
{
	unsigned short cAddress[128];  // 地址
	unsigned short cName[64];      // 名称
	unsigned short cType[64];      // 类型
	unsigned short cUrl[256];      // Url地址
	unsigned short cCityCode[64];  // 城市编码
	unsigned short cPguid[32];     // 唯一编号
	unsigned short cTel[64];       // 电话号码
	unsigned short cImageid[64];   // 图片ID
	double         X;             // X坐标
	double         Y;             // Y坐标
	long           lDistance;      // 周边查询时,距离中心点距离
	long           lNumOfPlatForm; // 站台数量 xml扩展信息
	MPLATFORM      *pPlatForms;    // 具体站台 xml扩展信息
};

struct MPOISEARCHRESULT // POI查询结果
{
	long  lCountNum; // 实际返回的数据总条数,跟用户的权限有关
	long  lTotalNum; // 符合查询条件的总条数
	long  lNum;      // 当页返回的数据条数

	MPOI *pPois;     // 具体的POI结果
};

/////////////////////////////////驾车查询/////////////////////////////////

//*****************驾车导航*****************

struct REGION // 避让区域
{
	htl::vector<MLONLAT> lonlats; // 避让区域坐标组
};

struct MAUTONAVISEARCHOPTIONS // 驾车导航查询参数
{
	MAUTONAVISEARCHOPTIONS()
	{
		lPer             = 1; // 默认返回50个点
		lRouteType       = 0; // 默认时间优先
		lAvoidanceType   = 3; // 默认区域避让加名称避让
		lSegmentCoorType = 1; // 默认只返回路段起点、终点

		memset(cName, 0, sizeof(cName));
	};

	long lPer;                     // 抽稀值 假如路线总长度为1000个点,我们把抽稀值填为150,则总长度就只返回150个点,1返回50个点
	long lRouteType;               // 路径计算方式 
	                               // lRouteType=0  时间优先
	                               // lRouteType=1  费用优先(不走收费路段最快道路)
	                               // lRouteType=2  距离优先
	                               // lRouteType=3  不走快速路(不走快速路,不包含高速路)
	                               // lRouteType=9  多策略(同时使用时间优先、费用优先、距离优先三个策略计算路径)
	                               // lRouteType=10 国道优先
	                               // lRouteType=11 省道优先
	long lSegmentCoorType;         // 路段坐标类型 
	                               // lSegmentCoorType = 0 不返回路段坐标 
	                               // lSegmentCoorType = 1 只返回路段起点、终点 
	                               // lSegmentCoorType = 2 返回路段所有坐标

	htl::vector<REGION> Regions;   // 避让区域
	char cName[64];                // 避让区域名称
	long lAvoidanceType;           // 路径规划时避让的信息,Regions和cName有一个不为空时候,avoidanceType就不能为空,否则查询无结果.
	                               // lAvoidanceType=1 区域避让
	                               // lAvoidanceType=2 名称避让
	                               // lAvoidanceType=3 区域避让加名称避让
	htl::vector<MLONLAT> PassByXY; // 途经点坐标
};

struct MAUTOSEGMENT // 路段
{
	MAUTOSEGMENT()
	{
		lRoadLength = 0;
		memset(cForm, 0, sizeof(cForm));
		memset(cGrade, 0, sizeof(cGrade));
		memset(cDirection, 0, sizeof(cDirection));
		memset(cRoadName, 0, sizeof(cRoadName));
		memset(cDriveTime, 0, sizeof(cDriveTime));
		memset(cAction, 0, sizeof(cAction));
		memset(cAccessorialInfo, 0, sizeof(cAccessorialInfo));
		memset(cTextInfo, 0, sizeof(cTextInfo));
	};
	
	long           lRoadLength;          // 路段长度
	unsigned short cForm[32];            // 道路描述
	unsigned short cGrade[32];           // 道路等级
	unsigned short cDirection[16];       // 行使方向
	unsigned short cRoadName[64];        // 道路名称
	unsigned short cDriveTime[32];       // 估算行驶时间
	unsigned short cAction[16];          // 辅助动作
	unsigned short cAccessorialInfo[32]; // 动作
	unsigned short cTextInfo[128];       // 本段道路行使文字描述
	htl::vector<MLONLAT> Coor;           // 路段坐标
};

struct MAUTONAVISEARCHRESULT // 驾车导航查询结果
{
	MAUTONAVISEARCHRESULT()
	{
		lTotalNum = 0;
		pSegments = NULL;
	};
	
	long                 lTotalNum; // 路线包含的路段数量
	MAUTOSEGMENT        *pSegments; // 具体的路段结果

	htl::vector<MLONLAT> Bound;     // 路线外接矩形 左下、右上坐标
	htl::vector<MLONLAT> Coors;     // 路线坐标
};

//*****************驾车导航距离*****************

struct MAUTODISSEARCHOPTIONS // 驾车导航距离查询参数
{
	MAUTODISSEARCHOPTIONS()
	{
		lRouteType = 0; // 默认时间优先
	};

	long lRouteType; // 路径计算方式 lRouteType=0 时间优先; lRouteType=1 距离优先
};

struct MAUTOROUTE // 路线
{
	long lRoadLength; // 路线长度
};

struct MAUTODISSEARCHRESULT // 驾车导航距离查询结果
{
	MAUTOROUTE *pRoutes; // 具体的路线结果
};

/////////////////////////////////公交查询/////////////////////////////////

//*****************公交导航*****************

struct MBUSNAVISEARCHOPTIONS // 公交导航查询参数
{
	MBUSNAVISEARCHOPTIONS()
	{
		lPer       = 1; // 默认返回50个点
		lRouteType = 0; // 默认时间优先
	};

	long lPer;       // 抽稀值 假如路线总长度为1000个点,我们把抽稀值填为150,则总长度就只返回150个点,1返回50个点
	long lRouteType; // 路径计算方式 0默认、1最经济、2最少换乘、3最少步行、4最舒适                            
};

struct MBUSDEPOTNAME // 公交站点名称
{
	MBUSDEPOTNAME()
	{
		memset(cName, 0, sizeof(cName));
	};
	
	unsigned short cName[32]; // 名称
};

struct MBUSSEGMENT // 路段
{
	MBUSSEGMENT()
	{
		memset(cStartName, 0, sizeof(cStartName));
		memset(cEndName, 0, sizeof(cEndName));
		memset(cBusName, 0, sizeof(cBusName));
		lDriverLength   = 0; 
		lFootLength     = 0; 
		lPassDepotCount = 0;
	};
	
	unsigned short cStartName[32];            // 起点名称
	unsigned short cEndName[32];              // 终点名称
	unsigned short cBusName[64];              // 公交名称
	htl::vector<MBUSDEPOTNAME> PassDepotName; // 途径站点名称
	long lDriverLength;                       // 行驶距离
	long lFootLength;                         // 步行距离
	long lPassDepotCount;                     // 途径站点数
	htl::vector<MLONLAT> CoordinateList;      // 路段坐标
	htl::vector<MLONLAT> PassDepotNameCoor;   // 途径站点坐标
};

struct MBUSPROJECT // 换乘方案
{
	MBUSPROJECT()
	{
		memset(cExpense, 0, sizeof(cExpense));
		lSegmentCount  = 0; 
		pSegments      = NULL; 
		lFootEndLength = 0;
	};
	
	unsigned short cExpense[32];  // 换乘方案价格
	long           lSegmentCount; // 换乘次数
	MBUSSEGMENT   *pSegments;     // 具体的路段结果

	long lFootEndLength;          // 换乘方案结束后,步行到终点距离
	htl::vector<MLONLAT> Bound;   // 路线外接矩形 左下、右上坐标
};

struct MBUSNAVISEARCHRESULT // 公交导航查询结果
{
	MBUSNAVISEARCHRESULT()
	{
		lTotalNum     = 0; 
		pBussProjects = NULL; 
	};
	
	long         lTotalNum;     // 换乘方案数量
	MBUSPROJECT *pBussProjects; // 具体的换乘方案结果
};

//*****************公交信息查询*****************

struct MBUSINFOSEARCHOPTIONS // 公交信息查询参数
{
	MBUSINFOSEARCHOPTIONS()
	{
		lRecordsPerPage = 10; // 默认为10
	    lPageNum        = 1;  // 默认为1
		lResData        = 0;  // 默认不返回xml的扩展信息
	};

	long lRecordsPerPage; // 每页记录数
	long lPageNum;        // 分页号(显示第几页)
	long lResData;        // 是否返回xml的扩展信息(xml扩展信息目前是途经点信息 ) 0不返回 1返回                        
};

struct MSTATION // 车站
{
	MSTATION()
	{
		memset(cName, 0, sizeof(cName));
		memset(&Coor, 0, sizeof(Coor));
		memset(cSpell, 0, sizeof(cSpell));
		memset(cCode, 0, sizeof(cCode));
		lStationNum = 0; 
	};
	
	unsigned short cName[32];   // 车站名称
	MLONLAT        Coor;        // 车站坐标
	unsigned short cSpell[128]; // 车站名称拼音
	unsigned short cCode[32];   // 编码
	long           lStationNum; // 车站次序
};

struct MBUSINFO // 公交信息
{
	MBUSINFO()
	{
		fLength = 0; 
		memset(cName, 0, sizeof(cName));
		memset(cLine_id, 0, sizeof(cLine_id));
		memset(cStartName, 0, sizeof(cStartName));
		memset(cEndName, 0, sizeof(cEndName));
		memset(cStartTime, 0, sizeof(cStartTime));
		memset(cEndTime, 0, sizeof(cEndTime));
		memset(cCompany, 0, sizeof(cCompany));	
		fBasicPrice   = 0;
		fTotakPrice   = 0;
		bIcCard       = false;
		lNumOfStation = 0;
		pStations     = NULL;
	};
	
	float                 fLength;        // 公交路线长度
	unsigned short        cName[32];      // 公交名称
	unsigned short        cLine_id[64];   // 公交线路ID
	unsigned short        cStartName[32]; // 起点名称
	unsigned short        cEndName[32];   // 终点名称
	unsigned short        cStartTime[32]; // 开车时间
	unsigned short        cEndTime[32];   // 收车时间
	unsigned short        cCompany[64];   // 所属公司
	float                 fBasicPrice;    // 一站票价
	float                 fTotakPrice;    // 总票价
	bool                  bIcCard;        // 是否可以使用IC卡
	long                  lNumOfStation;  // 途经车站的数量 xml扩展信息
	MSTATION             *pStations;      // 途经车站       xml扩展信息
	htl::vector<MLONLAT>  CoordinateList; // 路线坐标       xml扩展信息
};

struct MBUSINFOSEARCHRESULT // 公交信息查询结果
{
	MBUSINFOSEARCHRESULT()
	{
		lTotalNum  = 0; 
		lNum       = 0;
		pBussInfos = NULL;  
	};
	
	long      lTotalNum;  // 符合查询条件的总条数
	long      lNum;       // 此次返回的数据条数

	MBUSINFO *pBussInfos; // 具体的公交信息
};

/////////////////////////////////坐标查询/////////////////////////////////

struct MCOORDINATESEARCHOPTIONS // 坐标查询参数
{
	MCOORDINATESEARCHOPTIONS()
	{
		lCr = 0; // ?
	};

	long lCr; // ?                           
};

struct MCOORDINATESEARCHRESULT // 坐标查询结果
{
	MLONLAT Coor; // 查询后结果 经纬度
};

/////////////////////////////////位置查询/////////////////////////////////

struct MREGEOCODESEARCHOPTIONS // 位置查询参数
{
	MREGEOCODESEARCHOPTIONS()
	{
		lPoiNumber = 10;  // 默认返回10个POI点
		lRange     = 300; // 默认距离范围为300米
		lPattern   = 0;   // 默认返回地标性POI
		lRoadLevel = 0;   // 默认道路等级0-11范围的道路
		memset(cExkey, 0, sizeof(cExkey));
	};

	long lPoiNumber; // 返回周边的POI数量;
	long lRange;     // 限定周边热点POI和道路的距离范围
	long lPattern;   // 返回数据的模式,0为返回地标性POI,1为返回全部POI,如果xy在繁华地区设置为0效果较好,如果xy在偏远地区设置1更好
	long lRoadLevel;     // 道路等级 lRoadLevel 此参数目前为0－3，和国家标准的道路等级划分的对应关系如下:
	// lRoadLevel＝0,代表的标准道路等级0-11范围的道路
	// lRoadLevel＝1,代表的标准道路等级2-11范围的道路
	// lRoadLevel＝2,代表的标准道路等级7-11范围的道路
	// lRoadLevel＝3,代表的标准道路等级9-11范围的道路
	// 国家标准的道路等级划分共12级,参考如下：
	// 0 图廓线 未命名道路
	// 1 非导航道路
	// 2 普通道路
	// 3 次要道路
	// 4 县乡村内部道路
	// 5 乡公路
	// 6 县道
	// 7 主要道路
	// 8 主要大街、城市快速道
	// 9 省道
	// 10 国道
	// 11 高速公路

	char cExkey[64]; // 返回数据排除关键字
};

struct MPROVINCE // 省
{
	unsigned short cName[32]; // 省名
	long           lCode;     // 省编号
};

struct MCITY // 市
{
	unsigned short cName[32];   // 市名
	long           lCode;       // 市编号
	unsigned short cTelnum[16]; // 电话区号
};

struct MDISTRICT // 区域
{
	unsigned short cName[32]; // 区域名
	long           lCode;     // 区域编号
};

struct MROUNDROAD // 周边道路
{
	long           lId;            // 道路id
	unsigned short cName[32];      // 道路名
	unsigned short cDirection[32]; // 相对中心点方向
	float          fDistance;      // 相对中心点距离
	long           lWidth;         // 路宽
};

struct MROUNDPOI // 周边兴趣点
{
	unsigned short cType[64];      // 类型
	unsigned short cPguid[32];     // 唯一编号
	unsigned short cName[32];      // 名称
	unsigned short cAddress[128];  // 地址
	unsigned short cTel[64];       // 电话号码
	unsigned short cDirection[32]; // 相对中心点方向
	float          fDistance;      // 相对中心点距离
	MLONLAT        Coor;           // 坐标
};

struct MCROSSPOI // 交叉兴趣点
{
	unsigned short cName[32]; // 名称
	MLONLAT        Coor;      // 坐标
};

struct MREGEOCODESEARCHRESULT // 位置查询结果
{
	MPROVINCE   Province;        // 省
	MCITY       City;            // 市
	MDISTRICT   District;        // 区域
	long        lNumOfRoundRoad; // 周边道路的数量
	MROUNDROAD *pRoundRoads;     // 周边道路
	long        lNumOfRoundPoi;  // 周边兴趣点的数量
	MROUNDPOI  *pRoundPois;      // 周边兴趣点
	long        lNumOfCrossPoi;  // 交叉兴趣点的数量
	MCROSSPOI  *pCrossPois;      // 交叉兴趣点
};

struct MADDRESSPOI // 地址匹配兴趣点
{
	unsigned short cName[32]; // 名称
	MLONLAT        Coor;      // 坐标
};

struct MADDRESSMATHINGRESULT // 地址匹配查询结果
{
	long         lNumOfAddressPoi; // 地址匹配兴趣点的数量
	MADDRESSPOI *pAddressPois;     // 地址匹配兴趣点
};

struct MBSLRESULT // 基站定位查询结果
{
	unsigned short cCityCode[64]; // 城市编码
	long           lRadius;       // 误差半径
	MLONLAT        Coor;          // 坐标
};

#endif
//______________________________________________文件结束__________________________________________
