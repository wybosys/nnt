
# ifndef __WSI_AUTIOPLAYER_8C24C6E0E21543079AFD33641872FF65_H_INCLUDED
# define __WSI_AUTIOPLAYER_8C24C6E0E21543079AFD33641872FF65_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(AudioPlayer);

@interface AudioPlayer : WSIObject {
    
    NSURL* _target;
    NSUInteger _loopCount;
    BOOL _background;
    
    WSIDECL_PRIVATE(AudioPlayer);
}

@property (nonatomic, copy) NSURL* target;
@property (nonatomic, assign) NSUInteger loopCount;
@property (nonatomic, assign) BOOL background;

- (BOOL)play;
- (void)stop;

@end

WSI_EXTERN signal_t kSignalPlayCompleted;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(player)

class Audio
: public ns::Object<AudioPlayer>
{
public:
    
    Audio();
    
    void set_target(ns::URL const&);
    ns::URL target() const;
    
    bool play();
    void stop();

    void set_loop(uint);
    void set_autoreplay(bool=true);
    void set_background(bool=true);
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif // cxx

# endif // objc

# endif
