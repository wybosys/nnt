
# include "Core.h"
# include "FlateBP.h"

WSI_BEGIN_CXX

template <typename T>
T tpl_inflate(T __val) {
    double ret = __val;
    if (ret < 1)
        ret += .1f;
    else if (ret < 10)
        ret += 1.f;
    else if (ret < 100)
        ret += 10.f;
    else if (ret < 1000)
        ret += 50.f;
    else if (ret < 10000)
        ret += 200.f;
    else if (ret < 100000)
        ret += 10000.f;
    else
        ret *= 1 + 1/log10(ret);
    return (T)ret;
}

template <typename T>
T tpl_deflate(T __val) {
    double ret = __val;
    if (ret < 1)
        ret -= .1f;
    else if (ret < 10)
        ret -= 1.f;
    else if (ret < 100)
        ret -= 10.f;
    else if (ret < 1000)
        ret -= 50.f;
    else if (ret < 10000)
        ret -= 200.f;
    else if (ret < 100000)
        ret -= 10000.f;
    else
        ret *= 1 - 1/log10(ret);
    return (T)ret;
}

int bp_inflate_int(int __val) {
    return tpl_inflate(__val);
}

int bp_deflate_int(int __val) {
    return tpl_deflate(__val);
}

float bp_inflate_float(float __val) {
    return tpl_inflate(__val);
}

float bp_deflate_float(float __val) {
    return tpl_deflate(__val);
}

double bp_inflate_double(double __val) {
    return tpl_inflate(__val);
}

double bp_deflate_double(double __val) {
    return tpl_deflate(__val);
}

WSI_END_CXX
