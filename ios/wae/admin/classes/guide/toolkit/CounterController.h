
# ifndef __WAE_TOOLKIT_COUNTER_534063BE876E4D1DBA0CC3BB931B6410_H_INCLUDED
# define __WAE_TOOLKIT_COUNTER_534063BE876E4D1DBA0CC3BB931B6410_H_INCLUDED

# include "WaeController.h"

WAE_BEGIN_NS2(guide, toolkit)

class CounterCell
: public ui::TableCell<CounterCell>
{
public:
    
    CounterCell();
    void layout_subviews();
    void update();
    
    ui::Label lbl_name, lbl_idr, lbl_counter;
    
};

class CounterDeviceCell
: public ui::TableCell<CounterCell>
{
public:
    
    CounterDeviceCell();
    void layout_subviews();
    void update();
    
    ui::Label lbl_dev, lbl_idr, lbl_counter;
};

class CounterTable
: public ui::PlainTable<CounterTable, CounterCell>
{
    
};

class CounterDeviceTable
: public ui::PlainTable<CounterDeviceTable, CounterDeviceCell>
{
    
};

class CounterView
: public ui::View<CounterView>
{
public:
    
    CounterView();
    void layout_subviews();
    
    CounterTable tbl_app;
    CounterDeviceTable tbl_dev;
    
};

class CounterController
: public ui::Controller<CounterController, CounterView>,
public IWorkController
{
public:
    
    CounterController();
    void view_loaded();
    void refresh();
    
protected:
    
    void mdl_launch(AnyObject&);
    void mdl_devicelaunch(AnyObject&);
    
};

WAE_END_NS2

# endif
