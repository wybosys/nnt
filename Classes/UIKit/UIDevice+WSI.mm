
# import "Core.h"
# import "UIDevice+WSI.h"
# import <sys/utsname.h>

WSI_BEGIN_OBJC

double device_version() {
    double version = [[UIDevice currentDevice].systemVersion doubleValue];
    return version;
}

bool need_manual_appear() {
    double version = [[UIDevice currentDevice].systemVersion doubleValue];
    return version < 5.0;
}

bool support_blocks() {
    double version = [[UIDevice currentDevice].systemVersion doubleValue];
    return version >= 4.0;
}

bool support_multitasks() {
    UIDevice* device = [UIDevice currentDevice];
    BOOL backgroundSupported = NO;
    if ([device respondsToSelector:@selector(isMultitaskingSupported)]) {
        backgroundSupported = device.multitaskingSupported;
    }
    return backgroundSupported;
}

enum
{
    MODEL_IPHONE_SIMULATOR,
    MODEL_IPAD_SIMULATOR,
    MODEL_IPOD_TOUCH,
    MODEL_IPHONE,
    MODEL_IPAD
};

static uint detectDevice() {
    NSString *model = [[UIDevice currentDevice] model];
    // Some iPod Touch return "iPod Touch", others just "iPod"
    
    uint detected;
    
    if ([model isEqualToString:@"iPhone Simulator"]) {
        detected = MODEL_IPHONE_SIMULATOR;
    } else if ([model isEqualToString:@"iPad Simulator"]) {
        detected = MODEL_IPAD_SIMULATOR;
    } else if ([model isEqualToString:@"iPad"]) {
        detected = MODEL_IPAD;
    } else if ([model isEqualToString:@"iPod Touch"]) {
        detected = MODEL_IPOD_TOUCH;
    } else if ([model isEqualToString:@"iPod touch"]) {
        detected = MODEL_IPOD_TOUCH;
    } else if ([model isEqualToString:@"iPod"]) {
        detected = MODEL_IPOD_TOUCH;
    } else {
        // Could be an iPhone V1 or iPhone 3G (model should be "iPhone")
        struct utsname u;
        
        // u.machine could be "i386" for the simulator, "iPod1,1" on iPod Touch, "iPhone1,1" on iPhone V1 & "iPhone1,2" on iPhone3G
        
        uname(&u);

        //if (!strcmp(u.machine, "iPhone1,1")) {
        //    detected = MODEL_IPHONE;
        //} else {
        detected = MODEL_IPHONE;
        //}
    }
    
    return detected;
}

WSIIMPL_CATEGORY(UIDevice, WSI);

@interface UIDevice ()

+ (uint) detectDevice;

@end

@implementation UIDevice (WSI)

- (CGAffineTransform)orientTransform {
    CGAffineTransform ret = CGAffineTransformIdentity;
    
    uint orient = [UIApplication sharedApplication].statusBarOrientation;
    if (orient == UIDeviceOrientationUnknown) {
        orient = self.orientation;
    }
    
    switch (orient) {
        default: break;
        case UIDeviceOrientationPortrait: {
        } break;
        case UIDeviceOrientationPortraitUpsideDown: {
            ret = CGAffineTransformRotate(ret, M_PI);
        } break;
        case UIDeviceOrientationLandscapeLeft: {
            ret = CGAffineTransformRotate(ret, M_PI_2);
        } break;
        case UIDeviceOrientationLandscapeRight: {
            ret = CGAffineTransformRotate(ret, M_PI + M_PI_2);
        } break;
    }
    
    return ret;
}

- (CGAffineTransform)transform {
    CGAffineTransform ret = {0};
    
    switch (self.orientation) {
        default:
        case UIDeviceOrientationLandscapeLeft: {
            ret.b = 1;
            ret.c = -1;
        } break;
        case UIDeviceOrientationLandscapeRight: {
            ret.b = -1;
            ret.c = 1;
        } break;
        case UIDeviceOrientationPortrait: {
            ret.a = 1;
            ret.d = 1;
        } break;
        case UIDeviceOrientationPortraitUpsideDown: {
            ret.a = -1;
            ret.d = -1;
        } break;
    }
    
    return ret;
}

- (CATransform3D)orientTransform3D {
    CATransform3D ret = CATransform3DIdentity;

    uint orient = [UIApplication sharedApplication].statusBarOrientation;
    if (orient == UIDeviceOrientationUnknown) {
        orient = self.orientation;
    }
    
    switch (orient) {
        default: break;
        case UIDeviceOrientationPortrait: {
        } break;
        case UIDeviceOrientationPortraitUpsideDown: {
            ret = CATransform3DMakeRotation(M_PI, 0, 0, 1);
        } break;
        case UIDeviceOrientationLandscapeLeft: {
            ret = CATransform3DMakeRotation(M_PI_2, 0, 0, 1);
        } break;
        case UIDeviceOrientationLandscapeRight: {
            ret = CATransform3DMakeRotation(M_PI + M_PI_2, 0, 0, 1);

        } break;
    }

    return ret;
}

+ (BOOL)isIPhone {
    int model = detectDevice();
    return MODEL_IPHONE == model;
}

+ (BOOL)isIPhoneSimulator {
    int model = detectDevice();
    return MODEL_IPHONE_SIMULATOR == model;
}

+ (BOOL)isIPad {
    int model = detectDevice();
    return MODEL_IPAD == model;
}

+ (BOOL)isIPadSimulator {
    int model = detectDevice();
    return MODEL_IPAD_SIMULATOR == model;
}

+ (BOOL)isIPod {
    int model = detectDevice();
    return MODEL_IPOD_TOUCH == model;
}

@end

WSI_END_OBJC
