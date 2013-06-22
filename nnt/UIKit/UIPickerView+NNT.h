
# ifndef __NNT_UIKIT_UIPICKERVIEW_A6EBDC6A53B34C1AB40C2CE744A73B29_H_INCLUDED
# define __NNT_UIKIT_UIPICKERVIEW_A6EBDC6A53B34C1AB40C2CE744A73B29_H_INCLUDED

# import "UIControl+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNT_EXTERN NSUInteger kUIPickerViewHeight;

@interface NNTUIPickerView : UIPickerView {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

- (id)initWithFrame:(CGRect)frame;

@end

NNTDECL_EXTERN_CLASS(UIDrumPickerView);

@protocol UIDrumPickerViewDataSource<NSObject>

// returns the number of 'columns' to display.
- (NSInteger)numberOfComponentsInDrumPickerView:(UIDrumPickerView *)pickerView;

// returns the # of rows in each component..
- (NSInteger)drumPickerView:(UIDrumPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component;

@end


@protocol UIDrumPickerViewDelegate<NSObject>
@optional

// returns width of column and height of row for each component.
- (CGFloat)drumPickerView:(UIDrumPickerView *)pickerView widthForComponent:(NSInteger)component;
- (CGFloat)drumPickerView:(UIDrumPickerView *)pickerView rowHeightForComponent:(NSInteger)component;
- (NSString *)drumPickerView:(UIDrumPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component;
- (void)drumPickerView:(UIDrumPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component;

@end

@interface UIDrumPickerView : NNTUIControl

@end

@interface NNTUIDatePicker : UIDatePicker {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

- (id)initWithFrame:(CGRect)frame;

@end

_CXXCONTROL_DECL(NNTUIDatePicker);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class DatePicker
: public Control<DatePicker, _CXXCONTROL(NNTUIDatePicker)>
{
public:
    
    DatePicker()
    {
        PASS;
    }
    
    void set_mode(UIDatePickerMode mode)
    {
        this->_self.datePickerMode = mode;
    }
    
    UIDatePickerMode mode() const
    {
        return this->_self.datePickerMode;
    }
    
    void set_locale(ns::Locale const& lc)
    {
        this->_self.locale = lc;
    }
    
    void set_calendar(ns::Calendar const& cr)
    {
        this->_self.calendar = cr;
    }
    
    void set_timezone(ns::TimeZone const& tz)
    {
        this->_self.timeZone = tz;
    }
    
    void set_date(ns::Date const& da, bool ani = true)
    {
        if (ani)
            this->_self.date = da;
        else
            [this->_self setDate:da animated:NO];
    }
    
    void set_period(ns::DatePeriod const& period)
    {
        this->_self.minimumDate = period.begin();
        this->_self.maximumDate = period.end();
    }

    void set_countdown_duration(ns::TimeInterval const& ti)
    {
        this->_self.countDownDuration = ti;
    }
    
    void set_minute_interval(int interval)
    {
        this->_self.minuteInterval = interval;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
