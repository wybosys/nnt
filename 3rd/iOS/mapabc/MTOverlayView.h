//
//  MTOverlayView.h
//  iMapSDKLib
//
//  Created by Duan Sijiu on 10-12-16.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MTMapObj.h"
/*!
    @header
    @abstract    绘制“地图上图形”的基类
*/

@interface MTOverlayView : UIView <MTMapObj>{
@package    
    CGFloat _lineWidth;
    CGLineJoin _lineJoin;
    CGLineCap _lineCap;
	
	CGPathRef _path;
}
/*!
 @abstract    绘制面的填充色
 */
@property (nonatomic,retain) UIColor *fillColor;
/*!
 @abstract    绘线的颜色
 */
@property (nonatomic,retain) UIColor *strokeColor;

/*!
    @method     
    @abstract   绘制面
    @param path: 点集
	@param context: 绘制上下文
*/
- (void)strokePath:(CGPathRef)path inContext:(CGContextRef)context;

/*!
 @method     
 @abstract   绘制线
 @param path: 点集
 @param context: 绘制上下文
 */
- (void)fillPath:(CGPathRef)path inContext:(CGContextRef)context;

/*!
 @method     
 @abstract   创建点集的方法，需要有子类具体实现。 向 _path 中创建点集。
 */
- (void)createPath;

/*!
 @abstract 点集 
 */
@property CGPathRef path; // path will be retained


@end
