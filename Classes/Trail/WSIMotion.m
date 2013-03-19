
# import "Core.h"
# import "NNTMotion.h"
# import <CoreMotion/CoreMotion.h>

NNT_BEGIN_OBJC

signal_t kSignalAccelerometerUpdate = @"::nnt::trail::motion::accelerometer";
signal_t kSignalGyroUpdate = @"::nnt::trail::motion::gyro";
signal_t kSignalDeviceMotionUpdate = @"::nnt::trail::motion::device";

@interface NNTMotionPrivate : NNTObject {
    
}

@property (nonatomic, assign) NNTMotion *d_owner;

@end

@implementation NNTMotionPrivate

@synthesize d_owner;

- (id)init {
    self = [super init];
    return self;
}

@end

static CMMotionManager *__gs_motion_manager = nil;

@implementation NNTMotion

# ifdef NNT_iOS_4

@synthesize motionManager;

# endif

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNTMotion);
    
# ifdef NNT_iOS_4
        
    NNT_SYNCHRONIZED(self)
    if (__gs_motion_manager == nil) {
        __gs_motion_manager = [[CMMotionManager alloc] init];
        NNT *wsiobj = [NNT shared];
        if (wsiobj) {
            [wsiobj storeSet:@"::nnt::trail::motion::singleton" obj:__gs_motion_manager];
            [__gs_motion_manager release];
        }
        motionManager = __gs_motion_manager;
    }
    NNT_SYNCHRONIZED_END
    
    motionManager.accelerometerUpdateInterval = 1.f;
    motionManager.gyroUpdateInterval = 1.f;
    motionManager.deviceMotionUpdateInterval = 1.f;
    
# endif
    
    return self;
}

- (void)dealloc {    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalAccelerometerUpdate)
NNTEVENT_SIGNAL(kSignalGyroUpdate)
NNTEVENT_SIGNAL(kSignalDeviceMotionUpdate)
NNTEVENT_END

- (void)start {
# ifdef NNT_iOS_4
    
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
# ifdef NNT_iOS_4
    
    [motionManager stopAccelerometerUpdates];
    [motionManager stopGyroUpdates];
    [motionManager stopDeviceMotionUpdates];
    
# endif
}

@end

NNT_END_OBJC