
# ifndef __WSI_VISION_AVCAMSNAPSHOT_5B16CCE45A254A36A17A296188CF899E_H_INCLUDED
# define __WSI_VISION_AVCAMSNAPSHOT_5B16CCE45A254A36A17A296188CF899E_H_INCLUDED

# import "AVCamCaptureManager.h"

WSI_BEGIN_HEADER_OBJC

@interface AVCamSnapshotManager : AVCamCaptureManager <AVCaptureVideoDataOutputSampleBufferDelegate> {
    @private
    BOOL _snapshot;
}

@property (nonatomic, retain) AVCaptureStillImageOutput *stillImageOutput;
@property (nonatomic, retain) AVCaptureVideoDataOutput *snapshotOutput;

- (void)captureStillImage;
- (void)snapshot;

@end

WSI_END_HEADER_OBJC

# endif