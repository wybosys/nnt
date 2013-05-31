
# ifndef __NNT_UIKIT_PROGRESS_F2AF700DB1034AEF88F417553C24AF01_H_INCLUDED
# define __NNT_UIKIT_PROGRESS_F2AF700DB1034AEF88F417553C24AF01_H_INCLUDED

# import "UIControl+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UIProgressControl : UIControl {
    UIProgressView* _progressView;
    
    float _max, _value;
}

@property (nonatomic) UIProgressViewStyle progressViewStyle;
@property (nonatomic) float progress;
@property (nonatomic) float max, value;

@property (nonatomic, retain) UIColor* progressTintColor     NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
@property (nonatomic, retain) UIColor* trackTintColor     NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
@property (nonatomic, retain) UIImage* progressImage NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
@property (nonatomic, retain) UIImage* trackImage NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

@end

_CXXCONTROL_DECL(UIProgressControl);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class ProgressControl
: public Control<ProgressControl, _CXXCONTROL(UIProgressControl)>
{
    typedef Control<ProgressControl, _CXXCONTROL(UIProgressControl)> super;
    
public:
    
    ProgressControl()
    {
        PASS;
    }
    
    void set_progress(float val)
    {
        this->_self.progress = val;
    }
    
    float progress() const
    {
        return this->_self.progress;
    }
    
    void set_max(float val)
    {
        this->_self.max = val;
    }
    
    float max() const
    {
        return this->_self.max;
    }
    
    void set_value(float val)
    {
        this->_self.value = val;
    }
    
    float value() const
    {
        return this->_self.value;
    }
    
    void set_progress(ui::Color const& colr)
    {
        this->_self.progressTintColor = colr;
    }
    
    ui::Color progress_color() const
    {
        return this->_self.progressTintColor;
    }
    
    void set_track(ui::Color const& colr)
    {
        this->_self.trackTintColor = colr;
    }
    
    ui::Color track_color() const
    {
        return this->_self.trackTintColor;
    }
    
    void set_progress(ui::Image const& img)
    {
        this->_self.progressImage = img;
    }
    
    ui::Image progress_image() const
    {
        return this->_self.progressImage;
    }
    
    void set_track(ui::Image const& img)
    {
        this->_self.trackImage = img;
    }
    
    ui::Image track_image() const
    {
        return this->_self.trackImage;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
