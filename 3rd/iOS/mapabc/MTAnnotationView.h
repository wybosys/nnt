//
//  MTAnnotationView.h
//  iMapSDK
//
//  Created by Duan Sijiu on 10-12-13.
//  Copyright 2010 Autonavi . All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MTMapObj.h"
#import "MTAnnotation.h"
#import "MTLabel.h"

@protocol MTAnnotationView_Delegate;

/*!
    @header
    @abstract    标注视图类，从UIView类继承
*/
@interface MTAnnotationView : UIView <MTMapObj,MTAnnotation>{

}
/*!
 @abstract    标注的图标资源
 */
@property (nonatomic, retain) UIImage *image;
/*!
 @abstract    标注是否可以被拾起
 */
@property (nonatomic) BOOL enablePickUp;

/*!
    @method     
    @abstract   标注视图的构造
*/
+(id)annotationViewWithFrame:(CGRect)frame UIImage:(UIImage*)img Delegate:(id<MTAnnotationView_Delegate>)delegate;

/*!
 @method     
 @abstract   为标注对象添加文字标签
 */
-(void) addLabel:(MTLabel*) label;
@end


/*!
 @header MTAnnotationView_Delegate
 @abstract MTAnnotationView回调接口协议类，从NSObject类继承。
 */
@protocol MTAnnotationView_Delegate<NSObject>
@optional

/*!
 @function
 @abstract 标注点击事件响应回调
 @param annotationView 标注视图实例指针
 */
-(void)AnnotationSelected:(MTAnnotationView*)annotationView;
@end


