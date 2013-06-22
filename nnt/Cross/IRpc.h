
# ifndef __NNT_CROSS_IRPC_AA6DAD2468CF48CB885B1D3C27711F92_H_INCLUDED
# define __NNT_CROSS_IRPC_AA6DAD2468CF48CB885B1D3C27711F92_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(Model);

/*!
 *! @interface IRpc
 *! interface for Remote Process Call.
 */
@protocol IRpc <NSObject>

//! disconnect.
- (void)disconnect;

//! isconnect.
- (BOOL)is_connected;

//! @function call method (sync).
- (NSObject*)call:(Model*)model withUrl:(NSURL*)url;

@end

NNT_END_HEADER_OBJC

# endif // objc

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cross)
NNT_BEGIN_NS(rpc)

class Interface
{    
    NNTDECL_INTERFACE(Interface);
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif