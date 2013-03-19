
# ifndef __E_CTRL_F5C797E9BED6403CADA47076DA2FDB29_H_INCLUDED
# define __E_CTRL_F5C797E9BED6403CADA47076DA2FDB29_H_INCLUDED

NNTAPP_BEGIN

class EView
: public wsi::ui::View<EView>
{
public:
    EView();
    void layout_subviews();
};

class EController
: public wsi::ui::Controller<EController, EView>
{
public:
    void view_loaded();
    
protected:
    void act_appear();
    void act_disappear();
};

NNTAPP_END

# endif