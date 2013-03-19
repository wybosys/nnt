
# ifndef __NNT_CORE_NSFILECONNECTION_97B6128B9F8041E1BD46EF6E1E4A2302_H_INCLUDED
# define __NNT_CORE_NSFILECONNECTION_97B6128B9F8041E1BD46EF6E1E4A2302_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface NSFileConnection : NNTObject {
    
    //! the file url.
    NSURL* url;
    
    //! if in thread.
    BOOL inThread;
    
    //! size of cache.
    usize cacheSize;
        
    @private
    BOOL _finished;
    BOOL _cancel;
}

@property (nonatomic, copy) NSURL* url;
@property (nonatomic, assign) BOOL inThread;
@property (nonatomic, assign) usize cacheSize;

- (id)initWithURL:(NSURL*)url start:(BOOL)start;
- (id)initWithURL:(NSURL*)url;

- (void)start;
- (void)startAsync;
- (void)cancel;

@end

NNT_EXTERN usize kFileConnectionDefaultCacheSize;

NNT_EXTERN signal_t kSignalFileConnectionOpened;
NNT_EXTERN signal_t kSignalFileConnectionReceiveData;
NNT_EXTERN signal_t kSignalFileConnectionDataChanged;
NNT_EXTERN signal_t kSignalFileConnectionFinish;
NNT_EXTERN signal_t kSignalFileConnectionError;

NNT_END_HEADER_OBJC

# endif

# endif