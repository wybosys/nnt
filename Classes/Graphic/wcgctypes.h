
# ifndef __WSI_WCG_CTYPES_FF4C48F6C2104A2EAF00D5A78E012252_H_INCLUDED
# define __WSI_WCG_CTYPES_FF4C48F6C2104A2EAF00D5A78E012252_H_INCLUDED

WSI_BEGIN_HEADER_C

enum {
    WCGCID = 0x10000000,
    WCGCID_COLOR,
    WCGCID_GRADIENT
};

typedef uint cid_t;

typedef struct {
    const uint cid;
    rgba_t color;    
} wcg_color_t;

typedef struct {
    const uint cid;
    wcg_color_t begin_color;
    wcg_color_t end_color;
    real begin_position;
    real end_position;
    real angle;    
} wcg_gradient_t;

WSI_END_HEADER_C

# endif