
# ifndef __NNT_UIKIT_GESTURE_73FC5FF59BC44842A00F9DB0EA535DB6_H_INCLUDED
# define __NNT_UIKIT_GESTURE_73FC5FF59BC44842A00F9DB0EA535DB6_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTUIGestureRecognizer : UIGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUISwipeGestureRecognizer : UISwipeGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUITapGestureRecognizer : UITapGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUIPinchGestureRecognizer : UIPinchGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUIRotationGestureRecognizer : UIRotationGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUIPanGestureRecognizer : UIPanGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

@interface NNTUILongPressGestureRecognizer : UILongPressGestureRecognizer {
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

NNT_EXTERN signal_t kSignalGestureBegin;
NNT_EXTERN signal_t kSignalGestureChanged;
NNT_EXTERN signal_t kSignalGestureEnd;
NNT_EXTERN signal_t kSignalGestureActive;
NNT_EXTERN signal_t kSignalGestureCancel;

NNTDECL_OBJCXX_WRAPPER(NNTUIGestureRecognizer);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(gesture)

NNT_BEGIN_NS(tpl)

class IGesture
: public RefObject
{
public:
    
    virtual void touches_begin(ns::Set const&, ui::Event const&)
    {
        PASS;
    }
    
    virtual void touches_end(ns::Set const&, ui::Event const&)
    {
        PASS;
    }
    
    virtual void touches_moved(ns::Set const&, ui::Event const&)
    {
        PASS;
    }
    
    virtual void touches_cancel(ns::Set const&, ui::Event const&)
    {
        PASS;
    }
    
    virtual void reset()
    {
        PASS;
    }
    
};

template <typename implT, typename gesT = NNT_OBJCXX_WRAPPER(NNTUIGestureRecognizer)>
class Gesture
: public Object<implT, gesT, IGesture>
{
public:
    
    Gesture()
    {
        this->_self = [[gesT alloc] init];
        
        if (NNT_OBJCXX_ISTYPE(this->_self))
        {
            NNT_OBJCXX_TYPE(this->_self)._cxxobj = this;
        }
    }
    
    ~Gesture()
    {
        if (NNT_OBJCXX_ISTYPE(this->_self))
        {
            NNT_OBJCXX_TYPE(this->_self)._cxxobj = NULL;
        }
    }
    
protected:
    
};

NNT_END_NS

class Swipe
: public tpl::Gesture<Swipe, NNTUISwipeGestureRecognizer>
{
public:
    
    Swipe()
    {
        PASS;
    }
    
    void set_direction(UISwipeGestureRecognizerDirection dir)
    {
        this->_self.direction = dir;
    }
    
    void set_requiredtouches(Fingers const& fg = finger::_1)
    {
        this->_self.numberOfTouchesRequired = fg;
    }
    
};

class Tap
: public tpl::Gesture<Tap, NNTUITapGestureRecognizer>
{
public:
    
    Tap()
    {
        PASS;
    }

    void set_requiredtaps(uint v)
    {
        this->_self.numberOfTapsRequired = v;
    }
    
    void set_requiredtouches(uint v)
    {
        this->_self.numberOfTouchesRequired = v;
    }
    
};

class Pinch
: public tpl::Gesture<Pinch, NNTUIPinchGestureRecognizer>
{
public:
    
    Pinch()
    {
        PASS;
    }
    
    void set_scale(real v)
    {
        this->_self.scale = v;
    }
    
    real velocity() const
    {
        return this->_self.velocity;
    }
    
};

class Pan
: public tpl::Gesture<Pan, NNTUIPanGestureRecognizer>
{
public:
    
    Pan()
    {
        PASS;
    }
    
    void set_minimum(Fingers const& fg)
    {
        this->_self.minimumNumberOfTouches = fg;
    }
    
    void set_maximum(Fingers const& fg)
    {
        this->_self.maximumNumberOfTouches = fg;
    }
    
};

class Rotation
: public tpl::Gesture<Rotation, NNTUIRotationGestureRecognizer>
{
public:
    
    Rotation()
    {
        PASS;
    }
    
    void set_rotation(cg::Angle const& v)
    {
        this->_self.rotation = v.rad();
    }
    
    cg::Angle rotation() const
    {
        return cg::Angle::Rad(this->_self.rotation);
    }
    
    real velocity() const
    {
        return this->_self.velocity;
    }
        
};

class LongPress
: public tpl::Gesture<LongPress, NNTUILongPressGestureRecognizer>
{
public:
    
    LongPress()
    {
        PASS;
    }
    
    void set_requiredtaps(uint v)
    {
        this->_self.numberOfTapsRequired = v;
    }
    
    void set_requiredtouches(uint v)
    {
        this->_self.numberOfTouchesRequired = v;
    }
    
    void set_duration(ns::TimeInterval ti)
    {
        this->_self.minimumPressDuration = ti;
    }
    
    void set_precision(real pr)
    {
        this->_self.allowableMovement = pr;
    }
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
