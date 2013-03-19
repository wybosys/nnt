
# import "Core.h"
# import "UIVideoController.h"
# import <MediaPlayer/MediaPlayer.h>

NNT_BEGIN_OBJC

@implementation UIVideoController

@dynamic contentURL;

- (id)init {
    self = [super init];
    
    _mpmovie = [[MPMoviePlayerController alloc] initWithContentURL:nil];
    
    return self;
}

- (id)initWithURL:(NSURL*)url {
    self = [super init];
    
    _mpmovie = [[MPMoviePlayerController alloc] initWithContentURL:url];
    
    return self;
}

- (void)dealloc {
    safe_release(_mpmovie);
    [super dealloc];
}

- (void)loadView {
    self.view = _mpmovie.view;
}

- (void)play {
    [_mpmovie play];
}

- (void)pause {
    [_mpmovie pause];
}

- (void)stop {
    [_mpmovie stop];
}

- (NSURL*)contentURL {
    return _mpmovie.contentURL;
}

- (void)setContentURL:(NSURL*)url {
    _mpmovie.contentURL = url;
}

@end

_CXXCONTROLLER_IMPL(UIVideoController);

NNT_END_OBJC