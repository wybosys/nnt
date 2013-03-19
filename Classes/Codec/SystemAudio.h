
# ifndef __WSI_SYSTEMAUDIO_264166B6102C4847A127FB6DFFCB30CA_H_INCLUDED
# define __WSI_SYSTEMAUDIO_264166B6102C4847A127FB6DFFCB30CA_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface SystemAudioManager : WSIObject {

    NSMutableDictionary* _dict;
    
}

+ (id)defaultManager;

- (BOOL)registerURL:(NSURL*)url withId:(NSString*)idr;
- (BOOL)play:(NSString*)idr;

@end

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class SystemAudio
{
public:
    
    static bool Register(ns::String const& idr, ns::URL const& url)
    {
        return [[SystemAudioManager defaultManager] registerURL:url withId:idr];
    }
    
    static bool Play(ns::String const& idr)
    {
        return [[SystemAudioManager defaultManager] play:idr];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

WSI_END_HEADER_OBJC

# endif
