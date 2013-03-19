
# ifndef __WSI_UIKIT_UISLIDER_35A5B2878B22402D90CACDBE2359FA9D_H_INCLUDED
# define __WSI_UIKIT_UISLIDER_35A5B2878B22402D90CACDBE2359FA9D_H_INCLUDED

# import "UILabel+WSI.h"
# import "UIButton+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface WSIUISlider : UISlider {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

- (void)changeValue:(float)value;

@end

WSI_EXTERN signal_t kSignalValueChanged;

@interface UISliderTitleValue : WSIUIView {
        
    //! title.
    WSIUILabel* title;
    
    //! slider.
    WSIUISlider* slider;
    
    //! value.
    WSIUILabel* value;
    
    float maximumValue, minimumValue, currentValue;
}

@property (nonatomic, retain) WSIUILabel* title;
@property (nonatomic, retain) WSIUISlider* slider;
@property (nonatomic, retain) WSIUILabel* value;

@property (nonatomic, assign) float maximumValue, minimumValue, currentValue;

+ (id)sliderWith:(NSString*)title max:(float)max min:(float)min cur:(float)cur;
- (id)initWith:(NSString*)title max:(float)max min:(float)min cur:(float)cur;

@end

@interface UISliderTitleValueReset : UISliderTitleValue {
    //! reset button.
    WSIUIButton* reset;
    
    //! default value.
    float defaultValue;
}

@property (nonatomic, retain) WSIUIButton* reset;
@property (nonatomic, assign) float defaultValue;

+ (id)sliderWith:(NSString*)title max:(float)max min:(float)min cur:(float)cur;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

template <typename sliderT = WSIUISlider>
class SliderControl
: public Control< SliderControl<sliderT>, sliderT>
{
public:
    
    SliderControl()
    {
        PASS;
    }
    
    void set_value(float val)
    {
        this->_self.value = val;
    }
    
    float value() const
    {
        return this->_self.value;
    }
    
    void set_minimum(float val)
    {
        this->_self.minimumValue = val;
    }
    
    float minimum() const
    {
        return this->_self.minimumValue;
    }
    
    void set_maximum(float val)
    {
        this->_self.maximumValue = val;
    }
    
    float maximum() const
    {
        return this->_self.maximumValue;
    }
    
};

typedef SliderControl<WSIUISlider> Slider;

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif