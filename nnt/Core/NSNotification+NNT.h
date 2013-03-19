
# ifndef __NNT_CORE_NOTIFICATION_78DF36F4DA4A435D9E4EEC3B1EC01EA5_H_INCLUDED
# define __NNT_CORE_NOTIFICATION_78DF36F4DA4A435D9E4EEC3B1EC01EA5_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTLocalNotification : UILocalNotification

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

NNT_BEGIN_NS(tpl)

template <typename notiT>
class Notification
: public ns::Object<notiT>
{
    typedef ns::Object<notiT> super;
    
public:
    
    Notification()
    {
        this->_self.timeZone = [NSTimeZone localTimeZone];
    }
    
    void set_date(ns::Date const& date)
    {
        this->_self.fireDate = date;
    }
    
    void set_timezone(ns::TimeZone const& tz)
    {
        this->_self.timeZone = tz;
    }
    
    void set_body(ns::String const& msg)
    {
        this->_self.alertBody = msg;
    }
    
    void set_action(ns::String const& act)
    {
        this->_self.alertAction = act;
    }
    
    void set_badge(uint val)
    {
        this->_self.applicationIconBadgeNumber = val;
    }
    
    void set_sound(ns::String const& name)
    {
        this->_self.soundName = name;
    }
    
    void set_userinfo(ns::Dictionary const& info)
    {
        this->_self.userInfo = info;
    }
    
};

NNT_END_NS

class LocalNotification
: public tpl::Notification<NNTLocalNotification>
{
    
public:
    
    void execute()
    {
        [[UIApplication sharedApplication] scheduleLocalNotification:this->_self];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif