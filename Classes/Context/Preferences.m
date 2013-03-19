
# import "Core.h"
# import "Preferences.h"

NNT_BEGIN

@interface PreferencesPrivate : NSObject {
	NSDictionary *settings;
}

@property (nonatomic, retain) NSDictionary *settings;

//! @function retrive settings from bundle file
- (void)retriveSettings;

//! @function get setting
- (NSString*)findSetting:(NSString*)__key;

@end

@implementation PreferencesPrivate

@synthesize settings;

- (void)retriveSettings {
	NSString *path_bundle = [[NSBundle mainBundle] bundlePath];
	NSString *path_settingsbundle = [path_bundle stringByAppendingPathComponent:NNT_SETTING_BUNDLE];
	NSString *path_file = [path_settingsbundle stringByAppendingPathComponent:NNT_SETTING_FILE];
	NSDictionary *settingsdict = [NSDictionary dictionaryWithContentsOfFile:path_file];
	NSArray *settingsarr = [settingsdict objectForKey:@"PreferenceSpecifiers"];
	NSDictionary *item;
	NSMutableDictionary *tmpdict = [NSMutableDictionary new];
	for (item in settingsarr) {
		id key = [item objectForKey:@"Key"];
		if (key) {
			[tmpdict setObject:item forKey:key];
		}
	}
	settings = [NSDictionary dictionaryWithDictionary:tmpdict];
	[tmpdict release];
}

- (NSString*)findSetting:(NSString*)__key {
	NSString* ret = [[NSUserDefaults standardUserDefaults] stringForKey:__key];
	if (ret) return ret; 
	NSString *path_bundle = [[NSBundle mainBundle] bundlePath];
	NSString *path_settingsbundle = [path_bundle stringByAppendingPathComponent:NNT_SETTING_BUNDLE];
	NSString *path_file = [path_settingsbundle stringByAppendingPathComponent:NNT_SETTING_FILE];
	NSDictionary *settingsdict = [NSDictionary dictionaryWithContentsOfFile:path_file];
	NSArray *prefs = [settingsdict objectForKey:@"PreferenceSpecifiers"];
	NSDictionary *item;
	for (item in prefs) {
		NSString *key = [item objectForKey:@"Key"];
		if (key && NSOrderedSame == [key compare:__key]) {
			return [item objectForKey:@"DefaultValue"];
		}
	}
	return nil;
}

@end

@implementation Preferences

@synthesize ctx;

- (id)init {
	self = [super init];
	d_ptr = [PreferencesPrivate new];
	return self;
}

- (void)dealloc {
	zero_release(d_ptr);
    
	[super dealloc]; 
}

- (NSString*)findSetting:(NSString*)__key{
    return [d_ptr findSetting:__key];
}

@end

NNT_END
