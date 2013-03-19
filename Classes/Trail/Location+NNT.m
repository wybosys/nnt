
# import "Core.h"
# import "NNTLocation.h"
# import <CoreLocation/CoreLocation.h>

NNT_BEGIN_OBJC

signal_t kSignalLocationChanged = @"::nnt::trail::locaion::changed";
signal_t kSignalHeadingChanged = @"::nnt::trail::heading::changed";
signal_t kSignalRegionEnter = @"::nnt::trail::region::enter";
signal_t kSignalRegionExit = @"::nnt::trail::region::exit";

@interface NNTLocationPrivate : NNTObject <CLLocationManagerDelegate> {
    
}

@property (nonatomic, assign) NNTLocation *d_owner;

@end

@implementation NNTLocationPrivate

@synthesize d_owner;

# pragma mark delegate.

- (void)locationManager:(CLLocationManager *)manager
	didUpdateToLocation:(CLLocation *)newLocation
           fromLocation:(CLLocation *)oldLocation {
    [d_owner emit:kSignalLocationChanged result:newLocation];
}

- (void)locationManager:(CLLocationManager *)manager
       didUpdateHeading:(CLHeading *)newHeading {
    [d_owner emit:kSignalHeadingChanged result:newHeading];
}

# ifdef NNT_iOS_4

- (void)locationManager:(CLLocationManager *)manager
         didEnterRegion:(CLRegion *)region {
    [d_owner emit:kSignalRegionEnter result:region];
}

- (void)locationManager:(CLLocationManager *)manager
          didExitRegion:(CLRegion *)region {
    [d_owner emit:kSignalRegionExit result:region];
}

# endif

@end

@implementation NNTLocation

@synthesize locationManager;
@dynamic distanceFilter, desiredAccuracy;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNTLocation);
    
    locationManager = [[CLLocationManager alloc] init];
    locationManager.delegate = d_ptr;
    
    return self;
}

- (void)dealloc {
    zero_release(locationManager);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalLocationChanged)
NNTEVENT_SIGNAL(kSignalHeadingChanged)
NNTEVENT_SIGNAL(kSignalRegionEnter)
NNTEVENT_SIGNAL(kSignalRegionExit)
NNTEVENT_END

- (void)start {
    [locationManager startUpdatingLocation];
    [locationManager startUpdatingHeading];
}

- (void)stop {   
    [locationManager stopUpdatingLocation];
    [locationManager stopUpdatingHeading];
}

- (double)distanceFilter {
    return locationManager.distanceFilter;
}

- (double)desiredAccuracy {
    return locationManager.desiredAccuracy;
}

- (void)setDistanceFilter:(double)val {
    locationManager.distanceFilter = val;
}

- (void)setDesiredAccuracy:(double)val {
    locationManager.desiredAccuracy = val;
}

@dynamic locationEnable;

- (BOOL)locationEnable {
# ifdef NNT_iOS_4
    return [CLLocationManager locationServicesEnabled];
# endif
# ifdef NNT_iOS3
    return self.locationManager.locationServicesEnabled;
# endif
}

@end

@implementation NNTLocation (location)

@dynamic location;

- (CLLocation*)location {
    return locationManager.location;
}

@end

@implementation NNTLocation (heading)

# ifdef NNT_iOS_4

@dynamic heading;

- (CLHeading*)heading {
    return locationManager.heading;
}

# endif

@end

NNT_END_OBJC