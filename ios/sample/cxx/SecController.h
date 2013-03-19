
# ifndef __SEC_CTLR_D7627BEFA7B74F4CB6F4BEB38C5D5164_H_INCLUDED
# define __SEC_CTLR_D7627BEFA7B74F4CB6F4BEB38C5D5164_H_INCLUDED

WSIAPP_BEGIN

class SecView
: public ui::View<SecView>
{
public:
    void layout_subviews();
};

class SecController
: public ui::Controller<SecController, SecView>
{
public:
    SecController();
    ~SecController();
    
    void view_loaded();
};

WSIAPP_END

# endif