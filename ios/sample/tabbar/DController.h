
# ifndef __D_CTLR_FA6C5E14596F400EA5480CB3782A25BE_H_INCLUDED
# define __D_CTLR_FA6C5E14596F400EA5480CB3782A25BE_H_INCLUDED

WSIAPP_BEGIN

class DView
: public wsi::ui::View<DView>
{
public:
    DView();
    void layout_subviews();
};

class DController
: public wsi::ui::Controller<DController, DView>
{
public:
    DController();
    void view_loaded();
};

WSIAPP_END

# endif