
# import "Core.h"
# import "ASIHTTPRequest.h"
# import "ASIHTTPRequestDelegate.h"
# import "ASIHttpRequest+WSI.h"

WSI_BEGIN_OBJC

@interface WSIASIHttpRequest ()

- (void)_exit;

@end

@implementation WSIASIHttpRequest

@dynamic delegate;
@synthesize receiveData;
@dynamic url;

- (id)initWithURL:(NSURL *)url {
    self = [super init];
    
    _httpreq = [[ASIHTTPRequest alloc] initWithURL:url];
    _httpreq.delegate = self;
    
    return self;
}

- (void)dealloc {
    [_httpreq release];
    [receiveData release];
    [super dealloc];
}

- (NSURL*)url {
    return _httpreq.url;
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalURLConnectionSendRequest)
WSIEVENT_SIGNAL(kSignalURLConnectionReceiveResponse)
WSIEVENT_SIGNAL(kSignalURLConnectionReceiveData)
WSIEVENT_SIGNAL(kSignalURLConnectionDataChanged)
WSIEVENT_SIGNAL(kSignalURLConnectionFinish)
WSIEVENT_SIGNAL(kSignalURLConnectionError)
WSIEVENT_SIGNAL(kSignalURLConnectionExit)
WSIEVENT_SIGNAL(kSignalURLConnectionWillRedirect)
WSIEVENT_SIGNAL(kSignalURLConnectionRedirected)
WSIEVENT_END

- (void)_exit { 
    [self emit:kSignalURLConnectionExit];
    
    [self release];
}

- (void)startAsynchronous {
    [self retain];
    
    [_httpreq startAsynchronous];
}

- (void)startSynchronous {
    [self retain];
    
    [_httpreq startSynchronous];
}

- (void)cancel {
    [_httpreq clearDelegatesAndCancel];
}

# pragma mark delegate.

- (void)requestStarted:(ASIHTTPRequest *)request {
    [self emit:kSignalURLConnectionSendRequest result:request];
}

- (void)request:(ASIHTTPRequest *)request didReceiveResponseHeaders:(NSDictionary *)responseHeaders {
    [self emit:kSignalURLConnectionReceiveResponse result:responseHeaders];
    
    NSMutableData* data = [[NSMutableData alloc] initWithCapacity:9126];
    self.receiveData = data;
    [data release];
}

- (void)request:(ASIHTTPRequest *)request willRedirectToURL:(NSURL *)newURL {
    [self emit:kSignalURLConnectionWillRedirect result:newURL];
}

- (void)requestFinished:(ASIHTTPRequest *)request {
    [self emit:kSignalURLConnectionFinish result:receiveData];
    
    [self _exit];
}

- (void)requestFailed:(ASIHTTPRequest *)request {
    [self emit:kSignalURLConnectionError];
    
    [self _exit];
}

- (void)requestRedirected:(ASIHTTPRequest *)request {
    [self emit:kSignalURLConnectionRedirected];
}

- (void)request:(ASIHTTPRequest *)request didReceiveData:(NSData *)__data {
    [self emit:kSignalURLConnectionReceiveData result:__data];
    
    NSMutableData* data = (NSMutableData*)self.receiveData;
    [data appendData:__data];
    
    [self emit:kSignalURLConnectionDataChanged result:data];}

@end

WSI_END_OBJC