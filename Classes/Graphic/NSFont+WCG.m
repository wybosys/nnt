
# import "Core.h"
# import "NSFont+WCG.h"

NNT_BEGIN_OBJC

@implementation NSFont (WCG)

- (NSMutableDictionary*)getAttributes {
    NSMutableDictionary * fontAttributes = [[NSMutableDictionary alloc] init];
    [fontAttributes setObject:self forKey:NSFontAttributeName];
    return [fontAttributes autorelease];
}

@end

NNT_END_OBJC