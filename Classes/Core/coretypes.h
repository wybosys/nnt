
# ifndef __NNT_CORETYPES_21C223C1E5BE4B77A1B58C5614DDDA8E_H_INCLUDED
# define __NNT_CORETYPES_21C223C1E5BE4B77A1B58C5614DDDA8E_H_INCLUDED

NNT_BEGIN_HEADER_C

enum {
    CoreTypeUnknow,
    CoreTypeObject = CoreTypeUnknow,
    CoreTypeArray,
    CoreTypeDictionary,
    CoreTypePair,
    CoreTypeString,
    CoreTypeData,
    CoreTypePointer,
};

typedef uint CoreTypes;

NNT_END_HEADER_C

# endif
