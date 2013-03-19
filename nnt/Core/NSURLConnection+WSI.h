
# ifndef __WSI_CORE_NSURLCONNECTION_AB34ECD484E744FC8225151EC0CB9261_H_INCLUDED
# define __WSI_CORE_NSURLCONNECTION_AB34ECD484E744FC8225151EC0CB9261_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface NSURLConnection (WSI)

@end

WSIDECL_CATEGORY(NSURLConnection, WSI);

@interface WSINSURLConnection : WSIObject {
    
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

+ (WSINSURLConnection *)connectionWithRequest:(NSURLRequest *)request delegate:(id)delegate;
+ (WSINSURLConnection *)connectionWithRequest:(NSURLRequest *)request;

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

WSI_EXTERN signal_t kSignalURLConnectionSendRequest;
WSI_EXTERN signal_t kSignalURLConnectionReceiveResponse;
WSI_EXTERN signal_t kSignalURLConnectionReceiveData;
WSI_EXTERN signal_t kSignalURLConnectionDataChanged;
WSI_EXTERN signal_t kSignalURLConnectionFinish;
WSI_EXTERN signal_t kSignalURLConnectionError;
WSI_EXTERN signal_t kSignalURLConnectionExit;

WSI_EXTERN signal_t kSignalURLConnectionWillRedirect;
WSI_EXTERN signal_t kSignalURLConnectionRedirected;

WSI_END_HEADER_OBJC

# endif