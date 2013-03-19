
# import "Core.h"
# import "WSIMotion.h"
# import <CoreMotion/CoreMotion.h>

WSI_BEGIN_OBJC

signal_t kSignalAccelerometerUpdate = @"::wsi::trail::motion::accelerometer";
signal_t kSignalGyroUpdate = @"::wsi::trail::motion::gyro";
signal_t kSignalDeviceMotionUpdate = @"::wsi::trail::motion::device";

@interface WSIMotionPrivate : WSIObject {
    
}

@property (nonatomic, assign) WSIMotion *d_owner;

@end

@implementation WSIMotionPrivate

@synthesize d_owner;

- (id)init {
    self = [super init];
    return self;
}

@end

static CMMotionManager *__gs_motion_manager = nil;

@implementation WSIMotion

# ifdef WSI_iOS_4

@synthesize motionManager;

# endif

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSIMotion);
    
# ifdef WSI_iOS_4
        
    WSI_SYNCHRONIZED(self)
    if (__gs_motion_manager == nil) {
        __gs_motion_manager = [[CMMotionManager alloc] init];
        WSI *wsiobj = [WSI shared];
        if (wsiobj) {
            [wsiobj storeSet:@"::wsi::trail::motion::singleton" obj:__gs_motion_manager];
            [__gs_motion_manager release];
        }
        motionManager = __gs_motion_manager;
    }
    WSI_SYNCHRONIZED_END
    
    motionManager.accelerometerUpdateInterval = 1.f;
    motionManager.gyroUpdateInterval = 1.f;
    motionManager.deviceMotionUpdateInterval = 1.f;
    
# endif
    
    return self;
}

- (void)dealloc {    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalAccelerometerUpdate)
WSIEVENT_SIGNAL(kSignalGyroUpdate)
WSIEVENT_SIGNAL(kSignalDeviceMotionUpdate)
WSIEVENT_END

- (void)start {
# ifdef WSI_iOS_4
    
    CMAccelerometerHandler hdl_accel = ^(CMAccelerometerData *accelerometerData, NSError *error) {
        [self emit:kSignalAccelerometerUpdate result:accelerometerData];
    };
    
    CMGyroHandler hdl_gyro = ^(CMGyroData *gyroData, NSError *error) {
        [self emit:kSignalGyroUpdate result:gyroData];
    };
    
    CMDeviceMotionHandler hdl_device = ^(CMDeviceMotion *motion, NSError *error) {
        [self emit:kSignalDeviceMotionUpdate result:motion];
    };

    [motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue mainQueue] withHandler:hdl_accel];
    [motionManager startGyroUpdatesToQueue:[NSOperationQueue mainQueue] withHandler:hdl_gyro];
    [motionManager startDeviceMotionUpdatesToQueue:[NSOperationQueue mainQueue] withHandler:hdl_device];
    
# endif
}

- (void)stop {
# ifdef WSI_iOS_4
    
    [motionManager stopAccelerometerUpdates];
    [motionManager stopGyroUpdates];
    [motionManager stopDeviceMotionUpdates];
    
# endif
}

@end

WSI_END_OBJC