
# import "Core.h"
# import "NSFont+WCG.h"

WSI_BEGIN_OBJC

@implementation NSFont (WCG)

- (NSMutableDictionary*)getAttributes {
    NSMutableDictionary * fontAttributes = [[NSMutableDictionary alloc] init];
    [fontAttributes setObject:self forKey:NSFontAttributeName];
    return [fontAttributes autorelease];
}

@end

WSI_END_OBJC