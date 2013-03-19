
# ifndef __NNT_UIKIT_VIDEOCONTROLLER_FF00658BB2AC473797DC1E3CC7C1AD0D_H_INCLUDED
# define __NNT_UIKIT_VIDEOCONTROLLER_FF00658BB2AC473797DC1E3CC7C1AD0D_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(MPMoviePlayerController);

@interface UIVideoController : NNTUIViewController {
    @protected
    MPMoviePlayerController* _mpmovie;
}

@property (nonatomic, copy) NSURL* contentURL;

- (id)init;
- (id)initWithURL:(NSURL*)url;

- (void)play;
- (void)pause;
- (void)stop;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

_CXXCONTROLLER_DECL(UIVideoController);

# include "UIViewController+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class VideoController
: public SimpleController<VideoController,
_CXXCONTROLLER(UIVideoController),
UIView
>
{
public:
    
    void open(ns::URL const& url)
    {
        this->_self.contentURL = url;
    }
    
    void play()
    {
        [this->_self play];
    }
    
    void stop()
    {
        [this->_self stop];
    }
    
    void pause()
    {
        [this->_self pause];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif