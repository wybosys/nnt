//
//  MAOverlayView.h
//  MAMapKit
//
// 
//  Copyright (c) 2011年 Autonavi Inc. All rights reserved.
//
#import <UIKit/UIKit.h>

#import "MAGeometry.h"
#import "MAOverlay.h"

/// 该类是地图覆盖物View的基类，所有地图覆盖物View需要继承自此类
@interface MAOverlayView : UIView
{
	@package
    id <MAOverlay> _overlay;
    MAMapRect _boundingMapRect;
    CGAffineTransform _mapTransform;
    id _geometryDelegate;
    id _canDrawCache;
    
    CFTimeInterval _lastTile;
    CFRunLoopTimerRef _scheduledScaleTimer;
    
    struct {
        unsigned int keepAlive:1;
        unsigned int levelCrossFade:1;
        unsigned int drawingDisabled:1;
        unsigned int usesTiledLayer:1;
    } _flags;
}

/**
 *初始化并返回一个overlay view
 *@param overlay 关联的overlay对象
 *@return 初始化成功则返回overlay view,否则返回nil
 */
- (id)initWithOverlay:(id <MAOverlay>)overlay;

///关联的overlay对象
@property (nonatomic, readonly) id <MAOverlay> overlay;

@end
