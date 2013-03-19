
# ifndef __WSI_VISION_AVCAMRECORDER_263DDBDDBEA341A08E0400B03A9FCA68_H_INCLUDED
# define __WSI_VISION_AVCAMRECORDER_263DDBDDBEA341A08E0400B03A9FCA68_H_INCLUDED

# import "AVCamCaptureManager.h"

WSI_BEGIN_HEADER_OBJC

@class AVCamRecorder;

@interface AVCamRecorderManager : AVCamCaptureManager {
}

@property (nonatomic, retain) AVCamRecorder *recorder;

- (void)startRecording;
- (void)stopRecording;

@end

WSI_END_HEADER_OBJC

# endif