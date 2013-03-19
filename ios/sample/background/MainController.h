
# ifndef __MAIN_CTLR_F4F62186423A4A6BBD02584849571EA6_H_INCLUDED
# define __MAIN_CTLR_F4F62186423A4A6BBD02584849571EA6_H_INCLUDED

# include "AudioPlayer.h"

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
  
    ui::BevelButton btn_aud;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    player::Audio aud;
    
    void act_audio();
    void act_audio_end();
    
};

NNTAPP_END

# endif
