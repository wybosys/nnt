
# ifndef __IMAGE_CTLR_30B3B110B38A4CA1BB4B41814190BF5F_H_INCLUDED
# define __IMAGE_CTLR_30B3B110B38A4CA1BB4B41814190BF5F_H_INCLUDED

WSIAPP_BEGIN

class ImageView
: public ui::View<ImageView>
{
public:
    ImageView();
    void layout_subviews();
    ui::ImageView view_img;
    ui::BevelButton btn_load;
    ui::TextField txt_url;
};

class ImageController
: public ui::Controller<ImageController, ImageView>
{
public:
    ImageController();
    void view_loaded();
    void act_load();
};

WSIAPP_END

# endif
