
# ifndef __SVC_CTLR_B5AEF4C58F6349D99D7B5E6A8CFDAC7C_H_INCLUDED
# define __SVC_CTLR_B5AEF4C58F6349D99D7B5E6A8CFDAC7C_H_INCLUDED

WSIAPP_BEGIN

class SvgView
: public ui::View<SvgView>
{
public:
    SvgView();
    void layout_subviews();
};

class SvgController
: public ui::Controller<SvgController, SvgView>
{
public:
    SvgController();
    void view_loaded();
    void test_svg();
};

WSIAPP_END

# endif