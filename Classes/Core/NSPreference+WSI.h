
# ifndef __WSI_NSPREFERENCE_0EA3800AD0FE423CB872786F43474E18_H_INCLUDED
# define __WSI_NSPREFERENCE_0EA3800AD0FE423CB872786F43474E18_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface NSPreference : WSIObject

+ (id)shared;
- (id)init;

- (id)objectForKey:(NSString*)key;
- (void)setObject:(id)obj forKey:(NSString*)key;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(core)

class Preference
{
public:
    
    Preference()
    {
        _prefs = [[NSPreference shared] retain];
    }
    
    ~Preference()
    {
        safe_release(_prefs);
    }
    
    static Preference& defaults()
    {
        static Preference __gs_prefs;
        return __gs_prefs;
    }
    
    ns::String find(ns::String const& key) const;
    
    void set(ns::String const& key, ns::String const& val)
    {
        [_prefs setObject:val forKey:key];
    }
    
protected:
    NSPreference* _prefs;
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif