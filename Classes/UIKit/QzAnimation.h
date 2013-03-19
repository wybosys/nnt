
# ifndef __NNT_QZ_ANIMATION_660F7DC100C74083867B9191124CEF61_H_INCLUDED
# define __NNT_QZ_ANIMATION_660F7DC100C74083867B9191124CEF61_H_INCLUDED

# import "../Graphic/NGPath.h"
# import "../Core/NSValue+NNT.h"

# ifdef NNT_CXX

NNT_BEGIN_HEADER_OBJC

@interface __cxxobject_qzanimation : NNTObject

@end

NNT_EXTERN signal_t kSignalAnimationStart;
NNT_EXTERN signal_t kSignalAnimationStop;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIObject+NNT.h"
# include "QzMediaTiming.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(qz)

class Transcation
{
protected:
    
    class ValuePair
    {
    public:
        
        ns::String key;
        id obj;
        
        ValuePair& operator = (id);

        operator id ()
        {
            return obj;
        }
        
    };
    
public:
    
    Transcation();
    ~Transcation();
    
    static void Begin();
    static void Commit();
    
    static void Flush();
    
    static void Lock();
    static void Unlock();
    
    static ValuePair At(ns::String const&);

};

template <typename aniT = CAAnimation>
class Animation
: public ::nnt::ns::Object<__cxxobject_qzanimation>,
public MediaTiming<Animation<aniT> >
{    
    typedef ::nnt::ns::Object<__cxxobject_qzanimation> super;
    
protected:
    
    Animation(id obj)
    : super(obj)
    {
        PASS;
    }
    
public:
    
    typedef struct {} animation_type;
    
    Animation()
    : super(nil)
    {
        this->_self = [[aniT animation] retain];
        this->_self.delegate = super::_self;
    }
    
    ~Animation()
    {
        safe_release(_self);
    }
    
    void set_timefunc(CAMediaTimingFunction* func)
    {
        [this->_self setTimingFunction:func];
    }
    
    void set_timefunc(ns::String const& str = kCAMediaTimingFunctionEaseIn)
    {
        [this->_self setTimingFunction:[CAMediaTimingFunction
                                        functionWithName:str]];
    }
    
    void play(CALayer* layer, ns::String const& name = ns::null_string)
    {
        [layer addAnimation:this->_self forKey:name];
    }
    
    void play(UIView* view, ns::String const& name = ns::null_string)
    {
        [view.layer addAnimation:this->_self forKey:name];
    }
    
    void play(UIViewController* ctlr, ns::String const& name = ns::null_string)
    {
        this->play(ctlr.view, name);
    }
    
    operator aniT* () const
    {
        return (aniT*)this->_self;
    }
    
    void set_removable(bool val)
    {
        this->_self.removedOnCompletion = val;
    }    
    
protected:
    
    aniT* _self;
    
};

template <typename aniT = CAPropertyAnimation>
class PropertyAnimation
: public Animation<aniT>
{
    typedef Animation<aniT> super;
    
protected:
    
    PropertyAnimation()
    {
        PASS;
    }
    
public:
    
    PropertyAnimation(ns::String const& keypath)
    : super(nil)
    {
        this->_self = [[aniT animationWithKeyPath:keypath] retain];
        this->_self.delegate = super::_self;
    }
    
    void set_keypath(ns::String const& keypath)
    {
        this->_self.keyPath = keypath;
    }
    
    ns::String keypath() const
    {
        return this->_self.keyPath;
    }
    
    void set_additive(bool val)
    {
        this->_self.additive = val;
    }
    
    bool additive() const
    {
        return this->_self.additive;
    }
    
    void set_cumulative(bool val)
    {
        this->_self.cumulative = val;
    }
    
    bool cumulative() const
    {
        return this->_self.cumulative;
    }
    
    void set_valuefunc(CAValueFunction* func)
    {
        this->_self.valueFunction = func;
    }
    
    CAValueFunction* valuefunc() const
    {
        return this->_self.valueFunction;
    }

};

template <typename aniT = CABasicAnimation>
class BasicAnimation
: public PropertyAnimation<aniT>
{
    
    typedef PropertyAnimation<aniT> super;
    
public:
    
    BasicAnimation()
    {
        PASS;
    }
    
    BasicAnimation(ns::String const& keypath)
    : super(keypath)
    {
        PASS;
    }
    
    void set_from(id val)
    {
        this->_self.fromValue = val;
    }
    
    void set_to(id val)
    {
        this->_self.toValue = val;
    }
    
    void set_by(id val)
    {
        this->_self.byValue = val;
    }
    
};

template <typename aniT = CAKeyframeAnimation>
class KeyAnimation
: public PropertyAnimation<aniT>
{
    typedef PropertyAnimation<aniT> super;
    
public:
    
    KeyAnimation()
    {
        PASS;
    }
    
    KeyAnimation(ns::String const& keypath)
    : super(keypath)
    {
        PASS;
    }
    
    void set_values(ns::Array const& arr)
    {
        this->_self.values = arr;
    }
    
    ns::Array values() const
    {
        return this->_self.values;
    }
    
    void set_path(cg::Path const& ph)
    {
        this->_self.path = ph;
    }
    
    cg::Path path() const
    {
        return this->_self.path;
    }
    
    void set_keytimes(ns::Array const& arr)
    {
        this->_self.keyTimes = arr;
    }
    
    ns::Array keytimes() const
    {
        return this->_self.keyTimes;
    }
    
    void set_timingfuncs(ns::Array const& arr)
    {
        this->_self.timingFunctions = arr;
    }
    
    ns::Array timingfuncs() const
    {
        return this->_self.timingFunctions;
    }
    
    void set_calculation(ns::String const& mode)
    {
        this->_self.calculationMode = mode;
    }
    
    ns::String calculation() const
    {
        return this->_self.calculationMode;
    }
    
    void set_tension(ns::Array const& arr)
    {
        this->_self.tensionValues = arr;
    }
    
    ns::Array tension() const
    {
        return this->_self.tensionValues;
    }
    
    void set_continuity(ns::Array const& arr)
    {
        this->_self.continuityValues = arr;
    }
    
    ns::Array continuity() const
    {
        return this->_self.continuityValues;
    }
    
    void set_bias(ns::Array const& arr)
    {
        this->_self.biasValues = arr;
    }
    
    ns::Array bias() const
    {
        return this->_self.biasValues;
    }
    
    void set_rotation(ns::String const& mode)
    {
        this->_self.rotationMode = mode;
    }
    
    ns::String rotation() const
    {
        return this->_self.rotationMode;
    }

};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif

# endif