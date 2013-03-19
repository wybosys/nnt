
# import "Core.h"
# import "UISettingsStore.h"

NNT_BEGIN_OBJC

@implementation UISettingsStore

- (void)setObject:(id)value forKey:(NSString*)key {
    [NSException raise:@"Unimplemented"
                format:@"setObject:forKey: must be implemented in subclasses of IASKAbstractSettingsStore"];
}

- (id)objectForKey:(NSString*)key {
    [NSException raise:@"Unimplemented"
                format:@"objectForKey: must be implemented in subclasses of IASKAbstractSettingsStore"];
    return nil;
}

- (void)setBool:(BOOL)value forKey:(NSString*)key {
    [self setObject:[NSNumber numberWithBool:value] forKey:key];
}

- (void)setFloat:(float)value forKey:(NSString*)key {
    [self setObject:[NSNumber numberWithFloat:value] forKey:key];
}

- (void)setInteger:(int)value forKey:(NSString*)key {
    [self setObject:[NSNumber numberWithInt:value] forKey:key];
}

- (void)setDouble:(double)value forKey:(NSString*)key {
    [self setObject:[NSNumber numberWithDouble:value] forKey:key];
}

- (BOOL)boolForKey:(NSString*)key {
    return [[self objectForKey:key] boolValue];
}

- (float)floatForKey:(NSString*)key {
    return [[self objectForKey:key] floatValue];
}
- (int)integerForKey:(NSString*)key {
    return [[self objectForKey:key] intValue];
}

- (double)doubleForKey:(NSString*)key {
    return [[self objectForKey:key] doubleValue];
}

- (BOOL)synchronize {
    return NO;
}

@end

NNT_END_OBJC