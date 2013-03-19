
# import "Core.h"
# import "NSFileConnection.h"
# include <sys/stat.h>
# import "App.h"

NNT_BEGIN_OBJC

usize kFileConnectionDefaultCacheSize = 4096;

signal_t kSignalFileConnectionOpened = @"::wsi::filecnt::opened";
signal_t kSignalFileConnectionReceiveData = @"::wsi::filecnt::data::recv";
signal_t kSignalFileConnectionDataChanged = @"::wsi::filecnt::data::changed";
signal_t kSignalFileConnectionFinish = @"::wsi::filecnt::finish";
signal_t kSignalFileConnectionError = @"::wsi::filecnt::error";

@interface NSFileConnection (hidden)

- (void)_load_file;

@end

@implementation NSFileConnection

@synthesize url, inThread, cacheSize;

- (id)initWithURL:(NSURL*)_url start:(BOOL)start {
    self = [super init];
    if (self) {
        if (_url.isFileURL == NO) {
            zero_release(self);
        }        
        if (self) {            
            self.url = _url;
            self.cacheSize = kFileConnectionDefaultCacheSize;
            
            if (start)
                [self start];
        }
    }
    return self;
}

- (id)initWithURL:(NSURL*)_url {
    return [self initWithURL:_url start:NO];
}

- (void)dealloc {
    [url release];
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalFileConnectionOpened)
NNTEVENT_SIGNAL(kSignalFileConnectionError)
NNTEVENT_SIGNAL(kSignalFileConnectionFinish)
NNTEVENT_SIGNAL(kSignalFileConnectionReceiveData)
NNTEVENT_SIGNAL(kSignalFileConnectionDataChanged)
NNTEVENT_END

- (void)_load_file {
    [NNT ThreadUse];    

    char const* objcpath = [[self.url relativePath] UTF8String];    

    struct stat _sta;
    lstat(objcpath, &_sta);

    FILE* fd = fopen(objcpath, "r");    
    if (fd == NULL) {
        trace_fmt(@"failed to open file: %@.", [self.url relativePath]);
        
        if (!_cancel)
            [self emit:kSignalFileConnectionError];
        
        [NNT ThreadFree];
        return;
    } else {
        if (!_cancel)
            [self emit:kSignalFileConnectionOpened data:&_sta];
    }
    
    // set ui.
    [NNTApplication shared].networkActivityIndicatorVisible = YES;

    // prepare global buffer.
    NSMutableData* data = [[NSMutableData alloc] initWithCapacity:_sta.st_size];
    
    // run loop.
    usize sz_cache = self.cacheSize;
    void* buf = malloc(sz_cache);
    fseek(fd, 0, SEEK_SET);
    while (!_finished &&
           !_cancel) {
        
        // read comp.
        usize sta = fread(buf, 1, sz_cache, fd);
        if (sta) {
            
            NSData *da = [[NSData alloc] initWithBytesNoCopy:buf length:sta freeWhenDone:NO];
            
            if (!_cancel)
                [self emit:kSignalFileConnectionReceiveData result:da];
            
            // add comp data to global.
            [data appendData:da];
            
            if (!_cancel)
                [self emit:kSignalFileConnectionDataChanged result:data];
            
            safe_release(da);
        }
        
        _finished = feof(fd) != 0;
    }

    // signal.
    if (!_cancel)
        [self emit:kSignalFileConnectionFinish result:data];

    // free tmp buffer.
    safe_release(data);
    free(buf);
    
    // close file description.
    fclose(fd);

    // reset ui.
    [NNTApplication shared].networkActivityIndicatorVisible = NO;

    [NNT ThreadFree];
}

- (void)cancel {
    _cancel = YES;
}

- (void)start {
    [self retain];
    
    _finished = NO;
    _cancel = NO;
        
    if (inThread) {
        [self _load_file];
    } else {
        [self performSelectorInBackground:@selector(_load_file) withObject:nil];
    }
    
    [self release];
}

- (void)startAsync {
    [self retain];
    
    _finished = NO;
    _cancel = NO;
    
    [self performSelectorInBackground:@selector(_load_file) withObject:nil];
    
    [self release];
}

@end

NNT_END_OBJC