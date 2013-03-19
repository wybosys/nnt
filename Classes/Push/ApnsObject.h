
# ifndef __NNT_PUSH_APNS_F76DC4C4BE714458ACF9A4C266A5D0C4_H_INCLUDED
# define __NNT_PUSH_APNS_F76DC4C4BE714458ACF9A4C266A5D0C4_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface APNSObject : NNTObject {
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

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(push)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
