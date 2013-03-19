
# ifndef __NNT_UIDEVICE_E8838E6451704A509091C2EB03C4E619_H_INCLUDED
# define __NNT_UIDEVICE_E8838E6451704A509091C2EB03C4E619_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UIDevice (NNT)

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

NNTDECL_CATEGORY(UIDevice, NNT);

NNT_EXTERN bool need_manual_appear();
NNT_EXTERN bool support_blocks();
NNT_EXTERN bool support_multitasks();
NNT_EXTERN double device_version();

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# import <AudioToolbox/AudioToolbox.h>

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

NNT_BEGIN_NS(tpl)

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

NNT_END_NS

typedef tpl::Device<> Device;

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif