
# import "Core.h"
# import "NSFont+NNT.h"

NNT_BEGIN_OBJC

@implementation NSFont (Ng)

- (NSMutableDictionary*)getAttributes {
    NSMutableDictionary * fontAttributes = [[NSMutableDictionary alloc] init];
    [fontAttributes setObject:self forKey:NSFontAttributeName];
    return [fontAttributes autorelease];
}

@end

NNT_END_OBJC