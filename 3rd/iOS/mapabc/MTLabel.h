//
//  MTLabel.h
//  iMapSDKLib
//
//  Created by Duan Sijiu on 10-12-24.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>

/*!
    @header
    @abstract    文字标签视图 从UIView类继承
*/
@interface MTLabel : UIView{
}

/*!
 @method     
 @abstract   文字标签视图的构造（使用默认字体）
 @param      title 文字标签的文字内容
 */
+(id) labelWithTitle:(NSString*)title;
/*!
 @method     
 @abstract   文字标签视图的构造（使用指定字体）
 @param      title 文字标签的文字内容
 @param      font 文字标签的文字的字体
 */
+(id) labelWithTitle:(NSString*)title Font:(UIFont*) font;

/*!
 @method     
 @abstract   指定文字标签文字颜色
 @param      color 文字标签的文字颜色
 */
-(void) setTextColor:(UIColor*)color;
/*!
 @method     
 @abstract   指定文字标签背景颜色（标签的颜色）
 @param      color 文字标签的北京颜色
 */
-(void) setTipColor:(UIColor*)color;
/*!
 @method     
 @abstract   指定标签箭头指向SuperView的像素坐标
 @param      labelPoint 标签箭头指向SuperView的像素坐标
 */
-(void) setLabelPoint:(CGPoint) labelPoint;

@end
