
# import "Core.h"
# import "AlphabetFlow.h"

# ifdef WSI_OBJC

WSI_BEGIN_OBJC

@implementation AlphabetFlow

@synthesize curValue;

- (id)init {
    self = [super init];
    self.curValue = [AlphabetFlow defaultValue];
    return self;
}

- (void)dealloc {
    [curValue release];
    [super dealloc];
}

+ (NSString*)defaultValue {
    return @"A";
}

+ (NSString*)nextValue:(NSString *)value {
    char *ret = alphabetflow_next([value UTF8String], (uint)[value length]);
    NSString *str = [NSString stringWithUTF8String:ret];
    free(ret);
    return str;
}

+ (NSString*)prevValue:(NSString *)value {
    char *ret = alphabetflow_prev([value UTF8String], (uint)[value length]);
    NSString *str = [NSString stringWithUTF8String:ret];
    free(ret);
    return str;   
}

- (NSString*)next {
    char *ret = alphabetflow_next([curValue UTF8String], (uint)[curValue length]);
    self.curValue = [NSString stringWithUTF8String:ret];
    free(ret);
    return curValue;
}

- (NSString*)prev {
    char *ret = alphabetflow_prev([curValue UTF8String], (uint)[curValue length]);
    self.curValue = [NSString stringWithUTF8String:ret];
    free(ret);
    return curValue;
}

@end

WSI_END_OBJC

# endif