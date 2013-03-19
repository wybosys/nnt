
# include "Foundation+NNT.h"
# include "MainController.h"
# include "JuiceCocoa++.hpp"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
}

void MainView::layout_subviews()
{
    
}

void MainView::draw(CGContextRef ctx, const CGRect & rc)
{
    ::juice::cocoa::Graphics gra(ctx, rc);
    
    {
        ::juice::cocoa::Path ph;
        ph.add_rect(cg::Rect(100, 100, 100, 100));
        ::juice::cocoa::Brush br(cg::Color::Orange());
        ph.fill(gra, br);
    }
    
    {
        ::juice::cocoa::Path ph;
        ph.add_ellipse(cg::Rect(300, 300, 100, 100));
        //ph.move_to(cg::Point(300, 300));
        //ph.line_to(cg::Point(400, 400));
        ::juice::cocoa::Shadow sd;
        sd.set_offset(cg::Point(0, -20));
        sd.set_radius(50);
        sd.set_color(cg::Color::RGBA(0xFF00001F));
        ph.stroke(gra, sd);
        
        ::juice::cocoa::Pen pen(cg::Color::Blue());
        ph.stroke(gra, pen);
    }
    
    {
        ::juice::cocoa::Bezier bz;
        bz.set_rounded(cg::Rect(0, 0, 100, 100), cg::Rect(30, 30, 30, 30));
        ::juice::cocoa::Shadow sd;
        sd.set(gra);
        gra.layer().begin();
        ::juice::cocoa::Brush br(cg::Color::Red());
        bz.fill(gra, br);
        ::juice::cocoa::Pen pn(cg::Color::White(), 5);
        bz.stroke(gra, pn);
        gra.layer().end();
    }
    
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

NNTAPP_END
