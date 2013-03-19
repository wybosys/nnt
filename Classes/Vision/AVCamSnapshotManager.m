
# import "Core.h"
# import "AVCamSnapshotManager.h"
# import "AVCamUtilities.h"

NNT_BEGIN_OBJC

@interface AVCamCaptureManager (InternalUtilityMethods)

- (AVCaptureDevice *)cameraWithPosition:(AVCaptureDevicePosition)position;
- (AVCaptureDevice *)frontFacingCamera;
- (AVCaptureDevice *)backFacingCamera;
- (AVCaptureDevice *)audioDevice;

@end

@implementation AVCamSnapshotManager

@synthesize stillImageOutput;
@synthesize snapshotOutput;

- (id)init {
    self = [super init];
    
    _snapshot = NO;
    
    return self;
}

- (void)dealloc {
    safe_release(stillImageOutput);
    safe_release(snapshotOutput);
    
    [super dealloc];
}

- (void)snapshot {
    _snapshot = YES;
}

- (void)setupSession {
    [super setupSession];
    
    // Setup the still image file output
    AVCaptureStillImageOutput *newStillImageOutput = [[AVCaptureStillImageOutput alloc] init];
    NSDictionary *outputSettings = [[NSDictionary alloc] initWithObjectsAndKeys:
                                    AVVideoCodecJPEG, AVVideoCodecKey,
                                    nil];
    [newStillImageOutput setOutputSettings:outputSettings];
    [outputSettings release];
    
    // setup the snapshot output.
    AVCaptureVideoDataOutput* newSnapshotOutput = [[AVCaptureVideoDataOutput alloc] init];
    NSDictionary* snapshotSettings = [[NSDictionary alloc] initWithObjectsAndKeys:
                                      [NSNumber numberWithUnsignedInt:kCVPixelFormatType_32BGRA],
                                      (NSString*)kCVPixelBufferPixelFormatTypeKey, nil];
    newSnapshotOutput.alwaysDiscardsLateVideoFrames = YES;
    //newSnapshotOutput.minFrameDuration = CMTimeMake(1, 30);
    [[newSnapshotOutput connectionWithMediaType:AVMediaTypeVideo] setVideoMinFrameDuration:CMTimeMake(1, 30)];
    [newSnapshotOutput setSampleBufferDelegate:self queue:dispatch_get_main_queue()];
    [newSnapshotOutput setVideoSettings:snapshotSettings];
    [snapshotSettings release];
        
    if ([self.session canAddOutput:newStillImageOutput]) {
        [self.session addOutput:newStillImageOutput];
        self.stillImageOutput = newStillImageOutput;
    }
    if ([self.session canAddOutput:newSnapshotOutput]) {
        [self.session addOutput:newSnapshotOutput];
        self.snapshotOutput = newSnapshotOutput;
    }
    
    [newStillImageOutput release];
    [newSnapshotOutput release];
}

- (void)captureStillImage {    
    AVCaptureConnection *stillImageConnection = [AVCamUtilities connectionWithMediaType:AVMediaTypeVideo fromConnections:[[self stillImageOutput] connections]];
    if (stillImageConnection == nil)
        return;
    
    if ([stillImageConnection isVideoOrientationSupported])
        [stillImageConnection setVideoOrientation:self.orientation];
    
    [[self stillImageOutput] captureStillImageAsynchronouslyFromConnection:stillImageConnection
                                                         completionHandler:^(CMSampleBufferRef imageDataSampleBuffer, NSError *error) {	
                                                             UIImage* image = nil;
                                                             
															 if (imageDataSampleBuffer != NULL) {
																 NSData *imageData = [AVCaptureStillImageOutput jpegStillImageNSDataRepresentation:imageDataSampleBuffer];
                                                                 image = [[UIImage alloc] initWithData:imageData];
															 }
															 
															 if ([[self delegate] respondsToSelector:@selector(captureManagerStillImageCaptured:image:)]) {
																 [[self delegate] captureManagerStillImageCaptured:self image:image];
															 }
                                                             
                                                             [image release];
                                                         }];
}

@end

#pragma mark -
@implementation AVCamSnapshotManager (VideoDataOutputDelegate)

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    if (_snapshot == NO)
        return;
    
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer); 
    CVPixelBufferLockBaseAddress(imageBuffer,0); 
    uint8_t *baseAddress = (uint8_t *)CVPixelBufferGetBaseAddress(imageBuffer); 
    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(imageBuffer); 
    size_t width = CVPixelBufferGetWidth(imageBuffer); 
    size_t height = CVPixelBufferGetHeight(imageBuffer); 
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB(); 
    CGContextRef context = CGBitmapContextCreate(baseAddress,
                                                 width,
                                                 height,
                                                 8,
                                                 bytesPerRow,
                                                 colorSpace,
                                                 kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
    
    CGImageRef newImage = CGBitmapContextCreateImage(context); 
    CVPixelBufferUnlockBaseAddress(imageBuffer,0);
    CGContextRelease(context); 
    CGColorSpaceRelease(colorSpace);
    
    UIImage* image = [[UIImage alloc] initWithCGImage:newImage];
    CGImageRelease(newImage);
    
    if ([[self delegate] respondsToSelector:@selector(captureManagerSnapshotImageCompleted:image:)]) {
        [[self delegate] captureManagerSnapshotImageCompleted:self image:image];
    }
    
    [image release];
    
    _snapshot = NO;
}

@end

NNT_END_OBJC