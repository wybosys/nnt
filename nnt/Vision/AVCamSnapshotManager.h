
# ifndef __NNT_VISION_AVCAMSNAPSHOT_5B16CCE45A254A36A17A296188CF899E_H_INCLUDED
# define __NNT_VISION_AVCAMSNAPSHOT_5B16CCE45A254A36A17A296188CF899E_H_INCLUDED

# import "AVCamCaptureManager.h"

NNT_BEGIN_HEADER_OBJC

@interface AVCamSnapshotManager : AVCamCaptureManager <AVCaptureVideoDataOutputSampleBufferDelegate> {
    @private
    BOOL _snapshot;
}

@property (nonatomic, retain) AVCaptureStillImageOutput *stillImageOutput;
@property (nonatomic, retain) AVCaptureVideoDataOutput *snapshotOutput;

- (void)captureStillImage;
- (void)snapshot;

@end

NNT_END_HEADER_OBJC

# endif