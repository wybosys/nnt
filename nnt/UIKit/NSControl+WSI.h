
# ifndef __WSI_NSCONTROL_EEB81C4DAD1B48969CAD6CA98248DD37_H_INCLUDED
# define __WSI_NSCONTROL_EEB81C4DAD1B48969CAD6CA98248DD37_H_INCLUDED

# ifdef WSI_OBJC

# import "NSView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSI_EXTERN signal_t kSignalAction;

@interface NSControl (WSI)

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_OBJC

@interface _nscontrol_eventmonitor : cxxnsobject
- (void)action:(NSEvent*)evt;
@end

WSI_END_HEADER_OBJC

# include "NSView+WSI.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)

class IControl
: public IView
{
    
};

template <typename implT, typename controlT,
typename interT = IControl,
typename evtmonitorT = _nscontrol_eventmonitor
>
class Control
: public View<implT, controlT, interT>
{    
    typedef View<implT, controlT, interT> super;
    
public:
    
    Control()
    {
        _monitor = [[evtmonitorT alloc] init];
        _monitor.target = this->_self;
        
        this->_updateself();
    }
    
    ~Control()
    {
        zero_release(_monitor);
    }
        
    inline void set_value(ns::String const& str)
    {
        [this->_self setStringValue:str];
    }
    
    inline ns::String string_value() const
    {
        return [this->_self stringValue];
    }
    
    inline void set_value(int d)
    {
        [this->_self setIntValue:d];
    }
    
    inline void set_value(float f)
    {
        [this->_self setFloatValue:f];
    }
    
    inline void set_value(double d)
    {
        [this->_self setDoubleValue:d];
    }
    
    inline void set_value(id obj)
    {
        [this->_self setObjectValue:obj];
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
protected:
    
    void _updateself()
    {        
        // set common.
        if ([this->_self isKindOfClass:[NSControl class]]) {
            [this->_self setIgnoresMultiClick:YES];
            [this->_self setTarget:_monitor];
            [this->_self setAction:@selector(action:)];
        }
    }
     
protected:
    
    evtmonitorT* _monitor;
    
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif // cxx
# endif // objc

# endif