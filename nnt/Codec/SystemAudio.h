
# ifndef __NNT_SYSTEMAUDIO_264166B6102C4847A127FB6DFFCB30CA_H_INCLUDED
# define __NNT_SYSTEMAUDIO_264166B6102C4847A127FB6DFFCB30CA_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface SystemAudioManager : NNTObject {

    NSMutableDictionary* _dict;
    
}

+ (id)defaultManager;

- (BOOL)registerURL:(NSURL*)url withId:(NSString*)idr;
- (BOOL)play:(NSString*)idr;

@end

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

NNT_END_HEADER_OBJC

# endif
