
# ifndef __WAE_GUIDE_WAE_BE810C0CFF054ADA8A2A0741B5232915_H_INCLUDED
# define __WAE_GUIDE_WAE_BE810C0CFF054ADA8A2A0741B5232915_H_INCLUDED

WAE_BEGIN_NS(guide)

class ISummaryController
: public VirObject
{
public:
    
    typedef wtl::function<func_new> work_type;
    
    virtual void set_title(ns::String const&) = 0;
    virtual void set_summary(ns::String const&) = 0;
    virtual void set_work(work_type const&) = 0;
        
};

class SummaryView
: public ui::View<SummaryView>
{
public:
    
    SummaryView();
    
    void layout_subviews();
    
    ui::BevelButton btn_title;
    ui::TextView txt_summary;
    
};

class SummaryController
: public ui::Controller<SummaryController, SummaryView>,
public ISummaryController
{
public:
    
    SummaryController();
    
    void view_loaded();
    
    virtual void set_title(ns::String const&);
    virtual void set_summary(ns::String const&);
    virtual void set_work(work_type const&);
    
protected:
    
    void act_execute();
    
    work_type _work;
    
};

class IWorkController
: public VirObject
{
    
};

class WorkView
: public ui::View<WorkView>
{
public:
    
    WorkView();
    
    void layout_subviews();
    
};

class WorkController
: public ui::Controller<WorkController, WorkView>
{
public:
    
    WorkController();
    ~WorkController();
    
    void view_loaded();
    
};

WAE_END_NS

# endif
