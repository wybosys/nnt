
# ifndef __THD_CTLR_7B6474EF387449A1891F900E36F67CF7_H_INCLUDED
# define __THD_CTLR_7B6474EF387449A1891F900E36F67CF7_H_INCLUDED

WSIAPP_BEGIN

class ThdView
: public ui::View<ThdView>
{
public:
    
    ThdView();
    ~ThdView();
    
    void layout_subviews();
};

class ThdController
: public ui::Controller<ThdController, ThdView>
{
public:
    
    ThdController();
    ~ThdController();
    
    void view_loaded();
    
};

WSIAPP_END

# endif