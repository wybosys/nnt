
# ifndef __WSI_CROSS_IRPC_AA6DAD2468CF48CB885B1D3C27711F92_H_INCLUDED
# define __WSI_CROSS_IRPC_AA6DAD2468CF48CB885B1D3C27711F92_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(Model);

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

WSI_END_HEADER_OBJC

# endif // objc

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)
WSI_BEGIN_NS(rpc)

class Interface
{    
    WSIDECL_INTERFACE(Interface);
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif