
# import "Core.h"
# import "PreciseNumber.h"
# import <gmp/gmp.h>
# import <gmp/gmpxx.h>

NNT_BEGIN_OBJC

@implementation NSString (Precise)

+ (NSString *)stringFromMPF:(mpf_t)num {
    return @"";
}

+ (NSString *)stringFromMPZ:(mpz_t)num {
    char* str = mpz_get_str(NULL, 10, num);
    NSString* ret = [NSString stringWithUTF8String:str];
    free(str);
    return ret;
}

+ (NSString *)stringFromMPQ:(mpq_t)num {
    return @"";
}

@end

NNTIMPL_CATEGORY(NSString, Precise);

NNT_END_OBJC