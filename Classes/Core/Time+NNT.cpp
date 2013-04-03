
# include "Core.h"
# include "Time+NNT.h"

# include <time.h>
# include <math.h>

# ifdef NNT_MACH
#   include <mach/mach_time.h>
# endif

NNT_BEGIN_CXX

# ifdef NNT_MACH

class _timebase_init
{
public:
    
    _timebase_init()
    {
        mach_timebase_info(&gs_timebase_info);
        nd = gs_timebase_info.numer / gs_timebase_info.denom;
        ndmic = nd * 1e-3;
        ndmil = ndmic * 1e-3;
    }
    
    mach_timebase_info_data_t gs_timebase_info;
    double nd, ndmic, ndmil;
};

static _timebase_init _gs_timeinfo_init;

ulonglong get_tick_count()
{
    return mach_absolute_time();
}

ulonglong nanosec_tick_count(ulonglong tck)
{
    return tck * _gs_timeinfo_init.nd;
}

ulonglong micsec_tick_count(ulonglong tck)
{
    return tck * _gs_timeinfo_init.ndmic;
}

double millisec_tick_count(ulonglong tck)
{
    return tck * _gs_timeinfo_init.ndmil;
}

# endif

NNT_BEGIN_NS(core)

Time::Time()
{
    memset(&_tm, 0, sizeof(_tm));
}

Time::~Time()
{
    
}

Time Time::Local()
{
    Time ret;
    ret.local_time();
    return ret;
}

void Time::set_format(const core::string &fmt)
{
    _fmt = fmt;
}

void Time::local_time()
{
    time_t tmt = time(NULL);
	set_timestamp(tmt);
}

void Time::set_timestamp(uinteger ts)
{
    time_t tmt = (time_t)ts;

# ifdef NNT_MSVC
	struct tm ttm;
	if (localtime_s(&ttm, &tmt) != 0)
		trace_msg("failed to get localtime.");
	_tm = ttm;
# else
	struct tm* ttm = localtime(&tmt);
	_tm = *ttm;
# endif
}

uinteger Time::timestamp() const
{
    return (uinteger)mktime((struct tm*)&_tm);
}

core::string Time::to_string() const
{
    char time_string[1024];
    strftime(time_string, 1024, _fmt.c_str(), &_tm);
    return time_string;
}

void Time::set_second(int val)
{
    _tm.tm_sec = val;
}

void Time::set_minute(int val)
{
    _tm.tm_min = val;
}

void Time::set_hour(int val)
{
    _tm.tm_hour = val;
}

void Time::set_dayofmonth(int val)
{
    _tm.tm_mday = val;
}

void Time::set_month(int val)
{
    _tm.tm_mon = val - 1;
}

void Time::set_year(int val)
{
    _tm.tm_year = val - 1900;
}

void Time::set_dayofweek(int val)
{
    _tm.tm_wday = val;
}

void Time::set_dayofyear(int val)
{
    _tm.tm_yday = val;
}

int Time::second() const
{
    return _tm.tm_sec;
}

int Time::minute() const
{
    return _tm.tm_min;
}

int Time::hour() const
{
    return _tm.tm_hour;
}

int Time::dayofmonth() const
{
    return _tm.tm_mday;
}

int Time::month() const
{
    return _tm.tm_mon + 1;
}

int Time::year() const
{
    return _tm.tm_year + 1900;
}

int Time::dayofweek() const
{
    return _tm.tm_wday;
}

int Time::dayofyear() const
{
    return _tm.tm_yday;
}

bool Time::operator < (Time const& r) const
{
    if (_tm.tm_year - r._tm.tm_year > 0) return false;
    else if (_tm.tm_year - r._tm.tm_year < 0) return true;

    if (_tm.tm_mon - r._tm.tm_mon > 0) return false;
    else if (_tm.tm_mon - r._tm.tm_mon < 0) return true;
    
    if (_tm.tm_mday - r._tm.tm_mday > 0) return false;
    else if (_tm.tm_mday - r._tm.tm_mday < 0) return true;
    
    if (_tm.tm_hour - r._tm.tm_hour > 0) return false;
    else if (_tm.tm_hour - r._tm.tm_hour < 0) return true;
    
    if (_tm.tm_min - r._tm.tm_min > 0) return false;
    else if (_tm.tm_min - r._tm.tm_min < 0) return true;
    
    if (_tm.tm_sec - r._tm.tm_sec > 0) return false;
    else if (_tm.tm_sec - r._tm.tm_sec < 0) return true;
    
    return false;
}

