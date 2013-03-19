
# import "Core.h"
# import "NSNumber+WSI.h"

WSI_BEGIN_OBJC

WSIIMPL_CATEGORY(NSNumber, WSI);

@implementation NSNumber (WSI)

- (NSString*) stringValueBinary {
    return [NSNumber StringValueBinary:[self intValue]];
}

+ (NSString*) StringValueBinary:(int)__val {
    char buf[33]; buf[32] = 0;
    int matcher = 0x1;
    for (int i = 0; i < 32; ++i) {
        buf[31 - i] = (__val & matcher) ? '1' : '0';
        matcher = matcher << 1;
    }
    char *pbuf = buf + 31;
    for (int i = 0; i < 31; ++i) {
        if (buf[i] != '0') {
            pbuf = buf + i;
            break;
        }
    }
    return [NSString stringWithUTF8String:pbuf];
}

- (real)realValue {
# if REAL_IS_FLOAT
    return [self floatValue];
# else
    return [self doubleValue];
# endif
}

+ (NSNumber *)numberWithReal:(real)val {
# if REAL_IS_FLOAT
    return [NSNumber numberWithFloat:val];
# else
    return [NSNumber numberWithDouble:val];
# endif
}

- (WSIValueType)valueType {
    char const* type = [self objCType];
    if (strcmp(type, @encode(int)) == 0)
        return WSIValueTypeInt;
    else if (strcmp(type, @encode(long)) == 0)
        return WSIValueTypeLong;
    else if (strcmp(type, @encode(float)) == 0)
        return WSIValueTypeFloat;
    else if (strcmp(type, @encode(double)) == 0)
        return WSIValueTypeDouble;
    else if (strcmp(type, @encode(long long)) == 0)
        return WSIValueTypeLongLong;
    return WSIValueTypeUnknown;
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX

::NSNumber *number(int val) {
    return [::NSNumber numberWithInt:val];
}

::NSNumber *number(uint val) {
    return [::NSNumber numberWithUnsignedInt:val];
}

::NSNumber *number(long val) {
    return [::NSNumber numberWithLong:val];
}

::NSNumber *number(ulong val) {
    return [::NSNumber numberWithUnsignedLong:val];
}

::NSNumber *number(longlong val) {
    return [::NSNumber numberWithLongLong:val];
}

::NSNumber *number(ulonglong val) {
    return [::NSNumber numberWithUnsignedLongLong:val];
}

::NSNumber *number(float val) {
    return [::NSNumber numberWithFloat:val];
}

::NSNumber *number(double val) {
    return [::NSNumber numberWithDouble:val];
}

::NSNumber *number(char val) {
    return [::NSNumber numberWithChar:val];
}

::NSNumber *number(bool val) {
    return val ? NSNumberYes : NSNumberNo;
}

::NSNumber *boolnum(int val) {
    return val ? NSNumberYes : NSNumberNo;
}

WSI_END_CXX