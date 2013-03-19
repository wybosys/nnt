
# ifndef __WSI_UIKIT_GESTURE_73FC5FF59BC44842A00F9DB0EA535DB6_H_INCLUDED
# define __WSI_UIKIT_GESTURE_73FC5FF59BC44842A00F9DB0EA535DB6_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WSIUISwipeGestureRecognizer : UISwipeGestureRecognizer {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

@interface WSIUITapGestureRecognizer : UITapGestureRecognizer {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

@interface WSIUIPinchGestureRecognizer : UIPinchGestureRecognizer {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

@interface WSIUIRotationGestureRecognizer : UIRotationGestureRecognizer {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

@interface WSIUIPanGestureRecognizer : UIPanGestureRecognizer {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

@interface WSIUILongPressGestureRecognizer : UILongPressGestureRecognizer {
    WSIOBJECT_DECL;
}

WSIOBJECT_PROP;

@end

WSI_EXTERN signal_t kSignalGestureActive;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(gesture)

WSI_BEGIN_NS(tpl)

template <typename implT, typename gesT>
class Gesture
: public Object<implT, gesT>
{
public:
    
    Gesture()
    {
        PASS;
    }
    
};

WSI_END_NS

class Swipe
: public tpl::Gesture<Swipe, WSIUISwipeGestureRecognizer>
{
public:
    
    Swipe()
    {
        PASS;
    }
    
    void set(UISwipeGestureRecognizerDirection dir)
    {
        this->_self.direction = dir;
    }
    
    void set(Fingers const& fg = finger::_1)
    {
        this->_self.numberOfTouchesRequired = fg;
    }
    
};

class Tap
: public tpl::Gesture<Tap, WSIUITapGestureRecognizer>
{
public:
    
    Tap()
    {
        PASS;
    }
    
};

class Pinch
: public tpl::Gesture<Pinch, WSIUIPinchGestureRecognizer>
{
public:
    
    Pinch()
    {
        PASS;
    }
    
};

class Pan
: public tpl::Gesture<Pan, WSIUIPanGestureRecognizer>
{
public:
    
    Pan()
    {
        PASS;
    }
    
};

class Rotation
: public tpl::Gesture<Rotation, WSIUIRotationGestureRecognizer>
{
public:
    
    Rotation()
    {
        PASS;
    }
    
};

class LongPress
: public tpl::Gesture<LongPress, WSIUILongPressGestureRecognizer>
{
public:
    
    LongPress()
    {
        PASS;
    }
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
