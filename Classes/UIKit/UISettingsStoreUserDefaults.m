
# import "Core.h"
# import "UISettingsStoreUserDefaults.h"

WSI_BEGIN_OBJC

@implementation UISettingsStoreUserDefaults

- (void)setBool:(BOOL)value forKey:(NSString*)key {
    [[NSUserDefaults standardUserDefaults] setBool:value forKey:key];
}

- (void)setFloat:(float)value forKey:(NSString*)key {
    [[NSUserDefaults standardUserDefaults] setFloat:value forKey:key];
}

- (void)setDouble:(double)value forKey:(NSString*)key {
    [[NSUserDefaults standardUserDefaults] setDouble:value forKey:key];
}

- (void)setInteger:(int)value forKey:(NSString*)key {
    [[NSUserDefaults standardUserDefaults] setInteger:value forKey:key];
}

- (void)setObject:(id)value forKey:(NSString*)key {
    [[NSUserDefaults standardUserDefaults] setObject:value forKey:key];
}

- (BOOL)boolForKey:(NSString*)key {
    return [[NSUserDefaults standardUserDefaults] boolForKey:key];
}

- (float)floatForKey:(NSString*)key {
    return [[NSUserDefaults standardUserDefaults] floatForKey:key];
}

- (double)doubleForKey:(NSString*)key {
    return [[NSUserDefaults standardUserDefaults] doubleForKey:key];
}

- (int)integerForKey:(NSString*)key {
    return [[NSUserDefaults standardUserDefaults] integerForKey:key];
}

- (id)objectForKey:(NSString*)key {
    return [[NSUserDefaults standardUserDefaults] objectForKey:key];
}

- (BOOL)synchronize {
    return [[NSUserDefaults standardUserDefaults] synchronize];
}

@end

WSI_END_OBJC