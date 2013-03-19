
# ifndef __MAIN_CTLR_BF702C6A283D4FAEA0C0FC8A14031294_H_INCLUDED
# define __MAIN_CTLR_BF702C6A283D4FAEA0C0FC8A14031294_H_INCLUDED

NNTAPP_BEGIN

class CustomPickerItem
: public ui::PickerItem
{
public:
    
    CustomPickerItem();
    void layout_subviews();
    void update();
    void selected();
    
    ui::Label lbl;
    
};

class CustomPicker
: public ui::PickerControl<CustomPickerItem>
{
public:
    
};

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    CustomPicker picker;
    ui::DrumPicker drum;
    ui::DatePicker date;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    void act_picker_selectchanged(EventObj&);
    
};

NNTAPP_END

# endif