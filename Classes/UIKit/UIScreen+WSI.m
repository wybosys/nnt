
# import "Core.h"
# import "UIScreen+WSI.h"

WSI_BEGIN_OBJC

WSIIMPL_CATEGORY(UIScreen, WSI);

# define M_1_72 0.01388888888889
# define M_1_96 0.01041666666667

@implementation UIScreen (WSI)

- (CGSize)currentViewSize {
    uint orientation = [UIApplication sharedApplication].statusBarOrientation;
    if (orientation == UIDeviceOrientationUnknown) 
        orientation = [UIDevice currentDevice].orientation;
    
    CGSize ret = [self currentMode].size;
    if (UIInterfaceOrientationIsLandscape(orientation)) {
        CGFloat tmp = ret.width;
        ret.width = ret.height;
        ret.height = tmp;
    }
    return ret;
}

+ (CGRect)convertCurrentRect:(CGRect)rect {
    CGPoint pt = [UIScreen convertCurrentPoint:rect.origin];
    CGSize sz = [UIScreen convertCurrentSize:rect.size];
    return CGRectMakePtSz(pt, sz);
}

+ (CGSize)convertCurrentSize:(CGSize)size {
    uint orientation = [UIApplication sharedApplication].statusBarOrientation;
    if (orientation == UIDeviceOrientationUnknown) 
        orientation = [UIDevice currentDevice].orientation;

    return UIInterfaceOrientationIsLandscape(orientation) ? CGSizeMake(size.height, size.width) : size;
}

+ (CGPoint)convertCurrentPoint:(CGPoint)pt {
    uint orientation = [UIApplication sharedApplication].statusBarOrientation;
    if (orientation == UIDeviceOrientationUnknown) 
        orientation = [UIDevice currentDevice].orientation;
    
    return UIInterfaceOrientationIsLandscape(orientation) ? CGPointMake(pt.y, pt.x) : pt;
}

+ (int)convertCurrentOffset:(int)offset {
    uint orientation = [UIApplication sharedApplication].statusBarOrientation;
    if (orientation == UIDeviceOrientationUnknown) 
        orientation = [UIDevice currentDevice].orientation;
    if (orientation == UIInterfaceOrientationLandscapeLeft) {
        return offset;
    } else if (orientation == UIInterfaceOrientationLandscapeRight) {
        return -offset;
    } else if (orientation == UIInterfaceOrientationPortrait) {
        return offset;
    }
    return -offset;
}

+ (UIInterfaceOrientation)orientation {
    uint orientation = [UIApplication sharedApplication].statusBarOrientation;
    if (orientation == UIDeviceOrientationUnknown) 
        orientation = [UIDevice currentDevice].orientation;
    return orientation;
}

static int __gs_is_retina = -1;
static const real __ppi_retina = PPI_RETINA_DEVICE * M_1_96;
static const real __ppi_normal = PPI_NORMAL_DEVICE * M_1_96;

+ (real)pointD2D:(real)val {
    if ([UIScreen isRetina]) {
        return val * __ppi_retina;
    }
    return val * __ppi_normal;
}

+ (real)point2Normal:(real)val {
    return val * __ppi_normal;
}

+ (real)point2Retina:(real)val {
    return val * __ppi_retina;
}

+ (BOOL)isRetina {
    if (__gs_is_retina == -1) {
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
            __gs_is_retina = 0;
        }    
        else {
            if ([UIScreen instancesRespondToSelector:@selector(scale)]) {
                CGFloat scale = [[UIScreen mainScreen] scale];            
                if (scale > 1.0) {
                    __gs_is_retina = 1;
                } else {
                    __gs_is_retina = 0;
                }
            }
        }
    }
    return __gs_is_retina == 1;
}

@end

@implementation UIScreenImage

@synthesize name = _name, orientation = _orientation;

- (void)dealloc {
    [_name release];
    [super dealloc];
}

@end

WSI_END_OBJC
