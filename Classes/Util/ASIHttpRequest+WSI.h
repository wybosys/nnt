
# ifndef __WSI_UTIL_ASIHTTPREQUEST_1FD323001D424AA49A0631F8E897AA7C_H_INCLUDED
# define __WSI_UTIL_ASIHTTPREQUEST_1FD323001D424AA49A0631F8E897AA7C_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(ASIHTTPRequest);

@interface WSIASIHttpRequest : WSIObject {
    
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