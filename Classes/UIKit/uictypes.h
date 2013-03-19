
# ifndef __NNT_UIKIT_UICTYPES_3D32AFFC42D84B4EAC053238039CC69A_H_INCLUDED
# define __NNT_UIKIT_UICTYPES_3D32AFFC42D84B4EAC053238039CC69A_H_INCLUDED

# include "../Graphic/ng_ctypes.h"

NNT_BEGIN_HEADER_C

static usize cidtype_max_size() {
    usize ret = MAX(sizeof(wcg_color_t), sizeof(wcg_gradient_t));
    return ret;
}

# ifdef NNT_CXX

static const usize CIDTYPE_MAX_SIZE = cidtype_max_size();

# endif

NNT_END_HEADER_C

# endif