
# ifndef __C_CTLR_D67224EABCBE467697FA3CC6AF1351BF_H_INCLUDED
# define __C_CTLR_D67224EABCBE467697FA3CC6AF1351BF_H_INCLUDED

WSIAPP_BEGIN

class CView
: public wsi::ui::View<CView>
{
public:
    CView();
    void layout_subviews();
};

class CController
: public wsi::ui::Controller<CController, CView>
{
public:
    CController();
    void view_loaded();
};

WSIAPP_END

# endif