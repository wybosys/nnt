
# import "Core.h"
# import "WSISpatialite.h"
# include <sqlite3.h>
# import "../3rd/spatialite/spatialite.h"

WSI_BEGIN_OBJC

@implementation WSISpatialite

+ (NSString*)version {
    char const* ver = spatialite_version();
    return [NSString stringWithUTF8String:ver];
}

@end

WSI_END_OBJC