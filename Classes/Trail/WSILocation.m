
# import "WSIFoundation.h"
# import "WSILocation.h"
# import <CoreLocation/CoreLocation.h>

WSI_BEGIN_OBJC

signal_t kSignalLocationChanged = @"::wsi::trail::locaion::changed";
signal_t kSignalHeadingChanged = @"::wsi::trail::heading::changed";
signal_t kSignalRegionEnter = @"::wsi::trail::region::enter";
signal_t kSignalRegionExit = @"::wsi::trail::region::exit";

@interface WSILocationPrivate : WSIObject <CLLocationManagerDelegate> {
    
}

@property (nonatomic, assign) WSILocation *d_owner;

@end

@implementation WSILocationPrivate

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

# ifdef WSI_iOS_4

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

@implementation WSILocation

@synthesize locationManager;
@dynamic distanceFilter, desiredAccuracy;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSILocation);
    
    locationManager = [[CLLocationManager alloc] init];
    locationManager.delegate = d_ptr;
    
    return self;
}

- (void)dealloc {
    zero_release(locationManager);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalLocationChanged)
WSIEVENT_SIGNAL(kSignalHeadingChanged)
WSIEVENT_SIGNAL(kSignalRegionEnter)
WSIEVENT_SIGNAL(kSignalRegionExit)
WSIEVENT_END

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
# ifdef WSI_iOS_4
    return [CLLocationManager locationServicesEnabled];
# endif
# ifdef WSI_iOS3
    return self.locationManager.locationServicesEnabled;
# endif
}

@end

@implementation WSILocation (location)

@dynamic location;

- (CLLocation*)location {
    return locationManager.location;
}

@end

@implementation WSILocation (heading)

# ifdef WSI_iOS_4

@dynamic heading;

- (CLHeading*)heading {
    return locationManager.heading;
}

# endif

@end

WSI_END_OBJC