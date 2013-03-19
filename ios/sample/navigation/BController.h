
# ifndef __B_CTLR_8014F2E0B8B64849917A1A76777A9AB4_H_INCLUDED
# define __B_CTLR_8014F2E0B8B64849917A1A76777A9AB4_H_INCLUDED

NNTAPP_BEGIN

class BView
: public wsi::ui::View<BView>
{
public:
    BView();
    void layout_subviews();
};

class BController
: public wsi::ui::Controller<BController, BView>
{
public:
    BController();
    ~BController();
    void view_loaded();
    
protected:
    void act_appear();
    void act_disappear();
};

NNTAPP_END

# endif