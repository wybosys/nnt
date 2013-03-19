//
//  UpLoadController.h
//  MSC20Demo
//  ypzhao add
//  Created by ypzhao on 12-10-16.
//
//

#import <UIKit/UIKit.h>

@class DataUploader;
@class UpLoadView;

@protocol UpLoadControllerDelegate

- (void) onGrammer: (NSString*)grammer error: (int)err;

@end

@interface UpLoadController : UIView
{
    DataUploader *_dataUploader;
    UpLoadView   *_upLoadView;
    
    id <UpLoadControllerDelegate> _delegate;
}

@property(assign) id<UpLoadControllerDelegate> delegate;

- (id) initWithOrigin:(CGPoint) origin;

- (void) setContent: (NSString *)name data: (NSString*)data params: (NSString*)params;

- (void) start;

@end
