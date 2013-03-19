
# include "Core.h"
# include "Math+WSI.h"

WSI_BEGIN_C

real distance_points2d(real x0, real y0, real x1, real y1) {
    real v0 = x0 - x1;
    real v1 = y0 - y1;
    return sqrtr(v0 * v0 + v1 * v1);
}

real restrict_value(real val, real region, real precise) {
    real right = (int)(val / region) * region;
    if (val && real_equal(val, right, precise))
        return region;
    return val - right;
}

WSI_END_C
