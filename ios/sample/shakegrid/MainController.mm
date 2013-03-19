
# include "Foundation+NNT.h"
# include "MainController.h"
# include "QzEffect.h"

NNTAPP_BEGIN

class ShakeItem
: public ui::GridItem<>
{
public:
    
    ShakeItem()
    {
        img.set_image(ui::Image(@"logo@57.png"));
        
        add_sub(img);
        
        connect(kSignalViewClicked, _action(ShakeItem::act_shake), this).oneshot();
        
        cg::Shadow sd;
        sd.apply(*this);
    }
    
    void layout_subviews()
    {
        CGRect rc = CGRectDeflateCenter(bounds(), 10, 10);
        img.set_frame(rc);
    }
    
    void act_shake()
    {
        connect(kSignalViewClicked, _action(ShakeItem::act_unshake), this).oneshot();

        eff.start();
        add_effect(eff);
    
        trace_msg(@"begin shaking.");
    }
    
    void act_unshake()
    {
        connect(kSignalViewClicked, _action(ShakeItem::act_shake), this).oneshot();
        
        eff.stop();
        
        trace_msg(@"end shaking.");
    }
    
    ui::ImageView img;
    qz::effect::Tremble eff;
    
};

ShakeGrid::ShakeGrid()
{
    set_background(ui::Color::White());
}

void MainController::view_loaded()
{
    view().set_rows(10);
    view().set_cols(4);
    view().set_preferred_cols(4);
    view().set_preferred_rows(5);
    
    for (uint i = 0; i < 30; ++i)
    {
        ui::Instance<ShakeItem> item;
        view().add(item);
    }
    
    view().relayout_items();
}

NNTAPP_END