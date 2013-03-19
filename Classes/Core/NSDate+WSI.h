
# ifndef __NNT_CORE_NSDATE_F24B459AC86E4277B114FC0EB6598B84_H_INCLUDED
# define __NNT_CORE_NSDATE_F24B459AC86E4277B114FC0EB6598B84_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSDate (NNT)

- (id)initWithYear:(NSUInteger)year
             Month:(NSUInteger)month
               Day:(NSUInteger)day
              Hour:(NSUInteger)hour
            Minute:(NSUInteger)minute
            Second:(NSUInteger)second;

@end

@interface NSDatePeriod : NNTObject {
    NSDate *_begin, *_end;
}

@property (nonatomic, retain) NSDate *begin, *end;

- (BOOL)isDuring;

@end

NNT_EXTERN NSString *kTimeZoneBeijing, *kTimeZoneShanghai, *kTimeZoneChongqing;

NNTDECL_CATEGORY(NSDate, NNT);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "Time+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class TimeZone
: public ns::Object<NSTimeZone>
{
    typedef ns::Object<NSTimeZone> super;
    
public:
    
    TimeZone()
    {
        PASS;
    }
    
    TimeZone(ns::String const& name)
    : super(nil)
    {
        this->_self = [[NSTimeZone alloc] initWithName:name];
    }
        
    TimeZone(TimeZone const& r)
    : super(r._self)
    {
        PASS;
    }
    
    TimeZone(NSTimeZone* r)
    : super(r)
    {
        PASS;
    }
    
    static TimeZone Default()
    {
        return [NSTimeZone defaultTimeZone];
    }
    
    static TimeZone Local()
    {
        return [NSTimeZone localTimeZone];
    }
    
    static TimeZone System()
    {
        return [NSTimeZone systemTimeZone];
    }
    
    static ns::Array SupportNames()
    {
        return [NSTimeZone knownTimeZoneNames];
    }
    
    static TimeZone const& ShangHai()
    {
        static TimeZone __gs_timezone(kTimeZoneShanghai);
        return __gs_timezone;
    }
    
};

class Date
: public ns::Object<NSDate>
{
    typedef ns::Object<NSDate> super;
    
public:
    
    Date()
    {
        PASS;
    }
    
    Date(Date const& r)
    : super(r._self)
    {
        PASS;
    }
    
    Date(NSDate* r)
    : super(r)
    {
        PASS;
    }
    
    Date(core::Time const& tm)
    : super(nil)
    {
        this->_self = [[NSDate alloc] initWithYear:tm.year()
                                             Month:tm.month()
                                               Day:tm.dayofmonth() 
                                              Hour:tm.hour()
                                            Minute:tm.minute()
                                            Second:tm.second()];
    }
    
    static Date Current(int offset_seonds = 0)
    {
        return [NSDate dateWithTimeIntervalSinceNow:offset_seonds];
    }
    
    static Date Future()
    {
        return [NSDate distantFuture];
    }
    
    static Date Past()
    {
        return [NSDate distantPast];
    }
    
    /*
    Date& operator += (NSTimeInterval seconds)
     {
     NSDate* da = [this->_self addTimeInterval:seconds];
     this->_set(da);
        return *this;
     }
     */
    
    Date operator + (NSTimeInterval seconds) const
    {
        return [this->_self dateByAddingTimeInterval:seconds];
    }
    
    Date& operator += (NSTimeInterval seconds)
    {
        NSDate* da = [this->_self dateByAddingTimeInterval:seconds];
        this->_set(da);
        return *this;
    }
    
    Date operator - (NSTimeInterval seconds) const
    {
        return [this->_self dateByAddingTimeInterval:-seconds];
    }
    
    Date& operator -= (NSTimeInterval seconds)
    {
        NSDate* da = [this->_self dateByAddingTimeInterval:-seconds];
        this->_set(da);
        return *this;
    }
    
    Date& operator = (NSDate* da)
    {
        this->_set(da);
        return *this;
    }
    
    bool operator == (Date const& r) const
    {
        return [this->_self isEqualToDate:r];
    }
    
    bool operator != (Date const& r) const
    {
        return [this->_self isEqualToDate:r] == NO;
    }
    
    bool operator < (Date const& r) const
    {
        NSComparisonResult cop = [this->_self compare:r];
        return cop == NSOrderedDescending;
    }
    
    bool operator <= (Date const& r) const
    {
        NSComparisonResult cop = [this->_self compare:r];
        return
        cop == NSOrderedDescending ||
        cop == NSOrderedSame;
    }
    
    bool operator > (Date const& r) const
    {
        NSComparisonResult cop = [this->_self compare:r];
        return cop == NSOrderedAscending;
    }
    
    bool operator >= (Date const& r) const
    {
        NSComparisonResult cop = [this->_self compare:r];
        return
        cop == NSOrderedAscending ||
        cop == NSOrderedSame;
    }
    
};
    
class DatePeriod
: public ns::Object<NSDatePeriod>
{
    typedef ns::Object<NSDatePeriod> super;
    
public:
    
    DatePeriod()
    {
        PASS;
    }
    
    DatePeriod(Date const& begin, Date const& end)
    {
        this->_self.begin = begin;
        this->_self.end = end;
    }
    
    bool is_during() const
    {
        return [this->_self isDuring];
    }
    
    Date begin() const
    {
        return this->_self.begin;
    }
    
    Date end() const
    {
        return this->_self.end;
    }
    
};
    
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif