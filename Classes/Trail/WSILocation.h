
# ifndef __NNT_TRAIL_LOCATION_88FC6224DD91459FB98E16C3B61E1427_H_INCLUDED
# define __NNT_TRAIL_LOCATION_88FC6224DD91459FB98E16C3B61E1427_H_INCLUDED

# import <CoreLocation/CLLocation.h>
# import <CoreLocation/CLHeading.h>

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(CLLocationManager);
NNTDECL_PRIVATE_HEAD(NNTLocation);

NNT_EXTERN signal_t kSignalLocationChanged;
NNT_EXTERN signal_t kSignalHeadingChanged;
NNT_EXTERN signal_t kSignalRegionEnter;
NNT_EXTERN signal_t kSignalRegionExit;

@interface NNTLocation : NNTObject {
    
    CLLocationManager *locationManager;
    
    NNTDECL_PRIVATE(NNTLocation);
}

@property (nonatomic, retain) CLLocationManager *locationManager;

/*
 *  desiredAccuracy
 *  
 *  Discussion:
 *      The desired location accuracy. The location service will try its best to achieve
 *      your desired accuracy. However, it is not guaranteed. To optimize
 *      power performance, be sure to specify an appropriate accuracy for your usage scenario (eg,
 *      use a large accuracy value when only a coarse location is needed). Use kCLLocationAccuracyBest to
 *      achieve the best possible accuracy. Use kCLLocationAccuracyBestForNavigation for navigation.
 *      By default, kCLLocationAccuracyBest is used.
 */
@property(assign, nonatomic) double distanceFilter;

/*
 *  desiredAccuracy
 *  
 *  Discussion:
 *      The desired location accuracy. The location service will try its best to achieve
 *      your desired accuracy. However, it is not guaranteed. To optimize
 *      power performance, be sure to specify an appropriate accuracy for your usage scenario (eg,
 *      use a large accuracy value when only a coarse location is needed). Use kCLLocationAccuracyBest to
 *      achieve the best possible accuracy. Use kCLLocationAccuracyBestForNavigation for navigation.
 *      By default, kCLLocationAccuracyBest is used.
 */
@property(assign, nonatomic) double desiredAccuracy;

//! start & stop.
- (void)start;
- (void)stop;

//! enable check.
@property (nonatomic, readonly) BOOL locationEnable;

@end

@interface NNTLocation (location)

@property(readonly, nonatomic) CLLocation *location;

@end

@interface NNTLocation (heading)

# ifdef NNT_iOS_4
@property(readonly, nonatomic) CLHeading *heading;
# endif

@end

NNT_END_HEADER_OBJC

# endif