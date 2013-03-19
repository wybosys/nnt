
# ifndef __NNT_NULLRPC_69A741CB97D1442BBC49D53BCB33D390_H_INCLUDED
# define __NNT_NULLRPC_69A741CB97D1442BBC49D53BCB33D390_H_INCLUDED

# include "IRpc.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface NullRpc : NNTObject<IRpc> {
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

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

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

# define NNTRPC_CALLROUND ::nnt::NullRpcCallRound __rpc_callround(self)

NNT_END_HEADER_CXX

# endif // objc-cxx

# endif // objc

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cross)
NNT_BEGIN_NS(rpc)

class NullImplementation
: public Interface,
public cxx::Object<>
{
public:
    
    NullImplementation();
    virtual ~NullImplementation();
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
