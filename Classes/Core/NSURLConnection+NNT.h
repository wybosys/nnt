
# ifndef __NNT_CORE_NSURLCONNECTION_AB34ECD484E744FC8225151EC0CB9261_H_INCLUDED
# define __NNT_CORE_NSURLCONNECTION_AB34ECD484E744FC8225151EC0CB9261_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSURLConnection (NNT)

@end

NNTDECL_CATEGORY(NSURLConnection, NNT);

@interface NNTNSURLConnection : NNTObject {
    
    //! connection.
    NSURLConnection* _connection;
    
    //! request.
    NSURLRequest *_urlRequest;
    
    //! in thread, default is NO.
    BOOL _inThread;
    
    @private
    NSMutableData* _data;
    CFRunLoopRef _loop;
    BOOL _run;
}

@property (nonatomic, retain) NSURLConnection* connection;
@property (nonatomic, readonly, retain) NSURLRequest* urlRequest;
@property (nonatomic, assign) BOOL inThread;

+ (NNTNSURLConnection *)connectionWithRequest:(NSURLRequest *)request delegate:(id)delegate;
+ (NNTNSURLConnection *)connectionWithRequest:(NSURLRequest *)request;

- (id)initWithURLRequest:(NSURLRequest*)request delegate:(id)delegate;
- (id)initWithURLRequest:(NSURLRequest*)request;

- (id)initWithURLRequest:(NSURLRequest*)request delegate:(id)delegate start:(BOOL)start;
- (id)initWithURLRequest:(NSURLRequest*)request start:(BOOL)start;

//! start.
- (void)start;
- (void)startAsync;

//! cancel.
- (void)cancel;

//! sync.
+ (NSData *)sendSynchronousRequest:(NSURLRequest *)request returningResponse:(NSURLResponse **)response error:(NSError **)error;

@end

NNT_EXTERN signal_t kSignalURLConnectionSendRequest;
NNT_EXTERN signal_t kSignalURLConnectionReceiveResponse;
NNT_EXTERN signal_t kSignalURLConnectionReceiveData;
NNT_EXTERN signal_t kSignalURLConnectionDataChanged;
NNT_EXTERN signal_t kSignalURLConnectionFinish;
NNT_EXTERN signal_t kSignalURLConnectionError;
NNT_EXTERN signal_t kSignalURLConnectionExit;

NNT_EXTERN signal_t kSignalURLConnectionWillRedirect;
NNT_EXTERN signal_t kSignalURLConnectionRedirected;

NNT_END_HEADER_OBJC

# endif