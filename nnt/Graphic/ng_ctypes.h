
# ifndef __NNT_Ng_CTYPES_FF4C48F6C2104A2EAF00D5A78E012252_H_INCLUDED
# define __NNT_Ng_CTYPES_FF4C48F6C2104A2EAF00D5A78E012252_H_INCLUDED

# include "NGBase.h"

NNT_BEGIN_HEADER_C

enum {
    NgCID = 0x10000000,
    NgCID_COLOR,
    NgCID_GRADIENT
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

NNT_END_HEADER_C

# endif