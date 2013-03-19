
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    lbl_path.set_text(@"HERE");
    lbl_path.set_frame(cg::Rect(lbl_path.textsize()));
    
    add_sub(lbl_path);
}

void MainView::layout_subviews()
{
    
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().connect(kSignalTouchesBegin, _action(_class::touches_begin), this);
    view().connect(kSignalTouchesMoved, _action(_class::touches_moved), this);
    view().connect(kSignalTouchesEnd, _action(_class::touches_end), this);
    view().connect(kSignalPainting, _action(_class::painting), this);
}

void MainController::touches_begin(EventObj& evt)
{
    path.reset();
    
    cg::Point pt = ui::Touch(ns::Set(evt.result()).any()).location(view());
    path.move_to(pt);
}

void MainController::touches_moved(EventObj& evt)
{
    cg::Point pt = ui::Touch(ns::Set(evt.result()).any()).location(view());
    path.line_to(pt);
    view().redraw();
}

void MainController::touches_end(EventObj& evt)
{
    {
        qz::KeyAnimation<> ani(@"position");
        ani.set_path(path);
        ani.set_duration(5);
        view().lbl_path.add_animation(ani);
    }
    
    {
        qz::KeyAnimation<> ani(@"transform");
        ani.set_values(ns::MutableArray() << ns::Value(cg::Transform::Identity()) << ns::Value(cg::Transform::Scale(5, 5, 5) * cg::Transform::Rotate(cg::Angle(180), 0, 0, 1)));
        ani.set_duration(5);
        view().lbl_path.add_animation(ani);
    }
}

void MainController::painting()
{
    ::juice::cocoa::Graphics gra = ::juice::cocoa::Graphics::Current();
    ::juice::cocoa::Path dp = ::juice::cocoa::Path::Copy(path);
    dp.stroke(gra, ::juice::cocoa::Pen(5));
}

NNTAPP_END
