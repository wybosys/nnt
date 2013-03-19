
# ifndef __WSI_DTRACE_CONTROLLER_9D9B3030860A46D793A7052250C913E3_H_INCLUDED
# define __WSI_DTRACE_CONTROLLER_9D9B3030860A46D793A7052250C913E3_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSILua);

@interface DTraceController : WSIUIViewController {
    
    //! view for switch.
    UIView* viewForSwitch;
    
    //! lua object.
    WSILua* lua;

    //! show logo, default is YES.
    BOOL showLogo;
}

@property (nonatomic, assign) UIView* viewForSwitch;
@property (nonatomic, retain, readonly) WSILua* lua;
@property (nonatomic, assign) BOOL showLogo;

//! show.
- (void)show;

//! hide.
- (void)hide;

//! clear.
- (void)clear;

//! get shared.
+ (DTraceController*)shared;

@end

WSI_END_HEADER_OBJC

# endif