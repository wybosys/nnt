
# ifndef __WSI_CORE_NOTIFICATION_78DF36F4DA4A435D9E4EEC3B1EC01EA5_H_INCLUDED
# define __WSI_CORE_NOTIFICATION_78DF36F4DA4A435D9E4EEC3B1EC01EA5_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WSILocalNotification : UILocalNotification

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

WSI_BEGIN_NS(tpl)

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

WSI_END_NS

class LocalNotification
: public tpl::Notification<WSILocalNotification>
{
    
public:
    
    void execute()
    {
        [[UIApplication sharedApplication] scheduleLocalNotification:this->_self];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif