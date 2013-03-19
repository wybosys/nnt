
# ifndef __WSI_CORE_NSFILECONNECTION_97B6128B9F8041E1BD46EF6E1E4A2302_H_INCLUDED
# define __WSI_CORE_NSFILECONNECTION_97B6128B9F8041E1BD46EF6E1E4A2302_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface NSFileConnection : WSIObject {
    
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

WSI_EXTERN usize kFileConnectionDefaultCacheSize;

WSI_EXTERN signal_t kSignalFileConnectionOpened;
WSI_EXTERN signal_t kSignalFileConnectionReceiveData;
WSI_EXTERN signal_t kSignalFileConnectionDataChanged;
WSI_EXTERN signal_t kSignalFileConnectionFinish;
WSI_EXTERN signal_t kSignalFileConnectionError;

WSI_END_HEADER_OBJC

# endif

# endif