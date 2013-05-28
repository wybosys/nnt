
# ifndef __NNT_OPENCL_PRV_80620AB8488E4D5C8DAEADB2DE0677B1_H_INCLUDED
# define __NNT_OPENCL_PRV_80620AB8488E4D5C8DAEADB2DE0677B1_H_INCLUDED

# ifdef NNT_OPENCL

#   ifdef NNT_MACH

#     include <OpenCL/opencl.h>

#   endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNT_BEGIN_NS(opencl)

# define _OPENCL_VTO(type, def) \
typedef struct {} vt_##type##_t; \
NNT_CONST_VAR(vt_##type##_t, vt_##type##_o); \
inline NNTOpenCLValueType vt(type const&) { return NNTOpenCLValueType##def; } \
inline vt_##type##_t const& vt_o(type const&) { return vt_##type##_o; }

_OPENCL_VTO(char, Char);
_OPENCL_VTO(uchar, UChar);
_OPENCL_VTO(short, Short);
_OPENCL_VTO(ushort, UShort);
_OPENCL_VTO(int, Int);
_OPENCL_VTO(uint, UInt);
_OPENCL_VTO(long, Long);
_OPENCL_VTO(ulong, ULong);
_OPENCL_VTO(float, Float);
_OPENCL_VTO(double, Double);

static usize vt_sizeof(NNTOpenCLValueType vt)
{
    usize ret = 0;
    switch (vt)
    {
        case NNTOpenCLValueTypeChar: ret = sizeof(cl_char); break;
        case NNTOpenCLValueTypeUChar: ret = sizeof(cl_uchar); break;
        case NNTOpenCLValueTypeShort: ret = sizeof(cl_short); break;
        case NNTOpenCLValueTypeUShort: ret = sizeof(cl_ushort); break;
        case NNTOpenCLValueTypeInt: ret = sizeof(cl_int); break;
        case NNTOpenCLValueTypeUInt: ret = sizeof(cl_uint); break;
        case NNTOpenCLValueTypeLong: ret = sizeof(cl_long); break;
        case NNTOpenCLValueTypeULong: ret= sizeof(cl_ulong); break;
        case NNTOpenCLValueTypeFloat: ret = sizeof(cl_float); break;
        case NNTOpenCLValueTypeDouble: ret = sizeof(cl_double); break;
    }
    return ret;
}

NNT_END_NS

NNT_END_HEADER_CXX

# endif // cxx

# endif // opencl

# endif
