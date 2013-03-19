
# ifndef __WSI_CORETYPES_21C223C1E5BE4B77A1B58C5614DDDA8E_H_INCLUDED
# define __WSI_CORETYPES_21C223C1E5BE4B77A1B58C5614DDDA8E_H_INCLUDED

WSI_BEGIN_HEADER_C

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

WSI_END_HEADER_C

# endif