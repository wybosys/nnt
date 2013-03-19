
# ifndef __NNT_CORE_NSTIMER_8AD6EDDCC6434BB3B8FB7BC248998B17_H_INCLUDED
# define __NNT_CORE_NSTIMER_8AD6EDDCC6434BB3B8FB7BC248998B17_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface NNTNSTimer : NNTObject {        
    @private
    NSTimer *_timer;
    int _suspend;
    NSTimeInterval _seconds;
    BOOL _repeats;
}

@property (nonatomic, assign) NSTimeInterval interval;
@property (nonatomic, assign) BOOL repeat;

//! init.
- (id)init;
- (id)initWithTimeInterval:(NSTimeInterval)seconds repeats:(BOOL)repeats;

//! start.
- (void)start;

//! pause.
- (void)pause;

//! resume.
- (void)resume;

//! stop.
- (void)stop;

@end

NNT_EXTERN signal_t kSignalTimerStart;
NNT_EXTERN signal_t kSignalTimerStop;
NNT_EXTERN signal_t kSignalTimerFired;
NNT_EXTERN signal_t kSignalTimerSuspended;
NNT_EXTERN signal_t kSignalTimerResume;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class TimeInterval
{
public:
    
    TimeInterval(NSTimeInterval val = 0)
    : _val(val)
    {
        PASS;
    }
    
    static TimeInterval Second(double val)
    {
        return TimeInterval(val);
    }
    
    static TimeInterval Millisecond(ulong val)
    {
        return TimeInterval(val * 0.001f);
    }
    
    operator NSTimeInterval () const
    {
        return _val;
    }
    
    real seconds() const
    {
        return _val;
    }
    
    real milliseconds() const
    {
        return _val * 1000;
    }
    
    real minutes() const
    {
        return _val / 60;
    }
    
protected:
    
    NSTimeInterval _val;
    
};

class Timer
: public ns::Object<NNTNSTimer>
{
    typedef ns::Object<NNTNSTimer> super;
    
public:
    
    Timer()
    {
        PASS;    
    }
    
    Timer(NSTimeInterval interval, bool repeat = true)
    : super(nil)
    {
        this->_self = [[NNTNSTimer alloc] initWithTimeInterval:interval repeats:repeat];
    }
    
    void set(NSTimeInterval interval, bool repeat = true)
    {
        stop();
        
        this->_self.interval = interval;
        this->_self.repeat = repeat;
        
        start();        
    }
    
    void start()
    {
        [this->_self start];
    }
    
    void pause()
    {
        [this->_self pause];
    }
    
    void stop()
    {
        [this->_self stop];
    }
    
    void resume()
    {
        [this->_self resume];
    }
        
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

# ifdef second
#  undef second
# endif

NNTAPI(ulonglong) get_tick_count();
NNTAPI(ulonglong) nanosec_tick_count(ulonglong);
NNTAPI(ulonglong) micsec_tick_count(ulonglong);
NNTAPI(double)    millisec_tick_count(ulonglong);

NNT_STATIC_CONST cxx::signal_t kSignalTimerFired = "::wsi::core::timer::fired";

# ifdef NNT_MSVC

NNT_BEGIN_NS(msvc)

NNTCLASS(Timer);

class Timer
	: public cxx::Object<>
{
	typedef cxx::Object<> super;

public:

	Timer();
	~Timer();

	//! stop.
	void stop();

	//! set value.
	void set(real tm, bool rep = true);

	//! start.
	void start();

	//! is repeat.
	bool need_repeat() const;

	NNTDECL_SIGNALS_SLOTS;

protected:

	HANDLE _hdl;
	UINT _mseconds;
	bool _repeat;

};

NNT_END_NS

# endif

NNT_BEGIN_NS(core)

NNTCLASS(Time);

class Time
{
public:
    
    Time();
    ~Time();
    
    static Time Local();
    
public:
    
    //! set as current local time.
    void local_time();
    
    //! set format.
    void set_format(core::string const& fmt);
    
    //! set timestamp.
    void set_timestamp(ulong);
    
    //! timestamp.
    ulong timestamp() const;
    
    //! to string.
    core::string to_string() const;
    
    /* seconds after the minute [0-60] */
    /* minutes after the hour [0-59] */
    /* hours since midnight [0-23] */
    /* day of the month [1-31] */
    /* months since January [0-11] */
    /* years since 0 */
    /* days since Sunday [0-6] */
    /* days since January 1 [0-365] */
    /* Daylight Savings Time flag */
    
    void set_second(int val);
    void set_minute(int val);
    void set_hour(int val);
    void set_dayofmonth(int val);
    void set_month(int val);
    void set_year(int val);
    void set_dayofweek(int val);
    void set_dayofyear(int val);
    
    int second() const;
    int minute() const;
    int hour() const;
    int dayofmonth() const;
    int month() const;
    int year() const;
    int dayofweek() const;
    int dayofyear() const;
    
    bool operator < (Time const& r) const;
    bool operator <= (Time const& r) const;
    bool operator > (Time const& r) const;
    bool operator >= (Time const& r) const;
    bool operator == (Time const& r) const;
    bool operator != (Time const& r) const;
    Time& operator = (Time const& r);
    Time& operator += (ulong);
    Time operator + (ulong) const;
    
    //! is in one day.
    bool today(Time const& r) const;
    
    //! offset hour.
    Time offset_hour(int val) const;
    
protected:
    
    core::string _fmt;

    struct tm _tm;
    
};

class Timeout
{
public:
    
    Timeout()
    : _millisecond(100), _infinate(false)
    {
        PASS;
    }
    
    Timeout(long ms, bool inf)
    : _millisecond(ms), _infinate(inf)
    {
        PASS;
    }
    
    long millisecond() const
    {
        return _millisecond;
    }
    
    static Timeout const& Default()
    {
        static Timeout __timeout;
        return __timeout;
    }
    
    static Timeout Milliseconds(long val)
    {
        Timeout ret;
        ret._millisecond = val;
        return ret;
    }
    
    static Timeout const& Infinate()
    {
        static Timeout __timeout(0, true);
        return __timeout;
    }
    
    bool infinate() const
    {
        return _infinate;
    }
    
    void set_millisecond(long v)
    {
        _millisecond = v;
        _infinate = false;
    }
    
    void set_infinate(bool v = true)
    {
        _infinate = v;
    }
    
protected:
    
    long _millisecond;
    bool _infinate;
    
};

# if defined(NNT_MSVC)
typedef msvc::Timer Timer;
# elif defined(NNT_OBJC)
typedef ns::Timer Timer;
# endif

NNT_END_NS

NNT_END_HEADER_CXX

# endif

# endif