
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

# endif
