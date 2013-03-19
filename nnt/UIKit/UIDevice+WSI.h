
# ifndef __WSI_UIDEVICE_E8838E6451704A509091C2EB03C4E619_H_INCLUDED
# define __WSI_UIDEVICE_E8838E6451704A509091C2EB03C4E619_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIDevice (WSI)

//! get orient transforam.
- (CGAffineTransform)orientTransform;
- (CGAffineTransform)transform;

//! if is iphone.
+ (BOOL)isIPhone;
+ (BOOL)isIPhoneSimulator;

//! if is ipad.
+ (BOOL)isIPad;
+ (BOOL)isIPadSimulator;

//! if is ipod.
+ (BOOL)isIPod;

@end

WSIDECL_CATEGORY(UIDevice, WSI);

WSI_EXTERN bool need_manual_appear();
WSI_EXTERN bool support_blocks();
WSI_EXTERN bool support_multitasks();
WSI_EXTERN double device_version();

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# import <AudioToolbox/AudioToolbox.h>

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

WSI_BEGIN_NS(tpl)

template <typename devT = UIDevice>
class Device
: public ns::Object<devT>
{
public:
    
    static void Shake()
    {
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
    }
    
};

WSI_END_NS

typedef tpl::Device<> Device;

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif