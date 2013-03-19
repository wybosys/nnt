
# ifndef __WAE_ADMIN_INDEX_D333131D4C1B4D68A7A44500D2B70E1A_H_INCLUDED
# define __WAE_ADMIN_INDEX_D333131D4C1B4D68A7A44500D2B70E1A_H_INCLUDED

WAE_BEGIN

class IndexView
: public ui::View<IndexView>
{
public:
    
    IndexView();
    void layout_subviews();
  
    ui::BevelButton btn_logout;
    ui::AnnualRing anl_funs;
    ui::AnyController ctlr_guide;
    
    void setup_top();
    void reset_top();
    
protected:
    
    void act_ring_rotated(EventObj&);
    void act_ring_added(EventObj&);    
    
    void act_ranged_wae();
    void act_ranged_auth();
    void act_ranged_sapi();
    void act_ranged_utils();
    void act_ranged_sample();
    void act_ranged_toolkit();
    
};

class IndexController
: public ui::Controller<IndexController, IndexView>
{
public:
    
    IndexController();    
    void view_loaded();
    
protected:
    
    void act_logout();
    
};

WAE_END

# endif
