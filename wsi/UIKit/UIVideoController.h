
# ifndef __WSI_UIKIT_VIDEOCONTROLLER_FF00658BB2AC473797DC1E3CC7C1AD0D_H_INCLUDED
# define __WSI_UIKIT_VIDEOCONTROLLER_FF00658BB2AC473797DC1E3CC7C1AD0D_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(MPMoviePlayerController);

@interface UIVideoController : WSIUIViewController {
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

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

_CXXCONTROLLER_DECL(UIVideoController);

# include "UIViewController+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif