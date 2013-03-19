
# ifndef __NNT_TRAIL_MOTION_15A3814BF07C4362BB01C125EEF9ED17_H_INCLUDED
# define __NNT_TRAIL_MOTION_15A3814BF07C4362BB01C125EEF9ED17_H_INCLUDED

# import <CoreMotion/CMAccelerometer.h>
# import <CoreMotion/CMDeviceMotion.h>
# import <CoreMotion/CMGyro.h>

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(CMMotionManager);
NNTDECL_PRIVATE_HEAD(NNTMotion);

extern signal_t kSignalAccelerometerUpdate;
extern signal_t kSignalGyroUpdate;
extern signal_t kSignalDeviceMotionUpdate;

@interface NNTMotion : NNTObject {

# ifdef NNT_iOS_4
    
    CMMotionManager *motionManager;
    
# endif
    
    NNTDECL_PRIVATE(NNTMotion);
}

# ifdef NNT_iOS_4

@property (nonatomic, readonly) CMMotionManager *motionManager;

# endif

- (void)start;
- (void)stop;

@end

NNT_END_HEADER_OBJC

# endif