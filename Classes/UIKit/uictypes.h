
# ifndef __WSI_UIKIT_UICTYPES_3D32AFFC42D84B4EAC053238039CC69A_H_INCLUDED
# define __WSI_UIKIT_UICTYPES_3D32AFFC42D84B4EAC053238039CC69A_H_INCLUDED

# include "../Graphic/wcgctypes.h"

WSI_BEGIN_HEADER_C

static usize cidtype_max_size() {
    usize ret = MAX(sizeof(wcg_color_t), sizeof(wcg_gradient_t));
    return ret;
}

# ifdef WSI_CXX

static const usize CIDTYPE_MAX_SIZE = cidtype_max_size();

# endif

WSI_END_HEADER_C

# endif