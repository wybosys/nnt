
# include "Foundation+NNT.h"
# include "ScriptController.h"
# include "Python+NNT.h"
# include "Lua+NNT.h"

NNTAPP_BEGIN

ScriptView::ScriptView()
{
    input.layer().border().set_width(1);
    output.layer().border().set_width(1);
    output.set_readonly();
    run.set_text(@"RUN");
    segment.set_items(ns::MutableArray() << @"Python" << @"Lua");
    
    add_sub(input);
    add_sub(output);
    add_sub(run);
    add_sub(segment);
}

void ScriptView::layout_subviews()
{
    layout::vbox lyt(bounds());
    lyt.set_margin(5, 5);
    layout::linear lnr(lyt);
    lnr << (pixel)50 << (flex)1 << (flex)1;
    
    segment.set_frame(lyt << lnr);
    output.set_frame(lyt << lnr);
    input.set_frame(lyt << lnr);
    
    run.set_frame(CGRectMakePtSz(CGPointAddX(output.frame().rt(), -50), CGSizeMake(50, 50)));
}

NNTDECL_PRIVATE_BEGIN_CXX(ScriptController)

void init()
{
    python = NULL;
    lua = NULL;
}

void dealloc()
{
    clear();
}

void clear()
{
    safe_release(python);
    safe_release(lua);
}

id<NNTScript> script()
{
    if (python) {
        return python;
    } else if (lua) {
        return lua;
    }
    return nil;
}

NNTPython* python;
NNTLua* lua;

NNTDECL_PRIVATE_END_CXX

ScriptController::ScriptController()
{
    NNTDECL_PRIVATE_CONSTRUCT(ScriptController);
    
    set_orientation(UIOrientationEnableAll);
}

ScriptController::~ScriptController()
{
    NNTDECL_PRIVATE_DESTROY();
}

void ScriptController::view_loaded()
{
    view().segment.connect(kSignalSelectChanged, _action(_class::script_changed), this);
    view().run.connect(kSignalButtonClicked, _action(_class::script_run), this);
    
    view().segment.set_select(0);
}

void ScriptController::script_changed(EventObj& evt)
{
    view().input.set_text(@"");
    view().output.set_text(@"");
    d_ptr->clear();
    
    switch (view().segment.selected())
    {
        case 0:
        {
            NNTPython* python = [[NNTPython alloc] init];
            d_ptr->python = python;
            safe_release(python);
        } break;
        case 1:
        {
            NNTLua* lua = [[NNTLua alloc] init];
            d_ptr->lua = lua;
            safe_release(lua);
        } break;
    }
}

void ScriptController::script_run(EventObj& evt)
{
    ns::String str = view().input.text();
    if (![d_ptr->script() executeString:str])
    {
        view().output.set_text([d_ptr->script() errorMessage]);
    }
    else
    {
        view().output.set_text(@"");
    }
}

NNTAPP_END
