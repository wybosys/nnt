
# ifndef __MAIN_CTLR_0597DF0FEC0441448BF54A85736DD1EC_H_INCLUDED
# define __MAIN_CTLR_0597DF0FEC0441448BF54A85736DD1EC_H_INCLUDED

NNTAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();

    ui::BevelButton btn_base64_encode, btn_base64_decode;
    ui::BevelButton btn_sha1, btn_sha2;
    ui::BevelButton btn_ec_en, btn_ec_de;
    
    void act_base64_encode();
    void act_base64_decode();
    void act_sha1();
    void act_sha2();
    void act_ec_en();
    void act_ec_de();
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    void view_loaded();
    
};

NNTAPP_END

# endif