bool Time::operator <= (Time const& r) const
{
    return *this < r || *this == r;
}

bool Time::operator > (Time const& r) const
{
    if (_tm.tm_year - r._tm.tm_year > 0) return true;
    else if (_tm.tm_year - r._tm.tm_year < 0) return false;
    
    if (_tm.tm_mon - r._tm.tm_mon > 0) return true;
    else if (_tm.tm_mon - r._tm.tm_mon < 0) return false;
    
    if (_tm.tm_mday - r._tm.tm_mday > 0) return true;
    else if (_tm.tm_mday - r._tm.tm_mday < 0) return false;
    
    if (_tm.tm_hour - r._tm.tm_hour > 0) return true;
    else if (_tm.tm_hour - r._tm.tm_hour < 0) return false;
    
    if (_tm.tm_min - r._tm.tm_min > 0) return true;
    else if (_tm.tm_min - r._tm.tm_min < 0) return false;
    
    if (_tm.tm_sec - r._tm.tm_sec > 0) return true;
    else if (_tm.tm_sec - r._tm.tm_sec < 0) return false;
    
    return false;
}

bool Time::operator >= (Time const& r) const
{
    return *this > r || *this == r;
}

bool Time::operator == (Time const& r) const
{
    return _tm.tm_year == r._tm.tm_year &&
    _tm.tm_mon == r._tm.tm_mon &&
    _tm.tm_mday == r._tm.tm_mday &&
    _tm.tm_hour == r._tm.tm_hour &&
    _tm.tm_min == r._tm.tm_min &&
    _tm.tm_sec == r._tm.tm_sec;
}

bool Time::operator != (Time const& r) const
{
    return !(*this == r);
}

bool Time::today(const ::nnt::core::Time &r) const
{
    return _tm.tm_year == r._tm.tm_year &&
    _tm.tm_mon == r._tm.tm_mon &&
    _tm.tm_mday == r._tm.tm_mday; 
}

Time Time::offset_hour(int val) const
{
    Time ret = *this;
    val = ret._tm.tm_hour + val;
    if (val < 0)
    {
        ret._tm.tm_mday = (int)floor(val / 24.f);
        ret._tm.tm_hour = 24 + val % 24;
    }
    else if (val > 0)
    {
        ret._tm.tm_mday += (int)floor(val / 24.f);
        ret._tm.tm_hour = val % 24;
    }
    return ret;
}

Time& Time::operator = (const ::nnt::core::Time &r)
{
    _fmt = r._fmt;
    _tm = r._tm;
    return *this;
}

Time& Time::operator += (uinteger tm)
{
    uinteger ts = timestamp();
    ts += tm;
    set_timestamp(ts);
    return *this;
}

Time Time::operator + (uinteger tm) const
{
    Time ret = *this;
    return ret += tm;
}

NNT_END_NS

# ifdef NNT_MSVC

NNT_BEGIN_NS(msvc)

Timer::Timer()
: _hdl(NULL), _mseconds(0), _repeat(true)
{

}

Timer::~Timer()
{
	stop();
}

NNTDECL_SIGNALS_BEGIN(Timer, super)
NNT_SIGNAL(kSignalTimerFired)
NNTDECL_SIGNALS_END

void Timer::stop()
{
	if (_hdl == NULL)
		return;

	::DeleteTimerQueueTimer(NULL, _hdl, NULL);
	_hdl = NULL;
}

void Timer::set(real tm, bool rep)
{
	_mseconds = (UINT)(tm * 1000);
	_repeat = rep;
}

bool Timer::need_repeat() const
{
	return _repeat;
}

static void _cb_timer(PVOID param, BOOLEAN timerofwaitfired)
{
	Timer* tm = (Timer*)param;

	// event.
	tm->emit(kSignalTimerFired);
}

void Timer::start()
{
	stop();

	BOOL suc = ::CreateTimerQueueTimer(&_hdl, 
		NULL, 
		(WAITORTIMERCALLBACK)
		_cb_timer, 
		this, 
		_mseconds, 
		TRIEXP(_repeat, _mseconds, 0),
		//WT_EXECUTEDEFAULT
		WT_EXECUTEINTIMERTHREAD
		);
	if (suc == FALSE)
		trace_msg("Failed to create new timer.");
}

NNT_END_NS

# endif

NNT_END_CXX
