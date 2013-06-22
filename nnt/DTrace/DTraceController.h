
# ifndef __NNT_DTRACE_CONTROLLER_9D9B3030860A46D793A7052250C913E3_H_INCLUDED
# define __NNT_DTRACE_CONTROLLER_9D9B3030860A46D793A7052250C913E3_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTLua);

@interface DTraceController : NNTUIViewController {
    
    //! view for switch.
    UIView* viewForSwitch;
    
    //! lua object.
    NNTLua* lua;

    //! show logo, default is YES.
    BOOL showLogo;
}

@property (nonatomic, assign) UIView* viewForSwitch;
@property (nonatomic, retain, readonly) NNTLua* lua;
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

NNT_END_HEADER_OBJC

# endif