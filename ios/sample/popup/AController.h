
# ifndef __A_CTLR_98D28B107CFC4642BB6A527202A2D7C3_H_INCLUDED
# define __A_CTLR_98D28B107CFC4642BB6A527202A2D7C3_H_INCLUDED

NNTAPP_BEGIN

using namespace ::wsi;

class AView
: public ui::View<AView>
{
public:
    AView();
    void layout_subviews();
    ui::BevelButton btn_dismiss;
};

class AController
: public ui::Controller<AController, AView>
{
public:
    AController();
    ~AController();
    void view_loaded();
    
protected:
    void act_dismiss();
    void act_appear();
};

NNTAPP_END

# endif