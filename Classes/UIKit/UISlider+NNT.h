
# ifndef __NNT_UIKIT_UISLIDER_35A5B2878B22402D90CACDBE2359FA9D_H_INCLUDED
# define __NNT_UIKIT_UISLIDER_35A5B2878B22402D90CACDBE2359FA9D_H_INCLUDED

# import "UILabel+NNT.h"
# import "UIButton+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface NNTUISlider : UISlider {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

- (void)changeValue:(float)value;

@end

NNT_EXTERN signal_t kSignalValueChanged;

@interface UISliderTitleValue : NNTUIView {
        
    //! title.
    NNTUILabel* title;
    
    //! slider.
    NNTUISlider* slider;
    
    //! value.
    NNTUILabel* value;
    
    float maximumValue, minimumValue, currentValue;
}

@property (nonatomic, retain) NNTUILabel* title;
@property (nonatomic, retain) NNTUISlider* slider;
@property (nonatomic, retain) NNTUILabel* value;

@property (nonatomic, assign) float maximumValue, minimumValue, currentValue;

+ (id)sliderWith:(NSString*)title max:(float)max min:(float)min cur:(float)cur;
- (id)initWith:(NSString*)title max:(float)max min:(float)min cur:(float)cur;

@end

@interface UISliderTitleValueReset : UISliderTitleValue {
    //! reset button.
    NNTUIButton* reset;
    
    //! default value.
    float defaultValue;
}

@property (nonatomic, retain) NNTUIButton* reset;
@property (nonatomic, assign) float defaultValue;

+ (id)sliderWith:(NSString*)title max:(float)max min:(float)min cur:(float)cur;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

template <typename sliderT = NNTUISlider>
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

typedef SliderControl<NNTUISlider> Slider;

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif