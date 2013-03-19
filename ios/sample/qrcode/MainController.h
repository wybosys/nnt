
# ifndef __CTLR_MAIN_02B25412B02847878958C022DBCA9FEC_H_INCLUDED
# define __CTLR_MAIN_02B25412B02847878958C022DBCA9FEC_H_INCLUDED

# include "CodecDetectController.h"

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    vision::CodecDetect ctlr_reader;
    ui::ImageView img_origin, img_gray;
    ui::TextView txt_result;
    
    void act_try(EventObj& evt);
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
    void act_success(EventObj& evt);
    
};

WSIAPP_END

# endif
