
# import "Core.h"
# import "ICRCameraController.h"
# import "Time+WSI.h"
# import "UIImage+WSI.h"

WSI_BEGIN_OBJC

@implementation ICRCameraView

@synthesize camera = _camera;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _camera = [[UICameraView alloc] initWithZero];
    [self addSubview:_camera];
    safe_release(_camera);
    
    return self;
}

- (void)layoutSubviews {
    _camera.frame = self.bounds;
}

@end

WSIDECL_PRIVATE_BEGIN(ICRCameraController, NSObject) {
    WSINSTimer* _timer;
    BOOL _processing;
}

- (void)suspend;
- (void)resume;

WSIDECL_PRIVATE_IMPL(ICRCameraController)

- (id)init {
    self = [super init];
    
    [_timer = [WSINSTimer alloc] initWithTimeInterval:1 repeats:YES];
    [_timer connect:kSignalTimerFired sel:@selector(act_timer) obj:self];
    [_timer start];
    
    _processing = NO;
    
    return self;
}

- (void)dealloc {
    [_timer stop];
    [_timer release];
    [super dealloc];
}
     
- (void)act_timer {
    UICameraView* view = d_owner.cameraView.camera;
    [view snapshot];
}

- (void)suspend {
    [_timer pause];
}

- (void)resume {
    [_timer resume];
}

     
WSIDECL_PRIVATE_END

@implementation ICRCameraController

@synthesize cameraView = _cameraView;

- (id)init {
    self = [super init];            
    WSIDECL_PRIVATE_INIT(ICRCameraController);        
    return self;
}

- (void)dealloc {        
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalSnapshot)
WSIEVENT_END

- (void)loadView {
    _cameraView = [[ICRCameraView alloc] initWithZero];
    self.view = _cameraView;
    [_cameraView release];
}

- (void)viewIsLoading {
    [_cameraView.camera connect:kSignalSnapshot sig:kSignalSnapshot obj:self];
}

- (void)suspend {
    [d_ptr suspend];
}

- (void)resume {
    [d_ptr resume];
}

@end

_CXXCONTROLLER_IMPL(ICRCameraController);

WSI_END_OBJC
