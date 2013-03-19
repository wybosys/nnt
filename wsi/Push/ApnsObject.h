
# ifndef __WSI_PUSH_APNS_F76DC4C4BE714458ACF9A4C266A5D0C4_H_INCLUDED
# define __WSI_PUSH_APNS_F76DC4C4BE714458ACF9A4C266A5D0C4_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface APNSObject : WSIObject {
    UIRemoteNotificationType _notiType;
}

@property (nonatomic, assign) UIRemoteNotificationType notificationType;

//! register apple notification system object.
- (void)registerToSystem;

//! unregister.
- (void)unregisterFromSystem;

//! is registered.
+ (BOOL)isRegistered;

//! get device token.
+ (NSData*)deviceToken;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(push)

class Apns
: public ns::Object<APNSObject>
{
public:
    
    Apns()
    {
        PASS;
    }
    
    void set(uint nt)
    {
        this->_self.notificationType = (UIRemoteNotificationType)nt;
    }
    
    UIRemoteNotificationType notifactionType() const
    {
        return this->_self.notificationType;
    }
    
    void register_to()
    {
        [this->_self registerToSystem];
    }
    
    void unregister()
    {
        [this->_self unregisterFromSystem];
    }
    
    static bool is_registered()
    {
        return [APNSObject isRegistered];
    }
    
    static ns::Data device_token()
    {
        return [APNSObject deviceToken];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
