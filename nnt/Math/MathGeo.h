
# ifndef __WSI_MATH_GEO_70D02C7ABB974E3A9AD05EAEA091870E_H_INCLUDED
# define __WSI_MATH_GEO_70D02C7ABB974E3A9AD05EAEA091870E_H_INCLUDED

# include "Math+WSI.h"

WSI_BEGIN_HEADER_C

# define LATITUDE_1DEG           111000
# define LATITUDE_1CENT          1850

# define LONGITUDE_1DEG(lat)     ( cos(lat) * LATITUDE_1DEG )
# define LONGITUDE_1CENT(lat)    ( LONGITUDE_1DEG(lat) * M_1_60)

WSI_EXTERN double geo_distance(double lat0, double ltd0, double lat1, double ltd1);
WSI_EXTERN double geo_distance_angle(double lat0, double ltd0, double lat1, double ltd1);

typedef double GeoDegree;

struct _GeoLocation
{
    GeoDegree latitude;
    GeoDegree longitude;
};

typedef struct _GeoLocation GeoLocation;

struct _GeoSpan
{
    GeoDegree dlatitude;
    GeoDegree dlongitude;
};

typedef struct _GeoSpan GeoSpan;

struct _GeoRegion
{
    GeoLocation center;
    GeoSpan span;
};

typedef struct _GeoRegion GeoRegion;

WSI_END_HEADER_C

# endif