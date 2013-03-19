//
//  MAPinAnnotationView.h
//  MAMapKit
//
//  
//  Copyright (c) 2011年 Autonavi Inc. All rights reserved.
//

#import "MAAnnotationView.h"


enum {
    MAPinAnnotationColorRed = 0,
    MAPinAnnotationColorGreen,
    MAPinAnnotationColorPurple
};
typedef NSUInteger MAPinAnnotationColor;

///提供类似大头针效果的annotation view
@interface MAPinAnnotationView : MAAnnotationView
{
@private
    MAPinAnnotationColor _pinColor;
	BOOL _animatesDrop;
}
///大头针的颜色，有MAPinAnnotationColorRed, MAPinAnnotationColorGreen, MAPinAnnotationColorPurple三种
@property (nonatomic) MAPinAnnotationColor pinColor;
///动画效果
@property (nonatomic) BOOL animatesDrop;


@end
