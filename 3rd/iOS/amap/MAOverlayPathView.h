//
//  MAOverlayPathView.h
//  MAMapKit
//
//  
//  Copyright (c) 2011年 Autonavi Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MAOverlayView.h"

/// 该类定义了一个基本的OverlayView，并且在MAMapKit中预置了几个经常使用的OverlayView
@interface MAOverlayPathView : MAOverlayView {
    @package    
    UIColor *_fillColor;
    UIColor *_strokeColor;
    
    CGFloat _lineWidth;
    CGLineJoin _lineJoin;
    CGLineCap _lineCap;
    CGFloat _miterLimit;
    CGFloat _lineDashPhase;
    NSArray *_lineDashPattern;
    CGPathRef _path;
    
    struct _pointXY{
        struct _pointXY* pre;
        CGPoint pointXY;
        struct _pointXY* next;
    } *mutiPointRef;
}

/// 填充颜色
@property (retain) UIColor *fillColor;
/// 画笔颜色
@property (retain) UIColor *strokeColor;

/// 画笔宽度，默认为0
@property CGFloat lineWidth;
/// LineJoin，默认为kCGLineJoinRound
@property CGLineJoin lineJoin;
/// LineCap，默认为kCGLineCapRound
@property CGLineCap lineCap;
/// miterLimit,在样式为kCGLineJoinMiter时有效，默认为10
@property CGFloat miterLimit;
/// lineDashPhase, 默认为0
@property CGFloat lineDashPhase;
/// lineDashPattern,一个NSNumbers的数组，默认为nil
@property (copy) NSArray *lineDashPattern;

/**
 *生成要绘制的path，子类需要重写此函数，并且对path属性赋值：self.path = newPath;
 */
- (void)createPath;
/// path对象
@property CGPathRef path;

/**
 *绘制path
 *@param path 要绘制的CGPath
 *@param context CGContext对象
 */
- (void)strokePath:(CGPathRef)path inContext:(CGContextRef)context;

/**
 *填充path
 *@param path 要绘制的CGPath
 *@param context CGContext对象
 */
- (void)fillPath:(CGPathRef)path inContext:(CGContextRef)context;

@end
