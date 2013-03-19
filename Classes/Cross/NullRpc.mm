
# import "Core.h"
# import "NullRpc.h"
# import "App.h"
# import "Model.h"
# import "NullObjParser.h"

NNT_BEGIN_OBJC

@implementation NullRpc

@synthesize showProgress = _showProgress;
@synthesize verbose = _verbose;

- (id)init {
    self = [super init];
    
    _showProgress = YES;
    
    _verbose = NNTDEBUG_EXPRESS(YES) NNTRELEASE_EXPRESS(NO);
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (BOOL)is_connected {
	return YES;
}

- (void)disconnect {
    PASS;
}

- (NSObject*)call:(Model *)model withUrl:(NSURL*)url {
    // prepare parser.
    [model.objparser prepare:model];
    
    return nil;
}

- (void)begin_call {
    
    if (_showProgress)
        [self progress_begin];
    
}

- (void)end_call {
    
    if (_showProgress)
        [self progress_end];
    
}

- (void)progress_begin {
# ifdef NNT_TARGET_IOS
    
    [NNTApplication shared].networkActivityIndicatorVisible = YES;
    
# endif
}

- (void)progress_end {
# ifdef NNT_TARGET_IOS
    
    [NNTApplication shared].networkActivityIndicatorVisible = NO;
    
# endif
}

@end

@interface NullRpc (async)

@end

@implementation NullRpc (async)

- (void)connection:(NNTNSURLConnection *)connection didReceiveData:(NSData *)data {
    NSMutableData *tgt_data = [connection storeFind:@"::wsi::core::connection::data"];
    if (tgt_data == nil) {
        tgt_data = [[NSMutableData alloc] initWithData:data];
        [connection storeSet:@"::wsi::core::connection::data" obj:tgt_data];
        [tgt_data release];
    } else {
        [tgt_data appendData:data];
    }
    
    [connection emit:kSignalURLConnectionReceiveData result:tgt_data];
}

- (void)connectionDidFinishLoading:(NNTNSURLConnection *)connection {
    NSMutableData *tgt_data = [connection storeFind:@"::wsi::core::connection::data"];
    [connection emit:kSignalURLConnectionFinish result:tgt_data];
}

- (void)connection:(NNTNSURLConnection *)connection didFailWithError:(NSError *)error {
    [connection emit:kSignalURLConnectionError];
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    [connection emit:kSignalURLConnectionReceiveResponse result:response];
}

@end

NNT_END_OBJC