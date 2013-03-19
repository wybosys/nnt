//
//  MACircleView.h
//  MAMapKit
//
//  Created by yin cai on 11-12-30.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "MACircle.h"
#import "MAOverlayPathView.h"
/// 该类用于定义圆对应的View
@interface MACircleView : MAOverlayPathView


/**
 *根据指定圆生成对应的View
 *@param circle 指定的圆
 *@return 生成的View
 */
- (id)initWithCircle:(MACircle *)circle;

/// 该View对应的圆
@property (nonatomic, readonly) MACircle *circle;

@end
