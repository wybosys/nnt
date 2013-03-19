
# ifndef __NNT_UIKIT_THEME_43232220F0E242C782869ABF9BF8F1BA_H_INCLUDED
# define __NNT_UIKIT_THEME_43232220F0E242C782869ABF9BF8F1BA_H_INCLUDED

# import "../Core/Directory+NNT.h"

NNT_BEGIN_HEADER_OBJC

# ifdef NNT_TARGET_IOS

@interface NSObject (UITheme)

- (UIColor*)asColor;
- (UIImage*)asImage;

@end

NNTDECL_CATEGORY(NSObject, UITheme);

# endif

NNTDECL_PRIVATE_HEAD(UITheme);

@interface UITheme : NNTObject {    
    NNTDECL_PRIVATE_EX(UITheme, d_ptr_theme);
}

- (id)init;

//! get theme file's extension.
+ (NSString*)themeExtension;

//! load theme file.
- (BOOL)loadTheme:(NSString*)name;
- (BOOL)loadTheme:(NSString *)name type:(NNTDirectoryType)type;

//! instance a object by key from theme.
- (id)instanceObject:(char const*)key;
- (id)instanceObjectByString:(NSString*)key;
- (id)instanceObject:(void*)key klen:(uint)len;

//! get data.
- (NSData*)dataForKey:(char const*)key;
- (NSData*)dataForValue:(NSString*)key;
- (NSData*)dataForKey:(void*)key klen:(uint)len;

//! store object.
- (void)storeObject:(char const*)key data:(void*)data dlen:(uint)dlen;
- (void)storeObject:(void*)key klen:(uint)klen data:(void*)data dlen:(uint)dlen;
- (void)storeObjectString:(NSString*)key data:(void*)data dlen:(uint)dlen;

//! store class object.
- (void)storeObject:(char const*)key obj:(id)obj;
- (void)storeObjectString:(NSString*)key obj:(id)obj;

//! all keys.
- (NSArray*)allKeys;

//! remove key.
- (void)removeKey:(char const*)key;
- (void)removeValue:(NSString*)key;
- (void)removeKey:(void*)key klen:(uint)len;

//! name.
- (NSString*)themeName;

//! walk.
typedef bool (*UIThemeWalkFunc)(char const* key, uint klen, id obj);
- (void)walk:(UIThemeWalkFunc)func;

//! sync.
- (void)flush;

@end

//! get current theme.
NNT_EXTERN UITheme* currentTheme;

//! load theme.
NNT_EXTERN void LoadTheme(NSString* name);

//! select theme.
NNT_EXTERN void SelectTheme(UITheme*);

//# ifdef NNT_DEBUG
//extern void AppDebugThemeInit(UITheme*);
//# endif

# define NNTDEBUG_THEME //void AppDebugThemeInit(UITheme* theme)

# ifndef _R
#   define _R(resid) [currentTheme instanceObject:resid]
# endif

# ifdef NNT_DEBUG
#   define NNTDEBUG_THEME_IMPL //void AppDebugThemeInit(UITheme* theme) {}
# else
#   define NNTDEBUG_THEME_IMPL SPACE
# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class ThemeItem
{
public:
    
    ThemeItem(id r)
    : _obj(r)
    {
        PASS;
    }
    
    operator Color () const
    {
        return [_obj asColor];
    }
    
    operator Image () const
    {
        return [_obj asImage];
    }
        
protected:
    
    id _obj;
    
};

class Theme
: public ns::Object<UITheme>
{
    typedef ns::Object<UITheme> super;
    
public:
    
    Theme()
    {
        PASS;
    }
    
    Theme(objc_type* r)
    : super(r)
    {
        PASS;
    }
    
    static ns::String FileExtension()
    {
        return [UITheme themeExtension];
    }

    bool load(ns::String const& theme)
    {
        return [this->_self loadTheme:theme];
    }
    
    bool load(ns::String const& theme, NNTDirectoryType type)
    {
        return [this->_self loadTheme:theme type:type];
    }
    
    ThemeItem instance(ns::String const& key) const
    {
        return [this->_self instanceObjectByString:key];
    }
    
    ThemeItem instance(core::string const& key) const
    {
        return [this->_self instanceObject:key.c_str()];
    }
    
    ThemeItem instance(core::data const& da) const
    {
        return [this->_self instanceObject:(void*)da.bytes() klen:da.length()];
    }
    
    ns::Data find(core::string const& key) const
    {
        return [this->_self dataForKey:key.c_str()];
    }
    
    ns::Data find(ns::String const& key) const
    {
        return [this->_self dataForValue:key];
    }
    
    ns::Data find(core::data const& key) const
    {
        return [this->_self dataForKey:(void*)key.bytes() klen:key.length()];
    }

    void set(core::string const& key, core::data const& da)
    {
        [this->_self storeObject:key.c_str() data:(void*)da.bytes() dlen:da.length()];
    }
    
    void set(core::data const& key, core::data const& da)
    {
        [this->_self storeObject:(void*)key.bytes() klen:key.length() data:(void*)da.bytes() dlen:da.length()];
    }
    
    void set(ns::String const& key, core::data const& da)
    {
        [this->_self storeObjectString:key data:(void*)da.bytes() dlen:da.length()];
    }

    void set(core::string const& key, id obj)
    {
        [this->_self storeObject:key.c_str() obj:obj];
    }
    
    void set(ns::String const& key, id obj)
    {
        [this->_self storeObjectString:key obj:obj];
    }
    
    void remove(core::string const& key)
    {
        [this->_self removeKey:key.c_str()];
    }
    
    void remove(ns::String const& key)
    {
        [this->_self removeValue:key];
    }
    
    void remove(core::data const& key)
    {
        [this->_self removeKey:(void*)key.bytes() klen:key.length()];
    }
    
    ns::String name() const
    {
        return [this->_self themeName];
    }

    void flush()
    {
        [this->_self flush];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
