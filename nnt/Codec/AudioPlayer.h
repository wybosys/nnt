
# ifndef __NNT_AUTIOPLAYER_8C24C6E0E21543079AFD33641872FF65_H_INCLUDED
# define __NNT_AUTIOPLAYER_8C24C6E0E21543079AFD33641872FF65_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(AudioPlayer);

@interface AudioPlayer : NNTObject {
    
    NSURL* _target;
    NSUInteger _loopCount;
    BOOL _background;
    
    NNTDECL_PRIVATE(AudioPlayer);
}

@property (nonatomic, copy) NSURL* target;
@property (nonatomic, assign) NSUInteger loopCount;
@property (nonatomic, assign) BOOL background;

- (BOOL)play;
- (void)stop;

@end

NNT_EXTERN signal_t kSignalPlayCompleted;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(player)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif // cxx

# endif // objc

# endif
