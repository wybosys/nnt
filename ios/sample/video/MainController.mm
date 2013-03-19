
# import "Foundation+NNT.h"
# import "MainController.h"

NNTAPP_BEGIN

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    ns::URL url;
    //url = @"http://v.youku.com/player/getRealM3U8/vid/XMzY4MTk0NzAw/type/flv/ts/1337239787/video.m3u8";
    url = ns::URL::Bundle(@"Movie.m4v");
    
    open(url);
    play();
}

NNTAPP_END
