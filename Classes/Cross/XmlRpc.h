
# ifndef __WSI_CROSS_XMLRPC_4C819E035E884D5E97A63E2EF18D6D04_H_INCLUDED
# define __WSI_CROSS_XMLRPC_4C819E035E884D5E97A63E2EF18D6D04_H_INCLUDED

# include "NullRpc.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(XmlRpc);
WSIDECL_EXTERN_DELEGATE(XmlRpc);

@interface XmlRpc : NullRpc {
    
    //! delegate.
	id <XmlRpcDelegate> delegate;
	
    //! url.
	//NSString *url;
    
    //! service.
	//NSString *service;
	
	WSIDECL_PRIVATE(XmlRpc);
}

@property (nonatomic, retain) id <XmlRpcDelegate> delegate;
//@property (nonatomic, retain) NSString *url;
//@property (nonatomic, retain) NSString *service;

@end

@protocol XmlRpcDelegate <NSObject>

- (void)xmlrpcDidStartLoading:(XmlRpc*)rpc;
- (void)xmlrpcDidReceiveResult:(XmlRpc*)rpc result:(id)result;

@end

WSI_END_HEADER_OBJC

# endif

# endif