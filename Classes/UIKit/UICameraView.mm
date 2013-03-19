
# import "Core.h"
# import "UICameraView.h"
# import "AVCamSnapshotManager.h"

NNT_BEGIN_OBJC

signal_t kSignalSnapshot = @"::nnt::snapshot";

NNTDECL_PRIVATE_BEGIN(UICameraView, NNTObject) <AVCamCaptureManagerDelegate>

@property (nonatomic, readonly) AVCamSnapshotManager *captureManager;
@property (nonatomic, assign) AVCaptureVideoPreviewLayer* layerCapture;

NNTDECL_PRIVATE_IMPL(UICameraView)

@synthesize captureManager;
@synthesize layerCapture;

- (id)init {
    self = [super init];
    
    if (NNT_DEVICE_ISIPAD_SIMULATOR | NNT_DEVICE_ISIPHONE_SIMULATOR)
        [Msgbox info:_W(@"Camera run on device only !")];

    captureManager = [[AVCamSnapshotManager alloc] init];
    captureManager.delegate = self;
    
    [captureManager setupSession];
    
    if (captureManager) {
        layerCapture = [[AVCaptureVideoPreviewLayer alloc] initWithSession:captureManager.session];
    }
    
    if (layerCapture) {
        if ([layerCapture respondsToSelector:@selector(connection)]) {
            AVCaptureConnection* connection = [layerCapture performSelector:@selector(connection)];
            if (connection.isVideoOrientationSupported) {
                connection.videoOrientation = AVCaptureVideoOrientationPortrait;
            }
        } else if ([layerCapture isOrientationSupported]) {
            layerCapture.orientation = AVCaptureVideoOrientationPortrait;
        }
        
        layerCapture.videoGravity = AVLayerVideoGravityResizeAspectFill;
    }
    
    return self;
}

- (void)dealloc {
    captureManager.delegate = nil;
    
    safe_release(layerCapture);
    safe_release(captureManager);
    
    [super dealloc];
}

# pragma mark delegate.

- (void)captureManagerSnapshotImageCompleted:(AVCamCaptureManager *)captureManager image:(UIImage *)image {
    [d_owner emit:kSignalSnapshot result:image];
}

NNTDECL_PRIVATE_END

@implementation UICameraView

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    NNTDECL_PRIVATE_INIT_EX(UICameraView, d_ptr_camera);
    
    self.layer.masksToBounds = YES;
    
    if (d_ptr_camera.captureManager) {
        d_ptr_camera.layerCapture.frame = self.bounds;
        [self.layer addSublayer:d_ptr_camera.layerCapture];
    
        // start.
        [d_ptr_camera.captureManager startSession];
    }
    
    return self;
}

- (void)dealloc {
    [d_ptr_camera.captureManager stopSession];
    
    NNTDECL_PRIVATE_DEALLOC_EX(d_ptr_camera);
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalSnapshot)
NNTEVENT_END

- (void)layoutSubviews {
    CGRect const bounds = self.bounds;    
    d_ptr_camera.layerCapture.frame = bounds;
}

- (void)snapshot {
    [d_ptr_camera.captureManager snapshot];
}

@end

_CXXVIEW_IMPL(UICameraView);

NNT_END_OBJC
