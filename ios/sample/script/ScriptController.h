
# ifndef __SAMPLE_SCRIPT_00DA391DB75448588540646FE11EF801_H_INCLUDED
# define __SAMPLE_SCRIPT_00DA391DB75448588540646FE11EF801_H_INCLUDED

NNTAPP_BEGIN

class ScriptView
: public ui::View<ScriptView>
{
public:
    
    ScriptView();
    void layout_subviews();
    
    ui::TextView input, output;
    ui::BevelButton run;
    ui::SegmentedControl segment;
    
};

NNTDECL_PRIVATE_HEAD_CXX(ScriptController);

class ScriptController
: public ui::Controller<ScriptController, ScriptView>
{
    NNTDECL_PRIVATE_CXX(ScriptController);
    
public:
    
    ScriptController();
    ~ScriptController();
    void view_loaded();
    
protected:
    
    void script_changed(EventObj&);
    void script_run(EventObj&);
    
};

NNTAPP_END

# endif
