
# ifndef __NNT_AUTIOPLAYER_8C24C6E0E21543079AFD33641872FF65_H_INCLUDED
# define __NNT_AUTIOPLAYER_8C24C6E0E21543079AFD33641872FF65_H_INCLUDED

# include "../Drivers/AudioObject.h"
# include "AudioStream.h"

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

# ifdef NNT_CXX

# include "../Core/Task+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(audio)

typedef enum
{
    kPlayerStatePlaying,
    kPlayerStateStopped,
    kPlayerStateSuspended,
    kPlayerStateWait,
} PlayerState;

NNT_EXTERN signal_t kSignalPlayerStopped;
NNT_EXTERN signal_t kSignalPlayerPlaying;
NNT_EXTERN signal_t kSignalPlayerSuspended;

class AbstractAudioPlayer
: public cxx::Object<>
{
public:
    
    AbstractAudioPlayer();
    ~AbstractAudioPlayer();
    
    virtual bool load(PCMAudioStream const&) = 0;
    
    virtual bool play() = 0;
    virtual bool stop() = 0;
    virtual bool resume() = 0;
    virtual bool suspend() = 0;
    virtual PlayerState state() const;
    
    virtual bool is_playing() const = 0;
    virtual bool is_suspended() const = 0;
    
};

# ifdef NNT_TARGET_IOS

class OpenALAudioPlayer
: public AbstractAudioPlayer
{
public:
    
    OpenALAudioPlayer();
    ~OpenALAudioPlayer();
    
    virtual bool load(PCMAudioStream const&);
    
    virtual bool play();
    virtual bool stop();
    virtual bool resume();
    virtual bool suspend();
    
    virtual bool is_playing() const;
    virtual bool is_suspended() const;
    
protected:
    
    void clean();
    
    static int OpenALAudioPlayerStateWatcher(core::Task*, void*);
    
    unsigned int _src;
    unsigned int _buf;
    core::Task _tskwh;
    PlayerState _state;
    
};

typedef OpenALAudioPlayer Player;

# endif

# ifdef NNT_TARGET_ANDROID

/*
 class CCOpenMaxAudioPlayer
 : public CCAbstractAudioPlayer
 {
 
 };
 */

class CCOpenSLAudioPlayer
: public CCAbstractAudioPlayer
{
public:
    
    CCOpenSLAudioPlayer();
    ~CCOpenSLAudioPlayer();
    
    virtual bool load(CCPCMAudioStream const&);
    
    virtual bool play();
    virtual bool stop();
    virtual bool resume();
    virtual bool suspend();
    
    virtual bool is_playing() const;
    virtual bool is_suspended() const;
    
};

typedef CCOpenSLAudioPlayer CCAudioPlayer;

# endif

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
