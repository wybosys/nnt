
# import "Core.h"
# import "NSPreference+NNT.h"

NNT_BEGIN_OBJC

using namespace nnt;

@interface NSPreference ()

- (id)_find_in_plist:(NSString*)key;

@end

@implementation NSPreference

+ (id)shared {
    id ret = nil;
    NNT_SYNCHRONIZED(self)
    static NSPreference* __gs_preference = [[self alloc] init];
    ret = __gs_preference;
    NNT_SYNCHRONIZED_END
    return ret;
}

- (id)init {
    self = [super init];
    return self;
}

- (id)objectForKey:(NSString*)key {
    id ret = [[NSUserDefaults standardUserDefaults] objectForKey:key];
    if (ret == NULL) {
        ret = [self _find_in_plist:key];
    }
    return ret;
}

- (void)setObject:(id)obj forKey:(NSString*)key {
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    [defaults setObject:obj forKey:key];
    [defaults synchronize];
}

- (id)_find_in_plist:(NSString*)key {
    id ret = nil;
    ns::String path_settings = [[NSBundle mainBundle] pathForResource:@"Settings" ofType:@"bundle"];
    if(path_settings.is_null())
        return ret;
    ns::String path_root = path_settings + @"/Root.plist";
    ns::Dictionary dict = [NSDictionary dictionaryWithContentsOfFile:path_root];
    if (dict.is_null())
        return ret;
    ns::Array arr = dict[@"PreferenceSpecifiers"];
    if (arr.is_null())
        return ret;
    
    for (id each in *arr)
    {
        ns::Dictionary item(each);
        ns::String identity = item[@"Key"];
        if (identity == ns::String(key))
        {
            ret = item[@"DefaultValue"];
            break;
        }
    }
    
    return ret;
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(core)

ns::String Preference::find(ns::String const& key) const
{
    id ret = [_prefs objectForKey:key];
    if ([ret isKindOfClass:[NSString class]])
        return (NSString*)ret;
    if ([ret isKindOfClass:[NSNumber class]])
        return [(NSNumber*)ret stringValue];
    return ns::String::Null();
}

NNT_END_NS
NNT_END_CXX
