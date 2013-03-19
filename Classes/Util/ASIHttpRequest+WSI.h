
# ifndef __NNT_UTIL_ASIHTTPREQUEST_1FD323001D424AA49A0631F8E897AA7C_H_INCLUDED
# define __NNT_UTIL_ASIHTTPREQUEST_1FD323001D424AA49A0631F8E897AA7C_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(ASIHTTPRequest);

@interface NNTASIHttpRequest : NNTObject {
    
    //! delegate.
    id delegate;
    
    //! asi http request.
    ASIHTTPRequest* _httpreq;
    
    //! receiveData.
    NSData* receiveData;
}

@property (nonatomic, assign) id delegate;
@property (nonatomic, retain) NSData* receiveData;
@property (nonatomic, readonly) NSURL* url;

//! init.
- (id)initWithURL:(NSURL*)url;

//! start.
- (void)startAsynchronous;
- (void)startSynchronous;

//! cancel.
- (void)cancel;

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