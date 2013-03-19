
# include "WSIFoundation.h"
# include "MainController.h"
# include "Linear.h"

WSIAPP_BEGIN

MainView::MainView()
{    
    set_background(ui::Color::White());
    
    add_sub(badge);
    badge.set_value(@"123");
    
    btn_0.set_text(@"0");
    btn_1.set_text(@"1");
    
    cg::MutableTextStyle ts, uts;
    ts.set_fontsize(40);
    uts.set_fontsize(20);
    ts.set_fontcolor(cg::Color::Red());
    uts.set_fontcolor(cg::Color::Green());
    
    btn_0.set_unchecked(cg::Image(@"a.png"));
    btn_0.set_checked(cg::Image(@"b.png"));
    btn_0.set_unchecked(uts);
    btn_0.set_checked(ts);
    btn_1.set_unchecked(cg::Image(@"c.png"));
    btn_1.set_checked(cg::Image(@"d.png"));
    btn_1.set_unchecked(uts);
    btn_1.set_checked(ts);
    
    add_sub(btn_0);
    add_sub(btn_1);
    
    grp.add(btn_0);
    grp.add(btn_1);
    
    btn_parent.set_text(@"PARENT");
    btn_parent.set_frame(cg::Rect(btn_parent.textsize()));
    
    btn_child0.set_text(@"0");
    btn_child1.set_text(@"1");
    btn_child2.set_text(@"2");
    btn_child0.set_frame(cg::Rect(0, 0, 50, 50));
    btn_child1.set_frame(cg::Rect(0, 0, 50, 50));
    btn_child2.set_frame(cg::Rect(0, 0, 50, 50));
    
    add_sub(btn_parent);
}

void MainView::layout_subviews()
{
    badge.move_to(cg::Point(0, 0));
    
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (pixel)100 << (flex)1 << (flex)1;
    lyt << lnr;
    
    layout::hbox lytb(lyt << lnr);
    layout::linear lnrb(lytb);
    lnrb << (flex)1 << (pixel)100 << (pixel)100 << (flex)1;
    lytb << lnrb;
    btn_0.set_frame(lytb << lnrb);
    btn_1.set_frame(lytb << lnrb);
    
    btn_parent.move_center(cg::Rect(lyt << lnr).center());
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().btn_parent.connect(kSignalButtonClicked, _action(_class::act_parent_clicked), this);
    view().btn_child0.connect(kSignalButtonClicked, _action(_class::act_child_clicked), this);
    view().btn_child1.connect(kSignalButtonClicked, _action(_class::act_child_clicked), this);
    view().btn_child2.connect(kSignalButtonClicked, _action(_class::act_child_clicked), this);
    
    view().grp.set_selected(view().btn_0);
}

void MainController::act_parent_clicked()
{
    view().add_sub(view().btn_child0);
    view().add_sub(view().btn_child1);
    view().add_sub(view().btn_child2);
    
    cg::Point pt = view().btn_parent.frame().center();

    math::linear::Circle<real, cg::Point> cir(100, pt);
    
    {
        qz::KeyAnimation<> ani(@"position");
        ani.set_duration(0.3f);
        
        ani.set_values(ns::MutableArray() << ns::Value(pt) << ns::Value(cir.at_angle(cg::Angle(45))));
        view().btn_child0.add_animation(ani);
        
        ani.set_values(ns::MutableArray() << ns::Value(pt) << ns::Value(cir.at_angle(cg::Angle(90))));
        view().btn_child1.add_animation(ani);
        
        ani.set_values(ns::MutableArray() << ns::Value(pt) << ns::Value(cir.at_angle(cg::Angle(135))));
        view().btn_child2.add_animation(ani);
    }
    
    {
        qz::KeyAnimation<> ani(@"transform");
        ani.set_values(ns::MutableArray() << ns::Value(cg::Transform::Scale(.1f, .1f, .1f) * cg::Transform::Rotate(180, 0, 0, 1)) << ns::Value(cg::Transform::Identity()));
        ani.set_duration(0.3f);
        view().btn_child0.add_animation(ani);
        view().btn_child1.add_animation(ani);
        view().btn_child2.add_animation(ani);
    }
    
    view().btn_child0.move_center(cir.at_angle(cg::Angle(45)));
    view().btn_child1.move_center(cir.at_angle(cg::Angle(90)));
    view().btn_child2.move_center(cir.at_angle(cg::Angle(135)));
}

void MainController::act_child_clicked()
{
    cg::Point pt = view().btn_parent.frame().center();
    
    math::linear::Circle<real, cg::Point> cir(100, pt);
        
    {
        qz::KeyAnimation<> ani(@"transform");
        ani.set_values(ns::MutableArray() << ns::Value(cg::Transform::Identity()) << ns::Value(cg::Transform::Scale(.1f, .1f, .1f) * cg::Transform::Rotate(180, 0, 0, 1)));
        ani.set_duration(0.3f);
        view().btn_child0.add_animation(ani);
        view().btn_child1.add_animation(ani);
        view().btn_child2.add_animation(ani);
    }

    
    perform(_perform_action(_class::hide_child), .3f);
}

void MainController::hide_child()
{
    view().btn_child0.remove_fromsuper();
    view().btn_child1.remove_fromsuper();
    view().btn_child2.remove_fromsuper();
}

WSIAPP_END
