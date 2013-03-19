
# import "Core.h"
# import "Spatialite+NNT.h"
# include <sqlite3.h>
# import "../3rd/spatialite/spatialite.h"

NNT_BEGIN_OBJC

@implementation NNTSpatialite

+ (NSString*)version {
    char const* ver = spatialite_version();
    return [NSString stringWithUTF8String:ver];
}

@end

NNT_END_OBJC