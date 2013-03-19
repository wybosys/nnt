
# ifndef __WSI_NULLRPC_69A741CB97D1442BBC49D53BCB33D390_H_INCLUDED
# define __WSI_NULLRPC_69A741CB97D1442BBC49D53BCB33D390_H_INCLUDED

# include "IRpc.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface NullRpc : WSIObject<IRpc> {
    BOOL _showProgress;
    BOOL _verbose;
}

@property (nonatomic, assign) BOOL showProgress, verbose;

//! begin and end call.
- (void)begin_call;
- (void)end_call;

//! show.
- (void)progress_begin;
- (void)progress_end;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

class NullRpcCallRound
{
    
    NullRpc *rpc;
    
public:
    
    NullRpcCallRound(NullRpc* __rpc)
    : rpc(__rpc)
    {
        [rpc begin_call];
    }
    
    ~NullRpcCallRound()
    {
        [rpc end_call];
    }    
    
};

# define WSIRPC_CALLROUND ::wsi::NullRpcCallRound __rpc_callround(self)

WSI_END_HEADER_CXX

# endif // objc-cxx

# endif // objc

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)
WSI_BEGIN_NS(rpc)

class NullImplementation
: public Interface,
public cxx::Object<>
{
public:
    
    NullImplementation();
    virtual ~NullImplementation();
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
