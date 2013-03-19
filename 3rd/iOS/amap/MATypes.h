/*
 *  MATypes.h
 *  MAMapKit
 *
 *  
 *  Copyright 2011 Autonavi Inc. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>


enum {
    MAMapTypeStandard = 0,//标准栅格图
    MAMapTypeSatellite,//影像图
    MAMapTypeVector//矢量图
};
typedef NSUInteger MAMapType;


UIKIT_EXTERN NSString *MAErrorDomain;

enum MAErrorCode {
    MAErrorUnknown = 1,
    MAErrorServerFailure,
    MAErrorLoadingThrottled,
    MAErrorPlacemarkNotFound,
};


typedef CGFloat MAZoomScale;