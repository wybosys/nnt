
# import "Core.h"
# import "AudioPlayer.h"
# import <AVFoundation/AVAudioPlayer.h>
# import <AVFoundation/AVAudioSession.h>

NNT_BEGIN_OBJC

signal_t kSignalPlayCompleted = @"::wsi::play::completed";

static bool __gs_session_playback = false;

static void packPlayback()
{
    if (__gs_session_playback)
        return;
    __gs_session_playback = true;
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback error:nil];
}

static void unpackPlayback()
{
    if (!__gs_session_playback)
        return;
    __gs_session_playback = false;
    [[AVAudioSession sharedInstance] setCategory:nil error:nil];
}

NNTDECL_PRIVATE_BEGIN(AudioPlayer, NNTObject)
<AVAudioPlayerDelegate>
{
    AVAudioPlayer* _player;
}

@property (nonatomic, retain) AVAudioPlayer* player;

NNTDECL_PRIVATE_IMPL(AudioPlayer)

@synthesize player;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(_player);
    [super dealloc];
}

- (void)setPlayer:(AVAudioPlayer *)pyr {
    [NNTObject refobjSet:&_player ref:pyr];
    
    if (_player == nil)
        return;
    
    // set.
    _player.delegate = self;
    
    if (d_owner.loopCount == -1) {
        _player.numberOfLoops = -1;
    } else if (d_owner.loopCount == 0) {
        _player.numberOfLoops = 0;
    } else {
        _player.numberOfLoops = d_owner.loopCount - 1;
    }
    
    if (d_owner.background) {
        packPlayback();
    } else {
        unpackPlayback();
    }
}

# pragma mark delegate

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    if (d_owner.background) {
        unpackPlayback();
    }
    
    if (flag) {
        [d_owner emit:kSignalPlayCompleted];
    }
}

NNTDECL_PRIVATE_END

@implementation AudioPlayer

@synthesize target = _target;
@synthesize loopCount = _loopCount;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(AudioPlayer);
    
    return self;
}

- (void)dealloc {
    safe_release(_target);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalPlayCompleted)
NNTEVENT_END

- (BOOL)play {
    NSError* err = nil;
    AVAudioPlayer* player = [[AVAudioPlayer alloc] initWithContentsOfURL:_target error:&err];
    if (err) {
        safe_release(player);
        return NO;
    }
    
    // set.
    d_ptr.player = player;
    safe_release(player);
    
    // play.
    return [player play];
}

- (void)stop {
    [d_ptr.player stop];
    d_ptr.player = nil;
}

- (void)enableBackground:(BOOL)enb {
    _background = enb;
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(player)

Audio::Audio()
{
    
}

void Audio::set_target(ns::URL const& url)
{
    this->_self.target = url;
}

ns::URL Audio::target() const
{
    return this->_self.target;
}

bool Audio::play()
{
    return [this->_self play];
}

void Audio::stop()
{
    [this->_self stop];
}

void Audio::set_loop(uint num)
{
    this->_self.loopCount = num;
}

void Audio::set_autoreplay(bool b)
{
    if (b)
        set_loop(-1);
    else
        set_loop(0);
}

void Audio::set_background(bool b)
{
    this->_self.background = b;
}

NNT_END_NS
NNT_END_CXX
