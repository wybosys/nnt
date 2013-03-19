
# ifndef __WSI_UIKIT_UISETTINGSSTORE_58ED0D6E8A704B9AB479DD7050C7F456_H_INCLUDED
# define __WSI_UIKIT_UISETTINGSSTORE_58ED0D6E8A704B9AB479DD7050C7F456_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@protocol UISettingsStore <NSObject>

@required

- (void)setBool:(BOOL)value      forKey:(NSString*)key;
- (void)setFloat:(float)value    forKey:(NSString*)key;
- (void)setDouble:(double)value  forKey:(NSString*)key;
- (void)setInteger:(int)value    forKey:(NSString*)key;
- (void)setObject:(id)value      forKey:(NSString*)key;
- (BOOL)boolForKey:(NSString*)key;
- (float)floatForKey:(NSString*)key;
- (double)doubleForKey:(NSString*)key;
- (int)integerForKey:(NSString*)key;
- (id)objectForKey:(NSString*)key;
- (BOOL)synchronize; // Write settings to a permanant storage. Returns YES on success, NO otherwise

@end

@interface UISettingsStore : NSObject <UISettingsStore> {
    
}

@end

WSI_END_HEADER_OBJC

# endif