
# ifndef __NNT_CORETYPES_21C223C1E5BE4B77A1B58C5614DDDA8E_H_INCLUDED
# define __NNT_CORETYPES_21C223C1E5BE4B77A1B58C5614DDDA8E_H_INCLUDED

NNT_BEGIN_HEADER_C

typedef enum
{
    NNTCoreTypeUnknow,
    NNTCoreTypeObject = NNTCoreTypeUnknow,
    NNTCoreTypeArray,
    NNTCoreTypeDictionary,
    NNTCoreTypePair,
    NNTCoreTypeString,
    NNTCoreTypeData,
    NNTCoreTypePointer,
} NNTCoreType;

typedef enum
{
    NNTValueTypeUnknown,
    NNTValueTypeInt,
    NNTValueTypeUInt,
    NNTValueTypeShort,
    NNTValueTypeUShort,
    NNTValueTypeChar,
    NNTValueTypeUChar,
    NNTValueTypeLong,
    NNTValueTypeULong,
    NNTValueTypeLongLong,
    NNTValueTypeULongLong,
    NNTValueTypeString,
    NNTValueTypeFloat,
    NNTValueTypeDouble,
} NNTValueType;

typedef enum
{
    NNTOpenCLValueTypeChar,
    NNTOpenCLValueTypeUChar,
    NNTOpenCLValueTypeShort,
    NNTOpenCLValueTypeUShort,
    NNTOpenCLValueTypeHalf = NNTOpenCLValueTypeUShort,
    NNTOpenCLValueTypeInt,
    NNTOpenCLValueTypeUInt,
    NNTOpenCLValueTypeLong,
    NNTOpenCLValueTypeULong,
    NNTOpenCLValueTypeFloat,
    NNTOpenCLValueTypeDouble,
} NNTOpenCLValueType;

NNT_END_HEADER_C

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

# ifdef NNT_OPENCL

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

# endif

NNT_END_NS

NNT_END_HEADER_CXX

# endif

# endif
