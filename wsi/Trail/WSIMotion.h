
# ifndef __WSI_TRAIL_MOTION_15A3814BF07C4362BB01C125EEF9ED17_H_INCLUDED
# define __WSI_TRAIL_MOTION_15A3814BF07C4362BB01C125EEF9ED17_H_INCLUDED

# import <CoreMotion/CMAccelerometer.h>
# import <CoreMotion/CMDeviceMotion.h>
# import <CoreMotion/CMGyro.h>

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(CMMotionManager);
WSIDECL_PRIVATE_HEAD(WSIMotion);

extern signal_t kSignalAccelerometerUpdate;
extern signal_t kSignalGyroUpdate;
extern signal_t kSignalDeviceMotionUpdate;

@interface WSIMotion : WSIObject {

# ifdef WSI_iOS_4
    
    CMMotionManager *motionManager;
    
# endif
    
    WSIDECL_PRIVATE(WSIMotion);
}

# ifdef WSI_iOS_4

@property (nonatomic, readonly) CMMotionManager *motionManager;

# endif

- (void)start;
- (void)stop;

@end

WSI_END_HEADER_OBJC

# endif