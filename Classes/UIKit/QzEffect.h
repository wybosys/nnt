
# ifndef __NNT_UIKIT_QZEFFECT_DC0ED3827ADC494D8FAB5B9C184F3819_H_INCLUDED
# define __NNT_UIKIT_QZEFFECT_DC0ED3827ADC494D8FAB5B9C184F3819_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@protocol QzEffect <NSObject>

- (void)active:(CALayer*)layer;

@end

@interface QzEffect : NNTObject <QzEffect> {
    
    //! effect's layer.
    CALayer* _layer;
    
    //! duration.
    NSTimeInterval _duration;
    
    //! if repeat. [sys]
    real _repeat;
    
    //! reverse. [sys]
    BOOL _reverse;
    
    //! recur. default is 0. -1 if non-stop.
    NSUInteger _recur;
    
    // pointer to other effect.
    QzEffect* _accord;
    QzEffect* _next;
    
}

@property (nonatomic, readonly, retain) CALayer* layer;
@property (nonatomic, assign) NSTimeInterval duration;
@property (nonatomic, retain) QzEffect *next, *accord;
@property (nonatomic, assign) real repeat;
@property (nonatomic, assign) BOOL reverse;
@property (nonatomic, assign) NSUInteger recur;

//! active effect for view.
- (void)activeInView:(UIView*)view;

//! prepare effect.
- (void)prepare;

//! effect begin.
- (void)begin;

//! process effect.
- (void)active;

//! effect end.
- (void)end;

@end

NNT_EXTERN NSTimeInterval kQzEffectDuration;

NNT_EXTERN signal_t kSignalEffectComplete;

NNTDECL_OBJCXX_WRAPPER(QzEffect);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(qz)

NNT_BEGIN_NS(tpl)

class IEffect
: public ns::cxx::IObject
{
public:
    
    virtual void active(CALayer*) = 0;
    virtual void prepare() = 0;
    virtual void begin() = 0;
    virtual void active() = 0;
    virtual void end() = 0;
    
};

template <typename objT = NNT_OBJCXX_WRAPPER(QzEffect) >
class Effect
: public ns::cxx::Object<objT, IEffect>
{
public:
    
    typedef struct {} effect_type;
    
    Effect()
    {
        PASS;
    }
    
    ~Effect()
    {
        PASS;
    }

    void set_duration(ns::TimeInterval const& tm)
    {
        this->_self.duration = tm;
    }
    
    ns::TimeInterval duration() const
    {
        return this->_self.duration;
    }
    
    void set_repeat(real cnt)
    {
        this->_self.repeat = cnt;
    }
    
    real repeat() const
    {
        return this->_self.repeat;
    }
    
    void set_reverse(bool val)
    {
        if (val)
        {
            if (this->_self.repeat == 0)
                this->_self.repeat = 1;
            this->_self.reverse = val;
        }
        else
        {
            this->_self.reverse = false;
        }
    }
    
    bool is_reverse() const
    {
        return this->_self.reverse;
    }
    
    void set_recur(uint cnt)
    {
        this->_self.recur = cnt;
    }
    
    uint recur() const
    {
        return this->_self.recur;
    }
    
    virtual void active(CALayer* layer)
    {
        PASS;
    }
    
    virtual void prepare()
    {
        PASS;
    }
    
    virtual void begin()
    {
        PASS;
    }
    
    virtual void active()
    {
        PASS;
    }
    
    virtual void end()
    {
        PASS;
    }
    
    template <typename effT>
    effT& next(effT const& eff)
    {
        ntl::const_pointer<effT> ptr(eff);
        this->_self.next = *ptr;
        return ntl::down_const(eff);
    }
    
    template <typename effT>
    effT& accord(effT const& eff)
    {
        ntl::const_pointer<effT> ptr(eff);
        this->_self.accord = *ptr;
        return ntl::down_const(eff);
    }
    
protected:
    
    CALayer* _layer() const
    {
        return this->_self.layer;
    }
    
    bool _need_stop() const
    {
        return this->_self.layer.retainCount == 1;
    }

};

NNT_END_NS

NNT_BEGIN_NS(effect)

typedef tpl::Effect<> Effect;

class Fadein
: public Effect
{
public:
    
    Fadein();
    
    virtual void prepare();
    virtual void active();
    
    real from, to;
};

class Fadeout
: public Fadein
{
public:
    
    Fadeout();
    
};

class Shadow
: public Effect
{
public:
    
    Shadow();
    
    virtual void prepare();
    virtual void active();
    
    cg::Shadow from, to;
    
};

class Scale
: public Effect
{
public:
    
    Scale();
    
    virtual void prepare();
    virtual void active();
    
    real from, to;
    
};

class Tremble
: public Effect
{
public:
    
    Tremble();
    ~Tremble();
    
    virtual void prepare();
    virtual void active();
    
    void start();
    void stop();
    
    real range;
    bool rand;
    
protected:
    
    real _now;
    CATransform3D _mat;
    
};

class Translation
: public Effect
{
public:
    
    Translation();
    
    virtual void prepare();
    virtual void active();
    
    cg::Point from, to;
};

class Slide
: public Translation
{
    typedef Translation super;
    
public:
    
    Slide();
    
    virtual void prepare();
    
    enum
    {
        LEFT, RIGHT, TOP, BOTTOM,
    } direction;
    
    bool in;
    
};

class SlideOut
: public Slide
{
public:
    
    SlideOut()
    {
        in = false;
    }
    
};

class Popout
: public Effect
{
public:
    
    Popout();
    
    virtual void prepare();
    virtual void active();
    
};

class Popin
: public Effect
{
public:
    
    Popin();
    
    virtual void prepare();
    virtual void active();
    
};

class OpenBook
: public Effect
{
public:
    
    OpenBook();
    
    virtual void prepare();
    virtual void active();
};

NNT_END_NS

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
