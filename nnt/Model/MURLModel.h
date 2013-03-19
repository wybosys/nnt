
# ifndef __NNT_MODEL_URLMODEL_FD18B932DAF94E6692FB3942CA4E3C60_H_INCLUDED
# define __NNT_MODEL_URLMODEL_FD18B932DAF94E6692FB3942CA4E3C60_H_INCLUDED

# include "Model.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

enum {
    MURLHeaderFieldMechSet = 0x01,
    MURLHeaderFieldMechAdd = 0x02,
};
typedef uint MURLHeaderFieldMech;

@interface MURLHeaderField : NSObject {
    MURLHeaderFieldMech mech;
    NSString *field, *value;
}

@property (nonatomic, assign) MURLHeaderFieldMech mech;
@property (nonatomic, copy) NSString *field, *value;

@end

@interface Model (URLModel)

- (void)setHttpHeaderValue:(NSString *)value forField:(NSString *)field;
- (void)addHttpHeaderValue:(NSString *)value forField:(NSString *)field;

+ (MURLHeaderField*)SetHttpHeaderValue:(NSString *)value forField:(NSString *)field;
+ (MURLHeaderField*)AddHttpHeaderValue:(NSString *)value forField:(NSString *)field;

@end

NNT_END_HEADER_OBJC

# endif // objc

# endif