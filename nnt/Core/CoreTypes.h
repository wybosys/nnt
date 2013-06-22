
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

static usize vt_sizeof(NNTValueType vt)
{
    usize ret = 0;
    switch (vt)
    {
        default: break;
        case NNTValueTypeInt: case NNTValueTypeUInt:
            ret = sizeof(int); break;
        case NNTValueTypeShort: case NNTValueTypeUShort:
            ret = sizeof(short); break;
        case NNTValueTypeChar: case NNTValueTypeUChar:
            ret = sizeof(char); break;
        case NNTValueTypeLong: case NNTValueTypeULong:
            ret = sizeof(long); break;
        case NNTValueTypeLongLong: case NNTValueTypeULongLong:
            ret = sizeof(longlong); break;
        case NNTValueTypeFloat:
            ret = sizeof(float); break;
        case NNTValueTypeDouble:
# ifdef NNT_C_OPENCL
            ret = sizeof(float) + sizeof(float); break;
# else
            ret = sizeof(double); break;
# endif
    }
    return ret;
}

NNT_END_HEADER_C

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

# define _CORE_VT(val, vt) \
inline NNTValueType vt(val const&) { return NNTValueType##vt; }

NNT_END_HEADER_CXX

# endif

# endif
