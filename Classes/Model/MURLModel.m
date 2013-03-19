
# import "Core.h"
# import "MURLModel.h"

NNT_BEGIN_OBJC

@implementation MURLHeaderField

@synthesize mech, field, value;

- (void)dealloc {
    zero_release(field);
    zero_release(value);
    [super dealloc];
}

@end

@implementation Model (URLModel)

- (void)setHttpHeaderValue:(NSString *)value forField:(NSString *)field {
    MURLHeaderField* seg = [[MURLHeaderField alloc] init];
    seg.mech = MURLHeaderFieldMechSet;
    seg.field = field;
    seg.value = value;
    [self.extendDatas addObject:seg];
    [seg release];
}

- (void)addHttpHeaderValue:(NSString *)value forField:(NSString *)field {
    MURLHeaderField* seg = [[MURLHeaderField alloc] init];
    seg.mech = MURLHeaderFieldMechAdd;
    seg.field = field;
    seg.value = value;
    [self.extendDatas addObject:seg];
    [seg release];
}

+ (MURLHeaderField*)SetHttpHeaderValue:(NSString *)value forField:(NSString *)field {
    MURLHeaderField* seg = [[MURLHeaderField alloc] init];
    seg.mech = MURLHeaderFieldMechSet;
    seg.field = field;
    seg.value = value;
    return [seg autorelease];
}

+ (MURLHeaderField*)AddHttpHeaderValue:(NSString *)value forField:(NSString *)field {
    MURLHeaderField* seg = [[MURLHeaderField alloc] init];
    seg.mech = MURLHeaderFieldMechAdd;
    seg.field = field;
    seg.value = value;
    return [seg autorelease];
}

@end

NNT_END_OBJC