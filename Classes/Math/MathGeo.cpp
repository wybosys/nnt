
# include "Core.h"
# include "MathGeo.h"

NNT_BEGIN_C

double geo_distance(double lat0, double ltd0, double lat1, double ltd1)
{
    double a = lat0 - lat1;
    double b = ltd0 - ltd1;
    double s = 2 * asin(sqrt(sin(a * .5f) * sin(a * .5f) + cos(lat0) * cos(lat1) * sin(b * .5f) * sin(b * .5f))) * 6378.127e3;
    return s;
}

double geo_distance_angle(double lat0, double ltd0, double lat1, double ltd1) {
    return geo_distance(ANGLE2RAD(lat0), ANGLE2RAD(ltd0), ANGLE2RAD(lat1), ANGLE2RAD(ltd1));
}

NNT_END_C
