
# ifndef __WSI_CROSS_JSONRPC_60E01BC19C0A40B5AD4DFF02C92BCE51_H_INCLUDED
# define __WSI_CROSS_JSONRPC_60E01BC19C0A40B5AD4DFF02C92BCE51_H_INCLUDED

# include "NullRpc.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(JsonRpc);

@protocol JsonRpcDelegate <NSObject>

- (void)jsonRpcDidStartLoading:(JsonRpc*)client;
- (void)jsonRpcExec:(JsonRpc*)client didReceiveResult:(id)result;
- (void)jsonRpcExec:(JsonRpc*)client didFailWithErrorCode:(NSNumber*)code message:(NSString*)message;
- (void)jsonRpcExec:(JsonRpc*)client didFailWithErrorCode:(NSNumber*)code message:(NSString*)message data:(NSData*) responseData;

@end

//! @class JsonRpc Client
@interface JsonRpc : NullRpc {
	
    //! url.
	NSString *url;
    
    //! service.
	NSString *service;
    
    //! delegate.
	id <JsonRpcDelegate> delegate;
	
	WSIDECL_PRIVATE(JsonRpc);
}

@property (nonatomic, retain) NSString *url;
@property (nonatomic, retain) NSString *service;
@property (nonatomic, assign) id <JsonRpcDelegate> delegate;

@end

WSI_END_HEADER_OBJC

# endif

# endif